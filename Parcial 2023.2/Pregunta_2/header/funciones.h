#ifndef FUNCIONES_H
#define FUNCIONES_H
#include<fstream>
    //lectura del Alumnos.txt
void lecturaARRalumnos(int& num_alumnos,int* ARRcodigoAlumnos,
                        char* ARRescalaAlumnos
                    ,const char* nomArch);
    //lectura del Cursos.txt
void lecturaARRcursos(int& num_cursos,int* ARRcodigoCursos,
                    double* ARRcreditoCursos,
                    const char* nomArch);
    //lectura del Escalas.txt
void lecturaARRescalas(int& num_escalas,int* ARRanoEscalas,
                    char* ARRescalaEscalas,double* ARRmontoEscalas,
                    const char* nomArch);
int compresionCiclo(int ano,int ciclo);
 //Emitir un reporte simple
void emitirReporteSimple(int num_escalas,int* ARRanoEscalas,
                    char* ARRescalaEscalas
                    ,double* ARRmontoEscalas);
    //Actualizando
void acutlizandoDatos(int num_alumnos,int num_escalas,int num_cursos,
                    int* ARRcodigoAlumnos,int* ARRcodigoCursos,
                    int* ARRanoEscalas,char* ARRescalaAlumnos,
                    char* ARRescalaEscalas,double* ARRcreditoCursos
                    ,double* ARRmontoEscalas,int* ARRcantidad,
                    double* ARRcantCreditos,double* ARRtotalIngresos);
    //Ordenamos los datos
void ordenar(int* ARRanoEscalas,char* ARRescalaAlumnos,
            int* ARRcantidad,double* ARRmontoEscalas
            ,double* ARRcantCreditos,double* ARRtotalIngresos,
            int num_escalas);
    //Emitir el reporte final
void reporte(int* ARRanoEscalas,char* ARRescalaAlumnos,
            int* ARRcantidad,double* ARRmontoEscalas
            ,double* ARRcantCreditos,double* ARRtotalIngresos,
            int num_escalas
            ,const char* nomArch);
#endif