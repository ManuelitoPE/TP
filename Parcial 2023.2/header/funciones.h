#ifndef FUNCIONES_H
#define FUNCIONES_H
#include<fstream>
void pedirDatos(int& ano,int& ciclo);
    //Emitimos el reporte
void emitirReporte(const char* nomAlumnos,const char* nomCursos,
                const char* nomEscalas,const char* nomMatricula,
                const char* nomReporte,int ano,int ciclo);
void encabezado(int ciclo,int ano,ofstream& archReport);
void linea(ofstream& archReport, int num,char signo);
void verificarElanoYCiclo(ifstream& archMatricula,int ciclo,int ano);
void lecturaDeAlumno(char& escalaAlumno,ifstream& archMatricula,
                    ofstream& archReport,ifstream& archAlumnos);

void datosAlumno(int codigoAlumno,char& escalaAlumno,
                ifstream& archAlumnos,ofstream& report);
void subEncabezado(ofstream& archReport);
void lecturaCursos(ifstream& archMatricula,ifstream& archCursos,
            char escalaAlumno,int ano, int ciclo,
            double& totalCreditos,double& totalApagar,
            ofstream& archReport,ifstream& escalas);
void datosCursos(ofstream& archReport,ifstream& archCursos,
                double& creditoCursos,int codigoCursos,
                int contCursos);
void impresionNombreCursos(ifstream& archCursos,ofstream& archReport);
double busquedaDEvalorCredito(char escalaAlumno,
                ifstream& escalas,int ano,int ciclo);
void totales(double totalCreditos,double totalApagar,
            ofstream& archReport);
void resumen(int contAlumnos,double montoTotal,
            ofstream& archReport);



#endif