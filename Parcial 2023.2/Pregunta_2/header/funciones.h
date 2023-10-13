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
void descomprimir(int num,int& ano,int& ciclo);

    //Actualizando
void acutlizandoDatos(int num_alumnos,int num_escalas,int num_cursos,
                    int* ARRcodigoAlumnos,int* ARRcodigoCursos,
                    int* ARRanoEscalas,char* ARRescalaAlumnos,
                    char* ARRescalaEscalas,double* ARRcreditoCursos
                    ,double* ARRmontoEscalas,int* ARRcantidad,
                    double* ARRcantCreditos,
                    const char* nomArch);
char busquedaEscala(int* ARRcodigoAlumnos,char* ARRescalaAlumnos,
                               int codigoAlumno,int num_alumnos);
int busquedaPosicion_escala(int anoREF,int cicloREF,
                        char escalaREF,int* ARRanoEscalas,char* 
                        ARRescalaEscalas,int num_escalas);
void sumaCantidadCreditos(double* ARRcantCreditos,int posicion_escala
                        ,int* ARRcodigoCursos,double* ARRcreditoCursos,
                        ifstream& arch,int num_cursos);
int buscarCredito(int* ARRcodigoCursos,int codigoREF,int num_cursos);
    //Ordenamos los datos
void ordenar(int* ARRanoEscalas,char* ARRescala,
            int* ARRcantidad,double* ARRmontoEscalas
            ,double* ARRcantCreditos,
            int num_escalas);
void cambiarInt(int& a,int& b);
void cambiarDouble(double& a,double& b);
void cambiarChar(char& a,char& b);
    //Emitir el reporte final
void reporte(int* ARRanoEscalas,char* ARRescala,
            int* ARRcantidad,double* ARRmontoEscalas
            ,double* ARRcantCreditos,
            int num_escalas
            ,const char* nomArch);
void linea(ofstream& arch,int num,char signo);
#endif