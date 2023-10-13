#include<iostream>
#include<iomanip>
#include<fstream>
using namespace std;
#include"../header/funciones.h"
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



