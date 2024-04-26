/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   funciones.h
 * Author: Sergio Manuel Sutta Pinedo 20210646
 *
 * Created on 22 de abril de 2024, 07:09 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H
void emitirReporte(const char* nomMedicos,const char* nomCitasMedicas,
                   const char* nomReporte);
void encabezado(ofstream& report);
void linea(ofstream& report,int n,char c);
void lecturaDeDatos(int& dd,int& mm,int& aa,int& dni,int& hhI,int& minI,
                    int& ssI,int& hhF,int& minF,int& ssF,
                    int& doctor,double& porcentaje,double& medicina,
                    char& receta,ifstream& archCitas);
void impresionDeDatos(int dd,int mm,int aa,int dni,int hhI,int minI,
                    int ssI,int hhF,int minF,int ssF,
                    int doctor,double porcentaje,double medicina,
                    char receta,int& paciente,double& pacienteGasto,
                    double& total,ifstream& archMedicos,
                    ofstream& report);
void impresionDuracion(double& duracionH,int hhI,int minI,int ssI,
                       int hhF,int minF,int ssF,ofstream& report);
int convertSeg(int hh,int min,int ss);
void convertHMS(int& hh,int& min,int& ss,int duracion);
void impresionDatosMedico(int doctor,double& tarifa,
                          ifstream& archMedicos,ofstream& report);
void impresionNombre(ifstream& archMedicos,ofstream& report,
                     bool mayuscula);
void impresionPago(int& paciente,double duracionH,double tarifa,double porcentaje,
                   double medicina,double& pacienteGasto,
                   double& total,ofstream& report,int dni);
#endif /* FUNCIONES_H */

