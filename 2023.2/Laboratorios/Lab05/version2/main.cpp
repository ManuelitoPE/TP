//Author: MAKO
#include <iostream>
#include <iomanip>
using namespace std;
#include "header/funciones.h"
#define MAX_ALUMNOS 100 
#define MAX_CURSOS 50
#define MAX_ESCALAS 10
int main(){
    //Variables
    int alumnos=0,cursos=0,escalas=0;
    int ARRalumnosCod[MAX_ALUMNOS],ARRalumnosEsc[MAX_ALUMNOS];
    int ARRcursosCod[MAX_CURSOS];
    double ARRcursosCre[MAX_CURSOS],ARRescalasCos[MAX_ESCALAS];
    //Variables Totales
    int ARRtotalCursos[MAX_ALUMNOS]{},ARRtotalMatriculados[MAX_CURSOS]{};
    double ARRtotalCreditos[MAX_ALUMNOS]{},ARRtotalPagar[MAX_ALUMNOS]{},
           ARRtotalIngresos[MAX_CURSOS]{};
    lecturaDeAlumnos(alumnos,ARRalumnosCod,ARRalumnosEsc,
                     "docs/Alumnos.txt");
    lecturaDeCursos(cursos,ARRcursosCod,ARRcursosCre,
                    "docs/Cursos.txt");
    lecturaDeEscalas(escalas,ARRescalasCos,"docs/Escalas.txt");
    calculos(alumnos,cursos,escalas,ARRalumnosCod,ARRalumnosEsc,
             ARRcursosCod,ARRcursosCre,ARRescalasCos,ARRtotalCreditos,
             ARRtotalCursos,ARRtotalIngresos,ARRtotalMatriculados,
             ARRtotalPagar,"docs/Matricula.txt");
    ordenarAlumnos(ARRalumnosCod,ARRalumnosEsc,ARRtotalCreditos,
                   ARRtotalCursos,ARRtotalPagar,alumnos);
    ordenarCursos(ARRcursosCod,ARRcursosCre,ARRtotalMatriculados,
                   ARRtotalIngresos,cursos);
    emitirReporte(ARRalumnosCod,ARRalumnosEsc,ARRtotalCreditos,
                  ARRtotalCursos,ARRtotalPagar,alumnos,
                  ARRcursosCod,ARRcursosCre,ARRtotalMatriculados,
                   ARRtotalIngresos,cursos,"docs/Reporte.txt");
    return 0;
}