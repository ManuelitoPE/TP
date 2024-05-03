//Author: MAKO
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "header/funciones.h"
#define MAX_LINEA 100
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
    int codMedico;
    double tarifa;
    //Varibles de Resumen
    int codMedicoMAX;
    double totalMedicoMAX=0;
    while(true){
        archMedicos>>codMedico;
        if(archMedicos.eof())break;
        archMedicos>>ws; archMedicos.get();
        report<<left<<setw(20)<<"Codigo del medico:"<<codMedico<<endl
              <<setw(20)<<"Nombre del medico: ";
        imprimirNombre(report,archMedicos,'/','A'); archMedicos>>ws;
        report<<endl<<setw(20)<<"Especialidad: ";
        imprimirNombre(report,archMedicos,' ','B'); archMedicos>>tarifa;
        report<<endl<<setw(20)<<"Tarifa: "<<tarifa<<endl<<"PACIENTES ATENDIDOS"<<endl;
        lecturaImpresionCitas(codMedico,tarifa,codMedicoMAX,totalMedicoMAX,
                              archCitasMedicas,archMedicinas,report);
        linea(report,MAX_LINEA,'=');
    }   
    imprimirMejorMedico(codMedicoMAX,totalMedicoMAX,archMedicos,report);
}
void encabezado(ofstream& report){
    report<<setw(60)<<"EMPRESA DE SALUD S.A."<<endl;
    linea(report,MAX_LINEA,'=');
    report<<setw(60)<<"REGISTRO DE CITAS MEDICAS"<<endl;
    linea(report,MAX_LINEA,'=');
}
void linea(ofstream& report,int n,char c){
    for (int i = 0; i < n; i++)report<<c;
    report<<endl;
}
void imprimirNombre(ofstream& report,ifstream& arch,
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
    else report<<setw(34-cont)<<" ";
}
void lecturaImpresionCitas(int codMedico,double tarifa,int& codMedicoMAX,
                           double& totalMedicoMAX,ifstream& archCitasMedicas,
                           ifstream& archMedicinas,ofstream& report){
    //Variables
    int dd,mm,aa,dni,hhI,minI,ssI,hhF,minF,ssF,aux_codMed,duracion;
    double porcentaje,duracionH,pagoCita,pagoMedicinas=0,pagoTotal,ingreso=0;
    char c;
    //Reiniciamos el cursor
    archCitasMedicas.clear();
    archCitasMedicas.seekg(0,ios::beg); 
    while(true){
        archCitasMedicas>>dd;
        if(archCitasMedicas.eof())break;
        archCitasMedicas>>c>>mm>>c>>aa>>dni>>porcentaje>>hhI>>c
                        >>minI>>c>>ssI>>hhF>>c>>minF>>c>>ssF
                        >>aux_codMed;
        if(condicion(aux_codMed,codMedico,hhI,minI,ssI,
                     hhF,minF,ssF,duracion,duracionH)){
            imprimirCita(dd,mm,aa,dni,hhI,minI,ssI,hhF,minF,ssF,
                         duracion,duracionH,porcentaje,tarifa,
                         report,pagoCita);
            imprimirMedicinas(archCitasMedicas,archMedicinas,
                              porcentaje,pagoMedicinas,report);
            pagoTotal=pagoCita+pagoMedicinas;
            ingreso+=pagoTotal;
            report<<setw(30)<<"Pago total por medicinas:"<<pagoMedicinas<<endl
                  <<setw(30)<<"Pago total: "<<pagoTotal<<endl;
        }else while(archCitasMedicas.get()!='\n');
    }
    if(ingreso>totalMedicoMAX){
        totalMedicoMAX=ingreso; codMedicoMAX=codMedico;
    }
}
bool condicion(int aux_codMed,int codMedico,int hhI,int minI,
               int ssI,int hhF,int minF,int ssF,int& duracion,
               double& duracionH){
    //Variables
    int inicio=convertSeg(hhI,minI,ssI);
    int final=convertSeg(hhF,minF,ssF);
    duracion=final-inicio;
    duracionH=(double)duracion/3600;
    if(aux_codMed==codMedico and duracion<MAX_DURACION)return true;
    else return false;
}
int convertSeg(int hh,int min,int ss){
    return hh*3600+min*60+ss;
}
void imprimirCita(int dd,int mm,int aa,int dni,int hhI,int minI,
                  int ssI,int hhF,int minF,int ssF,int duracion,
                  double duracionH,double porcentaje,double tarifa,
                  ofstream& report,double& pagoCita){
    //Variables
    int hh,min,ss;
    double descuento= ((tarifa*duracionH)*porcentaje)/100;
    pagoCita= tarifa*duracionH-descuento;
    convertHMS(hh,min,ss,duracion); 
    subEncabezado(report);
    report<<right<<setfill('0')<<setw(2)<<dd<<'/'<<setw(2)<<mm<<'/'
          <<setw(4)<<aa<<setfill(' ')<<setw(3)<<" "<<left
          <<setw(11)<<dni<<right<<setfill('0')<<setw(2)<<hhI<<':'
          <<setw(2)<<minI<<':'<<setw(2)<<ssI<<setfill(' ')<<setw(3)<<" "
          <<setfill('0')<<setw(2)<<hhF<<':'
          <<setw(2)<<minF<<':'<<setw(2)<<ssF<<setfill(' ')<<setw(3)<<" "
          <<setfill('0')<<setw(2)<<hh<<':'
          <<setw(2)<<min<<':'<<setw(2)<<ss<<setfill(' ')<<setw(12)<<" "
          <<setw(5)<<porcentaje<<'%'<<setw(18)<<" "<<setw(5)<<pagoCita<<endl
          <<left<<setw(25)<<"Medicinas Recetadas: "<<endl;
}
void subEncabezado(ofstream& report){
    linea(report,MAX_LINEA,'-');
    report<<setw(13)<<"Fecha"
          <<setw(12)<<"Paciente"
          <<setw(12)<<"Inicio"
          <<setw(8)<<"Fin"
          <<setw(12)<<"Duracion"
          <<setw(28)<<"% de descuento por Seguro"
          <<setw(10)<<"Pago por citas"<<endl;
    linea(report,MAX_LINEA,'-');
}
void convertHMS(int& hh,int& min,int& ss,int duracion){
    hh=(int)duracion/3600;
    duracion-=hh*3600;
    min=(int)duracion/60;
    duracion-=min*60;
    ss=duracion;
}
void imprimirMedicinas(ifstream& archCitasMedicas,ifstream& archMedicinas,
                       double porcentaje,double& pagoMedicinas,
                       ofstream& report){
    //Variables
    int codPRo,cantPro,cont=1;
    subEncabezado2(report);
    while(archCitasMedicas.get()!='\n'){
        archCitasMedicas>>codPRo>>cantPro;
        report<<setw(25)<<" "<<right<<setfill('0')<<setw(2)
              <<cont<<setfill(' ')<<left<<setw(4)<<" "
              <<setw(10)<<codPRo;
        imprimirMedicina(codPRo,cantPro,porcentaje,
                         pagoMedicinas,archMedicinas,report);
        cont++;
    }   
}
void subEncabezado2(ofstream& report){
    report<<setw(25)<<" "<<setw(6)<<"No."
          <<setw(10)<<"Codigo"
          <<setw(30)<<"Descripcion"
          <<setw(10)<<"Cantidad"
          <<setw(10)<<"Precio"
          <<setw(10)<<"Pago"<<endl;
}
void imprimirMedicina(int codPRo,int cantPro,double porcentaje,
                      double& pago,ifstream& archMedicinas,
                      ofstream& report){
    //Variables
    int aux_codPro;
    double precio,descuento,total;
    //Reiniciamos el cursor
    archMedicinas.clear();
    archMedicinas.seekg(0,ios::beg);
    while(true){
        archMedicinas>>aux_codPro;
        if(archMedicinas.eof())break;
        if(aux_codPro==codPRo){
            archMedicinas>>ws;
            imprimirNombre(report,archMedicinas,' ','C'); archMedicinas>>precio;
            descuento= ((precio*cantPro)*porcentaje)/200;
            total= (precio*cantPro)-descuento;
            report<<setw(7)<<cantPro<<setw(9)<<precio<<total<<endl;
            pago+=total;
            break;
        }else while(archMedicinas.get()!='\n');
    } 
}
void imprimirMejorMedico(int codMedicoMAX,double totalMedicoMAX,
                         ifstream& archMedicos,ofstream& report){
    //Variables
    int aux_cod;
    double tarifa;
    //Reiniciamos el cursor
    archMedicos.clear();
    archMedicos.seekg(0,ios::beg);
    report<<"MEDICO QUE APORTO MAS INGRESOS AL INSTITUTO: "<<endl
          <<setw(20)<<"Codigo del medico: "<<codMedicoMAX<<endl
          <<setw(20)<<"Nombre del medico: ";
    while(true){
        archMedicos>>aux_cod;
        if(archMedicos.eof())break;
        if(aux_cod==codMedicoMAX){
            archMedicos>>ws; archMedicos.get();
            imprimirNombre(report,archMedicos,'/','A'); archMedicos>>ws;
            report<<endl<<setw(20)<<"Especialidad: ";
            imprimirNombre(report,archMedicos,' ','B'); archMedicos>>tarifa;
            report<<endl<<setw(20)<<"Tarifa: "<<tarifa<<endl
                  <<"Total ingresado por el medico: "<<totalMedicoMAX<<endl;
            linea(report,MAX_LINEA,'=');
            break;
        }else while(archMedicos.get()!='\n');
    }

}
