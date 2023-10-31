#include<iostream>
#include<iomanip>
#include<fstream>
using namespace std;
#include "../header/funciones.h"
//Solicitud 
void solicitudDeSemestre(int& anio,int& ciclo){
    //Variable 
    // char c;
    // cout<<"Ingrese el anio y ciclo: ";
    // cin>>anio>>c>>ciclo;
    anio=2023;
    ciclo=1;
}
    //Lectura de Alumnos
void lecturaAlumnos(int* ARRcodigoAlumnos,char* ARRescalaAlumnos
                ,int& num_alumnos,const char* nomArch){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: Se produjo un error al abrir "<<nomArch<<endl;
        exit(1);
    }
    //Variables
}
    //lectura de Cursos
void lecturaCursos(int* ARRcodigoCursos,double* ARRcreditoCursos,
                int& num_cursos,const char* nomArch){

}    
//Lectura de Escalas
void lecturaEscala(int* ARRsemestreEscalas,char* ARRescalaEscalas,
                double* ARRmontoEscalas,int& num_alumnos,
                const char* nomArch){

}
