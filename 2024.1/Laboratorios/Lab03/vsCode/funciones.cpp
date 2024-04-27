//Author: Mako
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "header/funciones.h"
#define MAX_LINEA 155

void emitirReporte(const char* nomCitasMedicas,const char* nomMedicos,
                   const char* nomReporte){
    ifstream archCitasMedicas(nomCitasMedicas,ios::in);
    if(not archCitasMedicas.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomCitasMedicas<<endl;
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
    int dd,mm,aa,dni,hhI,minI,ssI,hhF,minF,ssF,medico;
    double porcentaje,medicamentos;
    char receta;
    // Variables Resumen
    double totalIngresos=0,montoGastado=0;
    int paciente;
    while(true){
        lecturaDeDatos(dd,mm,aa,dni,hhI,minI,ssI,
                       hhF,minF,ssF,medico,porcentaje,
                       medicamentos,receta,archCitasMedicas);
        if(archCitasMedicas.eof())break;
        impresionDatos(dd,mm,aa,dni,hhI,minI,ssI,
                       hhF,minF,ssF,medico,porcentaje,
                       medicamentos,receta,totalIngresos,
                       montoGastado,paciente,archMedicos,
                       report);
    }
    linea(report,MAX_LINEA,'=');
    report<<"Total de ingresos: "<<totalIngresos<<endl;
    linea(report,MAX_LINEA,'=');
    report<<setw(60)<<"Paciente que mas gasto en una cita medica: "<<paciente<<endl
          <<setw(60)<<"Monto gastado: "<<montoGastado<<endl;
    linea(report,MAX_LINEA,'=');
}
void encabezado(ofstream& report){
    report<<setw(85)<<"EMPRESA DE SALUD S.A."<<endl;
    linea(report,MAX_LINEA,'=');
    report<<setw(88)<<"REGISTRO DE CITAS MEDICAS"<<endl;
    linea(report,MAX_LINEA,'=');
    report<<left<<setw(13)<<"Fecha"
          <<setw(11)<<"Paciente"
          <<setw(11)<<"Inicio"
          <<setw(11)<<"Fin"
          <<setw(10)<<"Duracion"
          <<setw(16)<<"% por Seguro"
          <<setw(40)<<"Medico"
          <<setw(20)<<"Especialida"
          <<setw(10)<<"Pago (cita+medicinas)"<<endl;
    linea(report,MAX_LINEA,'-');
}
void linea(ofstream& report,int n,char c){
    for (int i = 0; i < n; i++)report<<c;
    report<<endl;
}
void lecturaDeDatos(int& dd,int& mm,int& aa,int& dni,
                    int& hhI,int& minI,int& ssI,
                    int& hhF,int& minF,int& ssF,int& medico,
                    double& porcentaje,double& medicamentos,
                    char& receta,ifstream& arch){
    //Variables
    char c;
    arch>>dd;
    if(arch.eof())return;
    arch>>c>>mm>>c>>aa>>dni>>porcentaje>>hhI>>c>>minI>>c>>ssI
        >>hhF>>c>>minF>>c>>ssF>>medico>>receta;
    if(receta=='S')arch>>medicamentos;
    else medicamentos=0;
}
void impresionDatos(int dd,int mm,int aa,int dni,
                    int hhI,int minI,int ssI,
                    int hhF,int minF,int ssF,int medico,
                    double porcentaje,double medicamentos,
                    char receta,double& totalIngresos,
                    double& montoGastado,int& paciente,
                    ifstream& archMedicos,ofstream& report){
    //Variables
    double duracionH,tarifa;
    report<<right<<setfill('0')<<setw(2)<<dd<<'/'<<setw(2)<<mm
          <<'/'<<setw(4)<<aa<<setfill(' ')<<setw(3)<<" "<<left
          <<setw(11)<<dni<<right<<setfill('0')<<setw(2)<<hhI<<':'
          <<setw(2)<<minI<<':'<<setw(2)<<ssI<<setfill(' ')<<setw(3)<<" "
          <<setfill('0')<<setw(2)<<hhF<<':'<<setw(2)<<minF<<':'
          <<setw(2)<<ssF<<setfill(' ')<<setw(3)<<" ";
    impresionDuracion(hhI,minI,ssI,hhF,minF,ssF,duracionH,report);
    report<<setw(5)<<porcentaje<<'%'<<left<<setw(7)<<" ";
    // Aparte de imprimir sacamos la tarifa
    impresionDatosMedico(medico,tarifa,archMedicos,report);
    impresionPago(duracionH,tarifa,porcentaje,dni,paciente,montoGastado,
                  medicamentos,totalIngresos,report);
}
void impresionDuracion(int hhI,int minI,int ssI,int hhF,int minF,
                       int ssF,double& duracionH,ofstream& report){
    //Variables
    int hh,min,ss;
    int inicio= convertSeg(hhI,minI,ssI);
    int final= convertSeg(hhF,minF,ssF);
    int duracion= final-inicio;
    duracionH= (double)duracion/3600; 
    convertHMS(hh,min,ss,duracion);
    report<<setfill('0')<<setw(2)<<hh<<':'<<setw(2)<<min<<':'
          <<setw(2)<<ss<<setfill(' ')<<setw(5)<<" ";
}
int convertSeg(int hh,int min,int ss){
    return hh*3600+min*60+ss;
}
void convertHMS(int& hh,int& min,int& ss,int duracion){
    hh= (int)duracion/3600;
    duracion-=hh*3600;
    min= (int)duracion/60;
    duracion-=min*60;
    ss=duracion;
}
void impresionDatosMedico(int medico,double& tarifa,
                          ifstream& archMedicos,ofstream& report){
    //Variables
    int aux_medico;
    // Reseteamos el cursor
    archMedicos.clear();
    archMedicos.seekg(0,ios::beg);
    while(true){
        archMedicos>>aux_medico;
        if(archMedicos.eof())break;
        if(aux_medico==medico){
            archMedicos>>ws;
            impresionNombre(archMedicos,report,false);
            archMedicos>>ws;
            impresionNombre(archMedicos,report,true);
            archMedicos>>tarifa;
            break;
        }else while(archMedicos.get()!='\n');
    }
}
void impresionNombre(ifstream& arch,ofstream& report,
                     bool mayuscula){
    //Variables
    bool primera=true;
    char c;
    int cont=0;
    while(true){
        c=arch.get();
        if(c==' ')break;
        if(c=='_'){
                report<<' ';
                primera=true;
        }else{
            if(mayuscula)c-=(c>='A' and c<='Z')?0:'a'-'A';
            else {
                c+=(primera)?0:'a'-'A';
                primera=false;
            }
            report<<c;
        }
        cont++;
    }
    if(mayuscula)report<<setw(28-cont)<<" ";
    else report<<setw(40-cont)<<" ";
}
void impresionPago(double duracionH,double tarifa,double porcentaje,int dni,
                   int& paciente,double& montoGastado,double medicamentos,
                   double& totalIngresos,ofstream& report){
    //Variables
    double consulta= tarifa*duracionH;
    double descuento= (consulta*porcentaje)/100 +(medicamentos*porcentaje)/200;
    double pago= consulta+medicamentos-descuento;
    if(pago>montoGastado){
        montoGastado=pago;
        paciente=dni;
    }
    totalIngresos+=pago;
    report<<pago<<endl;
}