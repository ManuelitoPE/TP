// Author: MAKO
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "header/funciones.h"
#define MAX_LINEA 100
void datos(int& distritoA,int& distritoB,int& hh,int& min,
           int& ss,int& hhD,int& minD,int& ssD,char& alimentos){
    //Variable
    char c;
    // cout<<right<<setw(70)<<"CINEPUTAS"<<endl;
    // for (int i = 0; i < MAX_LINEA; i++)cout<<'='; cout<<endl;   
    // cout<<left<<"Estimado usuario a continuacion se le hara una"
    //     <<" serie de pregutnas para poder ofrecerle una lista "
    //     <<"de peliculas a la que puede asistir"<<endl;
    // for (int i = 0; i < MAX_LINEA; i++)cout<<'-'; cout<<endl;
    // cout<<"Ingrese 2 distritos de los cines que desea visitar: ";
    // cin>>distritoA>>distritoB;
    // cout<<"Ingrese la hora de su disponibilidad (HH:MM:SS): ";
    // cin>>hh>>c>>min>>c>>ss;
    // cout<<"Ingrese la duracion maxima (HH:MM:SS): ";
    // cin>>hhD>>c>>minD>>c>>ssD;
    // cout<<"Finalmente, ingresara con alimentos (S=si o N=no)? ";cin>>alimentos;
    // for (int i = 0; i < MAX_LINEA; i++)cout<<'-'; cout<<endl;   
    // cout<<"Su lista fue creada existosamente !";
    distritoA=9650; distritoB= 4632;
    hh=16; min=0; ss=0; hhD=4; minD=0; ssD=0;alimentos='N';
}
void emitReporte(const char* nomArch,const char* nomReport,
                 int& distritoA,int& distritoB,int& hh,int& min,
                 int& ss,int& hhD,int& minD,int& ssD,
                 char& alimentos){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"No se pudo abrir el archivo "<<nomArch<<endl;
        exit(1);
    }
    ofstream report(nomReport,ios::out);
    if(not report.is_open()){
        cout<<"No se pudo abrir el archivo "<<nomArch<<endl;
        exit(1);
    }
    report.precision(2);
    report<<fixed;
    encabezado(distritoA,distritoB,hh,min,ss,hhD,minD,ssD,
               alimentos,report);
    //Variables
    int distritos=0,aux_distrito,contPeliculas=0,
        totalPeliculas=0;

    while(distritos<2){
        arch>>aux_distrito;
        if(arch.eof())break;
        if(aux_distrito==distritoA or aux_distrito==distritoB){
            arch>>ws;
            lecturaImpresionDatos(arch,report,hh,min,ss,hhD,minD,
                                  ssD,alimentos,aux_distrito,
                                  contPeliculas);
            totalPeliculas+=contPeliculas;
            linea(report,MAX_LINEA,'-');
            distritos++;
        }else while(arch.get()!='\n');
    }
    linea(report,MAX_LINEA,'=');
    report<<"Tiene "<<totalPeliculas<<" opciones con los datos"
          <<"que ha ingresado";
}
void linea(ofstream& report,int num,char c){
    for (int i = 0; i < num; i++)report<<c;    
    report<<endl;
}
void encabezado(int& distritoA,int& distritoB,int& hh,int& min,
           int& ss,int& hhD,int& minD,int& ssD,char& alimentos,
           ofstream& report){
    report<<right<<setw(50)<<"CINEPUTAS"<<endl;
    linea(report,MAX_LINEA,'=');
    report<<left<<"Distritos: "<<distritoA<<", "<<distritoB<<endl
          <<"Disponibilidad: a partir de las "<<right<<setfill('0')
          <<setw(2)<<hh<<':'<<setw(2)<<min<<':'<<setw(2)<<ss<<left
          <<setfill(' ')<<endl
          <<"Duracion maxima: "<<right<<setfill('0')<<setw(2)<<hhD
          <<':'<<setw(2)<<minD<<':'<<setw(2)<<ssD<<left<<setfill(' ')
          <<" horas"<<endl;
    determinarAlimentos(alimentos,report);
    report<<right<<setw(85)<<"LISTA DE PELICULAS A LAS QUE PUEDE ASISTIR"<<endl;
}
void determinarAlimentos(char food,ofstream& report){
    report<<"El cliente ";
    if(food!='N')report<<"no ";
    report<<"llevara alimentos"<<endl;
    linea(report,MAX_LINEA,'=');
}
void lecturaImpresionDatos(ifstream& arch,ofstream& report,int hh,
                      int min,int ss,int hhD,int minD,
                      int ssD,char alimentos,int aux_distrito,
                      int& contPeliculas){
    // Varibles
    int sala,hhI,minI,ssI,hhF,minF,ssF,duracionPelicula,non;
    double costo;
    char aux_alimento,c;
    contPeliculas=0;
    report<<left<<setw(5)<<" "<<"DISTRITO: "<<aux_distrito<<" - ";
    impresionNombre(arch,report,non); report<<endl<<endl;
    encabezado2(report);
    while(arch.get()!='\n'){
        arch>>sala>>costo>>aux_alimento>>hhI>>c>>minI>>c>>ssI
            >>hhF>>c>>minF>>c>>ssF>>ws;
        if(condicionales(hh,min,ss,hhD,minD,ssD,alimentos,
                        aux_alimento,hhI,minI,ssI,hhF,minF,
                        ssF,duracionPelicula)){
            impresionPelicula(sala,costo,hhI,minI,ssI,hhF,minF,
                              ssF,duracionPelicula,report,arch);
            contPeliculas++;
        }else{
            while(true){
                c=arch.get();
                if(c==' ' or c=='\n'){
                    arch.unget();
                    break;
                }
            }
        }
    }
    linea(report,MAX_LINEA,'-');
    if(contPeliculas==0)
        report<<"NO HAY PELICULAS PARA ESAS CONDICIONES";
    else report<<"CANTIDAD DE PELICULAS: "<<contPeliculas;
    report<<endl;
}
void impresionNombre(ifstream& arch,ofstream& report
                     ,int& cont){
    bool mayuscula=true;
    char c;
    while(true){
        c=arch.get();
        if(c==' ' or c=='\n'){
            arch.unget();
            break;
        }else if(c=='_')report<<" ";
        else report<<c;
        cont++;
    }
}
void encabezado2(ofstream& report){
    report<<left<<setw(5)<<" "<<setw(10)<<"SALA"
          <<setw(38)<<"PELICULA"
          <<setw(11)<<"COSTO"
          <<setw(12)<<"INICIA"
          <<setw(13)<<"TERMINA"
          <<setw(15)<<"DURACION"<<endl;
}
bool condicionales(int hh,int min,int ss,int hhD,int minD,int ssD,
                   char alimentos,char aux_alimento,int hhI,
                   int minI,int ssI,int hhF,int minF,int ssF,
                   int& duracionPelicula){
    int disponibilidadInicial=convertirSeg(hh,min,ss);
    int duracion= convertirSeg(hhD,minD,ssD);
    int inicioPelicula=convertirSeg(hhI,minI,ssI);
    int finalPelicula=convertirSeg(hhF,minF,ssF);
    duracionPelicula=finalPelicula-inicioPelicula;
    if(alimentos==aux_alimento and inicioPelicula>=disponibilidadInicial
       and duracion>=duracionPelicula)return true;
    else return false;
}
int convertirSeg(int hh,int min,int ss){
    return hh*3600+min*60+ss;
}
void impresionPelicula(int sala,double costo,int hhI,int minI,
                       int ssI,int hhF,int minF,int ssF,
                       int duracion,ofstream& report,
                       ifstream& arch){
    //Varibales 
    int hh,min,ss,cont;
    convertirHMS(hh,min,ss,duracion);
    report<<left<<setw(5)<<" "<<setw(10)<<sala;
    impresionNombre(arch,report,cont);
    report<<setw(38-cont)<<" "
          <<setw(10)<<costo<<right<<setfill('0')
          <<setw(2)<<hhI<<':'<<setw(2)<<minI<<':'
          <<setw(2)<<ssI<<setfill(' ')<<setw(5)<<" "
          <<setfill('0')<<setw(2)<<hhF<<':'
          <<setw(2)<<minF<<':'<<setw(2)<<ssF
          <<setfill(' ')<<setw(5)<<" "<<setfill('0')
          <<setw(2)<<hh<<':'<<setw(2)<<min<<':'
          <<setw(2)<<ss<<setfill(' ')<<endl<<left;
}
void convertirHMS(int& hh,int& min,int& ss,int duracion){
    hh=(int)duracion/3600;
    duracion-=hh*3600;
    min=(int)duracion/60;
    duracion-=min*60;
    ss=duracion;
}

