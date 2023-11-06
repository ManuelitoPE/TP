//Author:MAKO
#include <iostream>
#include<iomanip>
#include<cstring>
using namespace std;
#include "../header/funciones.h"
#define MAX_ALUMNO 100
#define MAX_CURSO 50
#define MAX_ESCALA 30
/*
 * 
 */
int main(int argc, char** argv) {
    //variables
    int ciclo;
    double total=0;
    //Cantidad de datos
    int num_alumno=0,num_escala=0,num_curso=0;
    //Arreglos para alumnoss
    int ARRcodigoAlumno[MAX_ALUMNO];
    char* ARRnombreAlumno[MAX_ALUMNO], ARRescalaAlumno[MAX_ALUMNO];
    //Arreglos para cursos
    int ARRcodigoCurso[MAX_CURSO];
    double ARRcreditoCurso[MAX_CURSO];
    //Arreglos para escalas 
    int ARRcicloEscala[MAX_ESCALA];
    char ARRescalaEscala[MAX_ESCALA];
    double ARRcostoEscala[MAX_ESCALA];
    //ARREGLOS PARA EL INFORME
    int ARRnum_cursos[MAX_ALUMNO]{};
    double ARRnum_creditos[MAX_ALUMNO]{},ARRmonto_pagado[MAX_ALUMNO]{};
    //Solicitar datos
    solicitarDatosAlUsuario(ciclo);
    //Leer datos alumnos
    leerDatosAlumno(ARRcodigoAlumno, ARRnombreAlumno, 
                    ARRescalaAlumno,num_alumno,
                    "source/docs/Alumnos.txt");
    //Leer datos cursos
    leerDatosCurso(ARRcodigoCurso,ARRcreditoCurso,num_curso,
                   "source/docs/Cursos.txt");
    //Leer datos escalas 
    leerDatosEscala(ARRcicloEscala,ARRescalaEscala,ARRcostoEscala,
                    num_escala,"source/docs/Escalas.txt");
    //Completar datos 
    actualizarDatos(ciclo,num_alumno,num_escala,num_curso,
                    ARRcodigoAlumno,ARRnombreAlumno, ARRescalaAlumno,
                    ARRcodigoCurso,ARRcreditoCurso,ARRcicloEscala,
                    ARRescalaEscala,ARRcostoEscala,ARRnum_cursos,
                    ARRnum_creditos,ARRmonto_pagado,"source/docs/Matricula.txt");
    // Ordenar datos
    ordenarDatos(num_alumno,ARRcodigoAlumno,ARRnombreAlumno,
                  ARRescalaAlumno,ARRnum_cursos,
                  ARRnum_creditos,ARRmonto_pagado);
    //Calcular monto total
    calcularMonto(total,ARRmonto_pagado,num_alumno);
    //Emitir reporte
    emitirReporte(ciclo,num_alumno,ARRcodigoAlumno,ARRnombreAlumno,
                  ARRescalaAlumno,ARRnum_cursos,
                  ARRnum_creditos,ARRmonto_pagado,total,
                  "source/docs/ReporteDePagoPorAlumno.txt");
   
     return 0;
}

