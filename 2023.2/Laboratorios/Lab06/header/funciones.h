#ifndef FUNCIONES_H
#define FUNCIONES_H
//Solicitud 
void solicitudDeSemestre(int& anio,int& ciclo);
    //Lectura de Alumnos
void lecturaAlumnos(int* ARRcodigoAlumnos,char* ARRescalaAlumnos
                ,int& num_alumnos,const char* nomArch);
    //lectura de Cursos
void ordenarAlumnos(int* ARRcodigoAlumnos,char* ARRescalaAlumnos,
                    int& num_alumnos,int codigoAlumno,char escala);
void lecturaCursos(int* ARRcodigoCursos,double* ARRcreditoCursos,
                int& num_cursos,const char* nomArch);
void ordenarCursos(int* ARRcodigoCursos,double* ARRcreditoCursos,
                int& num_cursos,int codigoCurso,double credito);
    //Lectura de Escalas
void lecturaEscala(int* ARRsemestreEscalas,char* ARRescalaEscalas,
                double* ARRmontoEscalas,int& num_escalas,
                const char* nomArch);
//Actualizamos la matricula
void actualizacionMatricula(double* ARRnum_creditos,int* ARRnum_cursos,
                        double* ARRmonto_pagado,
                        int* ARRcodigoAlumnos,char* ARRescalaAlumnos,
                        int* ARRcodigoCursos,double* ARRcreditoCursos,
                        int* ARRsemestreEscalas,char* ARRescalaEscalas,
                        double* ARRmontoEscalas,int ciclo,int anio,
                        int num_alumnos,int num_cursos,int num_escalas,
                        const char* nomArch,double& total);
void procesarTotal(double* ARRmonto_pagado,int num_alumnos,double& total);
void procesoDecursos(double* ARRnum_creditos,int* ARRnum_cursos,
                    double* ARRmonto_pagado,
                    int* ARRcodigoAlumnos,char* ARRescalaAlumnos,
                    int* ARRcodigoCursos,double* ARRcreditoCursos,
                    int* ARRsemestreEscalas,char* ARRescalaEscalas,
                    double* ARRmontoEscalas,int ciclo,int anio,
                    int num_alumnos,int num_cursos,int num_escalas,
                    ifstream& arch,int codigoAlumno);
int buscarPosicion(int codigo,int* ARRcodigo,int num);
int buscarEscala(int anio,int ciclo,char ecalaAlumno,
                int* ARRsemestreEscalas,char* ARRescalaEscalas,
                int num_escalas);
//emitimos el reporte
void emitirReporte(double* ARRnum_creditos,int* ARRnum_cursos,
                    double* ARRmonto_pagado,
                    int* ARRcodigoAlumnos,char* ARRescalaAlumnos,
                    int* ARRcodigoCursos,double* ARRcreditoCursos,
                    int* ARRsemestreEscalas,char* ARRescalaEscalas,
                    double* ARRmontoEscalas,int ciclo,int anio,
                    int num_alumnos,int num_cursos,int num_escalas,
                    const char* nomNombres, const char* nomApellidos,
                    const char* nomArch,double total);
void modificarTexto(char* nombreAlumno,char* apellidoAlumno);
void linea(ofstream& arch,int num,char signo);
void encabezado(ofstream& arch,int anio,int ciclo);
#endif