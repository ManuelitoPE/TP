#include<iostream>
#include<iomanip>
using namespace std;
#include"../header/funciones.h"
#define MAX_ALUMNOS 100
#define MAX_CURSOS 50
#define MAX_ESCALAS 30
int main(int argc, char** argv){
    //VARIABLES
    int num_alumnos=0,num_escalas=0,num_cursos=0;
    //ARREGLOS
    int ARRcodigoAlumnos[MAX_ALUMNOS], ARRcodigoCursos[MAX_CURSOS]
        ,ARRanoEscalas[MAX_ESCALAS];
    char ARRescalaAlumnos[MAX_ALUMNOS], ARRescalaEscalas[MAX_ESCALAS];
    double ARRcreditoCursos[MAX_CURSOS],ARRmontoEscalas[MAX_ESCALAS];
    //ARREGLOS PARA MI INFORME
    int ARRcantidad[MAX_ESCALAS];
    double ARRtotalIngresos[MAX_ESCALAS],ARRcantCreditos[MAX_ESCALAS];
    //lectura del Alumnos.txt
    lecturaARRalumnos(num_alumnos,ARRcodigoAlumnos,ARRescalaAlumnos
                    ,"source/docs/Alumnos.txt");
    //lectura del Cursos.txt
    lecturaARRcursos(num_cursos,ARRcodigoCursos,ARRcreditoCursos,
                    "source/docs/Cursos.txt");
    //lectura del Escalas.txt
    lecturaARRescalas(num_escalas,ARRanoEscalas,ARRescalaEscalas
                    ,ARRmontoEscalas,"source/docs/Escalas.txt");
    //Emitir un reporte simple
    emitirReporteSimple(num_escalas,ARRanoEscalas,ARRescalaEscalas
                    ,ARRmontoEscalas);
    //Actualizando
    acutlizandoDatos(num_alumnos,num_escalas,num_cursos,
                    ARRcodigoAlumnos,ARRcodigoCursos,ARRanoEscalas,
                    ARRescalaAlumnos,ARRescalaEscalas,
                    ARRcreditoCursos,ARRmontoEscalas,
                    ARRcantidad,ARRcantCreditos,
                    ARRtotalIngresos);
    //Ordenamos los datos
    ordenar(ARRanoEscalas,ARRescalaAlumnos,ARRcantidad,ARRmontoEscalas
            ,ARRcantCreditos,ARRtotalIngresos,num_escalas);
    //Emitir el reporte final
    reporte(ARRanoEscalas,ARRescalaAlumnos,ARRcantidad,ARRmontoEscalas
            ,ARRcantCreditos,ARRtotalIngresos,num_escalas
            ,"source/docs/Reporte.txt");
    return 0;
}