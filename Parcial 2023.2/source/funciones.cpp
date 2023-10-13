#include<iostream>
#include<fstream>
#include<iomanip>

using namespace std;
#include"../header/funciones.h"
#define MAX_LINEA 100
#define MAX_NOMBRE 40
#define MAX_CURSO 40
void pedirDatos(int& ano,int& ciclo){
    // char c;
    // cout<<"Ingrese el ano y el ciclo: ";
    // cin>>ano>>c>>ciclo;
    ano=2023;
    ciclo=1;

}
    //Emitimos el reporte
void emitirReporte(const char* nomAlumnos,const char* nomCursos,
                const char* nomEscalas,const char* nomMatricula,
                const char* nomReporte,int ano,int ciclo){
    // Enlazamos los archivos
    ifstream archAlumnos(nomAlumnos,ios::in);
    if(not archAlumnos.is_open()){
        cout<<"Error: se produjo un error en abrir el arch "<<nomAlumnos<<endl;
        exit(1);
    }
    ifstream archCursos(nomCursos,ios::in);
    if(not archCursos.is_open()){
        cout<<"Error: se produjo un error en abrir el arch "<<nomCursos<<endl;
        exit(1);
    }
    ifstream archEscalas(nomEscalas,ios::in);
    if(not archEscalas.is_open()){
        cout<<"Error: se produjo un error en abrir el arch "<<nomEscalas<<endl;
        exit(1);
    }
    ifstream archMatricula(nomMatricula,ios::in);
    if(not archMatricula.is_open()){
        cout<<"Error: se produjo un error en abrir el arch "<<nomMatricula<<endl;
        exit(1);
    }
    ofstream archReport(nomReporte,ios::out);
    if(not archReport.is_open()){
        cout<<"Error: se produjo un error en abrir el arch "<<nomReporte<<endl;
        exit(1);
    }
    // Aplicamos la presicion
    archReport.precision(2);
    archReport<<fixed;
    // Imprimimos el encabezado
    encabezado(ciclo, ano, archReport);
    linea(archReport, MAX_LINEA,'=');
    // Variables
    int contAlumnos=0;
    double totalCreditos=0,totalApagar=0,montoTotal=0;
    char escalaAlumno;
    // Lectura e impresion del reporte 
    while (true){
        // Lectura de matricula
        verificarElanoYCiclo(archMatricula,ciclo,ano);
        if(archMatricula.eof())break;
        // Contamos el numero de alumnos
        contAlumnos++;
        // Lectura e impresion del alumno
        lecturaDeAlumno(escalaAlumno,archMatricula,
                        archReport, archAlumnos);
        linea(archReport, MAX_LINEA,'-');
        subEncabezado(archReport);
        //lectura de cursos
        lecturaCursos(archMatricula,archCursos,escalaAlumno,ano, 
                    ciclo,totalCreditos,totalApagar,archReport
                    ,archEscalas);
        linea(archReport, MAX_LINEA,'-');
        // Imprimimos el numero de creditos y monto total
        totales(totalCreditos,totalApagar,archReport);
        linea(archReport, MAX_LINEA,'=');
        montoTotal+=totalApagar;
        totalCreditos=0;
        totalApagar=0;
    }
    // Finalmente imprimimos un resumen 
    resumen(contAlumnos,montoTotal,archReport);

}
void encabezado(int ciclo,int ano,ofstream& archReport){
    archReport<<setw(60)<<right<<"INSTITUCION EDUCATIVA TP"<<endl;
    archReport<<setw(60)<<"DETALLE DE PAGOS REALIZADO POR CICLO"<<endl;
    archReport<<setw(50)<<"CICLO: "<<ano<<'-'<<ciclo<<left<<endl;
}
void linea(ofstream& archReport, int num,char signo){
    for(int i=0;i<num;i++){
        archReport<<signo;
    }
    archReport<<endl;
}
void verificarElanoYCiclo(ifstream& archMatricula,int ciclo,int ano){
    int anoREF,cicloREF;
    char c;
    while(true){
        archMatricula>>anoREF;
        if(archMatricula.eof())break;
        archMatricula>>c>>cicloREF;
        if(anoREF==ano && ciclo==cicloREF){
            break;
        }
        while(archMatricula.get()!='\n');
    }
}
void lecturaDeAlumno(char& escalaAlumno,ifstream& archMatricula,
                    ofstream& archReport,ifstream& archAlumnos){
    int codigoAlumno;
    archMatricula>>codigoAlumno;
    // ?Ya que tenemos el codigo de los alumnos
    archAlumnos.clear();
    archAlumnos.seekg(0,ios::beg);
    // Realizamos la busqueda
    int codigoAlumnoREF;
    while(true){
        archAlumnos>>codigoAlumnoREF;
        if(archAlumnos.eof())break;
        if(codigoAlumno==codigoAlumnoREF){
            //Imprimimos los datos del alumno y leemos la escala
            datosAlumno(codigoAlumno,escalaAlumno,archAlumnos,
                        archReport);
            break;
        }
        while(archAlumnos.get()!='\n');
    }
}
void datosAlumno(int codigoAlumno,char& escalaAlumno,
                ifstream& archAlumnos,ofstream& report){
    int contCaracteres=0;
    char c;
    report<<"ALUMNO: "<<codigoAlumno<<" - ";
    archAlumnos>>ws;
    while(true){
        c=archAlumnos.get();
        if(c==' ')break;
        contCaracteres++;
        if(c=='_')report<<" ";
        else{
            c-=('a'<=c && 'z'>=c)?'a'-'A':0;
            report<<c;
        }
    }
    // Leemos la escala
    archAlumnos>>escalaAlumno;
    report<<setw(MAX_NOMBRE-contCaracteres)<<" "<<"ESCALA: "<<escalaAlumno<<endl;
}
void subEncabezado(ofstream& archReport){
    archReport<<right<<setw(20)<<"CURSO MATRICULADO"<<setw(20)<<
                "CREDITOS"<<setw(20)<<"MONTO PAGADO"<<left<<endl;

}
void lecturaCursos(ifstream& archMatricula,ifstream& archCursos,
            char escalaAlumno,int ano, int ciclo,
            double& totalCreditos,double& totalApagar,
            ofstream& archReport,ifstream& escalas){
    // Variables
    int codigoCursos,contCursos=0;
    double monto,creditoCursos, valorCredito;
    // Ahora leemos los cursos
    while(true){
        archMatricula>>codigoCursos;
        
        // Contamos el curso
        contCursos++;
        // Datos Cursos 
        datosCursos(archReport,archCursos,creditoCursos,codigoCursos
                    ,contCursos);
        //Ahora  buscamos cuanto vale su credito
        valorCredito=busquedaDEvalorCredito(escalaAlumno,escalas,
                                            ano,ciclo);
        // Sumamos los creditos y imprimimos el monto
        monto=valorCredito*creditoCursos;
        archReport<<monto<<endl;
        totalCreditos+=creditoCursos;
        totalApagar+=monto;
        if(archMatricula.get()=='\n')break;
    }
}
void datosCursos(ofstream& archReport,ifstream& archCursos,
                double& creditoCursos,int codigoCursos
                ,int contCursos){
    // Varibales
    int codigoREF;
    char c;
    // Reiniciamos el puntero
    archCursos.clear();
    archCursos.seekg(0,ios::beg);
    while(true){
        archCursos>>codigoREF;
        if(archCursos.eof())break;
        if(codigoREF==codigoCursos){

            // Imprimimos los datos 
            archReport<<setw(3)<<" "<<right<<setfill('0')<<setw(2)
                    <<contCursos<<')'<<setfill(' ')<<left<<setw(2)
                    <<" "<<codigoCursos<<" - ";
            impresionNombreCursos(archCursos,archReport);
            // Leemos el credito
            archCursos>>creditoCursos;
            archReport<<setw(8)<<creditoCursos;
            break;
        }
        while(archCursos.get()!='\n');
    }
}
void impresionNombreCursos(ifstream& archCursos,ofstream& archReport){
    char c;
    int contCaracteres=0;
    archCursos>>ws;
    while (true){
        c=archCursos.get();
        if(c==' ')break;
        contCaracteres++;
        if(c=='_')archReport<<' ';
        else{
            archReport<<c;
        }
    }
    archReport<<setw(MAX_CURSO-contCaracteres)<<" ";
}
double busquedaDEvalorCredito(char escalaAlumno,
                ifstream& escalas,int ano,int ciclo){
    // Varibales 
    int anoREF,cicloREF;
    char c,escalaREF; 
    double monto;
    // Reiniciamos las escalas
    escalas.clear();
    escalas.seekg(0,ios::beg);
    while(true){
        escalas>>anoREF;
        if(escalas.eof())break;
        escalas>>c>>cicloREF>>escalaREF;
        if(anoREF==ano && ciclo==cicloREF && escalaREF==escalaAlumno){
            escalas>>monto;
            break;
        }
        while(escalas.get()!='\n');
    }
    return monto;
}
void totales(double totalCreditos,double totalApagar,
            ofstream& archReport){
    archReport<<"TOTAL CREDITOS: "<<totalCreditos<<setw(3)<<" "
            <<"TOTAL MONTO PAGADO: "<<totalApagar<<endl;
}
void resumen(int contAlumnos,double montoTotal,
            ofstream& archReport){
    archReport<<"RESUMEN:"<<endl<<"CANTIDAD TOTAL DE ALUMNOS: "<<contAlumnos
            <<setw(3)<<" "<<"MONTO TOTAL PAGADO: "<<montoTotal;
}




