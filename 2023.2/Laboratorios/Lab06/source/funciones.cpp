#include<iostream>
#include<iomanip>
#include<fstream>
using namespace std;
#include "../header/funciones.h"
#define MAX_LINEA 100
#define MAX_NOMBRE 30
#define MAX_APELLIDO 20
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
    int codigoAlumno;
    char escala;
    while(true){
        arch>>codigoAlumno;
        if(arch.eof())break;
        arch>>escala;
        arch.get();
        ordenarAlumnos(ARRcodigoAlumnos,ARRescalaAlumnos,num_alumnos
                    ,codigoAlumno,escala);
    }
}
void ordenarAlumnos(int* ARRcodigoAlumnos,char* ARRescalaAlumnos,
                    int& num_alumnos,int codigoAlumno,char escala){
    int i;
    for (i = num_alumnos-1; i >=0; i--){
        if(codigoAlumno>ARRcodigoAlumnos[i])break;
        ARRcodigoAlumnos[i+1]=ARRcodigoAlumnos[i];
        ARRescalaAlumnos[i+1]=ARRescalaAlumnos[i];
    }
    ARRcodigoAlumnos[i+1]=codigoAlumno;
    ARRescalaAlumnos[i+1]=escala;
    num_alumnos++;
}
    //lectura de Cursos
void lecturaCursos(int* ARRcodigoCursos,double* ARRcreditoCursos,
                int& num_cursos,const char* nomArch){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: Se produjo un error al abrir "<<nomArch<<endl;
        exit(1);
    }
    //Variables
    int codigoCurso;
    double credito;
    while(true){
        arch>>codigoCurso;
        if(arch.eof())break;
        arch>>ws;
        while(arch.get()!=' ');
        arch>>credito;
        arch.get();
        ordenarCursos(ARRcodigoCursos,ARRcreditoCursos,num_cursos
                    ,codigoCurso,credito);
    }
}    
void ordenarCursos(int* ARRcodigoCursos,double* ARRcreditoCursos,
                int& num_cursos,int codigoCurso,double credito){
    int i;
    for(i= num_cursos-1;i>=0;i--){
        if(codigoCurso>ARRcodigoCursos[i])break;
        ARRcodigoCursos[i+1]=ARRcodigoCursos[i];
        ARRcreditoCursos[i+1]=ARRcreditoCursos[i];
    }
    ARRcodigoCursos[i+1]=codigoCurso;
    ARRcreditoCursos[i+1]=credito;
    num_cursos++;
}
//Lectura de Escalas
void lecturaEscala(int* ARRsemestreEscalas,char* ARRescalaEscalas,
                double* ARRmontoEscalas,int& num_escalas,
                const char* nomArch){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: Se produjo un error al abrir "<<nomArch<<endl;
        exit(1);
    }
    //Variables
    int anio,ciclo;
    char c;
    while(true){
        arch>>anio>>c>>ciclo;
        if(arch.eof())break;
        arch>>ARRescalaEscalas[num_escalas]>>ARRmontoEscalas[num_escalas];
        ARRsemestreEscalas[num_escalas]=anio*10+ciclo;
        num_escalas++;
    }
}
//Actualizamos la matricula
void actualizacionMatricula(double* ARRnum_creditos,int* ARRnum_cursos,
                        double* ARRmonto_pagado,
                        int* ARRcodigoAlumnos,char* ARRescalaAlumnos,
                        int* ARRcodigoCursos,double* ARRcreditoCursos,
                        int* ARRsemestreEscalas,char* ARRescalaEscalas,
                        double* ARRmontoEscalas,int ciclo,int anio,
                        int num_alumnos,int num_cursos,int num_escalas,
                        const char* nomArch,double& total){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: Se produjo un error al abrir "<<nomArch<<endl;
        exit(1);
    }
    //Variables
    int anioREF,cicloREF,codigoAlumno;
    char c;
    while(true){
        arch>>anioREF;
        if(arch.eof())break;
        arch>>c>>cicloREF;
        if(cicloREF==ciclo and anioREF==anio){
            arch>>codigoAlumno;
            procesoDecursos(ARRnum_creditos,ARRnum_cursos,
                        ARRmonto_pagado,
                        ARRcodigoAlumnos, ARRescalaAlumnos,
                        ARRcodigoCursos, ARRcreditoCursos,
                        ARRsemestreEscalas, ARRescalaEscalas,
                        ARRmontoEscalas, ciclo, anio,
                        num_alumnos, num_cursos, num_escalas,
                        arch,codigoAlumno);
        }
        else{while(arch.get()!='\n');}
    }
    procesarTotal(ARRmonto_pagado,num_alumnos,total);
}
void procesarTotal(double* ARRmonto_pagado,int num_alumnos,double& total){
    for(int i=0;i<num_alumnos;i++){
        total+=ARRmonto_pagado[i];
    }
}
void procesoDecursos(double* ARRnum_creditos,int* ARRnum_cursos,
                    double* ARRmonto_pagado,
                    int* ARRcodigoAlumnos,char* ARRescalaAlumnos,
                    int* ARRcodigoCursos,double* ARRcreditoCursos,
                    int* ARRsemestreEscalas,char* ARRescalaEscalas,
                    double* ARRmontoEscalas,int ciclo,int anio,
                    int num_alumnos,int num_cursos,int num_escalas,
                    ifstream& arch,int codigoAlumno){
    //Variables

    int posEscala,posAlumno,codigoCurso,posLibro;
    //Buscamos la posicion de la escla del alumno
    posAlumno=buscarPosicion(codigoAlumno,ARRcodigoAlumnos,num_alumnos);
    while(true){
        arch>>codigoCurso;
        ARRnum_cursos[posAlumno]++;
        //Buscamos la posicion del libro
        posLibro=buscarPosicion(codigoCurso,ARRcodigoCursos,num_cursos);
        ARRnum_creditos[posAlumno]+=ARRcreditoCursos[posLibro];
        //Buscamos la escala
        posEscala=buscarEscala(anio,ciclo,ARRescalaAlumnos[posAlumno],
                            ARRsemestreEscalas,ARRescalaEscalas,
                            num_escalas);
        ARRmonto_pagado[posAlumno]+=ARRcreditoCursos[posLibro]*ARRmontoEscalas[posEscala];
        if(arch.get()=='\n')break;
    }
}
int buscarPosicion(int codigo,int* ARRcodigo,int num){
    int limitInf=0,limitSup=num-1;
    int ptomedio;
    while(true){
        if(limitInf>limitSup)return -1;
        ptomedio=(limitInf+limitSup)/2;
        if(ARRcodigo[ptomedio]==codigo)return ptomedio;
        if(ARRcodigo[ptomedio]>codigo)limitSup=ptomedio-1;
        if(ARRcodigo[ptomedio]<codigo) limitInf=ptomedio+1;
    }
}
int buscarEscala(int anio,int ciclo,char ecalaAlumno,
                int* ARRsemestreEscalas,char* ARRescalaEscalas,
                int num_escalas){
    int semestre=anio*10+ciclo;
    for(int i=0;i<num_escalas;i++){
        if(ARRsemestreEscalas[i]==semestre and 
            ARRescalaEscalas[i]==ecalaAlumno) return i;
    }
    return -1;
}
//emitimos el reporte
void emitirReporte(double* ARRnum_creditos,int* ARRnum_cursos,
                    double* ARRmonto_pagado,
                    int* ARRcodigoAlumnos,char* ARRescalaAlumnos,
                    int* ARRcodigoCursos,double* ARRcreditoCursos,
                    int* ARRsemestreEscalas,char* ARRescalaEscalas,
                    double* ARRmontoEscalas,int ciclo,int anio,
                    int num_alumnos,int num_cursos,int num_escalas,
                    const char* nomNombres, const char* nomApellidos,
                    const char* nomArch,double total){
    ofstream arch(nomArch,ios::out);
    if(not arch.is_open()){
        cout<<"ERROR: Se produjo un error al abrir "<<nomArch<<endl;
        exit(1);
    }
    ifstream Arch_nombre(nomNombres,ios::in);
    if(not Arch_nombre.is_open()){
        cout<<"ERROR: Se produjo un error al abrir "<<nomNombres<<endl;
        exit(1);
    }
    ifstream Arch_apellidos(nomApellidos,ios::in);
    if(not Arch_apellidos.is_open()){
        cout<<"ERROR: Se produjo un error al abrir "<<nomApellidos<<endl;
        exit(1);
    }
    arch.precision(2);
    arch<<fixed;
    //Variables
    int codigo,posAlumno;
    char apellidoAlumno[MAX_APELLIDO];
    char nombreAlumno[MAX_NOMBRE];
    encabezado(arch,anio,ciclo);
    while(true){
        Arch_nombre>>codigo;
        Arch_apellidos>>apellidoAlumno;
        if(Arch_nombre.eof())break;
        posAlumno=buscarPosicion(codigo,ARRcodigoAlumnos,num_alumnos);
        if(codigo==ARRcodigoAlumnos[posAlumno] and 
            ARRnum_cursos[posAlumno]!=0){
                Arch_nombre>>nombreAlumno;
                modificarTexto(nombreAlumno,apellidoAlumno);
                arch<<ARRcodigoAlumnos[posAlumno]<<" - "
                    <<setw(35)<<nombreAlumno<<setw(15)<<ARRnum_cursos[posAlumno]
                    <<setw(15)<<ARRnum_creditos[posAlumno]<<setw(10)
                    <<ARRescalaAlumnos[posAlumno]<<ARRmonto_pagado[posAlumno]<<endl;
        }
        while(Arch_nombre.get()!='\n');
    }
    // for(int i=0;i<num_alumnos;i++){
    //     arch<<i+1<<" "<<ARRcodigoAlumnos[i]<<" - "<<ARRnum_cursos[i]<<" "
    //         <<setw(20)<<ARRnum_creditos[i]<<setw(10)
    //         <<ARRescalaAlumnos[i]<<ARRmonto_pagado[i]<<endl;
    // }
    linea(arch,MAX_LINEA,'-');
    arch<<"MONTO TOTAL PAGADO:"<<setw(74)<<right<<total<<endl;
    linea(arch,MAX_LINEA,'=');
}
void modificarTexto(char* nombreAlumno,char* apellidoAlumno){
    char aux[100];
    int numCad, primerEspacio,fin;
    for(int i=0; nombreAlumno[i];i++){
        if(nombreAlumno[i]=='_')nombreAlumno[i]=' ';
        else{
            nombreAlumno[i]-=('a'<=nombreAlumno[i] and 'z'>=nombreAlumno[i])?'a'-'A':0;
        }
    }
}
void linea(ofstream& arch,int num,char signo){
    for(int i=0;i<num;i++){
        arch<<signo;
    }
    arch<<endl;
}
void encabezado(ofstream& arch,int anio,int ciclo){
    arch<<setw(63)<<"INSTITUCION EDUCATIVA_TP"<<endl
        <<setw(70)<<"DETALLE DE PAGOS REALIZADOS POR CICLO"<<endl
        <<setw(50)<<"CICLO: "<<anio<<"-"<<ciclo<<endl;
    linea(arch,MAX_LINEA,'=');
    arch<<setw(5)<<" "<<setw(35)<<left<<"ALUMNO"
        <<setw(18)<<"No. DE CURSOS"<<setw(15)<<"CREDITOS"
        <<setw(10)<<"ESCALA"<<setw(10)<<"MONTO PAGADO"<<endl;
    linea(arch,MAX_LINEA,'-');
}