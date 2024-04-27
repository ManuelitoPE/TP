#include <iostream>
#include<iomanip>
#include<fstream>
using namespace std;
#include "../header/funciones.h"
#define MAX_LINEA 100
    // Leer datos de los alumnos
void leerDatosAlumnos(int* ARRcodigoAlumno,int* ARRescalaAlumno,
                    int& num_Alumnos,const char* nomArch){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: Se produjo un error al abrir "<<nomArch<<endl;
        exit(1);
    }
    //Variables

    while (true){
        arch>>ARRcodigoAlumno[num_Alumnos];
        if(arch.eof())break;
        arch>>ws;
        while (arch.get()!=' ');
        arch>>ARRescalaAlumno[num_Alumnos];
        num_Alumnos++;
    }
    
}
    //Leer los datos de los cursos
void leerDatosCursos(int* ARRcodigoCursos,double* ARRcreditosCursos,
                    int& num_cursos,const char* nomArch){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: Se produjo un error al abrir "<<nomArch<<endl;
        exit(1);
    }
    while (true){
        arch>>ARRcodigoCursos[num_cursos];
        if(arch.eof())break;
        arch>>ws;
        while (arch.get()!=' ');
        arch>>ARRcreditosCursos[num_cursos];
        num_cursos++;
    }
}
    // Leer el dato de la escala
void leerDatosEscala(double* ARRmontoEscalas,int& num_escalas,
                const char* nomArch){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: Se produjo un error al abrir "<<nomArch<<endl;
        exit(1);
    }
    //Varibale
    int escala;
    while (true){
        arch>>escala;
        if(arch.eof())break;
        arch>>ARRmontoEscalas[num_escalas];        
        num_escalas++;
    }
}
    //Calculos
void calculos(int num_Alumnos,int num_escalas,int num_cursos,
            int* ARRcodigoAlumno,int* ARRescalaAlumno,
            int* ARRcodigoCursos,double* ARRcreditosCursos,
            double* ARRmontoEscalas,double* totalCreditos,
            double* totalApagar,double* totalIngresos,
            int* totalCursos, int* alumnosMatriculados
            ,const char* nomArch){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: Se produjo un error al abrir "<<nomArch<<endl;
        exit(1);
    }
    //Variables
    int codigoAlumno,codigoCursos,posAlumno,posCursos;
    // 
    while(true){
        arch>>codigoAlumno;
        if(arch.eof())break;
        arch>>codigoCursos;
        //Buscar la posicion del alumno
        posAlumno=buscar(codigoAlumno,ARRcodigoAlumno,num_Alumnos);
        //Ahora sumo la cantidad cursos 
        totalCursos[posAlumno]++;
        //Tengo que contar los creditos de los alumnos
        posCursos=buscar(codigoCursos,ARRcodigoCursos,num_cursos);
        totalCreditos[posAlumno]+=ARRcreditosCursos[posCursos];
        //Ahora sumamos el total a pagar
        totalApagar[posAlumno]+=ARRcreditosCursos[posCursos]*ARRmontoEscalas[ARRescalaAlumno[posAlumno]-1];
        //Contar el total de alumnos matriculados
        alumnosMatriculados[posCursos]++;
        totalIngresos[posCursos]+=ARRcreditosCursos[posCursos]*ARRmontoEscalas[ARRescalaAlumno[posAlumno]-1];
    }
}
int buscar(int codigo,int* ARR,int num){
    int i;
    for (i = 0; i < num; i++){
        if(ARR[i]==codigo)break;
    }
    return i;
}
    //Ordenar
void ordenar(int num_Alumnos,int num_cursos,int* ARRcodigoAlumno,
            int* ARRescalaAlumno,int* ARRcodigoCursos,
            double* ARRcreditosCursos,double* totalCreditos,
            double* totalApagar,double* totalIngresos, 
            int* totalCursos,int*  alumnosMatriculados){
    //Ordenar alumnos
    for(int i=0;i<num_Alumnos-1;i++){
        for (int k = i+1; k < num_Alumnos; k++){
            if(totalApagar[i]<totalApagar[k]){
                cambiarInt(ARRcodigoAlumno[i],ARRcodigoAlumno[k]);
                cambiarInt(ARRescalaAlumno[i],ARRescalaAlumno[k]);
                cambiarInt(totalCursos[i],totalCursos[k]);
                cambiarDouble(totalCreditos[i],totalCreditos[k]);
                cambiarDouble(totalApagar[i],totalApagar[k]);                
            }
        }
        
    }
    for(int i=0;i<num_cursos-1;i++){
        for (int k = i+1; k < num_cursos; k++){
            if(alumnosMatriculados[i]>alumnosMatriculados[k]){
                cambiarInt(ARRcodigoCursos[i],ARRcodigoCursos[k]);
                cambiarDouble(ARRcreditosCursos[i],ARRcreditosCursos[k]);
                cambiarInt(alumnosMatriculados[i],alumnosMatriculados[k]);
                cambiarDouble(totalIngresos[i],totalIngresos[k]);                
            }
        }
    }
}
void cambiarInt(int& a, int& b){\
    int aux=a;
    a=b;
    b=aux;
}
void cambiarDouble(double& a,double& b){
    double aux=a;
    a=b;
    b=aux;
}
    // emitir reporte
void emitirReporte(int num_Alumnos,int num_cursos,int* ARRcodigoAlumno,
            int* ARRescalaAlumno,int* ARRcodigoCursos,
            double* ARRcreditosCursos,double* totalCreditos,
            double* totalApagar,double* totalIngresos, 
            int* totalCursos,int*  alumnosMatriculados,
            const char* nomArch){
    ofstream arch(nomArch,ios::out);
    if(not arch.is_open()){
        cout<<"ERROR: Se produjo un error al abrir "<<nomArch<<endl;
        exit(1);
    }
    arch<<setw(50)<<right<<"INSTITUCION EDUCATIVA_TP"<<left<<endl;
    arch<<setw(50)<<right<<"RELACION DE PAGO DE LOS ALUMNOS"<<left<<endl;
    linea(arch,MAX_LINEA,'=');
    arch<<setw(3)<<" "<<setw(10)<<"ALUMNO"<<setw(10)<<"ESCALA"<<setw(15)<<
        "TOTAL DE CREDITOS"<<setw(15)<<"TOTAL DE CURSOS"<<setw(15)<<"TOTAL A PAGAR"<<endl;
    linea(arch,MAX_LINEA,'-');
    for(int i=0;i<num_Alumnos;i++){
        arch<<setfill('0')<<right<<setw(2)<<i+1<<')'<<setfill(' ')<<
            left<<setw(2)<<" "<<setw(13)<<ARRcodigoAlumno[i]<<setw(13)<<
            ARRescalaAlumno[i]<<setw(13)<<totalCreditos[i]<<setw(13)<<
            totalCursos[i]<<setw(13)<<totalApagar[i]<<endl;
    }
    linea(arch,MAX_LINEA,'=');
    arch<<right<<setw(50)<<"RELACION DE INGRESOS POR CADA CURSO"<<endl;
    linea(arch,MAX_LINEA,'=');
    arch<<setw(3)<<" "<<setw(10)<<"CURSO"<<setw(10)<<"CREDITOS"<<setw(15)<<
        "ALUMNOS MATRICULADOS"<<setw(15)<<"TOTAL DE INGRESOS"<<endl;

    for(int i=0;i<num_cursos;i++){
        arch<<setfill('0')<<right<<setw(2)<<i+1<<')'<<setfill(' ')<<
            left<<setw(2)<<" "<<setw(13)<<ARRcodigoCursos[i]<<setw(13)<<
            ARRcreditosCursos[i]<<setw(13)<<alumnosMatriculados[i]<<setw(13)<<
            totalIngresos[i]<<endl;
    }
    linea(arch,MAX_LINEA,'=');
}
void linea(ofstream& arch,int num, char signo){
    for (int i = 0; i < num; i++){
        arch<<signo;
    }
    arch<<endl;
}


