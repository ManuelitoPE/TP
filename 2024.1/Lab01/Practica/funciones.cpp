//Author: MAKO
#include<iostream>
#include<iomanip>
using namespace std;
#include "header/funciones.h"
#define MAX_LINEA 101
int num;
void emitirReporte(){
    cout.precision(2);
    cout<<fixed;
    //Varibles
    int codigoCiudad,dd,mm,aa,hhI,minI,ssI,hhF,minF,ssF,
        error=0;
    double volumen,duracion;
    char inicialCiudad;
    bool statusRegistro;
    //Variables Estadistica
    double duracionMax=0,volumenMax=0;
    encabezado();
    while(true){
        lecturaDeDatos(codigoCiudad,dd,mm,aa,
                       hhI,minI,ssI,hhF,minF,ssF,error,
                       volumen,inicialCiudad,statusRegistro);
        if(cin.eof())break;
        impresionDatos(codigoCiudad,dd,mm,aa,
                       hhI,minI,ssI,hhF,minF,ssF,duracion,
                       volumen,inicialCiudad,statusRegistro);
        procesoEstadistica(duracionMax,duracion,volumenMax,volumen
                            );
    }
    linea(MAX_LINEA,'-');
    emitirEstadisticas(error,duracionMax,volumenMax);

}
void encabezado(){
    cout<<right<<setw(60)<<"REPORTE DE PRECIPITACIONES"<<endl;
    linea(MAX_LINEA,'=');
    cout<<left<<setw(21)<<"Estado de Registro"
        <<setw(12)<<"Ciudad"
        <<setw(15)<<"Fecha"
        <<setw(15)<<"Inicio"
        <<setw(10)<<"Fin"
        <<setw(15)<<"Dueracion"
        <<setw(15)<<"Volumen"<<endl;
    linea(MAX_LINEA,'=');
}
void linea(int num,char c){
    for (int i = 0; i < num; i++){
        cout<<c;
    }
    cout<<endl;
}
void lecturaDeDatos(int& codigoCiudad,int& dd,int& mm,int& aa,
                    int& hhI,int& minI,int& ssI,int& hhF,int& minF,
                    int& ssF,int& error,double& volumen,char& inicialCiudad,
                    bool& statusRegistro){
    //Variables
    char c;
    statusRegistro=true;
    cin>>codigoCiudad;
    if(cin.eof())return;
    cin>>inicialCiudad>>dd>>c>>mm>>c>>aa>>hhI>>c>>minI>>c>>ssI;
    if(hhI+minI+ssI!=0){
       cin>>hhF>>c>>minF>>c>>ssF>>volumen;
    }else{
        statusRegistro=false;  
        error++; 
    }
}
void impresionDatos(int codigoCiudad,int dd,int mm,int aa,
                    int hhI,int minI,int ssI,int hhF,int minF,
                    int ssF,double& duracion,double volumen,char inicialCiudad,
                    bool statusRegistro){
    impresionStatus(statusRegistro);
    cout<<codigoCiudad<<" - "<<setw(5)<<inicialCiudad
        <<setfill('0')<<right<<setw(2)<<dd<<"/"<<setw(2)<<mm
        <<'/'<<setw(4)<<aa<<setfill(' ')<<left;
    if(statusRegistro){
        cout<<setfill(' ')<<right<<setw(5)<<" "
            <<setfill('0')<<setw(2)<<hhI<<":"<<setw(2)<<minI
            <<':'<<setw(2)<<ssI<<setfill(' ')<<setw(6)<<" "
            <<setfill('0')<<setw(2)<<hhF<<":"<<setw(2)<<minF
            <<':'<<setw(2)<<ssF<<setfill(' ')<<setw(5)<<" "<<left;
        impresionDuracion(hhI,minI,ssI,hhF,minF,ssF,duracion);
        cout<<volumen<<endl;                
    }else{
        cout<<endl;
    }
}
void impresionStatus(bool statusRegistro){
    cout<<setw(5)<<" "<<setw(15);
    if(statusRegistro)cout<<"Correcto";
    else cout<<"Incorrecto";
}
void impresionDuracion(int hhI,int minI,int ssI,int hhF,
                       int minF,int ssF,double& duracion){
    //Variables
    int inicio= convertirSeg(hhI,minI,ssI);
    int final= convertirSeg(hhF,minF,ssF);
    duracion=final-inicio;
    int hh,min,ss;
    convertirHMS(hh,min,ss,duracion);
    cout<<right<<setfill('0')<<setw(2)<<hh<<":"<<setw(2)<<min
            <<':'<<setw(2)<<ss<<setfill(' ')<<left<<setw(6)<<" ";
}
int convertirSeg(int hh,int min,int ss){
    return hh*3600+min*60+ss;
}
void convertirHMS(int& hh,int& min,int& ss,double duracion){
    hh= (int)duracion/3600;
    duracion-=hh*3600;
    min=(int)duracion/60;
    duracion-=min*60;
    ss=duracion;
}
void procesoEstadistica(double& duracionMax,double duracion,
                        double& VolumenMax,double volumen){
    if(duracion>duracionMax)duracionMax=duracion;
    if(volumen>VolumenMax)VolumenMax=volumen;
}
void emitirEstadisticas(int error,double duracion,double volumenMax){
    //Varibles
    int hh,min,ss;
    convertirHMS(hh,min,ss,duracion);
    cout<<"Estadisticas: "<<endl;
    linea(MAX_LINEA,'-');
    cout<<setw(99)<<"Ciudad con mayor tiempo de lluvia: código, inicial y tiempo en horas:minutos:segundos"<<right
        <<setfill('0')<<setw(2)<<hh<<":"<<setw(2)<<min<<':'<<setw(2)<<ss<<setfill(' ')<<left<<setw(6)<<" "<<endl
        <<setw(99)<<"Cantidad de registros con error:"<<error<<endl
        <<setw(99)<<"Ciudad con mayor volumen de precipitación:  código, inicial y volumen"<<volumenMax<<endl
        <<setw(99)<<"Precipitación más antigua: código, inicial,volumen"<<endl
        <<setw(99)<<"Tiempo total de lluvia y volumen: duración total horas:minutos:segundos suma volumen"<<endl
        <<setw(99)<<"Menor y mayor fecha del periodo: dd/mm/aaaa - dd/mm/aaaa"<<endl;
}