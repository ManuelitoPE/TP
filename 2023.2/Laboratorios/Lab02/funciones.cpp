// Author: MAKO
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "header/funciones.h"
#define MAX_LINEA 110
void emitirReporte(const char* nomArch,const char* Reporte){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: Se produjo un error al abrir "<<nomArch<<endl;
        exit(1);
    }
    ofstream report(Reporte,ios::out);
    if(not report.is_open()){
        cout<<"ERROR: Se produjo un error al abrir "<<Reporte<<endl;
        exit(1);
    }
    report.precision(2);
    report<<fixed;
    encabezado(report);
    // Variables
    int dni,dd,mm,aa,tiempoTotal;
    char sexo,compania;
    //Variables Estadisitcas

    while (true){
        lectura_impresion(arch,report,dni,sexo,compania,
                          dd,mm,aa);
        if(arch.eof())break;
        lectura_impresionCanales(arch,report,tiempoTotal);
        break;
    }
}
void encabezado(ofstream& report){
    report<<right<<setw(60)<<"EMPRESA DE OPINION DE MERCADO S.A."<<endl;
    linea(report,MAX_LINEA,'=');
    report<<setw(10)<<" "<<"REGISTRO DE PREFERENCIAS DE LOS TELEVIDENTES"<<endl;
    linea(report,MAX_LINEA,'=');
    report<<left<<setw(10)<<"DNI Ro."
          <<setw(30)<<"NOMBRE"
          <<setw(12)<<"SEXO"
          <<setw(12)<<"CATEGORIA"
          <<setw(12)<<"COMPANIA"
          <<setw(12)<<"CANAL"
          <<setw(12)<<"RANGO"
          <<setw(12)<<"DURACION"<<endl;
    linea(report,MAX_LINEA,'-');
}
void linea(ofstream& report,int num ,char c){
    for (int i = 0; i < num; i++){
        report<<c;
    }
    report<<endl;
}
void lectura_impresion(ifstream& arch,ofstream& report,int& dni,
                       char& sexo,char& compania,int& dd,int& mm,
                       int& aa){
    char c;
    arch>>dni;
    if(arch.eof())return;
    report<<setw(10)<<dni;
    arch>>sexo>>ws;
    impresionNombre(arch,report);
    arch>>compania>>dd>>c>>mm>>c>>aa;
    impresionSexo(report,sexo);
    impresionCategoria(report,aa);
    impresionCompania(report,compania);
}
void impresionNombre(ifstream& arch,ofstream& report){
    int cont=0;
    char c;
    bool mayuscula=true;
    while(true){
        c=arch.get();
        if(c==' ')break;
        cont++;
        if(c=='_'){
            report.put(' ');
            mayuscula=true;
        }else{
            c+=(mayuscula)?0:'a'-'A';
            report.put(c);
            mayuscula=false;
        }
    }
    report<<setw(30-cont)<<" ";
}
void impresionSexo(ofstream& report,char sexo){
    report<<setw(12);
    if(sexo=='F')report<<"Femenino";
    else report<<"Masculino";
}
void impresionCategoria(ofstream& report,char aa){
    report<<setw(12);
    if(aa>2009)report<<"Menor";
    else if(aa>1998)report<<"Joven";
    else report<<"Adulto";
}
void impresionCompania(ofstream& report,char compania){
    report<<setw(12);
    if(compania=='A')report<<"TVPUCP";
    else if(compania=='B')report<<"CableMas";
    else report<<"TPVision";
}
void lectura_impresionCanales(ifstream& arch,ofstream& report,
                              int& tiempoTotal){
    //Variables 
    int canal,hhI,minI,ssI,hhF,minF,ssF;
    char c;
    while(true){
        c= arch.get();
        if(c=='\n')break;
        arch>>canal>>hhI>>c>>minI>>c>>ssI>>hhF>>c>>minF>>c>>ssF;
        arch.clear();
        report<<endl<<setw(76)<<" "<<setw(10)<<canal
              <<right<<setfill('0')<<setw(2)<<hhI<<':'
              <<setw(2)<<minI<<':'<<setw(2)<<ssI<<'-'
              <<setw(2)<<hhF<<':'<<setw(2)<<minF<<':'
              <<setw(2)<<ssF<<setfill(' ')<<left<<setw(3)<<" ";
    }
}








