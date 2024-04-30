
/* 
 * File:   main.cpp
 * Author: Sergio Manuel Sutta Pinedo 20210646
 *
 * Created on 29 de abril de 2024, 07:05 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "funciones.h"
#define MAX_LINEA 100
//Maxima 2 horas 31 minutos 25 segundos
#define MAX_DURACION 9085

void emitirReporte(const char* nomCitasMedicas,const char* nomMedicinas,
                   const char* nomMedicos,const char* nomReporte){
    ifstream archCitasMedicas(nomCitasMedicas,ios::in);
    if(not archCitasMedicas.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomCitasMedicas<<endl;
        exit(1);
    }
    ifstream archMedicinas(nomMedicinas,ios::in);
    if(not archMedicinas.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomMedicinas<<endl;
        exit(1);
    }
    ifstream archMedicos(nomMedicos,ios::in);
    if(not archMedicos.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomMedicos<<endl;
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
    int codigoMedico;
    double tarifa;
    //Variables de Resumen
    int codMedicoAporte;
    double totalMedico=0;
    while(true){
        archMedicos>>codigoMedico;
        if(archMedicos.eof())break;
        report<<left<<setw(20)<<"Codigo del medico: "<<codigoMedico<<endl
              <<setw(20)<<"Nombre del medico: ";
        archMedicos>>ws; archMedicos.get();
        impresionNombre(report,archMedicos,'/','A'); archMedicos>>ws;
        report<<endl<<setw(20)<<"Especialidad: ";
        impresionNombre(report,archMedicos,' ','B'); archMedicos>>tarifa;
        report<<endl<<setw(20)<<"Tarifa:"<<tarifa<<endl<<"PACIENTES ATENDIDOS"<<endl;
        //Leemos y imprimimos
        lecturaDeCitas(codigoMedico,tarifa,codMedicoAporte,totalMedico,
                       archCitasMedicas,archMedicinas,report);
        report<<"MEDICO QUE APORTO MAS INRESOS "<<endl
              <<"Codigo"<<codMedicoAporte<<endl
              <<"Total ingresado: "<<totalMedico<<endl;
              
             
    }
}
void encabezado(ofstream& report){
    report<<setw(60)<<"EMPRESA DE SALUD S.A."<<endl;
    linea(report,MAX_LINEA,'=');   
    report<<setw(60)<<"REGISTRO DE CITAS MEDICAS"<<endl;
    linea(report,MAX_LINEA,'=');   
}
void linea(ofstream& report,int n,char c){
    for(int i=0;i<n;i++)report<<c;
    report<<endl;
}
void impresionNombre(ofstream& report,ifstream& arch,
                     char delimitador,char aux){
    //Variables
    int cont=0;
    char c;
    while(true){
        c=arch.get();
        if(c==delimitador)break;
        if(c=='_'){
            report<<' ';
            cont++;
            continue;
        }
        report<<c;
        cont++;
    }
    if(aux=='A')report<<setw(50-cont)<<" ";
    else if(aux=='B')report<<setw(25-cont)<<" ";
    else report<<setw(35-cont)<<" ";
}
void sub_encabezado(ofstream& report){
    linea(report,MAX_LINEA,'-');   
    report<<setw(20)<<"Fecha"
          <<setw(20)<<"Paciente"
          <<setw(20)<<"Inicio"
          <<setw(20)<<"Fin"
          <<setw(20)<<"Duracion"
          <<setw(20)<<"% de descuento por Seguro"
          <<setw(20)<<"Pago por cita"<<endl;
    linea(report,MAX_LINEA,'-');   
}
void lecturaDeCitas(int codigoMedico,double tarifa,int& codMedicoAporte,
                    double& totalMedico,ifstream& archCitasMedicas,
                    ifstream& archMedicinas,ofstream& report){
    //Variables
    int dd,mm,aa,dni,hhI,minI,ssI,hhF,minF,ssF,aux_codigoMedico,duracion;
    double porcentaje,duracionH,pagoCita,pagoMedicinasTotal=0,total;
    char c;
            
    //Reiniciamos cursor de archCitas Medicas
    archCitasMedicas.clear();
    archCitasMedicas.seekg(0,ios::beg);
    while(true){
        archCitasMedicas>>dd;
        if(archCitasMedicas.eof())break;
        archCitasMedicas>>c>>mm>>c>>aa>>dni>>porcentaje>>hhI>>c>>minI
                        >>c>>ssI>>hhF>>c>>minF>>c>>ssF>>aux_codigoMedico;
        //Evaluo la duracion y si es el mismo medico y saco la duracion
        if(condicion(codigoMedico,aux_codigoMedico,duracionH,duracion,
                     hhI,minI,ssI,hhF,minF,ssF)){
            impresionDatosCita(dd,mm,aa,dni,hhI,minI,ssI,hhF,minF,ssF,tarifa,
                               duracion,duracionH,porcentaje,pagoCita,report);
            lecturaMedicinasRecetas(archCitasMedicas,archMedicinas,pagoMedicinasTotal,
                                    report,porcentaje);
            total=pagoCita+pagoMedicinasTotal;
            report<<"Pago total: "<<total<<endl;
        }else while(archCitasMedicas.get()!='\n');
        //pago total
    }
    //si es el mayor pago resgistrado
    if(total>totalMedico){
        totalMedico=total;
        codMedicoAporte=codigoMedico;
    }
}
bool condicion(int codigoMedico,int aux_codigoMedico,double& duracionH,
               int& duracion,int hhI,int minI,int ssI,int hhF,int minF,int ssF){
    //Variables
    int inicio= hhI*3600+minI*60+ssI;
    int final= hhF*3600+minF*60+ssF;
    duracion = final-inicio;
    duracionH=(double)duracion/3600;
    if(duracion<MAX_DURACION and codigoMedico==aux_codigoMedico)return true;
    else return false;
}
void impresionDatosCita(int dd,int mm,int aa,int dni,int hhI,int minI,
                        int ssI,int hhF,int minF,int ssF,double tarifa,
                        int& duracion,
                        double duracionH,double porcentaje,double& pagoCita,
                        ofstream& report){
    //Variables
    int hh,min,ss;
    double descuento=((tarifa*duracionH)*porcentaje)/100;
    sub_encabezado(report);
    report<<right<<setfill('0')<<setw(2)<<dd<<'/'<<setw(2)<<mm<<'/'
          <<setw(4)<<aa<<setfill(' ')<<setw(3)<<" "<<left<<setw(10)<<dni
          <<right<<setfill('0')<<setw(2)<<hhI<<':'<<setw(2)<<minI<<':'
          <<setw(2)<<ssI<<setfill(' ')<<setw(3)<<" "<<setfill('0')
          <<setw(2)<<hhF<<':'<<setw(2)<<minF<<':'
          <<setw(2)<<ssF<<setfill(' ')<<setw(3)<<" "<<left;
    convertHMS(hh,min,ss,duracion);
    report<<right<<setfill('0')<<setw(2)<<hh<<':'<<setw(2)<<min<<':'
          <<setw(2)<<ss<<setfill(' ')<<setw(5)<<" "<<porcentaje<<'%';
    pagoCita= (tarifa*duracionH)-descuento;
    report<<setw(10)<<pagoCita<<endl<<left
          <<"Medicinas Recetadas: "<<endl;
}
void convertHMS(int& hh,int& min,int& ss,int duracion){
    hh=(int)duracion/3600;
    duracion-=hh*3600;
    min=(int)duracion/60;
    duracion-=min*60;
    ss=duracion;
}
void lecturaMedicinasRecetas(ifstream& archCitasMedicas,ifstream& archMedicinas,
                             double& pagoMedicinasTotal,
                             ofstream& report,double porcentaje){
    //Variables
    int codProducto,cantPro,cont=1;
    report<<setw(5)<<" "<<setw(5)<<"No."
              <<setw(10)<<"Codigo"
              <<setw(30)<<"Descripcion"
              <<setw(10)<<"Cantidad"
              <<setw(10)<<"Precio"
              <<setw(10)<<"Pago"<<endl;
    while(archCitasMedicas.get()!='\n'){
        archCitasMedicas>>codProducto>>cantPro;
        report<<setw(5)<<" "<<right<<setfill('0')<<setw(2)<<cont<<left<<setfill(' ')
              <<setw(3)<<" "<<setw(10)<<codProducto;
        buscarImprimirMedicina(report,archMedicinas,codProducto,cantPro,
                               pagoMedicinasTotal,porcentaje);
        cont++;
    }
    report<<"Pago total por medicinas: "<<pagoMedicinasTotal<<endl;
}
void buscarImprimirMedicina(ofstream& report,ifstream& archMedicinas,
                            int codProducto,int cantPro,
                            double& pagoMedicinasTotal,double porcentaje){
    //Variables
    int aux_cod;
    double precio;
    double descuento,pago;
    //Reiniciamos el cursor
    archMedicinas.clear();
    archMedicinas.seekg(0,ios::beg);
    while(true){
        archMedicinas>>aux_cod;
        if(archMedicinas.eof())break;
        if(aux_cod==codProducto){
            archMedicinas>>ws;
            impresionNombre(report,archMedicinas,' ','C');
            archMedicinas>>precio;
            report<<setw(10)<<cantPro
                  <<setw(10)<<precio;
            descuento=((cantPro*precio)*porcentaje)/100;
            pago=(cantPro*precio)-descuento;
            pagoMedicinasTotal+=pago;
            report<<pago<<endl;
            break;
        }else while(archMedicinas.get()!='\n');
    }
}