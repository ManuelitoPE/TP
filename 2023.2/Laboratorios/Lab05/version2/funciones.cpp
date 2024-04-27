//Author: Mako
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "header/funciones.h"
#define MAX_LINEA 80

void lecturaDeAlumnos(int& alumnos,int* ARRalumnosCod,
                      int* ARRalumnosEsc,const char* nomAlumnos){
    ifstream arch(nomAlumnos,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomAlumnos<<endl;
        exit(1);
    }
    //Variables

    while(true){
        arch>>ARRalumnosCod[alumnos];
        if(arch.eof())break;
        arch>>ws;
        while(arch.get()!=' ');
        arch>>ARRalumnosEsc[alumnos];
        alumnos++;
    }
}
void lecturaDeCursos(int& cursos,int* ARRcursosCod,double* ARRcursosCre,
                     const char* nomCursos){
    ifstream arch(nomCursos,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomCursos<<endl;
        exit(1);
    }
    //Variables

    while(true){
        arch>>ARRcursosCod[cursos];
        if(arch.eof())break;
        arch>>ws;
        while(arch.get()!=' ');
        arch>>ARRcursosCre[cursos];
        cursos++;
    }
}
void lecturaDeEscalas(int& escalas,double* ARRescalasCos,
                      const char* nomEscalas){
    ifstream arch(nomEscalas,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomEscalas<<endl;
        exit(1);
    }
    //Variables
    int aux;
    while(true){
        arch>>aux;
        if(arch.eof())break;
        arch>>ARRescalasCos[escalas];
        escalas++;
    }
}
void calculos(int alumnos,int cursos,int escalas,int* ARRalumnosCod,
              int* ARRalumnosEsc,int* ARRcursosCod,double* ARRcursosCre,
              double* ARRescalasCos,double* ARRtotalCreditos,
              int* ARRtotalCursos,double* ARRtotalIngresos,
              int *ARRtotalMatriculados,double* ARRtotalPagar,
              const char* nomMatricula){
    ifstream arch(nomMatricula,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomMatricula<<endl;
        exit(1);
    }
    //Variables
    int posAlumno,posCurso;
    int codAlumno,codCurso;
    while(true){
        arch>>codAlumno;
        if(arch.eof())break;
        arch>>codCurso;
        //Buscamos las posiciones
        posAlumno=buscar(codAlumno,ARRalumnosCod,alumnos);
        posCurso=buscar(codCurso,ARRcursosCod,cursos);
        //Alumno
        ARRtotalCreditos[posAlumno]+=ARRcursosCre[posCurso];
        ARRtotalCursos[posAlumno]++;
        ARRtotalPagar[posAlumno]+=ARRcursosCre[posCurso]*ARRescalasCos[ARRalumnosEsc[posAlumno]-1];
        //CURSOS
        ARRtotalMatriculados[posCurso]++;
        ARRtotalIngresos[posCurso]+=ARRcursosCre[posCurso]*ARRescalasCos[ARRalumnosEsc[posAlumno]-1];
    }
}
int buscar(int codigo,int* arr,int n){
    int i;
    for (i = 0; i < n; i++)if(codigo==arr[i])break;
    return i;
}
void ordenarAlumnos(int* ARRalumnosCod,int* ARRalumnosEsc,
                    double* ARRtotalCreditos,int* ARRtotalCursos,
                    double* ARRtotalPagar,int alumnos){
    for (int i = 0; i < alumnos-1; i++){
        for (int k = i+1; k < alumnos; k++){
            if(ARRtotalPagar[i]<ARRtotalPagar[k]){
                cambiarINT(ARRalumnosCod[i],ARRalumnosCod[k]);
                cambiarINT(ARRalumnosEsc[i],ARRalumnosEsc[k]);
                cambiarDOUBLE(ARRtotalCreditos[i],ARRtotalCreditos[k]);
                cambiarINT(ARRtotalCursos[i],ARRtotalCursos[k]);
                cambiarDOUBLE(ARRtotalPagar[i],ARRtotalPagar[k]);
            }
        }
    }
}
void cambiarINT(int& a,int& b){
    int aux;
    aux=a; a=b; b=aux;
}
void cambiarDOUBLE(double& a,double& b){
    double aux;
    aux=a; a=b; b=aux;    
}
void ordenarCursos(int* ARRcursosCod,double* ARRcursosCre,
                   int* ARRtotalMatriculados,double* ARRtotalIngresos,
                   int cursos){
    for (int i = 0; i < cursos-1; i++){
        for (int k = i+1; k < cursos; k++){
            if(ARRtotalMatriculados[i]>ARRtotalMatriculados[k]){
                cambiarINT(ARRcursosCod[i],ARRcursosCod[k]);
                cambiarDOUBLE(ARRcursosCre[i],ARRcursosCre[k]);
                cambiarINT(ARRtotalMatriculados[i],ARRtotalMatriculados[k]);
                cambiarDOUBLE(ARRtotalIngresos[i],ARRtotalIngresos[k]);
            }
        }
    }
}
void emitirReporte(int* ARRalumnosCod,int* ARRalumnosEsc,
                   double* ARRtotalCreditos,int* ARRtotalCursos,
                   double* ARRtotalPagar,int alumnos,
                   int* ARRcursosCod,double* ARRcursosCre,
                   int* ARRtotalMatriculados,double* ARRtotalIngresos,
                   int cursos,const char* nomReporte){
    ofstream report(nomReporte,ios::out);
    if(not report.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomReporte<<endl;
        exit(1);
    }
    encabezado(report);
    for (int i = 0; i < alumnos; i++){
        report<<right<<setfill('0')<<setw(2)<<i+1<<')'<<setfill(' ')
              <<setw(2)<<" "<<left<<setw(14)<<ARRalumnosCod[i]
              <<setw(11)<<ARRalumnosEsc[i]
              <<setw(22)<<ARRtotalCreditos[i]
              <<setw(14)<<ARRtotalCursos[i]
              <<setw(10)<<ARRtotalPagar[i]<<endl;
    }
    linea(report,MAX_LINEA,'='); report<<endl;
    encabezado2(report);
    for (int i = 0; i < cursos; i++){
        report<<right<<setfill('0')<<setw(2)<<i+1<<')'<<setfill(' ')
              <<setw(2)<<" "<<left<<setw(11)<<ARRcursosCod[i]
              <<setw(16)<<ARRcursosCre[i]
              <<setw(22)<<ARRtotalMatriculados[i]
              <<setw(14)<<ARRtotalIngresos[i]<<endl;
    }
    linea(report,MAX_LINEA,'='); report<<endl;
}
void encabezado(ofstream& report){
    report<<setw(50)<<"INSTITUCION EDUCATIVA_TP"<<endl
          <<setw(53)<<"RELAION DE PAGOS DE LOS ALUMNOS"<<endl;
    linea(report,MAX_LINEA,'=');
    report<<setw(12)<<"ALUMNO"
          <<setw(10)<<"ESCALA"
          <<setw(20)<<"TOTAL DE CREDITOS"
          <<setw(18)<<"TOTAL DE CURSOS"
          <<setw(16)<<"TOTAL A PAGAR"<<endl;
    linea(report,MAX_LINEA,'-');
}
void linea(ofstream& report,int n,char c){
    for (int i = 0; i < n; i++)report<<c;
    report<<endl;
}
void encabezado2(ofstream& report){
    report<<right<<setw(55)<<"RELACION DE INGRESOS POR CADA CURSO"<<endl;
    linea(report,MAX_LINEA,'=');
    report<<setw(10)<<"CURSO"
          <<setw(12)<<"CREDITOS"
          <<setw(23)<<"ALUMNOS MATRICULADOS"
          <<setw(20)<<"TOTAL DE INGRESOS"<<endl;
}