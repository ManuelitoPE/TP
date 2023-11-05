#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;
#include"../header/funciones.h"
#define MAX_TITULO 70
#define MAX_LINEA 100
void ingresoDeFecha(int& fecha){
    // Variables
    int dd,mm,aa;
    char c;
    // cout<<right<<setw(MAX_TITULO)
    //     <<"Reporte de Ventas y Ocupacion"<<endl;
    // cout<<"Ingrese una fecha con el formato dia/mes/anio"<<endl;
    // cout<<"Fecha: ";
    // cin>>dd>>c>>mm>>c>>aa;
    // fecha=convertirFecha(dd,mm,aa);
    fecha=20190418;
}
int convertirFecha(int dd,int mm,int aa){
    int fecha;
    fecha= aa*10000+mm*100+dd;
    return fecha;
}
    //Leer codigo de peliculas (misma cantidad del total recaudado)
void lecturaDePelicualas(int& numPeliculas,int* codPeli,int fecha,
                        const char* nomArch){
    //Enlazamos el archivo
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"Error: Se produjo un error en abrir "<<nomArch<<endl;
        exit(1);
    }
    //Variables
    int dd,mm,aa,ddf,mmf,aaf,fechaI,fechaF;
    char c;
    //Luego de enlazar leemos
    while(true){
        arch>>codPeli[numPeliculas];
        if(arch.eof())break;
        //Realizamos una verificacion si la peli esta 
        arch>>dd>>c>>mm>>c>>aa>>ddf>>c>>mmf>>c>>aaf;
        fechaI=convertirFecha(dd,mm,aa);
        fechaF=convertirFecha(ddf,mmf,aaf);
        if(fecha>=fechaI and fechaF>=fecha){
            numPeliculas++;
        }
        while(arch.get()!='\n');
    }
}
    //Leemos los datos de funciones
void lecturaDeFunciones(int& num_funciones,int* peliFunciones,
                    int* num_Salas_Funciones,int* horafunciones
                    ,const char* nomArch){
    //Enlazamos el archivo
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"Error: Se produjo un error en abrir "<<nomArch<<endl;
        exit(1);
    }
    //Variables
    int hh,min;
    char c;
    //Ahora leemos los datos
    while(true){
        arch>>peliFunciones[num_funciones];
        if(arch.eof())break;
        //Realizamos una verificacion si la peli esta 
        arch>>num_Salas_Funciones[num_funciones];
        arch>>hh>>c>>min;
        horafunciones[num_funciones]=convertirHora(hh,min);
        num_funciones++;
    }
}
int convertirHora(int hh,int min){
    int hora;
    hora=hh*100+min;
    return hora;
}
    //Leemos el numero de butacas por sala
void lecturaNumButacas(int* num_Butacas,int& numeroButa,
                    const char* nomArch){
    //Enlazamos el archivo
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"Error: Se produjo un error en abrir "<<nomArch<<endl;
        exit(1);
    }
    //Variables
    int num;
    while(true){
        arch>>num;
        if(arch.eof())break;
        //Realizamos una verificacion si la peli esta 
        arch>>num_Butacas[numeroButa];
        numeroButa++;
        while(arch.get()!='\n');
    }
}
    //Lectura de ventas
void lecturaVentas(const char* nomArch,int* codPeli,
                int* T_ButacasDis,int* cantFunciones,
                int* T_ButacasVend,int* T_ButacasOcu,
                double* recaudacionP,int* num_Butacas,
                int* peliFunciones,int* num_Salas_Funciones,
                int* horafunciones ,int numPeliculas,
                int numeroButa,int num_funciones,int fecha){
    //Enlazamos el archivo
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"Error: Se produjo un error en abrir "<<nomArch<<endl;
        exit(1);
    }
    // Variables
    int salaREF,horaREF,fechaREF,dd,mm,aa,hh,min,monto,vendido;
    int codigoP,posicion,butacas_ocupadas;
    char c;
    while (true){
        arch>>salaREF;
        if(arch.eof())break;
        arch>>dd>>c>>mm>>c>>aa;
        fechaREF=convertirFecha(dd,mm,aa);
        if(fechaREF==fecha){
            arch>>hh>>c>>min;
            horaREF=convertirHora(hh,min);
            //Con la hora y la sala busco la pelicula
            codigoP=buscarCodigo(peliFunciones,horafunciones,horaREF,salaREF
                        ,num_Salas_Funciones,num_funciones);
            //Con el codigo busco la posicion
            posicion=buscarPosicion(codigoP,codPeli,numPeliculas);
            //Con la posicion ya podemos anadir datos 
            arch>>recaudacionP[posicion]>>T_ButacasVend[posicion];
            //Tenemos que suma la cantidad de funciones
            cantFunciones[posicion]++;
            //Tenemos que sumar la cantidad de butacas disponibles
            T_ButacasDis[posicion]+=num_Butacas[salaREF];
            //Ahora tenemos que contar cuantas butacas estan
            //siendo ocupadas
            butacas_ocupadas=numeroOcupadas(arch);
            T_ButacasOcu[posicion]+=butacas_ocupadas;
        }
        while(arch.get()!='\n');

    }
    
}
int buscarCodigo(int* peliFunciones,int* horafunciones,int horaREF
            ,int salaREF,int* num_Salas_Funciones,int num_funciones){
    int i;
    for(i=0;i<num_funciones;i++)
        if(horafunciones[i]==horaREF && num_Salas_Funciones[i]==salaREF)break;
    
    return peliFunciones[i];

}
int buscarPosicion(int codigoP,int* codPeli,int numPeliculas){
    int i;
    for(i=0;i<numPeliculas;i++)
        if(codPeli[i]==codigoP)break;
    return i;
}
int numeroOcupadas(ifstream& arch){
    int num,cont=0;
    char c;
    while (true){
        arch>>c>>num;
        cont++;
        if(arch.get()=='\n')break;
    }
    return cont;
}
    //Emitir el reporte
void emitirReporte(const char* nomArch,int fecha,int* codPeli,
                int* T_ButacasDis, int* cantFunciones,
                int* T_ButacasVend,int* T_ButacasOcu,
                double* recaudacionP,int numPeliculas){
    //Enlazamos el archivo
    ofstream arch(nomArch,ios::out);
    if(not arch.is_open()){
        cout<<"Error: Se produjo un error en abrir "<<nomArch<<endl;
        exit(1);
    }
    //Variables
    double venta,ocupacion;
    //Imprimimos el encabezado
    encabezado(arch,fecha);
    linea(arch,MAX_LINEA,'=');
    //Ahora hacemos la impresion
    for(int i=0;i<numPeliculas;i++){
        arch<<"Pelicula: "<<codPeli[i]<<" - Tot.Recaudacion(S/.): "
            <<recaudacionP[i]<<endl;
        linea(arch,MAX_LINEA,'-');
        arch<<setw(20)<<"Cant.Funciones"<<setw(20)<<"Tot.Butacas.Disp"
            <<setw(20)<<"Tot.Butacas.vend"<<setw(20)<<"Tot.Butacas.Ocup"
            <<setw(20)<<"%Venta"<<setw(20)<<"%Ocupacion"<<endl;
        calculoVentayOcupacion(venta,ocupacion,T_ButacasVend[i],
                            T_ButacasDis[i],T_ButacasOcu[i]);
        arch<<setw(20)<<cantFunciones[i]<<setw(20)<<T_ButacasDis[i]
            <<setw(20)<<T_ButacasVend[i]<<setw(20)<<T_ButacasOcu[i]
            <<setw(20)<<venta<<setw(20)<<ocupacion<<endl;
        
    }
    linea(arch,MAX_LINEA,'=');
    // Cantidades finales
    estadisticas(arch,recaudacionP,numPeliculas,T_ButacasVend,
                T_ButacasDis,T_ButacasOcu);
}
void  encabezado(ofstream& arch,int fecha){
    int aa,dd,mm;
    aa=fecha/10000;
    fecha%=10000;
    mm=fecha/100;
    fecha%=100;
    dd=fecha;
    arch<<right<<setw(70)<<"REPORTE DE VENTAS Y OCUPACION DE SALAS"
        <<endl<<"Fecha: "<<setfill('0')<<setw(2)<<dd<<'/'
        <<setw(2)<<mm<<'/'<<setw(4)<<aa<<setfill(' ')<<left<<endl;
}
void linea(ofstream& arch,int num,char signo){
    for(int i=0; i<num;i++){
        arch<<signo;
    }
    arch<<endl;
}
void calculoVentayOcupacion(double& venta,double& ocupacion,
                            int T_ButacasVend,int T_ButacasDis,
                            int T_ButacasOcu){
    venta=((double)T_ButacasVend/T_ButacasDis)*100;
    ocupacion=((double)T_ButacasOcu/T_ButacasDis)*100;     
}
void estadisticas(ofstream& arch,double* recaudacionP,int numPeliculas,
                int* T_ButacasVend,int * T_ButacasDis,
                int* T_ButacasOcu){
    //Variables
    int totalVEND,totalDis,totalOcu;
    double venta,ocupacion,totalR;
    totalVEND=sumatotal(numPeliculas,T_ButacasVend);
    totalDis=sumatotal(numPeliculas,T_ButacasDis);
    totalOcu=sumatotal(numPeliculas,T_ButacasOcu);
    totalR=sumatotalDouble(numPeliculas,recaudacionP);;
    calculoVentayOcupacion(venta,ocupacion,totalVEND,
                            totalDis,totalOcu);
    arch<<left<<"Cantidad de Peliculas: "<<numPeliculas<<endl;
    arch<<"Total Recaudacion (s/.) "<<totalR<<endl;
    arch<<"%Venta total: "<<venta<<"%"<<endl;
    arch<<"%Ocupacion total: "<<ocupacion<<endl; 
}
int sumatotal(int num,int* arr){
    int total=0;
    for(int i=0;i<num;i++){
        total+=arr[i];
    }
    return total;
}
double sumatotalDouble(int num,double* arr){
    double total=0;
    for(int i=0;i<num;i++){
        total+=arr[i];
    }
    return total;
}
