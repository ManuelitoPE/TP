//Author: MAKO
#include<iostream>
#include<iomanip>
using namespace std;
#include "header/funciones.h"
#define MAX_LINEA 110
void emitirReporte(){
    cout.precision(4);
    cout<<fixed;
    //Variables
    int dni,num,aa,horaI,minI,segI,horaF,minF,segF,canal1,canal2,canal3;
    char c,sexo,compania;
    // Variables 
    int televidentes=0,cantMenores=0,cantMujAdult=0,cantHomJove=0,
        cantCanales=0;
    double promeMenoAdul,porcentaMujeres,porcentajeHombres,
           porcentajeAdultos,promedioTelevidentes;
    encabezado();
    while(true){
        lecturaDeDatos();
        if(cin.eof());

    }
    while (true){
        cin>>dni;
        if(cin.eof())break;
        televidentes++;
        cout<<setw(10)<<dni;
        cin>>sexo>>num>>c>>num>>c>>aa;
        impresionSexoCategoria(sexo,aa);
        cin>>horaI>>c>>minI>>c>>segI>>horaF>>c>>minF>>c>>segF;
        impresionHoraDuracion(horaI,minI,segI,horaF,minF,segF);
        lecturaCanales(canal1,canal2,canal3);
        cin>>compania;
        impresionCompania(compania);
        condicionales(cantMenores,cantMujAdult,cantHomJove,
                      cantCanales,promeMenoAdul,porcentaMujeres,
                      porcentajeHombres,porcentajeAdultos,
                      promedioTelevidentes,dni,aa,horaI,minI,
                      segI,horaF,minF,segF,sexo,compania);
    }
    linea(MAX_LINEA,'=');
    estadisticas(televidentes);
}
void encabezado(){
    cout<<right<<setw(50)<<"EMPRESA DE OPINION DE MERCADO S.A."<<endl;
    linea(MAX_LINEA,'=');
    cout<<setw(50)<<"REGISTRO DE PREFERENCIAS DE LOS TELEVIDENTES"<<endl;
    linea(MAX_LINEA,'=');
    cout<<left<<setw(10)<<"DNI No."
              <<setw(12)<<"Sexo"
              <<setw(12)<<"Categoria"
              <<setw(11)<<"Hora(P)"
              <<setw(11)<<"Hora(A)"
              <<setw(18)<<"Duracion(H:M:S)"
              <<setw(14)<<"Duracion(H)"
              <<setw(14)<<"Canales"
              <<setw(15)<<"Compania"<<endl;
    linea(MAX_LINEA,'-');    
}
void linea(int n,char c){
    for(int i=0; i < n; i++){
        cout<<c;
    }
    cout<<endl;
}
void impresionSexoCategoria(char sexo, int anio){
    // Sexo
    cout<<setw(12);
    if(sexo == 'M'){
        cout<<"Masculino";
    }else{
        cout<<"Femenino";
    }
    // Categoria
    cout<<setw(12);
    if(anio>2009){
        cout<<"Menor";
    }else if(anio>1988){
        cout<<"Joven"; 
    }else{
        cout<<"Adulto";
    }
}
void impresionHoraDuracion(int horaI,int minI,int segI,int horaF,
                        int minF,int segF){
    // Hora(A) y Hora(P)
    cout<<setfill('0')<<setw(2)<<horaI<<':'<<setw(2)<<minI<<':'<<setw(2)<<segI<<setfill(' ')
        <<setw(3)<<" "<<setfill('0')<<setw(2)<<horaF<<':'<<setw(2)<<minF<<':'<<setw(2)<<segF<<setfill(' ')
        <<setw(3)<<" ";
    // Duracion
    int horaP = convertirSegundos(horaI,minI,segI);
    int horaA = convertirSegundos(horaF,minF,segF);
    int duracion = horaA - horaP;
    double duracionH = (double)duracion/3600;
    int hora,min,seg;
    convertirHMS(hora,min,seg,duracion);

    cout<<setfill('0')<<setw(2)<<hora<<':'<<setw(2)<<min<<':'<<setw(2)<<seg
        <<setfill(' ')<<setw(11)<<" "<<duracionH<<setw(8)<<" "<<setfill(' ');
}
int convertirSegundos(int hora,int min,int seg){
    int total = hora*3600+min*60+seg;
    return total;
}
void convertirHMS(int& hora,int& min,int& seg,double duracion){
    int aux;
    hora= (int)duracion/3600;
    duracion -=  hora*3600;
    min= (int)duracion/60;
    duracion -= min*60;
    seg = duracion;
}
void lecturaCanales(int canal1,int canal2,int canal3){
    int aux=0,cont=0;
    for (int i = 0; i < 3; i++){
        cin>>aux;
        if(aux!=0){
            if(i!=0)cout<<'/';
            cout<<aux;
            cont++;
        }
    }
    cout<<setw(14-cont*4)<<"";
}
void impresionCompania(char compania){
    if(compania=='A') cout<<"TVPUCP";
    else if(compania=='B') cout<<"CableMas";
    else cout<<"TPVision";
    cout<<endl;
}
void estadisticas(int televidentes){
    cout<<right<<setw(30)<<"ESTADISTICAS OBTENIDAS:"<<endl<<left
        <<setw(7)<<" "<<setw(90)<<"Cantidad de televidentes registrados"<<televidentes<<endl
        <<setw(7)<<" "<<setw(90)<<"Cantidad de menores que ven entre las 14:00:00 y las 19:00:00"<<endl
        <<setw(7)<<" "<<setw(90)<<"Cantidad de mujeres adultas que NO ven television entre las 9:30:00 y las 12:45"<<endl
        <<setw(7)<<" "<<setw(90)<<"Cantidad de hombres jovenes que ve mas de 3 horas y media"<<endl
        <<setw(7)<<" "<<setw(90)<<"Cantidad de personas que ven los canales 770,312 o 577 pero no 314 ni 555"<<endl
        <<setw(7)<<" "<<setw(90)<<"Tiempo promedio que ven los menores y adultos"<<endl
        <<setw(7)<<" "<<setw(90)<<"Porcentaje de mujeres que ve TVPUCP"<<endl
        <<setw(7)<<" "<<setw(90)<<"Porcentaje de hombres jovenes que ve TPVision"<<endl
        <<setw(7)<<" "<<setw(90)<<"Porcentaje de adultos Registrados"<<endl
        <<setw(7)<<" "<<setw(90)<<"Promedio de canales que ven los televidentes"<<endl;
    linea(MAX_LINEA,'=');
}
void condicionales(int cantMenores,int cantMujAdult,int cantHomJove,
                   int cantCanales,double promeMenoAdul,double porcentaMujeres,
                   double porcentajeHombres,double porcentajeAdultos,
                   double promedioTelevidentes,int dni,int aa,int horaI,
                   int minI,int segI,int horaF,int minF,int segF,char sexo,
                   char compania){

}