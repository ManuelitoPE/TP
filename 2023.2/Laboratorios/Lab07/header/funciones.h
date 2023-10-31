/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   funciones.h
 * Author: Sergio Manuel Sutta Pinedo 20210646
 *
 * Created on 30 de octubre de 2023, 07:08 PM
 */

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
                    double* ARRmonto_pagado,ifstream& arch
                    ,int codigoAlumno,bool& saltar);
int buscarPosicion(int codigoAlumno,int* ARRcodigoAlumno,
                        int num_alumno);
int buscarPosicionEscala(int ciclo,char ARRescalaAlumno,
                 int* ARRcicloEscala,char* ARRescalaEscala,
                 int num_escala);
void emitirReporte(int ciclo,int num_alumno,int* ARRcodigoAlumno,
                   char** ARRnombreAlumno,
                   char* ARRescalaAlumno,int* ARRnum_cursos,
                   double* ARRnum_creditos,double* ARRmonto_pagado,
                     const char* nomArch);
void descomprimir(int ciclo,int& anio,int& cicloREF);
#endif /* FUNCIONES_H */

