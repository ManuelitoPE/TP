/* 
 * File:   funciones.cpp
 * Author: Sergio Manuel Sutta Pinedo 20210646
 *
 * Created on 22 de abril de 2024, 07:08 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "funciones.h"
#define MAX_LINEA 156
void emitirReporte(const char* nomMedicos,const char* nomCitasMedicas,
                   const char* nomReporte){
    ifstream archMedicos(nomMedicos,ios::in);
    if(not archMedicos.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomMedicos<<endl;
        exit(1);
    }
    ifstream archCitas(nomCitasMedicas,ios::in);
    if(not archCitas.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomCitasMedicas<<endl;
        exit(1);
    }
    ofstream report(nomReporte,ios::out);
    if(not report.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomReporte<<endl;
        exit(1);
    }
    report.precision(2);
    report<<fixed;
    encabezado(report);
    //Variables
    int dd,mm,aa,dni,hhI,minI,ssI,hhF,minF,ssF,doctor;
    double porcentaje,medicina;
    char receta;
    //Variables de Resumen
    int paciente;
    double total=0,pacienteGasto=0;
    while(true){
        lecturaDeDatos(dd,mm,aa,dni,hhI,minI,ssI,hhF,minF,ssF,
                       doctor,porcentaje,medicina,receta,
                       archCitas);
        if(archCitas.eof())break;
        impresionDeDatos(dd,mm,aa,dni,hhI,minI,ssI,hhF,minF,ssF,
                         doctor,porcentaje,medicina,receta,
                         paciente,pacienteGasto,total,archMedicos,
                         report);
    }
    linea(report,MAX_LINEA,'=');
    report<<"Total de ingresos: "<<total<<endl;
    linea(report,MAX_LINEA,'=');
    report<<setw(50)<<"Paciente que mas gasto en una cita medica: "<<paciente<<endl
          <<setw(50)<<"Monto gastado: "<<pacienteGasto<<endl;
    linea(report,MAX_LINEA,'=');
    
}
void encabezado(ofstream& report){
    report<<setw(80)<<"EMPRESA DE SALUD S.A."<<endl;
    linea(report,MAX_LINEA,'=');
    report<<setw(80)<<"REGISTRO DE CITAS MEDICAS"<<endl;
    linea(report,MAX_LINEA,'=');
    report<<left<<setw(13)<<"Fecha"
          <<setw(12)<<"Paciente"
          <<setw(12)<<"Inicio"
          <<setw(9)<<"Fin"
          <<setw(12)<<"Duracion"
          <<setw(16)<<"% por Seguro"
          <<setw(40)<<"Medico"
          <<setw(20)<<"Especialidad"
          <<setw(12)<<"Pago (cita+medicinas)"<<endl;
    linea(report,MAX_LINEA,'-');
}
void linea(ofstream& report,int n,char c){
    for(int i=0;i<n;i++)report<<c;
    report<<endl;
}
void lecturaDeDatos(int& dd,int& mm,int& aa,int& dni,int& hhI,int& minI,
                    int& ssI,int& hhF,int& minF,int& ssF,
                    int& doctor,double& porcentaje,double& medicina,
                    char& receta,ifstream& archCitas){
    //Variables
    char c;
    archCitas>>dd;
    if(archCitas.eof())return;
    archCitas>>c>>mm>>c>>aa>>dni>>porcentaje>>hhI>>c>>minI>>c>>ssI
             >>hhF>>c>>minF>>c>>ssF>>doctor>>receta;
    if(receta=='S')archCitas>>medicina;
    else medicina=0;
}
void impresionDeDatos(int dd,int mm,int aa,int dni,int hhI,int minI,
                    int ssI,int hhF,int minF,int ssF,
                    int doctor,double porcentaje,double medicina,
                    char receta,int& paciente,double& pacienteGasto,
                    double& total,ifstream& archMedicos,
                    ofstream& report){
    //Variables
    double duracionH,tarifa;
    report<<right<<setfill('0')<<setw(2)<<dd<<'/'<<setw(2)<<mm<<'/'
          <<setw(4)<<aa<<setfill(' ')<<setw(3)<<" "<<left
          <<setw(11)<<dni<<right<<setfill('0')<<setw(2)<<hhI<<':'
          <<setw(2)<<minI<<':'<<setw(2)<<ssI<<setfill(' ')<<setw(3)<<" "
          <<setfill('0')<<setw(2)<<hhF<<':'
          <<setw(2)<<minF<<':'<<setw(2)<<ssF<<setfill(' ')<<setw(3)<<" "
          <<left;
    //Sacamos duracinH y imprimimos la duracion
    impresionDuracion(duracionH,hhI,minI,ssI,hhF,minF,ssF,report);
    report<<setw(5)<<right<<porcentaje<<'%'<<setw(6)<<" "<<left;
    //Buscamos al medico y sacamos su tarifa
    impresionDatosMedico(doctor,tarifa,archMedicos,report);
    //Imprimimos el apgo
    impresionPago(paciente,duracionH,tarifa,porcentaje,medicina,pacienteGasto,
                  total,report,dni);
}
void impresionDuracion(double& duracionH,int hhI,int minI,int ssI,
                       int hhF,int minF,int ssF,ofstream& report){
    //Variables
    int hh,min,ss;
    int inicio= convertSeg(hhI,minI,ssI);
    int final= convertSeg(hhF,minF,ssF);
    int duracion= final-inicio;
    duracionH= (double)duracion/3600;
    convertHMS(hh,min,ss,duracion);
    report<<right<<setfill('0')<<setw(2)<<hh<<':'<<setw(2)<<min<<':'
          <<setw(2)<<ss<<setfill(' ')<<setw(8)<<" "<<left;
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
void impresionDatosMedico(int doctor,double& tarifa,
                          ifstream& archMedicos,ofstream& report){
    //Variables
    int aux_doctor;
    //Receteamos el cursor
    archMedicos.clear();
    archMedicos.seekg(0,ios::beg);
    while(true){
        archMedicos>>aux_doctor;
        if(archMedicos.eof())break;
        if(aux_doctor==doctor){
            archMedicos>>ws;
            impresionNombre(archMedicos,report,false);
            archMedicos>>ws;
            impresionNombre(archMedicos,report,true);
            archMedicos>>tarifa;
            break;
        }else while(archMedicos.get()!='\n');
    }
}
void impresionNombre(ifstream& archMedicos,ofstream& report,
                     bool mayuscula){
    //Varibles
    int cont=0;
    //Primera letra despues de un espacio
    bool primera=true;
    char c;
    while(true){
        c=archMedicos.get();
        if(c==' ')break;
        if(c=='_'){
                report<<' ';
                primera=true;
        }else{
            if(mayuscula)c-=(c>='A' and c<='Z')?0:'a'-'A';
            else {
                c+=(primera and c>='A' and c<='Z')?0:'a'-'A';
                primera=false;
            }
            report<<c;
        }
        cont++;
    }
    if(mayuscula)report<<setw(28-cont)<<" ";
    else report<<setw(40-cont)<<" ";
}
void impresionPago(int& paciente,double duracionH,double tarifa,double porcentaje,
                   double medicina,double& pacienteGasto,
                   double& total,ofstream& report,int dni){
   //Variables
    double costoCita= tarifa*duracionH;
    double descuento= costoCita*(porcentaje/100)+ medicina*(porcentaje/200);
    double gasto= costoCita+medicina-descuento;
    total+=gasto;
    if(gasto>pacienteGasto){
        pacienteGasto=gasto;
        paciente=dni;
    }
    report<<gasto<<endl;
}