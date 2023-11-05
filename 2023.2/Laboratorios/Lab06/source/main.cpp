//Author: MAKO
#include<iostream>
#include<iomanip>
using namespace std;
#include"../header/funciones.h"
#define MAX_ALUMNOS 100
#define MAX_CURSOS 50
#define MAX_ESCALAS 30
int main(int argc, char** argv){
    //Arrglos de alumnos
    int ARRcodigoAlumnos[MAX_ALUMNOS];
    char ARRescalaAlumnos[MAX_ALUMNOS];
    //Arreglos de cursos
    int ARRcodigoCursos[MAX_CURSOS];
    double ARRcreditoCursos[MAX_CURSOS];
    //Arreglos de escala
    int ARRsemestreEscalas[MAX_ESCALAS];
    char ARRescalaEscalas[MAX_ESCALAS];
    double ARRmontoEscalas[MAX_ESCALAS];
    //Arreglos para el informe
    int ARRnum_cursos[MAX_ALUMNOS]{};
    double ARRnum_creditos[MAX_ALUMNOS]{},ARRmonto_pagado[MAX_ALUMNOS]{};
    //Numero de datos
    int ciclo,anio;
    double total=0;
    int num_alumnos=0,num_cursos=0,num_escalas=0;
    //Solicitud 
    solicitudDeSemestre(anio,ciclo);
    //Lectura de Alumnos
    lecturaAlumnos(ARRcodigoAlumnos,ARRescalaAlumnos
                ,num_alumnos,"source/docs/Alumnos.txt");
    //lectura de Cursos
    lecturaCursos(ARRcodigoCursos,ARRcreditoCursos,
                num_cursos,"source/docs/Cursos.txt");
    //Lectura de Escalas
    lecturaEscala(ARRsemestreEscalas,ARRescalaEscalas,
                ARRmontoEscalas,num_escalas,"source/docs/Escalas.txt");
    //Actualizamos la matricula
    actualizacionMatricula(ARRnum_creditos,ARRnum_cursos,ARRmonto_pagado,
                        ARRcodigoAlumnos,ARRescalaAlumnos,ARRcodigoCursos,
                        ARRcreditoCursos,ARRsemestreEscalas,ARRescalaEscalas,
                        ARRmontoEscalas,ciclo,anio,
                        num_alumnos,num_cursos,num_escalas,
                        "source/docs/Matricula.txt",total);
    //emitimos el reporte
    emitirReporte(ARRnum_creditos,ARRnum_cursos,ARRmonto_pagado,
                ARRcodigoAlumnos,ARRescalaAlumnos,ARRcodigoCursos,
                ARRcreditoCursos,ARRsemestreEscalas,ARRescalaEscalas,
                ARRmontoEscalas,ciclo,anio,
                num_alumnos,num_cursos,num_escalas,
                "source/docs/AlumnosNombres.txt",
                "source/docs/AlumnosApellidos.txt",
                "source/docs/Reporte.txt",total);
    
    return 0;
}