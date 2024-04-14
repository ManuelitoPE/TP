// Author: MAKO
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "header/funciones.h"
#define MAX_LINEA 132
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
    int dni,dd,mm,aa,tiempoTotal=0;
    char sexo,compania;
    //Variables Estadisitcas
    int televidentes=0,cantMeAdu=0,tiempoMeAdu=0,
        cantMu=0,tiempoPromedio;
    double porcentajeMu;
    while (true){
        lectura_impresion(arch,report,dni,sexo,compania,
                          dd,mm,aa,tiempoTotal);
        if(arch.eof())break;
        televidentes++;
        condicionales(cantMeAdu,tiempoMeAdu,cantMu,
                      aa,sexo,tiempoTotal);
    }
    linea(report,MAX_LINEA,'=');
    calculoEstadisticas(tiempoPromedio,porcentajeMu,televidentes,
                        cantMeAdu,tiempoMeAdu,cantMu);
    estadisticas(televidentes,tiempoPromedio,porcentajeMu,report);
}
void encabezado(ofstream& report){
    report<<right<<setw(80)<<"EMPRESA DE OPINION DE MERCADO S.A."<<endl;
    linea(report,MAX_LINEA,'=');
    report<<setw(10)<<" "<<"REGISTRO DE PREFERENCIAS DE LOS TELEVIDENTES"<<endl;
    linea(report,MAX_LINEA,'=');
    report<<left<<setw(10)<<"DNI Ro."
          <<setw(45)<<"NOMBRE"
          <<setw(12)<<"SEXO"
          <<setw(12)<<"CATEGORIA"
          <<setw(12)<<"COMPANIA"
          <<setw(17)<<"CANAL"
          <<setw(14)<<"RANGO"
          <<setw(12)<<"DURACION"<<endl;
    linea(report,MAX_LINEA,'-');
}
void linea(ofstream& report,int num ,char c){
    for (int i = 0; i < num; i++)report<<c;
    report<<endl;
}
void lectura_impresion(ifstream& arch,ofstream& report,int& dni,
                       char& sexo,char& compania,int& dd,int& mm,
                       int& aa,int& tiempoTotal){
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
    lectura_impresionCanales(arch,report,tiempoTotal);
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
    report<<setw(45-cont)<<" ";
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
    tiempoTotal=0;
    while(true){
        c= arch.get();
        if(c=='\n')break;
        arch>>canal>>hhI>>c>>minI>>c>>ssI>>hhF>>c>>minF>>c>>ssF;
        arch.clear();
        report<<endl<<setw(92)<<" "<<setw(10)<<canal
              <<right<<setfill('0')<<setw(2)<<hhI<<':'
              <<setw(2)<<minI<<':'<<setw(2)<<ssI<<'-'
              <<setw(2)<<hhF<<':'<<setw(2)<<minF<<':'
              <<setw(2)<<ssF<<setfill(' ')<<left<<setw(3)<<" ";
        calculoImpresionDuracion(report,hhI,minI,ssI,hhF,minF,ssF,
                                tiempoTotal);
    }
    //Duracion Total
    int hh,min,ss;
    convertirHMS(hh,min,ss,tiempoTotal);
    report<<setw(107)<<" "<<"TIEMPO TOTAL : "<<right<<setfill('0')<<setw(2)<<hh<<':'
          <<setw(2)<<min<<':'<<setw(2)<<ss<<setfill(' ')
          <<endl<<left;
}
void calculoImpresionDuracion(ofstream& report,int hhI,int minI,int ssI,int hhF,
                         int minF,int ssF,int& tiempoTotal){
    int inicio= convertirSeg(hhI,minI,ssI);
    int final= convertirSeg(hhF,minF,ssF);
    int duracion= final-inicio;
    tiempoTotal+=duracion;
    //Convertir HMS
    int hh,min,ss;
    convertirHMS(hh,min,ss,duracion);
    report<<right<<setfill('0')<<setw(2)<<hh<<':'
          <<setw(2)<<min<<':'<<setw(2)<<ss<<setfill(' ')
          <<endl<<left;
}
int convertirSeg(int hh,int min,int ss){
    return hh*3600+min*60+ss;
}
void convertirHMS(int& hh,int& min,int& ss,int tiempoTotal){
    hh=(int)tiempoTotal/3600;
    tiempoTotal-=hh*3600;
    min=(int)tiempoTotal/60;
    tiempoTotal-=min*60;
    ss=tiempoTotal;
}
void condicionales(int& cantMeAdu,int& tiempoMeAdu,int& cantMu,
                   int aa,char sexo,int tiempoTotal){
    if(aa<1988 or aa>2009){
        cantMeAdu++;
        tiempoMeAdu+=tiempoTotal;
    }
    if(sexo=='F')cantMu++;
}
void calculoEstadisticas(int& tiempoPromedio,double& porcentajeMu,
                         int televidentes,int cantMeAdu,
                         int tiempoMeAdu,int cantMu){
    tiempoPromedio= (int)tiempoMeAdu/cantMeAdu;
    porcentajeMu=(double)(cantMu*100)/televidentes;
}
void estadisticas(int televidentes,int tiempoPromedio,
                  double porcentajeMu,ofstream& report){
    // Variables
    int hh,min,ss;
    convertirHMS(hh,min,ss,tiempoPromedio);
    report<<setw(5)<<" "<<setw(91)<<"ESTADISTICAS OBTENIDAS:"<<endl
          <<setw(5)<<" "<<setw(92)<<"Cantidad de televidentes registrados"<<televidentes<<endl
          <<setw(5)<<" "<<setw(87)<<"Tiempo promedio que ven los menores y adultos"<<right<<setfill('0')<<setw(2)<<hh<<':'
          <<setw(2)<<min<<':'<<setw(2)<<ss<<setfill(' ')<<endl<<left
          <<setw(5)<<" "<<setw(89)<<"Porcentaje de mujeres que ve TVPUCP"<<porcentajeMu<<'%'<<endl;
    linea(report,MAX_LINEA,'=');
}




