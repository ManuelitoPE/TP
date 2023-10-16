#ifndef FUNCIONES_H
#define FUNCIONES_H
#include<fstream>
    // Leer datos de los alumnos
void leerDatosAlumnos(int* ARRcodigoAlumno,int* ARRescalaAlumno,
                    int& num_Alumnos,const char* nomArch);
    //Leer los datos de los cursos
void leerDatosCursos(int* ARRcodigoCursos,double* ARRcreditosCursos,
                    int& num_cursos,const char*);
    // Leer el dato de la escala
void leerDatosEscala(double* ARRmontoEscalas,int& num_escalas,
                const char* nomArch);
    //Calculos
void calculos(int num_Alumnos,int num_escalas,int num_cursos,
            int* ARRcodigoAlumno,int* ARRescalaAlumno,
            int* ARRcodigoCursos,double* ARRcreditosCursos,
            double* ARRmontoEscalas,double* totalCreditos,
            double* totalApagar,double* totalIngresos,
            int* totalCursos, int* alumnosMatriculados
            ,const char* nomArch);
int buscar(int codigo,int* ARR,int num);
    //Ordenar
void ordenar(int num_Alumnos,int num_cursos,int* ARRcodigoAlumno,
            int* ARRescalaAlumno,int* ARRcodigoCursos,
            double* ARRcreditosCursos,double* totalCreditos,
            double* totalApagar,double* totalIngresos, 
            int* totalCursos,int*  alumnosMatriculados);
void cambiarInt(int& a, int& b);
void cambiarDouble(double& a,double& b);
    // emitir reporte
void emitirReporte(int num_Alumnos,int num_cursos,int* ARRcodigoAlumno,
            int* ARRescalaAlumno,int* ARRcodigoCursos,
            double* ARRcreditosCursos,double* totalCreditos,
            double* totalApagar,double* totalIngresos, 
            int* totalCursos,int*  alumnosMatriculados,
            const char* nomArch);
void linea(ofstream& arch,int num, char signo);

#endif