#include<iostream>
#include<iomanip>
using namespace std;
#include"../header/funciones.h"
#define MAX_ALUMNOS 100
#define MAX_CURSOS 50
#define MAX_ESCALAS 10
int main(int argc, char** argv){
    int num_Alumnos=0,num_escalas=0,num_cursos=0;
    // Arreglos
    int ARRcodigoAlumno[MAX_ALUMNOS],ARRescalaAlumno[MAX_ALUMNOS],
        ARRcodigoCursos[MAX_CURSOS];
    double ARRcreditosCursos[MAX_CURSOS],ARRmontoEscalas[MAX_ESCALAS];
    // Arreglos para el reporte
    double totalCreditos[MAX_ALUMNOS]{},totalApagar[MAX_ALUMNOS]{},
            totalIngresos[MAX_CURSOS]{};
    int totalCursos[MAX_ALUMNOS]{}, alumnosMatriculados[MAX_CURSOS]{};
    // Leer datos de los alumnos
    leerDatosAlumnos(ARRcodigoAlumno,ARRescalaAlumno,num_Alumnos,
                    "source/docs/Alumnos.txt");
    //Leer los datos de los cursos
    leerDatosCursos(ARRcodigoCursos,ARRcreditosCursos,num_cursos,\
                    "source/docs/Cursos.txt");
    // Leer el dato de la escala
    leerDatosEscala(ARRmontoEscalas,num_escalas,
                "source/docs/Escalas.txt");
    //Calculos
    calculos(num_Alumnos,num_escalas,num_cursos,ARRcodigoAlumno,
            ARRescalaAlumno,ARRcodigoCursos,ARRcreditosCursos,
            ARRmontoEscalas, totalCreditos,totalApagar,
            totalIngresos, totalCursos, alumnosMatriculados,
            "source/docs/Matricula.txt");
    //Ordenar
    ordenar(num_Alumnos,num_cursos,ARRcodigoAlumno,
            ARRescalaAlumno,ARRcodigoCursos,ARRcreditosCursos,
            totalCreditos,totalApagar,
            totalIngresos, totalCursos, alumnosMatriculados);
    // emitir reporte
    emitirReporte(num_Alumnos,num_cursos,ARRcodigoAlumno,
            ARRescalaAlumno,ARRcodigoCursos,ARRcreditosCursos,
            totalCreditos,totalApagar,
            totalIngresos, totalCursos, alumnosMatriculados,
            "source/docs/Reporte.txt");
    return 0;
}