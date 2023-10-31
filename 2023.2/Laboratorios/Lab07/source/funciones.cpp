/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */
//Author:Sergio Manuel Sutta Pinedo 20210646
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstring>
using namespace std;
#include "../header/funciones.h"
//Solicitar datos
void solicitarDatosAlUsuario(int& ciclo){
//    int anio,cicloREF;
//    char c;
//    cout<<"INSTITUCION EDUCATIVA_TP"<<endl;
//    cout<<"DETALLE DE PAGOS REALIZADOS POR CICLO"<<endl;
//    cout<<"Ingrese el ciclo para determinar lo que pagaria cada alumno"<<endl
//        <<";realizarlo en el formato (ejm. 2023-1): ";
//    cin>>anio>>c>>cicloREF;
//    ciclo=comprimirDatos(anio,cicloREF);
    ciclo=20221;
}
int comprimirDatos(int anio,int cicloREF){
    int ciclo;
    ciclo=anio*10+cicloREF;
    return ciclo;
}
    //Leer datos alumnos
void leerDatosAlumno(int* ARRcodigoAlumno,char** ARRnombreAlumno, 
                    char* ARRescalaAlumno,int& num_alumno,
                    const char* nomArch){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: Se produjo un error al abrir el arch "<<nomArch<<endl;
        exit(1);
    }
    //Variables
    
    while(true){
        arch>>ARRcodigoAlumno[num_alumno];
        if(arch.eof())break;
        arch>>ws;
        ARRnombreAlumno[num_alumno]=leerNombreExacto(arch,' ');
        arch>>ARRescalaAlumno[num_alumno];
        arch.get();
        ordenarAlumnos(ARRcodigoAlumno,ARRnombreAlumno, 
                ARRescalaAlumno,num_alumno,ARRcodigoAlumno[num_alumno],
                ARRnombreAlumno[num_alumno],ARRescalaAlumno[num_alumno]);
    }
}
char* leerNombreExacto(ifstream& arch,char delimitador){
    char *ptr,buff[100];
    arch>>buff;
    ptr=new char[strlen(buff)+1];
    strcpy(ptr,buff);
    return ptr;
}

void ordenarAlumnos(int* ARRcodigoAlumno,char** ARRnombreAlumno, 
             char* ARRescalaAlumno,int& num_alumno,
             int codigo,char* nombre,char escala){
    int i=num_alumno-1;
    while(i>=0 and codigo<ARRcodigoAlumno[i]){
        ARRcodigoAlumno[i+1]=ARRcodigoAlumno[i];
        ARRnombreAlumno[i+1]=ARRnombreAlumno[i];
        ARRescalaAlumno[i+1]=ARRescalaAlumno[i];
        i--;
    }
    ARRcodigoAlumno[i+1]=codigo;
    ARRnombreAlumno[i+1]=nombre;
    ARRescalaAlumno[i+1]=escala;
    num_alumno++;
}
    //Leer datos cursos
void leerDatosCurso(int* ARRcodigoCurso,double* ARRcreditoCurso,
                    int& num_curso,const char* nomArch){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: Se produjo un error al abrir el arch "<<nomArch<<endl;
        exit(1);
    }
    //Variables
    
    while(true){
        arch>>ARRcodigoCurso[num_curso];
        arch>>ws;
        if(arch.eof())break;
        while(arch.get()!=' ');
        arch>>ARRcreditoCurso[num_curso];
        arch.get();
        ordenarCurso(ARRcodigoCurso,ARRcreditoCurso,num_curso,
                    ARRcodigoCurso[num_curso],ARRcreditoCurso[num_curso]);
    }
}
void  ordenarCurso(int* ARRcodigoCurso,double* ARRcreditoCurso,
                   int& num_curso,int curso,double credito){
    int i=num_curso-1;
    while(i>=0 and curso<ARRcodigoCurso[i]){
        ARRcodigoCurso[i+1]=ARRcodigoCurso[i];
        ARRcreditoCurso[i+1]=ARRcreditoCurso[i];
        i--;
    }
    ARRcodigoCurso[i+1]=curso;
    ARRcreditoCurso[i+1]=credito;
    num_curso++;
}
   
    //Leer datos escalas 
void leerDatosEscala(int* ARRcicloEscala,char* ARRescalaEscala,
                    double* ARRcostoEscala,int& num_escala,
                    const char* nomArch){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: Se produjo un error al abrir el arch "<<nomArch<<endl;
        exit(1);
    }
    //Variables
    char c;
    int anio,ciclo;
    while(true){
        arch>>anio>>c>>ciclo;
        if(arch.eof())break;
        ARRcicloEscala[num_escala]=comprimirDatos(anio,ciclo);
        arch>>ARRescalaEscala[num_escala]>>ARRcostoEscala[num_escala];
        arch.get();
        num_escala++;
    }
}
void actualizarDatos(int ciclo,int num_alumno,int num_escala,int num_curso,
                    int* ARRcodigoAlumno,char** ARRnombreAlumno, 
                    char* ARRescalaAlumno,int* ARRcodigoCurso,
                    double *ARRcreditoCurso,int* ARRcicloEscala,
                    char* ARRescalaEscala,double* ARRcostoEscala,
                    int* ARRnum_cursos,double* ARRnum_creditos,
                    double* ARRmonto_pagado,const char* nomArch){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: Se produjo un error al abrir el arch "<<nomArch<<endl;
        exit(1);
    }
    //Variables
    int anio,cicloA,cicloREF,codigoAlumno;
    char c;
    
    while(true){
        bool saltar=true;
        arch>>anio>>c>>cicloA;
        if(arch.eof())break;
        cicloREF=comprimirDatos(anio,cicloA);
        
        if(cicloREF==ciclo){
            arch>>codigoAlumno;
            lecturaDecursos(ciclo,num_alumno,num_escala,num_curso,
                    ARRcodigoAlumno,ARRnombreAlumno, 
                    ARRescalaAlumno,ARRcodigoCurso,
                    ARRcreditoCurso,ARRcicloEscala,
                    ARRescalaEscala,ARRcostoEscala,
                    ARRnum_cursos,ARRnum_creditos,
                    ARRmonto_pagado,arch
                    ,codigoAlumno,saltar);
        }
        if(saltar){
        while(arch.get()!='\n');
        }
    }
}
void lecturaDecursos(int ciclo,int num_alumno,int num_escala,int num_curso,
                    int* ARRcodigoAlumno,char** ARRnombreAlumno, 
                    char* ARRescalaAlumno,int* ARRcodigoCurso,
                    double *ARRcreditoCurso,int* ARRcicloEscala,
                    char* ARRescalaEscala,double* ARRcostoEscala,
                    int* ARRnum_cursos,double* ARRnum_creditos,
                    double* ARRmonto_pagado,ifstream& arch
                    ,int codigoAlumno,bool& saltar){
    int codigoCurso,pos,pos2,pos3;
    pos=buscarPosicion(codigoAlumno,ARRcodigoAlumno,num_alumno);
    if(pos==-1){
        cout<<"Alumno no encontrado"<<endl;
        exit(1);
    }
    while(true){
        arch>>codigoCurso;
        ARRnum_cursos[pos]++;
        pos2=buscarPosicion(codigoCurso,ARRcodigoCurso,num_curso);
        if(pos2==-1){
        cout<<"Curso no encontrado"<<endl;
        exit(1);
        }
        ARRnum_creditos[pos]+=ARRcreditoCurso[pos2];
        pos3=buscarPosicionEscala(ciclo,ARRescalaAlumno[pos],
                 ARRcicloEscala,ARRescalaEscala,num_escala);
        if(pos3==-1){
        cout<<"No encontrado"<<endl;
        exit(1);
        }
        ARRmonto_pagado[pos]+=ARRcostoEscala[pos3]*ARRcreditoCurso[pos2];
        if(arch.get()=='\n'){
            saltar=false;
            break;
        }
    }
}
int buscarPosicion(int codigo,int* ARR,
                        int num){
    int limitInf=0,limitSup=num-1;
    int ptomedio;
    while(true){
        if(limitInf>limitSup)return -1;
        ptomedio=(limitInf+limitSup)/2;
        if(ARR[ptomedio]==codigo)return ptomedio;
        if(ARR[ptomedio]>codigo)limitSup=ptomedio-1;
        if(ARR[ptomedio]<codigo)limitInf=ptomedio+1;
    }
}
    int buscarPosicionEscala(int ciclo,char ARRescalaAlumno,
                     int* ARRcicloEscala,char* ARRescalaEscala,
                     int num_escala){
    for(int i=0;i<num_escala;i++){
        if(ARRcicloEscala[i]==ciclo 
                and ARRescalaAlumno==ARRescalaEscala[i])return i;
    }
    return -1;
}
void emitirReporte(int ciclo,int num_alumno,int* ARRcodigoAlumno,
                   char** ARRnombreAlumno,
                   char* ARRescalaAlumno,int* ARRnum_cursos,
                   double* ARRnum_creditos,double* ARRmonto_pagado,
                     const char* nomArch){
    ofstream arch(nomArch,ios::out);
    if(not arch.is_open()){
        cout<<"ERROR: Se produjo un error al abrir el arch "<<nomArch<<endl;
        exit(1);
    }
    int anio,cicloREF;
    descomprimir(ciclo,anio,cicloREF);
    arch<<"INSTITUCION EDUCATIVA_TP"<<endl;
        arch<<"DETALLE DE PAGOS REALIZADOS POR CICLO"<<endl;
        arch<<"CICLO: "<<anio<<" - "<<cicloREF<<endl;
        for(int i=0;i<num_alumno;i++){
            arch<<setfill('0')<<right<<setw(2)<<i<<")"<<left<<setfill(' ')
                    <<ARRcodigoAlumno[i]<<setw(4)<<" - "<<ARRnombreAlumno[i]
                    <<setw(4)<<" "<<ARRnum_cursos[i]<<setw(4)<<" "<<ARRnum_creditos[i]
                    <<setw(4)<<" "<<ARRmonto_pagado[i]<<endl;
        }
}
void descomprimir(int ciclo,int& anio,int& cicloREF){
    anio=ciclo/10;
    cicloREF=ciclo%10;
}