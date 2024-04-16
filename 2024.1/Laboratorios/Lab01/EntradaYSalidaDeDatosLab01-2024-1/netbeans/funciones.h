/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   funciones.h
 * Author: Sergio Manuel Sutta Pinedo 20210646
 *
 * Created on 8 de abril de 2024, 07:04 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H
void emitirReporte();
void linea(int num,char c);
void encabezado();
void lecturaDeDatos(int& dd,int& mm,int& aa,int& dni,int& hhI,int& minI,
                    int& ssI,int& hhF,int& minF,int& ssF,
                    double& tarifa,double& monto,char& especialidad,
                    char& receta);
void impresionDeDatos(int dd,int mm,int aa,int dni,int hhI,int minI,
                    int ssI,int hhF,int minF,int ssF,
                    double tarifa,double monto,char especialidad,
                    char receta,double& totalDeIngresos,
                    double& duracionH);
void impresionDuracion(int hhI,int minI,int ssI,int hhF,int minF,
                       int ssF,double& duracionH);
void impresionEspecialidad(char especialidad);
void convertirHMS(int& hh,int& min,int& ss,double duracion);
void impresionPago(double duracionH,double monto,double tarifa,
                   double& totalDeIngresos);
void estadisticasObtenidas(double promedioMedicina,double promedioMedicinaD,
                           double porcentajeNoRecetados,double porcentajePediatria,
                           int pacientesCardiologia,int pacientes350);
#endif /* FUNCIONES_H */

