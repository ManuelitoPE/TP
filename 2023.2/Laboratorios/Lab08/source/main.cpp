//Author: MAKO
#include<iostream>
#include<iomanip>
#include <cstdlib>
#include <string.h>
using namespace std;
#include "../header/Alumno.h"
#include "../header/Curso.h"
#include "../header/Escala.h"
#include "../header/funciones.h"

#define MAX_ALUMNOS 100
#define MAX_CURSOS 100
#define MAX_ESCALAS 30

int main(int argc, char** argv) {
    //ESTRUCTURAS
    struct Alumno alumnos[MAX_ALUMNOS]{};
    struct Curso cursos[MAX_CURSOS]{};
    struct Escala escalas[MAX_ESCALAS]{};
    //NUMERO DE DATOS DE LAS ESTRUCTURAS
    int numAlumnos=0,numCursos=0,numEscalas=0;
    //VARIABLES
    double total=0;
    int anio,ciclo;
    //SOLICITAR DATOS
    solicarDatosUsuario(anio,ciclo);
    //LECTURA DE ALUMNOS
    lecturaAlumnos(alumnos,numAlumnos,"source/docs/Alumnos.csv");
     //LECUTRA DE CURSOS 
    lecturaCursos(cursos,numCursos,"source/docs/Cursos.csv");
    //LECTURA DE ESCALAS
    lecturaEscalas(escalas,numEscalas,"source/docs/Escalas.csv");
    //ACTUALIZACION DE DATOS
    actulizacionDatos(total,alumnos,cursos,escalas,numAlumnos,
                    numCursos,numEscalas,
                    anio,ciclo,"source/docs/Matricula.csv");
    //ORDENANDO DATOS
    ordenarCursos(cursos, numCursos);
    //EMITIMOS EL REPORTE
    emitirReporte(total,anio,ciclo,cursos, numCursos,
                "source/docs/ReporteDePagoPorCurso.txt");
    return 0;
}

