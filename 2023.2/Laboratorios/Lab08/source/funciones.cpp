//Author: MAKO
#include<iostream>
#include<iomanip>
#include<cstring>
#include<fstream>
using namespace std;
#include "../header/Alumno.h"
#include "../header/Curso.h"
#include "../header/Escala.h"
#include"../header/funciones.h"
#define NO_ENCONTRADO -1
#define MAX_LINEA 100
//Solicitar datos al usuario 
void solicarDatosUsuario(int& anio,int& ciclo){
//    char c;
//    cout<<setw(50)<<"INSTITUCION EDUCATIVA_TP"<<endl
//        <<setw(50)<<"DETALLE DE PAGOS REALIZADOS POR CICLO"<<endl<<endl
//        <<left<<"Ingrese el ciclo que se desea analizar en el formato"
//              <<" xxxx-x: ";
//    cin>>anio>>c>>ciclo;
    anio=2023;
    ciclo=1;
}
    //Lectura de Alumnos
void lecturaAlumnos(struct Alumno *alumnos,int& numAlumnos,const char* nomArch){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: Se produjo un error al abrir "<<nomArch<<endl;
        exit(1);
    }
    //Variables
    int codigo;
    char nombre[50];
    char escala;
    while(true){
        arch>>codigo;
        if(arch.eof())break;
        alumnos[numAlumnos].codigo=codigo;
        arch.get(); //Sacamos la coma
        arch.getline(nombre,50,',');
        strcpy(alumnos[numAlumnos].nombre,nombre);
        arch>>escala;
        alumnos[numAlumnos].escala=escala;
        arch.get(); //Sacamos el salto de linea
        numAlumnos++;
    }
}
     //Lectura de cursos 
void lecturaCursos(struct Curso *cursos,int& numCursos,const char* nomArch){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: Se produjo un error al abrir "<<nomArch<<endl;
        exit(1);
    }
    //Variables
    int codigo;
    char nombre[60];
    double credito;
    while(true){
        arch>>codigo;
        if(arch.eof())break;
        cursos[numCursos].codigo=codigo;
        arch.get();//Sacamos la coma
        arch.getline(nombre,60,',');
        strcpy(cursos[numCursos].nombre,nombre);
        arch>>credito;
        cursos[numCursos].credito=credito;
        arch.get();//Sacamos el salto de linea
        numCursos++;
    }
    //Ponemos los nombres 
    mayusculas(cursos,numCursos);
}
void mayusculas(struct Curso *cursos,int numCursos){
    int cant;
    char c;
    for(int i=0;i<numCursos;i++){
        cant=strlen(cursos[i].nombre);
        for(int k=0;k<cant;k++){
            if(cursos[i].nombre[k]!=' '){
                c=cursos[i].nombre[k];
                cursos[i].nombre[k]-=('a'<=c and c<='z')?'a'-'A':0;
            }
        }
    }
}
    //Lectura de Escalas
void lecturaEscalas(struct Escala *escalas,int& numEscalas,const char* nomArch){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: Se produjo un error al abrir "<<nomArch<<endl;
        exit(1);
    }
    //Variables
    int anio,ciclo;
    char escala,c;
    double costo;
    while(true){
        arch>>anio;
        if(arch.eof())break;
        arch>>c>>ciclo;
        escalas[numEscalas].semestre=anio*10+ciclo;
        arch.get();//Sacamos la coma
        arch>>escala;
        escalas[numEscalas].escala=escala;
        arch.get();//Sacamos la coma
        arch>>costo;
        arch.get();//Sacamos el salto de linea
        escalas[numEscalas].costo_credito=costo;
        numEscalas++;
    }
}
void actulizacionDatos(double& total,struct Alumno *alumnos
                        ,struct Curso *cursos,
                        struct Escala *escalas,int numAlumnos,int numCursos,
                        int numEscalas,int anio,int ciclo,
                        const char* nomArch){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: Se produjo un error al abrir "<<nomArch<<endl;
        exit(1);
    }
    //Variables
    int anioREF,cicloREF,codigo_AlumnoREF;
    char c;
    while(true){    
        arch>>anioREF;
        if(arch.eof())break;
        arch>>c>>cicloREF;
        arch.get();//Sacamos la coma
        if(anio==anioREF and ciclo==cicloREF){
            arch>>codigo_AlumnoREF;
            arch.get();//Sacamos la coma
            procesarDatos(alumnos,cursos,escalas,numAlumnos,numCursos,
                        numEscalas,codigo_AlumnoREF, anio,ciclo,arch);
        } else{
            while(arch.get()!='\n');
        }
    }
    calcularTOTAL(total,cursos,numCursos);
}

void procesarDatos(struct Alumno *alumnos,struct Curso *cursos,
                    struct Escala *escalas,int numAlumnos,int numCursos,
                    int numEscalas,int codigo_AlumnoREF, 
                    int anio,int ciclo,ifstream& arch){
    int posAlumno,posCurso,posEscala;
    int codigo_curso;
    double monto;
    //Buscamos la posicion del alumno
    posAlumno=BuscarPoscionAlumno(alumnos,numAlumnos,codigo_AlumnoREF);
    if(posEscala==NO_ENCONTRADO){
        cout<<"El   alumno con el codigo "<<codigo_AlumnoREF
                <<" no fue encontrado"<<endl;
        exit(1);
        }
    while(true){
        arch>>codigo_curso;
        //Buscamos la posicion del curso
        posCurso=BuscarPosicionCurso(cursos, numCursos,codigo_curso);
        if(posCurso==NO_ENCONTRADO){
        cout<<"El curso con el codigo "<<codigo_curso<<" no fue encontrado"<<endl;
        exit(1);
        }
        posEscala=BuscarPosicionEscala(escalas,numEscalas,anio,ciclo
                                    ,alumnos[posAlumno].escala);
        if(posEscala==NO_ENCONTRADO){
        cout<<"La escala del alumno con el codigo "<<codigo_AlumnoREF
                <<"no fue encontrado"<<endl;
        exit(1);
        }
        cursos[posCurso].cantAlumnos++;
        monto=cursos[posCurso].credito*escalas[posEscala].costo_credito;
        cursos[posCurso].totalPagado+=monto;
        if(arch.get()=='\n')break;
    }
}
void calcularTOTAL(double& total,struct Curso *cursos,int numCursos){
    for(int i=0;i<numCursos;i++){
        total+=cursos[i].totalPagado;
    }
}
int BuscarPoscionAlumno(struct Alumno *alumnos,int numAlumnos,
                        int codigo_AlumnoREF){
    for(int i=0;i<numAlumnos;i++){
        if(alumnos[i].codigo==codigo_AlumnoREF)return i;
    }
    return NO_ENCONTRADO;
}
int BuscarPosicionCurso(struct Curso *cursos,int  numCursos,
                        int codigo_curso){
    for(int i=0;i<numCursos;i++){
        if(cursos[i].codigo==codigo_curso)return i;
    }
    return NO_ENCONTRADO;
}
int BuscarPosicionEscala(struct Escala *escalas,int numEscalas,
                        int anio,int ciclo,char escala){
    for(int i=0;i<numEscalas;i++){
        if(escalas[i].escala==escala and 
           escalas[i].semestre==anio*10+ciclo)return i;
    }
    return NO_ENCONTRADO;
}
void ordenarCursos(struct Curso *cursos,int  numCursos){
    for(int i=0;i<numCursos-1;i++){
        for(int k=i+1;k<numCursos;k++){
            if(cursos[i].cantAlumnos>cursos[k].cantAlumnos or
                cursos[i].cantAlumnos==cursos[k].cantAlumnos and
                strcmp(cursos[i].nombre,cursos[k].nombre)>0){
                cambiarStructua(cursos[i],cursos[k]);
            }
        }
    }
}
void cambiarStructua(struct Curso &cursoA,struct Curso &cursoB){
    struct Curso aux;
    aux=cursoA;
    cursoA=cursoB;
    cursoB=aux;
}
    //Emitimos el reporter
void emitirReporte(double total,int anio,int ciclo,struct Curso *cursos,
                    int  numCursos,const char* nomArch){
    ofstream arch(nomArch,ios::out);
    if(not arch.is_open()){
        cout<<"ERROR: Se produjo un error al abrir "<<nomArch<<endl;
        exit(1);
    }
    arch.precision(2);
    arch<<fixed;
    encabezado(anio,ciclo,arch);
    for(int i=0;i<numCursos;i++){
        arch<<setfill('0')<<right<<setw(2)<<i+1<<')'<<setfill(' ')<<left
            <<setw(6)<<cursos[i].codigo<<" - "
            <<setw(55)<<cursos[i].nombre
            <<setw(12)<<cursos[i].credito
            <<setw(10)<<cursos[i].cantAlumnos
            <<setw(10)<<cursos[i].totalPagado
            <<endl;
    }
    linea(arch,MAX_LINEA,'-');
    arch<<setw(88)<<"MONTO TOTAL PAGADO: "<<total<<endl;
    linea(arch,MAX_LINEA,'-');
}
void encabezado(int anio,int ciclo,ofstream& arch){
    arch<<setw(60)<<"INSTITUCION EDUCATIVA_TP"<<endl
        <<setw(65)<<"DETALLE DE PAGOS REALIZADOS POR CICLO"<<endl
        <<setw(48)<<"CICLO: "<<anio<<"-"<<ciclo<<endl;
    linea(arch,MAX_LINEA,'=');
    arch<<left<<setw(15)<<"No."<<setw(50)<<"CURSO"
        <<setw(10)<<"CREDITOS"
        <<setw(13)<<"ALUMNOS.MAT"
        <<setw(12)<<"MONTO PAGADO"<<right<<endl;
    linea(arch,MAX_LINEA,'-');
}
void linea(ofstream& arch,int num ,char signo){
    for(int i=0; i<num;i++){
        arch<<signo;
    }
    arch<<endl;
}