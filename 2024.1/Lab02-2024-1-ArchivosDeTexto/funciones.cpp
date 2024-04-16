
/* 
 * File:   funciones.cpp
 * Author: Sergio Manuel Sutta Pinedo 20210646
 *
 * Created on 15 de abril de 2024, 07:03 PM
 */
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "funciones.h"
#define MAX_LINEA 108
//1 HORA CON 15 MINUTOS Y 30 SEGUNDOS en segundos
#define MINIMO 4530
//2 HORAS 30 MINUTOS Y 25 SEGUNDOS en segundos
#define MAXIMO 9025
void emitirReporte(const char* nomArch,const char* reporte){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomArch<<endl;
        exit(1);
    }
    ofstream report(reporte,ios::out);
    if(not report.is_open()){
        cout<<"ERROR: No se pudo abrir "<<reporte<<endl;
        exit(1);
    }
    report.precision(2);
    report<<fixed;
    encabezado(report);
    //Variables
    int dd,mm,aa,dni,hhI,minI,ssI,hhF,minF,ssF,duracion;
    double porcentajeDescuento,tarifa,medicamentos;
    char especialidad,recetas;
    //Variables Estadisticas
    double totoalDeIngresos=0;
    int registrosArchivo=0,registrosProcesados=0;
    while(true){
        lecturaDeDatos(dd,mm,aa,dni,hhI,minI,ssI,hhF,minF,ssF,
                       porcentajeDescuento,tarifa,medicamentos,
                       especialidad,recetas,arch);
        if(arch.eof())break;
        registrosArchivo++;
        //Filtro por la condicion mencionada y saco la duracion en el proceso
        if(condicionYDuracion(hhI,minI,ssI,hhF,minF,ssF,
                              duracion,especialidad)){
            registrosProcesados++;
            impresionDeDatos(dd,mm,aa,dni,hhI,minI,ssI,hhF,minF,ssF,
                           porcentajeDescuento,tarifa,medicamentos,
                           especialidad,recetas,duracion,report,
                           totoalDeIngresos);
        }
    }
    linea(report,MAX_LINEA,'=');
    report<<"Total de ingresos: "<<totoalDeIngresos<<endl;
    linea(report,MAX_LINEA,'=');
    estadisticas(registrosArchivo,registrosProcesados,report);
}
void encabezado(ofstream& report){
    report<<setw(70)<<"EMPRESA DE SALUD S.A."<<endl;
    linea(report,MAX_LINEA,'=');
    report<<left<<setw(5)<<" "<<"REGISTRO DE CITAS DE LAS CONSULTAS MEDICAS EN PEDIATRIA"<<endl
          <<setw(5)<<" "<<"ENTRE 1 HORA CON 15 MINUTOS Y 30 SEGUNDOS Y 2 HORAS 30 MINUTOS Y 25 SEGUNDOS DE DURACION"<<endl;
    linea(report,MAX_LINEA,'=');
    report<<setw(13)<<"Fecha"
          <<setw(11)<<"Paciente"
          <<setw(11)<<"Inicio"
          <<setw(8)<<"Fin"
          <<setw(17)<<"Duracion(H:M:S)"
          <<setw(12)<<"Duracion(H)"
          <<setw(14)<<"% por Seguro"
          <<setw(10)<<"Pago(Cita+medicianas)"<<endl;
    linea(report,MAX_LINEA,'-');
    
}
void linea(ofstream& report,int num,char c){
    for(int i=0;i<num;i++)report<<c;
    report<<endl;
}
void lecturaDeDatos(int& dd,int& mm,int& aa,int& dni,int& hhI,
                    int& minI,int& ssI,int& hhF,int& minF,int& ssF,
                    double& porcentajeDescuento,double& tarifa,
                    double& medicamentos,char &especialidad,
                    char& recetas,ifstream& arch){
    //Variables
    char c;
    arch>>dd;
    if(arch.eof())return;
    arch>>c>>mm>>c>>aa>>dni>>porcentajeDescuento>>hhI>>c
        >>minI>>c>>ssI>>hhF>>c>>minF>>c>>ssF>>tarifa
        >>especialidad>>recetas;
    if(recetas=='S')arch>>medicamentos;
}
void impresionDeDatos(int dd,int mm,int aa,int dni,int hhI,
                    int minI,int ssI,int hhF,int minF,int ssF,
                    double porcentajeDescuento,double tarifa,
                    double medicamentos,char especialidad,
                    char recetas,int duracion,ofstream& report,
                    double& totoalDeIngresos){
    report<<right<<setfill('0')<<setw(2)<<dd<<'/'
          <<setw(2)<<mm<<'/'<<setw(4)<<aa<<setfill(' ')
          <<setw(3)<<" "<<left
          <<setw(10)<<dni<<right<<setfill('0')<<setw(2)<<hhI<<':'
          <<setw(2)<<minI<<':'<<setw(2)<<ssI<<setfill(' ')
          <<setw(2)<<" "<<setfill('0')<<setw(2)<<hhF<<':'
          <<setw(2)<<minF<<':'<<setw(2)<<ssF<<setfill(' ')
          <<setw(5)<<" ";
    impresionDuracion(duracion,report);
    if(recetas=='N')medicamentos=0;
    calculoYImpresionPago(porcentajeDescuento,duracion,tarifa,
                          medicamentos,report,totoalDeIngresos);
}
bool condicionYDuracion(int hhI,int minI,int ssI,int hhF,
                        int minF,int ssF,int& duracion,
                        char especialidad){
    int inicio= converSeg(hhI,minI,ssI);
    int final= converSeg(hhF,minF,ssF);
    duracion=final-inicio;
    if(duracion>=MINIMO and duracion<=MAXIMO and 
       especialidad=='P')return true;
    else return false;
}
int converSeg(int hh,int min,int ss){
    return hh*3600+min*60+ss;
}
void impresionDuracion(int duracion,ofstream& report){
    //Variables
    int hh,min,ss;
    double duracionH;
    convertHMS(hh,min,ss,duracion);
    report<<setfill('0')<<setw(2)<<hh<<':'
          <<setw(2)<<min<<':'<<setw(2)<<ss<<setfill(' ')
          <<setw(9)<<" "<<left;
    duracionH=(double)duracion/3600;
    report<<setw(13)<<duracionH;
}
void convertHMS(int& hh,int& min,int& ss,int duracion){
    hh=(int)duracion/3600;
    duracion-=hh*3600;
    min=(int)duracion/60;
    duracion-=min*60;
    ss=duracion;
}
void calculoYImpresionPago(double porcentajeDescuento,
                           int duracion,double tarifa,
                           double medicamentos, ofstream& report,
                           double& totoalDeIngresos){
    //Variables
    double duracionH=(double)duracion/3600;
    double descuento = (duracionH*tarifa)*(porcentajeDescuento/100)
                        +medicamentos*(porcentajeDescuento/200);
    double pago= (duracionH*tarifa)+medicamentos-descuento;
    totoalDeIngresos+=pago;
    report<<right<<setw(5)<<porcentajeDescuento<<'%'
            <<setw(15)<<right<<pago<<endl;
}
void estadisticas(int registrosArchivo,int registrosProcesados,
                  ofstream& report){
    double porcentaje= (registrosProcesados*100)/registrosArchivo;
    report<<"ESTADISTICAS OBTENIDAS:"<<endl
          <<setw(50)<<left<<"Cantidad de registros del archivo:"<<registrosArchivo<<endl
          <<setw(50)<<"Cantidad de registros procesados:"<<registrosProcesados<<endl
          <<setw(50)<<"Porcentaje de registros procesados:"<<porcentaje<<'%'<<endl;
    linea(report,MAX_LINEA,'=');
    
}