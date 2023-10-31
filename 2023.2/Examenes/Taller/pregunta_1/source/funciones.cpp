#include<iostream>
#include<iomanip>
#include<fstream>
using namespace std;
#include"../header/funciones.h"
#define MAX_LINEA 100
#define MAX_NOMBRE 40
// Pedimos la fecha
void pedirFecha(int& fecha){
    // Variables
    // int dd,mm,aa;
    // char c;
    // cout<<setw(50)<<right<<"Reporte de Ventas y Ocupacion de Salas"<<left<<endl;
    // cout<<"Ingrese la fecha a analizar en el formato dia/mes/anio: ";
    // cin>>dd>>c>>mm>>c>>aa;
    // fecha=convertirFecha(dd,mm,aa);
    fecha=20190511;
}
int convertirFecha(int dd,int mm,int aa){
    // Variables
    int fecha;
    fecha=aa*10000+mm*100+dd;
    //2021 09 09
    return fecha;
}
// Ahora emitimos el reporte
void emitirReporte(const char* nomFunciones,const char* nomPeliculas,const char* nomReport,
                    const char* nomSalas,const char* nomVentas,int fecha){
    // Enlazamos los archivos
    ifstream funciones(nomFunciones,ios::in);
    if(not funciones.is_open()){
        cout<<"Error: Se produjo un error en abrir en el archivo "<<nomFunciones<<endl;
        exit(1);
    }
    ifstream peliculas(nomPeliculas,ios::in);
    if(not peliculas.is_open()){
        cout<<"Error: Se produjo un error en abrir en el archivo "<<nomPeliculas<<endl;
        exit(1);
    }
    ifstream salas(nomSalas,ios::in);
    if(not salas.is_open()){
        cout<<"Error: Se produjo un error en abrir en el archivo "<<nomSalas<<endl;
        exit(1);
    }
    ifstream ventas(nomVentas,ios::in);
    if(not ventas.is_open()){
        cout<<"Error: Se produjo un error en abrir en el archivo "<<nomVentas<<endl;
        exit(1);
    }
    ofstream report(nomReport,ios::out);
    if(not report.is_open()){
        cout<<"Error: Se produjo un error en abrir en el archivo "<<nomReport<<endl;
        exit(1);
    }
    // Encabezado
    encabezado(report,fecha);
    linea(report,MAX_LINEA,'=');
    //Presicion
    report.precision(2);
    report<<fixed;
    // Variables
    int codigoPeli,totalButacasDis=0,totalButacasVen=0,totalButacasOcu=0,contPeliculas=0;
    double totalRecaudado=0;
    //Lectura e impresion de los datos
    while(true){
        // Leemos el archivo peliculas, verificamos si nuestra fecha esta valida dentro
        // de las fechas de la pelicula
        LecturaVerificacionEImpresion(report,peliculas,fecha,codigoPeli);
        if(peliculas.eof())break;
        // Imprimimos el sub-encabezado
        sub_encabezado(report);
        // Lectura e impresion de ventas 
        lecturaEImpresionSub_encabezado(report,funciones,salas,ventas,codigoPeli,totalRecaudado,
                                                totalButacasDis,totalButacasVen,totalButacasOcu,fecha);
        contPeliculas++;
    }
    // Ahora imprimimos las estadisticas
    linea(report,MAX_LINEA,'=');
    estadisticas(totalRecaudado,totalButacasDis,totalButacasVen,totalButacasOcu,report,contPeliculas);
}
void encabezado(ofstream& report,int fecha){
    int dd,mm,aa;
    aa=fecha/10000;
    fecha%=10000;
    mm=fecha/100;
    fecha%=100;
    dd=fecha;
    report<<setw(70)<<right<<"REPORTE DE VENTAS Y OCUPACION DE SALAS"<<left<<endl;
    report<<setw(50)<<right<<"Fecha: "<<setfill('0')<<setw(2)<<dd<<'/'<<setw(2)<<
        mm<<'/'<<setw(4)<<aa<<setfill(' ')<<left<<endl;
}
void linea(ofstream& report,int num,char sgino){
    for(int i=0;i<num;i++){
        report<<sgino;
    }
    report<<endl;
}
void LecturaVerificacionEImpresion(ofstream& report,ifstream& peliculas,int fecha,int& codigoPeli){
     // Leemos el archivo peliculas, verificamos si nuestra fecha esta valida dentro
     // de las fechas de la pelicula
    int fechaI,fechaF,dd,mm,aa,ddf,mmf,aaf;
    char c;
    while(true){
        peliculas>>codigoPeli;
        if(peliculas.eof())break;
        peliculas>>dd>>c>>mm>>c>>aa>>ddf>>c>>mmf>>c>>aaf;
        fechaI=convertirFecha(dd,mm,aa);
        fechaF=convertirFecha(ddf,mmf,aaf);
        if(fecha>=fechaI && fecha<=fechaF){
            report<<"Pelicula: "<<codigoPeli<<" - ";
            lecturaDelNombre(report,peliculas);
            linea(report,MAX_LINEA,'-');
            break;
        }
        while(peliculas.get()!='\n');
    }
}
void lecturaDelNombre(ofstream& report,ifstream& peliculas){
    // Variables
    char c;
    int contBlancos=0;
    while (true){
        c=peliculas.get();
        if(c=='\n')break;
        contBlancos++;
        if(c=='/')report<<" ";
        else{
            c-=('a'<=c && c<='z')?'a'-'A':0;
            report<<c;
        }
    }
    report<<setw(MAX_NOMBRE-contBlancos)<<" "<<endl;
}
void sub_encabezado(ofstream& report){
    report<<setw(20)<<left<<"Cant.Funciones"<<setw(20)<<"Tot.Butacas.Disp"<<setw(20)<<"Tot.Butacas.Vend"
        <<setw(20)<<"Tot.Butacas.Ocup."<<setw(20)<<"%Venta"<<setw(20)<<"%Ocupacion"<<endl;
}
void lecturaEImpresionSub_encabezado(ofstream& report,ifstream& funciones,ifstream& salas,ifstream& ventas,
                                    int codigoPeli,double& totalRecaudado,int& totalButacasDis,int& totalButacasVen,
                                    int& totalButacasOcu,int fecha){
    // Variables
    int n_sala,aa,mm,dd,fechaREF,hh,min,horaRef,hora,contFunciones=0,contButacas=0,butacas,vendido,t_vendido=0;
    int ocupados,t_ocupados=0;
    double recaudado,t_Recaudado=0;
    char c;
    // Primero debemos actualizar el buscador de ventas
    ventas.clear();
    ventas.seekg(0,ios::beg);
    
    // Ahora leemos ventas
    while (true){
        // Leemos el numero de sala
        ventas>>n_sala;
        if(ventas.eof())break;
        //Leemos la fecha para para ver si pertenece a la fecha que estamos analizando
        ventas>>ws;
        ventas>>dd>>c>>mm>>c>>aa;
        fechaREF=convertirFecha(dd,mm,aa);
        
        if(fecha==fechaREF){
            // Aqui si ya tenemos las fechas, buscamos de que pelicula se trata
            // Leemos la hora para entrar a funciones 
            ventas>>hh>>c>>min;
            horaRef=convertirHora(hh,min);
            
            // comparamos el codigo de la pelicula y la hora, copiamos numero de sala 
            hora=buscadorHORA(funciones,codigoPeli,n_sala);
    
            if(horaRef==hora){
                // Aqui ya me serciore que tengo el dato correcto
                // Contamos la funcion
                contFunciones++;
                // Sumamos la cantidad de butacas
                butacas=buscadorButacas(salas,n_sala);
                
                contButacas+=butacas;
                // Recaudado
                ventas>>recaudado;
                t_Recaudado+=recaudado;
                // Cantidad de butacas vendidas
                ventas>>vendido;
                t_vendido+=vendido;
                // Ahora leemos los ocupados
                ocupados=contOcupados(ventas);
                t_ocupados+=ocupados;

            }

        }
        while(ventas.get()!='\n');
    }
    // Imprimos los datos
    impresionDatos(report,contFunciones,contButacas,t_Recaudado,t_vendido,t_ocupados);
    // Sumamos la cantidad total de butacas, recaudado
    totalButacasDis+=contButacas;
    totalRecaudado+=t_Recaudado;
    totalButacasVen+=t_vendido;
    totalButacasOcu+=t_ocupados;
}
int convertirHora(int hh,int min){
    int hora;
    hora= hh*100+min;
    return hora;
}
int buscadorHORA(ifstream& funciones,int codigoPeli,int n_sala){
    // Variables
    int codigoref,salaref, hh,min,hora;
    char c;
    // Tengo que reiniciar el puntero
    funciones.clear();
    funciones.seekg(0,ios::beg);
    // Ahora hacemos la busqueda
    while(true){
        funciones>>codigoref;
        if(funciones.eof())break;
        if(codigoref==codigoPeli){
            funciones>>salaref;
            if(salaref==n_sala){
                funciones>>hh>>c>>min;
                hora=convertirHora(hh,min);
                break;
            }
        }
        while(funciones.get()!='\n');
    }
    return hora;
}
int buscadorButacas(ifstream& salas,int n_sala){
    int butacas,numero;
    // Reiniciamos el buscador
    salas.clear();
    salas.seekg(0,ios::beg);
    // Ahora buscamos
    while (true){
        salas>>numero;
        if(salas.eof())break;
        if(numero==n_sala){
            salas>>butacas;
            break;
        }
        while(salas.get()!='\n');
    }
    
    return butacas;
}
int contOcupados(ifstream& ventas){
    // Contaremos el numero de sitios ocupados
    int cont=0;
    int num;
    char c;
    ventas>>ws;
    while(true){
        ventas>>c>>num;
        cont++;
        if(ventas.get()=='\n')break;
    }
    return cont;
}
void impresionDatos(ofstream& report,int contFunciones,int contButacas,double t_Recaudado,int t_vendido,int t_ocupados){
    double p_ventas,p_ocupados;
    calculoVentaYOcupacion(p_ventas,p_ocupados,t_vendido,contButacas,t_ocupados);
    report<<setw(20)<<left<<contFunciones<<setw(20)<<contButacas<<setw(20)<<t_vendido
        <<setw(20)<<t_ocupados<<setw(20)<<p_ventas<<'%'<<setw(20)<<p_ocupados<<'%'<<endl;
}
void calculoVentaYOcupacion(double& p_ventas,double& p_ocupados,int t_vendido,int contButacas,int t_ocupados){
    p_ventas=((double)t_vendido/contButacas)*100;
    p_ocupados=((double)t_ocupados/contButacas)*100;
}
void estadisticas(int totalRecaudado,int totalButacasDis,int totalButacasVen,int totalButacasOcu,ofstream& report,int cont){
    double venta,ocupado;
    calculoVentaYOcupacion(venta,ocupado,totalButacasVen,totalButacasDis,totalButacasOcu);
    report<<"Cantidad de Peliculas: "<<cont<<endl;
    report<<"Total Recaudacion (s/.): "<<totalRecaudado<<endl;
    report<<"%Venta total: "<<venta<<endl;
    report<<"Ocupacion total: "<<ocupado<<endl;

}