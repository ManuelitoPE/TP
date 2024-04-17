//Author: MAKO
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "header/funciones.h"
#define MAX_LINEA 118
void emitirReporte(const char* Canales,
                   const char* Registro,
                   const char* Televidentes,
                   const char* reporte){
    ifstream archCanales(Canales,ios::in);
    if(not archCanales.is_open()){
        cout<<"ERROR: No se pudo abrir "<<Canales<<endl;
        exit(1);
    }
    ifstream archRegistro(Registro,ios::in);
    if(not archRegistro.is_open()){
        cout<<"ERROR: No se pudo abrir "<<Registro<<endl;
        exit(1);
    }
    ifstream archTelevidentes(Televidentes,ios::in);
    if(not archTelevidentes.is_open()){
        cout<<"ERROR: No se pudo abrir "<<Televidentes<<endl;
        exit(1);
    }
    ofstream report(reporte,ios::out);
    if(not report.is_open()){
        cout<<"ERROR: No se pudo abrir "<<reporte<<endl;
        exit(1);
    }
    encabezado(report);
    report.precision(2);
    report<<fixed;
    //Variables
    int canal,totalPersonas=0,duracionTotal=0,contMenores=0,
        contJovenes=0,contAdultos=0;
    while(true){
        lecturaYImpresionCanal(archCanales,report,canal);
        if(archCanales.eof())break;
        //Reiniciamos el contador
        totalPersonas=0; duracionTotal=0; contMenores=0;
        contJovenes=0; contAdultos=0; 
        impresionPersonas(canal,totalPersonas,duracionTotal,
                          contMenores,contJovenes,contAdultos,
                          archRegistro,archTelevidentes,report);
        estadisticas(totalPersonas,duracionTotal,contMenores,
                     contAdultos,contJovenes,report);
    }

}
void encabezado(ofstream& report){
    linea(report,MAX_LINEA,'=');
    report<<setw(80)<<"EMPRESA DE OPINION DE MERCADO TP S.A."<<endl
          <<setw(80)<<"AVENIDA UNIVERSITARIA 1234 SAN MIGUEL"<<endl
          <<setw(67)<<"LIMA-PERU"<<endl;
    linea(report,MAX_LINEA,'=');
    report<<setw(70)<<"REGISTRO DE PREFERENCIAS DE LOS TELEVIDENTES "
          <<"POR CANAL DE PREFERENCIA"<<endl;
    linea(report,MAX_LINEA,'=');
}
void linea(ofstream& report,int n,char c){
    for (int i = 0; i < n; i++)report<<c;
    report<<endl; 
}
void lecturaYImpresionCanal(ifstream& archCanales,
                            ofstream& report,int& canal){
    //Variables 
    char c;
    archCanales>>canal;
    if(archCanales.eof())return;
    archCanales>>ws>>c;
    report<<left<<"CANAL: ";
    impresionCanalNombre(archCanales,report);
    report<<"NUMERO: "<<canal<<endl;
    encabezado2(report);

}
void encabezado2(ofstream& report){
    report<<"LISTADO DE TELEVIDENTES QUE VEN EL CANAL:"<<endl;
    linea(report,MAX_LINEA,'-');
    report<<setw(10)<<"DNI No."
          <<setw(41)<<"NOMBRE"
          <<setw(12)<<"SEXO"
          <<setw(12)<<"CATEGORIA"
          <<setw(20)<<"COMPANIA"
          <<setw(15)<<"RANGO"
          <<setw(10)<<"DURACION"<<endl;
    linea(report,MAX_LINEA,'-');         
}
void impresionCanalNombre(ifstream& archCanales,ofstream& report){
    //Varibles
    int cont=0;
    while (true){
        char c= archCanales.get();
        if(c=='/')break;
        if(c!=' ' and c!='&')c-=('A'<=c and 'Z'>=c)?0:'a'-'A';      
        report<<c;
        cont++;
    }
    report<<setw(40-cont)<<" "; 
}
void impresionPersonas(int canal,int& totalPersonas,int& duracionTotal,
                       int& contMenores,int& contJovenes,int& contAdultos,
                       ifstream& archRegistro,ifstream& archTelevidentes,
                       ofstream& report){
    //Variables
    int dni,auxCanal,hhI,minI,ssI,hhF,minF,ssF;
    char c;
    //Reiniciar Registro
    archRegistro.clear();
    archRegistro.seekg(0,ios::beg);
    while (true){
        archRegistro>>dni;
        if(archRegistro.eof())break;
        //Lectura de canales 
        while (archRegistro.get()!='\n'){
            archRegistro>>auxCanal>>hhI>>c>>minI>>c>>ssI
                        >>hhF>>c>>minF>>c>>ssF;
            if(auxCanal==canal){
                totalPersonas++;
                impresionDatos(dni,hhI,minI,ssI,hhF,minF,ssF,
                               duracionTotal,contMenores,
                               contJovenes,contAdultos,
                               archTelevidentes,report);
            }
        }
    }
    linea(report,MAX_LINEA,'-');         
}
void impresionDatos(int dni,int hhI,int minI,int ssI,int hhF,
                    int minF,int ssF,int& duracionTotal,
                    int& contMenores,int& contJovenes,
                    int& contAdultos,ifstream& archTelevidentes,
                    ofstream& report){
    //Variables
    int auxDni,dd,mm,aa;
    char sexo,compania,c;
    //Reiniciar Telecidentes
    archTelevidentes.clear();
    archTelevidentes.seekg(0,ios::beg);
    while(true){
        archTelevidentes>>auxDni;
        if(archTelevidentes.eof())break;
        if(auxDni==dni){
            report<<setw(10)<<dni;
            archTelevidentes>>ws;
            impresionTelevidenteNombre(archTelevidentes,
                                       report);
            archTelevidentes>>dd>>c>>mm>>c>>aa>>sexo>>compania;
            impresionSexo(report,sexo);
            impresionCategoria(report,aa,contAdultos,contJovenes,
                               contMenores);
            impresionCompania(report,compania);
            impresionRangoYDuracion(hhI,minI,ssI,hhF,minF,ssF,
                                    duracionTotal,report);
            break;
        }else while(archTelevidentes.get()!='\n');
    }
}
void impresionTelevidenteNombre(ifstream& archTelevidentes,
                                ofstream& report){
    //Variables
    int cont=0,espacios=0;
    while (true){
        char c=archTelevidentes.get();
        if(c==' ')break;
        else if(c=='_'){
            report<<' ';
            espacios++;
        }else{
            cont++;
            c+=(cont%2!=0)?0:'a'-'A';
            report<<c;
        }
    }
    report<<setw(40-cont-espacios)<<" ";
}
void impresionSexo(ofstream& report,char sexo){
    report<<setw(14);
    if(sexo=='F')report<<"Femenino";
    else report<<"Masculino";
}

void impresionCategoria(ofstream& report,int aa,
                        int& contAdultos,int& contJovenes,
                        int& contMenores){
    report<<setw(11);
    if(aa>2009){
        report<<"Menor";
        contMenores++;
    }else if(aa>1988){
        report<<"Joven";
        contJovenes++;
    }else{
        report<<"Adulto";
        contAdultos++;
    }
}
void impresionCompania(ofstream& report,char compania){
    report<<setw(14);
    if(compania=='A')report<<"TVPUCP";
    else if(compania=='B')report<<"CableMas";
    else report<<"TPVision";
}
void impresionRangoYDuracion(int hhI,int minI,int ssI,int hhF,
                             int minF,int ssF,
                             int& duracionTotal,ofstream& report){
    //Variables
    int hh,min,ss;
    int inicio=convertSeg(hhI,minI,ssI);
    int fin=convertSeg(hhF,minF,ssF);
    int duracion=fin-inicio;
    convertHMS(hh,min,ss,duracion);
    duracionTotal+=duracion;
    report<<right<<setfill('0')<<setw(2)<<hhI<<':'
          <<setw(2)<<minI<<':'<<setw(2)<<ssI<<'-'
          <<setw(2)<<hhF<<':'<<setw(2)<<minF<<':'
          <<setw(2)<<ssF<<setfill(' ')<<setw(4)<<" "
          <<setfill('0')<<setw(2)<<hh<<':'
          <<setw(2)<<min<<':'<<setw(2)<<ss<<left
          <<setfill(' ')<<endl;
}
int convertSeg(int hh,int min,int ss){
    return hh*3600+min*60+ss;
}
void convertHMS(int& hh,int& min,int& ss,int duracion){
    hh=(int)duracion/3600;
    duracion-=hh*3600;
    min=(int)duracion/60;
    duracion-=min*60;
    ss=duracion;
}
void estadisticas(int totalPersonas,int duracionTotal,int contMenores,
                  int contAdultos,int contJovenes,ofstream& report){
    int hh,min,ss,duracionPromedio;
    double porMenores,porJovenes,porAdultos;
    porAdultos= (double)(contAdultos*100)/totalPersonas;
    porJovenes= (double)(contJovenes*100)/totalPersonas;
    porMenores= (double)(contMenores*100)/totalPersonas;
    duracionPromedio=(int)duracionTotal/totalPersonas;
    convertHMS(hh,min,ss,duracionPromedio);
    report<<"PROMEDIO DE TIEMPO QUE VEN LOS TELEVIDENTES EL CANAL: "
          <<right<<setfill('0')<<setw(2)<<hh<<':'
          <<setw(2)<<min<<':'<<setw(2)<<ss<<endl<<left
          <<setfill(' ')<<"PORCENTAJE SEGUN SU EDAD:"<<endl
          <<setw(10)<<" "<<setw(20)<<"MENORES:"<<porMenores<<'%'<<endl
          <<setw(10)<<" "<<setw(20)<<"JOVENES:"<<porJovenes<<'%'<<endl
          <<setw(10)<<" "<<setw(20)<<"ADULTOS:"<<porAdultos<<'%'
          <<endl<<"TOTAL DE PERSONAS QUE VEN EL CANAL: "<<totalPersonas
          <<endl;
    linea(report,MAX_LINEA,'=');         
}