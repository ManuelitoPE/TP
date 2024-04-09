/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

//Author: Sergio Manuel Sutta Pinedo 20210646

#include <iostream>
#include <iomanip>
using namespace std;
#include "funciones.h"
#define MAX_LINEA 115

void emitirReporte(){
    cout.precision(2);
    cout<<fixed;
    //Variables
    int dd,mm,aa,dni,hhI,minI,ssI,hhF,minF,ssF;
    double tarifa,monto,totalDeIngresos=0,duracionH;
    char especialidad,receta;
    //Variables Estadisticas
    int pacientes=0,pacienteRecetado=0,pacienteDermatologia=0,
        pacientesNoRecetados=0,pacientesPediatria=0,
        pacientesCardiologia=0,pacientes350=0;
    int dia;
    double totalMedicina=0,promedioMedicina,totalMedicinaD=0,
            promedioMedicinaD,porcentajeNoRecetados,porcentajePediatria;
    encabezado();
    while(true){
        lecturaDeDatos(dd,mm,aa,dni,hhI,minI,ssI,hhF,minF,ssF,
                       tarifa,monto,especialidad,receta);
        if(cin.eof())break;
        pacientes++;
        impresionDeDatos(dd,mm,aa,dni,hhI,minI,ssI,hhF,minF,ssF,
                       tarifa,monto,especialidad,receta,totalDeIngresos,
                       duracionH);
        //Condicionales
        if(receta!='N'){
            pacienteRecetado++;
            totalMedicina+=monto;
            if(especialidad=='D'){
                pacienteDermatologia++;
                totalMedicinaD+=monto;
            }
        }else{
            pacientesNoRecetados++;
            if(duracionH*tarifa>350)pacientes350++;
        }
        if(especialidad=='P'){
            pacientesPediatria++;
        }else if(especialidad=='C'){
            dia=aa*10000+mm*100+dd;
            if(dia>20240115){
                pacientesCardiologia++;
            }
        }
    }
    linea(MAX_LINEA,'=');
    cout<<"Total de Ingresos: "<<totalDeIngresos<<endl;
    linea(MAX_LINEA,'=');
    //Medicina Promedio
    promedioMedicina=totalMedicina/pacienteRecetado;
    //Medicina Promedio Dermatolodia
    promedioMedicinaD=totalMedicinaD/pacienteDermatologia;
    //Poecentaje de pacientes no recetados
    porcentajeNoRecetados=(pacientesNoRecetados*100)/pacientes;
    //Porcentaje de pacientes que se atendieron en pediatia
    porcentajePediatria=(pacientesPediatria*100)/pacientes;
    //Estadisticas
    estadisticasObtenidas(promedioMedicina,promedioMedicinaD,porcentajeNoRecetados,
                           porcentajePediatria,pacientesCardiologia,
                            pacientes350);
}
void linea(int num,char c){
    for(int i=0;i<num;i++){
        cout<<c;
    }
    cout<<endl;
}
void encabezado(){
    cout<<right<<setw(50)<<"EMPRESA DE SALUD S. A."<<endl;
    linea(MAX_LINEA,'=');
    cout<<setw(5)<<" "<<"REGISTRO DE CITAS DE LAS CONSULTAS MEDICAS"<<endl;
    linea(MAX_LINEA,'=');
    cout<<left<<setw(13)<<"Fecha"
        <<setw(11)<<"Paciente"
        <<setw(12)<<"Inicio"
        <<setw(9)<<"Fin"
        <<setw(17)<<"Duracion(H:M:S)"
        <<setw(15)<<"Duracion(H)"
        <<setw(14)<<"Especialidad"
        <<setw(10)<<"Pago (cita+medicinas)"<<endl;
    linea(MAX_LINEA,'-');   
}
void lecturaDeDatos(int& dd,int& mm,int& aa,int& dni,int& hhI,int& minI,
                    int& ssI,int& hhF,int& minF,int& ssF,
                    double& tarifa,double& monto,char& especialidad,
                    char& receta){
    //Variables 
    char c;
    cin>>dd;
    if(cin.eof())return;
    cin>>c>>mm>>c>>aa>>dni>>hhI>>c>>minI>>c>>ssI>>hhF>>c>>minF>>c>>ssF
       >>tarifa>>especialidad>>receta;
    if(receta!='N')cin>>monto;
}
void impresionDeDatos(int dd,int mm,int aa,int dni,int hhI,int minI,
                    int ssI,int hhF,int minF,int ssF,
                    double tarifa,double monto,char especialidad,
                    char receta,double& totalDeIngresos,
                    double& duracionH){
    cout<<right<<setfill('0')<<setw(2)<<dd<<'/'<<setw(2)<<mm<<'/'
        <<setw(4)<<aa<<setfill(' ')<<setw(3)<<' '<<left
        <<setw(10)<<dni<<right<<setfill('0')<<setw(2)<<hhI<<':'<<setw(2)
        <<minI<<':'<<setw(2)<<ssI<<setfill(' ')<<setw(3)<<' '
        <<right<<setfill('0')<<setw(2)<<hhF<<':'<<setw(2)
        <<minF<<':'<<setw(2)<<ssF<<setfill(' ')<<setw(6)<<' '<<left;
    //Duracion
    impresionDuracion(hhI,minI,ssI,hhF,minF,ssF,duracionH);
    //Especialidad
    impresionEspecialidad(especialidad);
    if(receta=='N')monto=0;
    //Pago
    impresionPago(duracionH,monto,tarifa,totalDeIngresos);
    
}
void impresionDuracion(int hhI,int minI,int ssI,int hhF,int minF,
                       int ssF,double& duracionH){
    //Variables
    int hh,min,ss,inicio,fin,duracion;
    inicio= hhI*3600+minI*60+ssI;
    fin= hhF*3600+minF*60+ssF;
    duracion= fin-inicio;
    duracionH= (double)duracion/3600;
    convertirHMS(hh,min,ss,duracion);
    cout<<right<<setfill('0')<<setw(2)<<hh<<':'<<setw(2)
        <<min<<':'<<setw(2)<<ss<<setfill(' ')<<setw(8)<<' '<<left
        <<setw(13)<<duracionH;
}
void convertirHMS(int& hh,int& min,int& ss,double duracion){
    hh=(int)duracion/3600;
    duracion-=hh*3600;
    min=(int)duracion/60;
    duracion-=min*60;
    ss=duracion;
}
void impresionEspecialidad(char especialidad){
    cout<<setw(15);
    if(especialidad=='C')cout<<"Cardiologia";
    else if(especialidad=='D')cout<<"Dermatologia";
    else cout<<"Pediatria";
}
void impresionPago(double duracionH,double monto,double tarifa,
                   double& totalDeIngresos){
    double pagoTotal= (duracionH*tarifa)+monto;
    totalDeIngresos+= pagoTotal;
    cout<<right<<setw(10)<<pagoTotal<<left<<endl;
}
void estadisticasObtenidas(double promedioMedicina,double promedioMedicinaD,
                           double porcentajeNoRecetados,double porcentajePediatria,
                           int pacientesCardiologia,int pacientes350){
    cout<<left<<setw(5)<<" "<<"ESTADISTICAS OBTENIDAS: "<<endl
        <<setw(5)<<" "<<setw(90)<<"Promedio de gastos por medicina de los pacientes que le recetaron medicinas"<<promedioMedicina<<endl
        <<setw(5)<<" "<<setw(90)<<"Promedio de gastos por medicina de los pacientes que se atendieron de dermatologia"<<promedioMedicinaD<<endl
        <<setw(5)<<" "<<setw(90)<<"Porcentaje de pacientes que no le recetaron medicinas"<<porcentajeNoRecetados<<'%'<<endl
        <<setw(5)<<" "<<setw(90)<<"Porcentaje de pacientes que se atendieron en pediatria"<<porcentajePediatria<<'%'<<endl
        <<setw(5)<<" "<<setw(90)<<"Cantidad de pacientes que se atendieron en cardiologia despues del 15/01/2024"<<pacientesCardiologia<<endl
        <<setw(5)<<" "<<setw(90)<<"Porcentaje de pacientes que no le recetaron medicinas y que gasto mas de 350.00"<<pacientes350<<endl;
    linea(MAX_LINEA,'=');
}