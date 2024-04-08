//Author: MAKO
#include<iostream>
#include<iomanip>
using namespace std;
#include "header/funciones.h"
#define MAX_LINEA 110
void emitirReporte(){
    cout.precision(2);
    cout<<fixed;
    //Variables
    int dni,num,aa,horaI,minI,segI,horaF,minF,segF,canal1,canal2,canal3;
    char c,sexo,compania;
    //Variables
    int televidentes=0,cantMenores=0,cantMujAdult=0,cantHomJove=0,
        cantCanales=0;
    int cantMenoAdult=0,personasTVPUCP=0,mujeTVPUCP=0,
        personasTPVIsion=0, hombJoveTPVision=0,adultos=0,canales=0;
    double promeMenoAdul,porcentaMujeres,porcentajeHombres,
           porcentajeAdultos,promedioTelevidentes,duracionH,
           duracionTotal=0;
    int hora,min,ss;
    encabezado();
    while(true){
        lecturaDeDatos(dni,aa,horaI,minI,segI,horaF,minF,segF,
                       canal1,canal2,canal3,sexo,compania,
                       televidentes);
        if(cin.eof())break;
        cout<<setw(10)<<dni;
        impresionSexoCategoria(sexo,aa);
        impresionHoraDuracion(horaI,minI,segI,horaF,minF,segF,duracionH);
        lecturaCanales(canal1,canal2,canal3);
        impresionCompania(compania);
        condicionales(cantMenores,cantMujAdult,cantHomJove,
                      cantCanales,cantMenoAdult,duracionTotal,personasTVPUCP,
                      mujeTVPUCP,personasTPVIsion,hombJoveTPVision,
                      adultos,canales, dni, aa, horaI,
                      minI, segI, horaF, minF, segF,sexo,
                      compania,duracionH,canal1,canal2,canal3);
    }
    linea(MAX_LINEA,'=');
    //Calculo Tiempo Promedio que ven los menores y adultos
    duracionTotal*= 3600;
    duracionTotal/=cantMenoAdult;
    convertirHMS(hora,min,ss,duracionTotal);
    //Porcentaje de mujeres que TVPUcp
    porcentaMujeres= (mujeTVPUCP*100)/personasTVPUCP;
    //Porcentaje de Hombres Jovenes que ve TPVision
    porcentajeHombres=(hombJoveTPVision*100)/personasTPVIsion;
    //Porcentaje de adultos
    porcentajeAdultos= (adultos*100)/televidentes;
    //Promedio de canales que ven los televidentes
    promedioTelevidentes= (double)canales/televidentes;
    estadisticas(televidentes,cantMenores,cantMujAdult,cantHomJove,
                cantCanales,hora,min,ss,porcentaMujeres,
                porcentajeHombres,porcentajeAdultos,promedioTelevidentes);
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
void lecturaDeDatos(int& dni,int& aa,int& horaI,int& minI,
               int& segI,int& horaF,int& minF,int& segF,
               int& canal1,int& canal2,int& canal3,char& sexo,
               char& compania,int& televidentes){
    char c;
    int num;
    cin>>dni;
    if(cin.eof())return;
    televidentes++;
    cin>>sexo>>num>>c>>num>>c>>aa>>horaI>>c>>minI>>c>>segI
       >>horaF>>c>>minF>>c>>segF>>canal1>>canal2>>canal3
       >>compania;
}
void impresionSexoCategoria(char sexo, int anio){
    // Sexo
    cout<<setw(12);
    if(sexo == 'M'){
        cout<<"Masculino";
    }else {
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
                        int minF,int segF,double& duracionH){
    // Hora(A) y Hora(P)
    cout<<right<<setfill('0')<<setw(2)<<horaI<<':'<<setw(2)<<minI<<':'<<setw(2)<<segI<<setfill(' ')
        <<setw(3)<<" "<<setfill('0')<<setw(2)<<horaF<<':'<<setw(2)<<minF<<':'<<setw(2)<<segF<<setfill(' ')
        <<setw(5)<<" ";
    // Duracion
    int horaP = convertirSegundos(horaI,minI,segI);
    int horaA = convertirSegundos(horaF,minF,segF);
    int duracion = horaA - horaP;
    duracionH = (double)duracion/3600;
    int hora,min,seg;
    convertirHMS(hora,min,seg,duracion);

    cout<<setfill('0')<<setw(2)<<hora<<':'<<setw(2)<<min<<':'<<setw(2)<<seg
        <<setfill(' ')<<left<<setw(11)<<" "<<duracionH<<setw(6)<<" "<<setfill(' ');
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
    cout<<canal1;
    if(canal2!=0){
        cout<<'/'<<canal2;
        if(canal3!=0){
            cout<<'/'<<canal3;
            cout<<setw(2)<<" ";
        }else
            cout<<setw(6)<<" ";
    }else
        cout<<setw(10)<<" ";
}
void impresionCompania(char compania){
    if(compania=='A') cout<<"TVPUCP";
    else if(compania=='B') cout<<"CableMas";
    else cout<<"TPVision";
    cout<<endl;
}
void condicionales(int& cantMenores,int& cantMujAdult,int& cantHomJove,
                   int& cantCanales,int& cantMenoAdult,double& duracionTotal,
                   int& personasTVPUCP,
                   int&  mujeTVPUCP,int& personasTPVIsion,int& hombJoveTPVision,
                   int& adultos,int& canales,int dni,int aa,int horaI,
                   int minI,int segI,int horaF,int minF,int segF,char sexo,
                   char compania,double duracionH,int canal1,int canal2,
                   int canal3){
    if(aa>2009 and horaI>=14 and horaF<=19)cantMenores++;
    if(aa<=1988 and sexo=='F' and ((horaF*100)+minF<930 or (horaI*100)+minI>1245))cantMujAdult++;
    if(aa<2009 and aa>1988 and sexo=='M' and duracionH>3.5)cantHomJove++;
    if(canal1!=555 and canal1!=314 and canal2!=555 and canal2!=314 and
       canal1!=555 and canal1!=314){
        if(canal1==770 or canal1==312 or canal1==577 or
            canal2==770 or canal2==312 or canal2==577 or
            canal3==770 or canal3==312 or canal3==577)cantCanales++;
    }
    if(aa>2009 or aa<1988){
        cantMenoAdult++;
        duracionTotal+=duracionH;
    }
    if(compania=='A'){
        personasTVPUCP++;
        if(sexo=='F')mujeTVPUCP++;
    }
    if(compania=='C'){
        personasTPVIsion++;
        if(sexo=='M' and aa>1988 and aa>2006)hombJoveTPVision++;
    }
    if(aa<1988)adultos++;
    if(canal1!=0){
        canales++;
        if(canal2!=0){
            canales++;
            if(canal3!=0)canales++;
        }
    }
}
void estadisticas(int televidentes,int cantMenores, int cantMujAdult,
                  int cantHombreJove,int cantCanales,int hora,int min,
                  int ss,double porcentaMujeres,double porcentajeHombres,
                  double porcentajeAdultos,double promedioTelevidentes){
    cout<<right<<setw(30)<<"ESTADISTICAS OBTENIDAS:"<<endl<<left
        <<setw(7)<<" "<<setw(90)<<"Cantidad de televidentes registrados"<<televidentes<<endl
        <<setw(7)<<" "<<setw(90)<<"Cantidad de menores que ven entre las 14:00:00 y las 19:00:00"<<cantMenores<<endl
        <<setw(7)<<" "<<setw(90)<<"Cantidad de mujeres adultas que NO ven television entre las 9:30:00 y las 12:45"<<cantMujAdult<<endl
        <<setw(7)<<" "<<setw(90)<<"Cantidad de hombres jovenes que ve mas de 3 horas y media"<<cantMenores<<endl
        <<setw(7)<<" "<<setw(90)<<"Cantidad de personas que ven los canales 770,312 o 577 pero no 314 ni 555"<<cantCanales<<endl
        <<setw(7)<<" "<<setw(90)<<"Tiempo promedio que ven los menores y adultos"
        <<right<<setfill('0')<<setw(2)<<hora<<':'<<setw(2)<<min<<":"<<setw(2)<<ss<<endl<<setfill(' ')<<left
        <<setw(7)<<" "<<setw(90)<<"Porcentaje de mujeres que ve TVPUCP"<<porcentaMujeres<<'%'<<endl
        <<setw(7)<<" "<<setw(90)<<"Porcentaje de hombres jovenes que ve TPVision"<<porcentajeHombres<<'%'<<endl
        <<setw(7)<<" "<<setw(90)<<"Porcentaje de adultos Registrados"<<porcentajeAdultos<<'%'<<endl
        <<setw(7)<<" "<<setw(90)<<"Promedio de canales que ven los televidentes"<<promedioTelevidentes<<endl;
    linea(MAX_LINEA,'=');
}