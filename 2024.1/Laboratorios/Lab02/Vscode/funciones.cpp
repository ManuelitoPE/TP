// Author: MAKO
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "header/funciones.h"
#define MAX_LINEA 113
// 2 horas 30 minutos y 25 segundos
#define MAXIMO 9025
// 1 hora 15 minutos y 30 segundos
#define MINIMO 4530
void emitirReporte(const char* nomArch,
                   const char* reporte){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: Se produjo un error al abrir "<<nomArch<<endl;
        exit(1);
    }
    ofstream report(reporte,ios::out);
    if(not report.is_open()){
        cout<<"ERROR: Se produjo un error al abrir "<<reporte<<endl;
        exit(1);
    }
    report.precision(2);
    report<<fixed;
    encabezado(report);
    //Varibles
    int dd,mm,aa,dni,hhI,minI,ssI,hhF,minF,ssF,
        duracion,totalIngresos=0;
    double porcentajeDescuento,tarifa,medicamentos;
    char especialidad,receta;
    //Variables Estadisticas
    int registros=0,registrosP=0;
    while (true){
        lecturaDeDatos(dd,mm,aa,dni,hhI,minI,ssI,
                       hhF,minF,ssF,porcentajeDescuento,
                       tarifa,medicamentos,especialidad,
                       receta,arch);
        if(arch.eof())break;
        registros++;
        if(condicionYCalculoDuracion(hhI,minI,ssI,
            hhF,minF,ssF,duracion,especialidad)){
            registrosP++;
            impresionDatos(dd,mm,aa,dni,hhI,minI,ssI,
                       hhF,minF,ssF,porcentajeDescuento,
                       tarifa,medicamentos,especialidad,
                       receta,duracion,totalIngresos,
                       report);
        }
    }
    linea(report,MAX_LINEA,'=');
    report<<left<<"Total de ingresos: "<<totalIngresos<<endl;
    linea(report,MAX_LINEA,'=');
    estadisticas(registros,registrosP,report);
    
}
void encabezado(ofstream& report){
    report<<setw(65)<<"EMPRESA DE SALUD S.A."<<endl;
    linea(report,MAX_LINEA,'=');
    report<<left<<setw(5)<<" "<<"REGISTRO DE CITAS DE LAS"
          <<" CONSULTAS MEDICAS EN PEDIATRIA"<<endl
          <<setw(5)<<" "<<"ENTRE 1 HORA CON 15 MINUTOS Y 30 SEGUNDOS "
          <<"Y 2 HORAS 30 MINUTOS Y 25 SEGUNDOS DE DURACION"<<endl;
    linea(report,MAX_LINEA,'=');
    report<<setw(13)<<"Fecha"
          <<setw(13)<<"Paciente"
          <<setw(12)<<"Inicio"
          <<setw(8)<<"Fin"
          <<setw(18)<<"Duracion(H:M:S)"
          <<setw(14)<<"Duracion(H)"
          <<setw(15)<<"& por Seguro"
          <<setw(10)<<"Pago(cita+medicinas)"<<endl;
    linea(report,MAX_LINEA,'-');
}
void linea(ofstream& report,int num, char c){
    for (int i = 0; i < num; i++)report<<c;
    report<<endl;
}
void lecturaDeDatos(int& dd,int& mm,int& aa,int& dni,
                    int& hhI,int& minI,int& ssI,
                    int& hhF,int& minF,int& ssF,
                    double& porcentajeDescuento,
                    double& tarifa,double& medicamentos,
                    char& especialidad,char& receta,
                    ifstream& arch){
    char c;
    arch>>dd;
    if(arch.eof())return;
    arch>>c>>mm>>c>>aa>>dni>>porcentajeDescuento
        >>hhI>>c>>minI>>c>>ssI>>hhF>>c>>minF>>c>>ssF
        >>tarifa>>especialidad>>receta;
    if(receta=='S')arch>>medicamentos;
    else medicamentos=0;
}
bool condicionYCalculoDuracion(int hhI,int minI,int ssI,
        int hhF,int minF,int ssF,int& duracion,
        char especialidad){
    int inicio= convertSeg(hhI,minI,ssI);
    int fin= convertSeg(hhF,minF,ssF);
    duracion= fin-inicio;
    if(duracion>=MINIMO and duracion<=MAXIMO and
       especialidad=='P')return true;
    else return false;
}
int convertSeg(int hh,int min,int ss){
    return hh*3600+min*60+ss;
}
void impresionDatos(int dd,int mm,int aa,int dni,
                    int hhI,int minI,int ssI,
                    int hhF,int minF,int ssF,
                    double porcentajeDescuento,
                    double tarifa,double medicamentos,
                    char especialidad,char receta,
                    int duracion,int& totalIngresos,
                    ofstream& report){
    //Variables
    double duracionH;
    report<<right<<setfill('0')<<setw(2)<<dd<<'/'
          <<setw(2)<<mm<<'/'<<setw(4)<<aa<<setfill(' ')
          <<setw(3)<<" "<<left<<setw(12)<<dni
          <<right<<setfill('0')<<setw(2)<<hhI<<':'
          <<setw(2)<<minI<<':'<<setw(2)<<ssI<<setfill(' ')
          <<setw(3)<<" "<<setfill('0')<<setw(2)<<hhF<<':'
          <<setw(2)<<minF<<':'<<setw(2)<<ssF<<setfill(' ')
          <<setw(5)<<" ";
    impresionDuracion(duracion,duracionH,report);
    impresionPago(tarifa,medicamentos,porcentajeDescuento,
                  duracionH,totalIngresos,report);
}
void impresionDuracion(int duracion,double& duracionH,
                       ofstream& report){
    //Varibles
    int hh,min,ss;
    convertHMS(hh,min,ss,duracion);
    duracionH=(double)duracion/3600;
    report<<setfill('0')<<setw(2)<<hh<<':'
          <<setw(2)<<min<<':'<<setw(2)<<ss<<setfill(' ')
          <<setw(10)<<" "<<left
          <<setw(12)<<duracionH;
}
void convertHMS(int& hh,int& min,int& ss,int duracion){
    hh=(int)duracion/3600;
    duracion-=hh*3600;
    min=(int)duracion/60;
    duracion-=min*60;
    ss=duracion;
}
void impresionPago(double tarifa,double medicamentos,
                   double porcentajeDescuento,
                   double duracionH,int& totalIngresos,
                   ofstream& report){
    //Variables
    double descuento = (tarifa*duracionH)*(porcentajeDescuento/100)+
                medicamentos*(porcentajeDescuento/200); 
    double pago= (tarifa*duracionH)+medicamentos-descuento;
    totalIngresos+=pago;
    report<<right<<setw(7)<<porcentajeDescuento<<'%'
          <<setw(19)<<pago<<endl;
}
void estadisticas(int registros,int registrosP,
                  ofstream& report){
    //Variables
    double porcentaje=(double)(registrosP*100)/registros; 
    report<<"ESTADISTICAS OBTENIDAS:"<<endl<<left
          <<setw(50)<<"Cantidad de registros del archivo:"<<registros<<endl
          <<setw(50)<<"Cantidad de registros procesados:"<<registrosP<<endl
          <<setw(50)<<"Porcentaje de registros procesados:"<<porcentaje<<'%'<<endl;
    linea(report,MAX_LINEA,'=');
}