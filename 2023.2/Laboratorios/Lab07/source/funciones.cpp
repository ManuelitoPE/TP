//Author:MAKO
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstring>
using namespace std;
#include "../header/funciones.h"
#define MAX_LINEA 100
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
    nombreEdicion(ARRnombreAlumno,num_alumno);
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
    //Cambiamos el nombre a nombreEdicion
void nombreEdicion(char** ARRnombreAlumno,int num_alumno){
    char* ptr;
    char* espacio;
    for(int i=0;i<num_alumno;i++){
        ptr=ARRnombreAlumno[i];
        for(int j=0;ptr[j];j++){
            //Le quitamos los espacios    
            if(ptr[j]=='_')ptr[j]=' ';
            else{
                ptr[j]-=(ptr[j]>='A' and ptr[j]<='Z')?0:'a'-'A';
            }
        }
    }
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
    int anio_matricula,ciclo_matricula,cicloREF,codigoAlumno;
    char c;
    
    while(true){
        bool saltar=true;
        arch>>anio_matricula>>c>>ciclo_matricula;
        if(arch.eof())break;
        cicloREF=comprimirDatos(anio_matricula,ciclo_matricula);
        //Verificamos el ciclo
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
    //Buscamos la posicion del alumno
    pos=buscarPosicion(codigoAlumno,ARRcodigoAlumno,num_alumno);
    if(pos==-1){
        cout<<"Alumno no encontrado"<<endl;
        exit(1);
    }
    while(true){
        arch>>codigoCurso;
        //Sumamos la cantidad de cursos
        ARRnum_cursos[pos]++;
        //Buscamos la posicion del curso
        pos2=buscarPosicion(codigoCurso,ARRcodigoCurso,num_curso);
        if(pos2==-1){
        cout<<"Curso no encontrado"<<endl;
        exit(1);
        }
        //Sumamos la cantidad de creditos
        ARRnum_creditos[pos]+=ARRcreditoCurso[pos2];
        //Buscamos la posicon del monto de la escala del alumno
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
    //Busqueda binaria
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
//Ordenar datos
void ordenarDatos(int num_alumno,int* ARRcodigoAlumno,
                char** ARRnombreAlumno,
                char* ARRescalaAlumno,int* ARRnum_cursos,
                double* ARRnum_creditos,double* ARRmonto_pagado){
    for(int i=0;i<num_alumno-1;i++){
        for(int j=i+1;j<num_alumno;j++){
            if(ARRescalaAlumno[i]-ARRescalaAlumno[j]<0 or 
                ARRescalaAlumno[i]-ARRescalaAlumno[j]==0 and
                strcmp(ARRnombreAlumno[i],ARRnombreAlumno[j])>0
                ){
                    cambiarINT(ARRcodigoAlumno[i],ARRcodigoAlumno[j]);
                    cambiarChar(ARRescalaAlumno[i],ARRescalaAlumno[j]);
                    cambiarDouble(ARRmonto_pagado[i],ARRmonto_pagado[j]);
                    cambiarString(ARRnombreAlumno[i],ARRnombreAlumno[j]);
                    cambiarDouble(ARRnum_creditos[i],ARRnum_creditos[j]);
                    cambiarINT(ARRnum_cursos[i],ARRnum_cursos[j]);
            }
        }
    }
}
void cambiarINT(int& a,int& b){
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
void cambiarChar(char& a, char& b){
    char aux;
    aux=a;
    a=b;
    b=aux;
}
void cambiarString(char* a, char* b){
    char aux[100];
    strcpy(aux,a);
    strcpy(a,b);
    strcpy(b,aux);
}
    //Calcular monto total
void calcularMonto(double& total,double* ARRmonto_pagado,int num_alumno){
    for(int i=0;i<num_alumno;i++){
        total+=ARRmonto_pagado[i];
    }
}
void emitirReporte(int ciclo,int num_alumno,int* ARRcodigoAlumno,
                char** ARRnombreAlumno,
                char* ARRescalaAlumno,int* ARRnum_cursos,
                double* ARRnum_creditos,double* ARRmonto_pagado,
                double total,const char* nomArch){
    ofstream arch(nomArch,ios::out);
    if(not arch.is_open()){
        cout<<"ERROR: Se produjo un error al abrir el arch "<<nomArch<<endl;
        exit(1);
    }
    arch.precision(2);
    arch<<fixed;
    //Descomprimimos nuestro ciclo
    int anio,cicloREF;
    descomprimir(ciclo,anio,cicloREF);
    //Encabezado
    encabezado(arch,anio,cicloREF);
        for(int i=0;i<num_alumno;i++){
            arch<<setw(5)<<" "<<setfill('0')<<right<<setw(2)<<i+1<<")"
                <<left<<setfill(' ')<<ARRcodigoAlumno[i]<<setw(4)<<"  -  "
                <<setw(35)<<ARRnombreAlumno[i]
                <<setw(7)<<ARRnum_cursos[i]
                <<setw(5)<<ARRnum_creditos[i]<<right
                <<setw(12)<<ARRescalaAlumno[i]
                <<setw(15)<<ARRmonto_pagado[i]<<endl<<left;
        }
    linea(arch,MAX_LINEA,'-');
    arch<<"Monto total de todos los estudiantes: "<<total<<endl;
    linea(arch,MAX_LINEA,'=');
}
void descomprimir(int ciclo,int& anio,int& cicloREF){
    anio=ciclo/10;
    cicloREF=ciclo%10;
}
void encabezado(ofstream& arch,int anio,int cicloREF){
    arch<<setw(50)<<"INSTITUCION EDUCATIVA_TP"<<endl
        <<setw(55)<<"DETALLE DE PAGOS REALIZADOS POR CICLO"<<endl
        <<setw(38)<<"CICLO: "<<anio<<" - "<<cicloREF<<endl;
    linea(arch,MAX_LINEA,'=');
    arch<<setw(15)<<"CODIGO"<<setw(30)<<"NOMBRE DEL ALUMNO"
        <<setw(15)<<"CURSOS"<<setw(10)<<"CREDITOS"
        <<setw(12)<<"ESCALA"
        <<setw(12)<<"MONTO"<<endl;
    linea(arch,MAX_LINEA,'-');
}
void linea(ofstream& arch, int num, char signo){
    for(int i=0;i<num;i++){
        arch<<signo;
    }
    arch<<endl;
}