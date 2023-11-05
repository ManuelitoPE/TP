//Author:MAKO
#ifndef FUNCIONES_H
#define FUNCIONES_H
#include<fstream>
//Solicitar datos
void solicitarDatosAlUsuario(int& ciclo);
int comprimirDatos(int anio,int cicloREF);
    //Leer datos alumnos
void leerDatosAlumno(int* ARRcodigoAlumno,char** ARRnombreAlumno, 
                    char* ARRescalaAlumno,int& num_alumno,
                    const char* nomArch);
char* leerNombreExacto(ifstream& arch,char delimitador);
void ordenarAlumnos(int* ARRcodigoAlumno,char** ARRnombreAlumno, 
                    char* ARRescalaAlumno,int& num_alumno,
                    int codigo,char* nombre,char escala);
void nombreEdicion(char** ARRnombreAlumno,int num_alumno);
    //Leer datos cursos
void leerDatosCurso(int* ARRcodigoCurso,double* ARRcreditoCurso,
                    int& num_curso,const char* nomArch);
void  ordenarCurso(int* ARRcodigoCurso,double* ARRcreditoCurso,
                   int& num_curso,int curso,double credito);
    //Leer datos escalas 
void leerDatosEscala(int* ARRcicloEscala,char* ARRescalaEscala,
                    double* ARRcostoEscala,int& num_escala,
                    const char* nomArch);
void actualizarDatos(int ciclo,int num_alumno,int num_escala,int num_curso,
                    int* ARRcodigoAlumno,char** ARRnombreAlumno, 
                    char* ARRescalaAlumno,int* ARRcodigoCurso,
                    double *ARRcreditoCurso,int* ARRcicloEscala,
                    char* ARRescalaEscala,double* ARRcostoEscala,
                    int* ARRnum_cursos,double* ARRnum_creditos,
                    double* ARRmonto_pagado,const char* nomArch);
void lecturaDecursos(int ciclo,int num_alumno,int num_escala,int num_curso,
                    int* ARRcodigoAlumno,char** ARRnombreAlumno, 
                    char* ARRescalaAlumno,int* ARRcodigoCurso,
                    double *ARRcreditoCurso,int* ARRcicloEscala,
                    char* ARRescalaEscala,double* ARRcostoEscala,
                    int* ARRnum_cursos,double* ARRnum_creditos,
                    double* ARRmonto_pagado,ifstream& arch,
                    int codigoAlumno,bool& saltar);
int buscarPosicion(int codigoAlumno,int* ARRcodigoAlumno,
                    int num_alumno);
int buscarPosicionEscala(int ciclo,char ARRescalaAlumno,
                        int* ARRcicloEscala,char* ARRescalaEscala,
                        int num_escala);
//Ordenar datos
void ordenarDatos(int num_alumno,int* ARRcodigoAlumno,
                char** ARRnombreAlumno,
                char* ARRescalaAlumno,int* ARRnum_cursos,
                double* ARRnum_creditos,double* ARRmonto_pagado);
void cambiarINT(int& a,int& b);
void cambiarDouble(double& a,double& b);
void cambiarChar(char& a, char& b);
void cambiarString(char* a, char* b);
    //Calcular monto total
void calcularMonto(double& total,double* ARRmonto_pagado,int num_alumno);
void emitirReporte(int ciclo,int num_alumno,int* ARRcodigoAlumno,
                    char** ARRnombreAlumno,
                    char* ARRescalaAlumno,int* ARRnum_cursos,
                    double* ARRnum_creditos,double* ARRmonto_pagado,
                    double total,const char* nomArch);
void descomprimir(int ciclo,int& anio,int& cicloREF);
void encabezado(ofstream& arch,int anio,int cicloREF);
void linea(ofstream& arch, int num, char signo);

#endif /* FUNCIONES_H */

