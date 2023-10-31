#ifndef FUNCIONES_H
#define FUNCIONES_H
//Solicitud 
void solicitudDeSemestre(int& anio,int& ciclo);
    //Lectura de Alumnos
void lecturaAlumnos(int* ARRcodigoAlumnos,char* ARRescalaAlumnos
                ,int& num_alumnos,const char* nomArch);
    //lectura de Cursos
void lecturaCursos(int* ARRcodigoCursos,double* ARRcreditoCursos,
                int& num_cursos,const char* nomArch);
    //Lectura de Escalas
void lecturaEscala(int* ARRsemestreEscalas,char* ARRescalaEscalas,
                double* ARRmontoEscalas,int& num_alumnos,
                const char* nomArch);
    
#endif