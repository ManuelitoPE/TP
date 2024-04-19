// Author: MAKO
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "header/funciones.h"
#define MAX_LINEA 100
void datosReporte(int& aa,int& ciclo){
    //Varibles
    // char c;
    // cout<<setw(60)<<"INSTITUCION EDUCATIVA_TP"<<endl
    //     <<setw(65)<<"DETALLE DE PAGOS REALIZADO POR CICLO"<<endl;
    // for(int i=0;i<100;i++)cout<<'=';
    // cout<<endl<<endl<<"Ingrese el anio y el ciclo(XXXX-X): ";
    // cin>>aa>>c>>ciclo;
    // cout<<endl<<"El reporte se emitio correctamente!!";
    aa=2023; ciclo=1;
}
void emitirReporte(const char* nomAlumnos,const char* nomCursos,
                  const char* nomEscalas,const char* nomMatricula,
                  const char* nomReporte,int aa,int ciclo){
    ifstream archAlumnos(nomAlumnos,ios::in);
    if(not archAlumnos.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomAlumnos<<endl;
        exit(1);
    }
    ifstream archCursos(nomCursos,ios::in);
    if(not archCursos.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomCursos<<endl;
        exit(1);
    }
    ifstream archEscalas(nomEscalas,ios::in);
    if(not archEscalas.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomEscalas<<endl;
        exit(1);
    }
    ifstream archMatricula(nomMatricula,ios::in);
    if(not archMatricula.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomMatricula<<endl;
        exit(1);
    }
    ofstream report(nomReporte,ios::out);
    if(not report.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomReporte<<endl;
        exit(1);
    }
    report.precision(2);
    report<<fixed;
    encabezado(report,aa,ciclo);
    //Variables
    int aux_aa,aux_ciclo;
    char c;
    //Varibales de Resumen
    int cantAlumnos=0;
    double montoTotalPagado=0;
    while(true){
        archMatricula>>aux_aa;
        if(archMatricula.eof())break;
        archMatricula>>c>>aux_ciclo;
        if(aa==aux_aa and ciclo==aux_ciclo){
            cantAlumnos++;
            lecturaDeDatos(aa,ciclo,montoTotalPagado,archMatricula,
                           archAlumnos,archCursos,archEscalas,
                           report);
        }else while(archMatricula.get()!='\n');
    }
    report<<"RESUMEN:"<<endl<<"CANTIDAD TOTAL DE ALUMNOS: "
          <<setw(7)<<cantAlumnos
          <<"MONTO TOTAL PAGADO: "<<montoTotalPagado<<endl;
}
void encabezado(ofstream& report,int aa,int ciclo){
    report<<setw(60)<<"INSTITUCION EDUCATIVA_TP"<<endl
        <<setw(65)<<"DETALLE DE PAGOS REALIZADO POR CICLO"<<endl
        <<setw(50)<<"CICLO: "<<aa<<'-'<<ciclo<<endl;
    linea(report,MAX_LINEA,'=');
}
void linea(ofstream& report,int n,char c){
    for (int i = 0; i < n; i++)report<<c;
    report<<endl;
}
void lecturaDeDatos(int aa,int ciclo,double& montoTotalPagado,
                    ifstream& archMatricula,ifstream& archAlumnos,
                    ifstream& archCursos,ifstream& archEscalas,
                    ofstream& report){
    //Variables
    int curso,numC=1;
    double credito,creditosT=0,precio,monto,montoTotal=0;
    char escala;   
    //Sacamos el codigo del alumno
    int codigoAlumno; archMatricula>>codigoAlumno;
    report<<"ALUMNO: "<<codigoAlumno<<" - ";
    // Impresion Nombre y sacamos la escala
    busquedaNombreEscala(report,archAlumnos,codigoAlumno,escala);
    encabezadoC(report);
    //Impresion de Cursos
    while (archMatricula.get()!='\n'){
        archMatricula>>curso;
        report<<right<<setfill('0')<<setw(2)<<numC<<left
              <<setfill(' ')<<") "<<curso<<' ';
        // Impresion Nombre y sacamos los creditos
        busquedaNombreCreditos(report,archCursos,curso,credito);
        report<<setw(11)<<credito; creditosT+=credito;
        //Impresion monto pagado
        busquedaPrecioCredito(aa,ciclo,escala,archEscalas,
                              precio);
        monto= precio*credito;
        montoTotal+=monto;
        report<<monto<<endl;
        numC++;
    }
    montoTotalPagado+=montoTotal;
    linea(report,MAX_LINEA,'-');
    report<<"TOTAL DE CREDITOS: "<<creditosT
          <<"  TOTAL DE MONTO PAGADO: "<<montoTotal<<endl;
    linea(report,MAX_LINEA,'=');
}
void busquedaNombreEscala(ofstream& report,ifstream& archAlumnos,
                          int codigoAlumno,char& escala){
    //Variables
    int aux_codigo;
    //Reiniciamos el cursor del ArchAlumnos
    archAlumnos.clear();
    archAlumnos.seekg(0,ios::beg);
    while(true){
        archAlumnos>>aux_codigo;
        if(archAlumnos.eof())break;
        if(aux_codigo==codigoAlumno){
            archAlumnos>>ws;
            impresionNombre(archAlumnos,true,report);
            archAlumnos>>escala; report<<"ESCALA: "<<escala<<endl;
            linea(report,MAX_LINEA,'-');
            break;
        }else while(archAlumnos.get()!='\n');
    }
}
void impresionNombre(ifstream& archAlumnos,bool mayuscula,
                     ofstream& report){
    //Variables
    int cont=0;
    while(true){
        char c= archAlumnos.get();
        if(c==' ')break;
        else{
            if(c=='_')report<<' ';
            else if('A'<= c and c<='z' and mayuscula){
                c-=(c>='A' and c<='Z')?0:'a'-'A';
                report<<c;
            }else report<<c;
            cont++;
        }
    }
    if(mayuscula)report<<setw(51-cont)<<" ";
    else report<<setw(60-cont)<<" ";
}
void encabezadoC(ofstream& report){
    report<<left<<setw(5)<<" "<<setw(65)<<"CURSO MATRICULADO"
          <<setw(10)<<"CREDITOS"
          <<setw(18)<<"MONTO PAGADO"<<endl;
}
void busquedaNombreCreditos(ofstream& report,ifstream& archCursos,   
                       int curso,double& credito){
    //Variables
    int aux_curso;
    //Reiniciamos el cursor
    archCursos.clear();
    archCursos.seekg(0,ios::beg); 
    while (true){
        archCursos>>aux_curso;
        if(archCursos.eof())break;
        if(aux_curso==curso){
            archCursos>>ws;
            impresionNombre(archCursos,false,report);
            archCursos>>credito;
            break;
        }else while(archCursos.get()!='\n');
    }
}
void busquedaPrecioCredito(int aa,int ciclo,char escala,
                           ifstream& archEscalas,double& precio){
    //Varibles 
    int aux_aa,aux_ciclo;
    char aux_escala,c;
    //Reiniciamos el cursor
    archEscalas.clear();
    archEscalas.seekg(0,ios::beg);
    while(true){
        archEscalas>>aux_aa;
        if(archEscalas.eof())break;
        archEscalas>>c>>aux_ciclo>>aux_escala;
        if(aux_aa==aa and aux_ciclo==ciclo and aux_escala==escala){
            archEscalas>>precio;
            break;
        }else while(archEscalas.get()!='\n');
    }
}

