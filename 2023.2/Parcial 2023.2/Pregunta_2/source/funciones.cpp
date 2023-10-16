#include<iostream>
#include<iomanip>
#include<fstream>
using namespace std;
#include"../header/funciones.h"
#define MAX_LINEA 100    
void lecturaARRalumnos(int& num_alumnos,int* ARRcodigoAlumnos,
                        char* ARRescalaAlumnos
                    ,const char* nomArch){
    //Enlazamos los archivos
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"Error: se produjo un error al abrir "<<nomArch;
        exit(1);
    }
    while(true){
        arch>>ARRcodigoAlumnos[num_alumnos];
        if(arch.eof())break;
        arch>>ws;
        while(arch.get()!=' ');
        arch>>ARRescalaAlumnos[num_alumnos];
        num_alumnos++;
    }
    // for(int i=0;i<num_alumnos;i++){
    //     cout<<*(ARRcodigoAlumnos+i)<<" "<<*(ARRescalaAlumnos+i)<<endl;
    // }
}
    //lectura del Cursos.txt
void lecturaARRcursos(int& num_cursos,int* ARRcodigoCursos,
                    double* ARRcreditoCursos,
                    const char* nomArch){
        //Enlazamos los archivos
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"Error: se produjo un error al abrir "<<nomArch;
        exit(1);
    }
        while(true){
        arch>>ARRcodigoCursos[num_cursos];
        if(arch.eof())break;
        arch>>ws;
        while(arch.get()!=' ');
        arch>>ARRcreditoCursos[num_cursos];
        num_cursos++;
    }
    //     for(int i=0;i<num_cursos;i++){
    //     cout<<*ARRcodigoCursos+i<<" "<<*ARRcreditoCursos+i<<endl;
    // }
}
    //lectura del Escalas.txt
void lecturaARRescalas(int& num_escalas,int* ARRanoEscalas,
                    char* ARRescalaEscalas,double* ARRmontoEscalas,
                    const char* nomArch){
        //Enlazamos los archivos
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"Error: se produjo un error al abrir "<<nomArch;
        exit(1);
    }
    // Variables
    int ano,ciclo,cicloYano;
    char c;
    while(true){
        arch>>ano;
        if(arch.eof())break;
        arch>>c>>ciclo;
        cicloYano=compresionCiclo(ano,ciclo);
        ARRanoEscalas[num_escalas]=cicloYano;
        arch>>ARRescalaEscalas[num_escalas]>>ARRmontoEscalas[num_escalas];
        num_escalas++;
    }
    //     for(int i=0;i<num_escalas;i++){
    //     cout<<*ARRanoEscalas+i<<" "<<*ARRescalaEscalas+i<<" "<<*ARRmontoEscalas+i<<endl;
    // }
}
int compresionCiclo(int ano,int ciclo){
    int ciclus;
    ciclus=ano*10+ciclo;
    return ciclus;
}
 //Emitir un reporte simple
void emitirReporteSimple(int num_escalas,int* ARRanoEscalas,
                    char* ARRescalaEscalas
                    ,double* ARRmontoEscalas){
    int ano,ciclo;
    //Imprimimos un encabezado adecuado
    cout<<setw(50)<<right<<"REPORTE DE PRUEBA DE ESCALAS"<<left<<endl;
    cout<<setw(15)<<"Ano y ciclo"<<setw(15)<<"Escala"<<setw(15)<<"Valor de credito"<<endl;
    for(int i=0;i<num_escalas;i++){
        descomprimir(*(ARRanoEscalas+i),ano,ciclo);
        cout<<setw(2)<<" "<<ano<<'-'<<ciclo<<setw(9)<<" "<<*(ARRescalaEscalas+i)<<
            setw(12)<<" "<<right<<setw(10)<<*(ARRmontoEscalas+i)<<left<<endl;

    }
    
}
void descomprimir(int num,int& ano,int& ciclo){
    ano=num/10;
    ciclo=num%10;
}
    //Actualizando
void acutlizandoDatos(int num_alumnos,int num_escalas,int num_cursos,
                    int* ARRcodigoAlumnos,int* ARRcodigoCursos,
                    int* ARRanoEscalas,char* ARRescalaAlumnos,
                    char* ARRescalaEscalas,double* ARRcreditoCursos
                    ,double* ARRmontoEscalas,int* ARRcantidad,
                    double* ARRcantCreditos,
                    const char* nomArch){
    //Enlazamos los archivos
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"Error: se produjo un error al abrir "<<nomArch;
        exit(1);
    }
    //Variables
    int anoREF,cicloREF,codigoAlumno,posicion_escala;
    char c,escalaREF;
    //Lectura del archivo
    while(true){
        //Necesito la cantidad de alimnos, el valor del credito ese ano
        //la cantidad de cretidos y el total de ingresos
        //Lectura del ano y el ciclo y el codigo para obtener la posicion 
        arch>>anoREF;
        if(arch.eof())break;
        arch>>c>>cicloREF>>codigoAlumno;
        //Buscamos la escala a la que pertenece
        escalaREF=busquedaEscala(ARRcodigoAlumnos,ARRescalaAlumnos,
                                codigoAlumno,num_alumnos);
        //Ya tengo la escala, busco la posicion del ano y ciclo
        posicion_escala=busquedaPosicion_escala(anoREF,cicloREF,
                        escalaREF,ARRanoEscalas,ARRescalaEscalas
                        ,num_escalas);
        //Ahora sumamos la cantidad de alumnos
        ARRcantidad[posicion_escala]++;
        //Sumamos los creditos de los cursos
        sumaCantidadCreditos(ARRcantCreditos,posicion_escala,ARRcodigoCursos
                            ,ARRcreditoCursos,arch,num_cursos);
    }
}
char busquedaEscala(int* ARRcodigoAlumnos,char* ARRescalaAlumnos,
                               int codigoAlumno,int num_alumnos){
    int i;
    for(i=0;i<num_alumnos;i++){
        if(ARRcodigoAlumnos[i]==codigoAlumno)break;
    }
    return ARRescalaAlumnos[i];
}
int busquedaPosicion_escala(int anoREF,int cicloREF,
                        char escalaREF,int* ARRanoEscalas,char* 
                        ARRescalaEscalas,int num_escalas){
    int fecha=compresionCiclo(anoREF,cicloREF);
    int i;
    for(i=0; i<num_escalas;i++)
        if(fecha==ARRanoEscalas[i] && escalaREF==ARRescalaEscalas[i])break;
    return i;
}
void sumaCantidadCreditos(double* ARRcantCreditos,int posicion_escala
                        ,int* ARRcodigoCursos,double* ARRcreditoCursos,
                        ifstream& arch,int num_cursos){
    // Variables
    int codigoREF,posicion;
    while(true){
        arch>>codigoREF;
        posicion=buscarCredito(ARRcodigoCursos,codigoREF,num_cursos);
        ARRcantCreditos[posicion_escala]+=ARRcreditoCursos[posicion];
        if(arch.get()=='\n')break;
    }
}      
int buscarCredito(int* ARRcodigoCursos,int codigoREF,int num_cursos){
    int i;
    for( i=0;i<num_cursos;i++)
        if(ARRcodigoCursos[i]==codigoREF)break;
    return i;
}          
    //Ordenamos los datos
void ordenar(int* ARRanoEscalas,char* ARRescalaEscala,
            int* ARRcantidad,double* ARRmontoEscalas
            ,double* ARRcantCreditos,
            int num_escalas){
    for(int i=0;i<num_escalas-1;i++){
        for(int k=i+1;k<num_escalas;k++){
            if(ARRcantidad[i]>ARRcantidad[k]){
                cambiarInt(ARRanoEscalas[i],ARRanoEscalas[k]);
                cambiarInt(ARRcantidad[i],ARRcantidad[k]);
                cambiarDouble(ARRmontoEscalas[i],ARRmontoEscalas[k]);
                cambiarDouble(ARRcantCreditos[i],ARRcantCreditos[k]);
                cambiarChar(ARRescalaEscala[i],ARRescalaEscala[k]);
            }
        }
    }
}
void cambiarInt(int& a,int& b){
    int aux;
    aux=a;
    a=b;
    b=aux;
}
void cambiarDouble(double& a,double& b){
    double aux;
    aux=a;
    a=b;
    b=aux;
}
void cambiarChar(char& a,char& b){
    char aux;
    aux=a;
    a=b;
    b=aux;
}
    //Emitir el reporte final
void reporte(int* ARRanoEscalas,char* ARRescalaEscala,
            int* ARRcantidad,double* ARRmontoEscalas
            ,double* ARRcantCreditos,
            int num_escalas
            ,const char* nomArch){
    //Enlazamos los archivos
    ofstream arch(nomArch,ios::out);
    if(not arch.is_open()){
        cout<<"Error: se produjo un error al abrir "<<nomArch;
        exit(1);
    }  
    //Variables
    int ano,ciclo;
    arch<<setw(50)<<right<<"INSTITUCION EDUCATIVA_TP"<<endl
        <<setw(50)<<"RELACION DE INGRESOS POR CICLOS Y ESCALAS"<<left<<endl;
    linea(arch,MAX_LINEA,'=');
    arch<<setw(15)<<"CICLO"<<setw(15)<<"ESCALA"<<setw(15)<<"CANT.ALUMNOS"
        <<setw(15)<<"VALOR.CREDITO"<<setw(15)<<"CANT.CREDITOS"<<setw(15)<<
        "TOTAL DE INGRESOS"<<endl;
    for(int i=0;i<num_escalas;i++){
        descomprimir(ARRanoEscalas[i],ano,ciclo);
        arch<<right<<setfill('0')<<setw(2)<<i+1<<")"<<left<<setfill(' ')<<ano<<'-'<<ciclo
            <<setw(9)<<" "<<ARRescalaEscala[i]<<setw(16)<<" "<<ARRcantidad[i]
            <<setw(11)<<" "<<ARRmontoEscalas[i]<<right<<setw(13)<<ARRcantCreditos[i]<<
            setw(10)<<ARRcantCreditos[i]*ARRmontoEscalas[i]<<endl;
    } 
}
void linea(ofstream& arch,int num,char signo){
    for(int i=0; i<num;i++){
        arch<<signo;
    }
    arch<<endl;
}
