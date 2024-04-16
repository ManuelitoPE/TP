/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   funciones.h
 * Author: Sergio Manuel Sutta Pinedo
 *
 * Created on 15 de abril de 2024, 07:08 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H
void emitirReporte(const char* nomArch,const char* reporte);
void encabezado(ofstream& report);
void linea(ofstream& report,int num,char c);
void lecturaDeDatos(int& dd,int& mm,int& aa,int& dni,int& hhI,
                    int& minI,int& ssI,int& hhF,int& minF,int& ssF,
                    double& porcentajeDescuento,double& tarifa,
                    double& medicamentos,char &especialidad,
                    char& recetas,ifstream& arch);
void impresionDeDatos(int dd,int mm,int aa,int dni,int hhI,
                    int minI,int ssI,int hhF,int minF,int ssF,
                    double porcentajeDescuento,double tarifa,
                    double medicamentos,char especialidad,
                    char recetas,int duracion,ofstream& report,
                    double& totoalDeIngresos);
bool condicionYDuracion(int hhI,int minI,int ssI,int hhF,
                        int minF,int ssF,int& duracion,
                        char especialidad);
int converSeg(int hhI,int minI,int ssI);
void impresionDuracion(int duracion,ofstream& report);
void convertHMS(int& hh,int& min,int& ss,int duracion);
void calculoYImpresionPago(double porcentajeDescuento,
                           int duracion,double tarifa,
                           double medicamentos, ofstream&report,
                           double& totoalDeIngresos);
void estadisticas(int registrosArchivo,int registrosProcesados,
                  ofstream& report);

#endif /* FUNCIONES_H */

