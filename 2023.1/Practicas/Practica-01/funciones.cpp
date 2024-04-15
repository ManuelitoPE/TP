// Author: MAKO
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "header/funciones.h"
#define MAX_LINEA 134
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
    int distritos=0,aux_distrito,contPeliculas=0;

    while(distritos<2){
        arch>>aux_distrito;
        if(arch.eof())break;
        if(aux_distrito==distritoA or aux_distrito==distritoB){
            arch>>ws;
            lecturaImpresionDatos(arch,report,hh,min,ss,hhD,minD,
                                  ssD,alimentos,aux_distrito,
                                  contPeliculas);
            distritos++;
        }else while(arch.get()!='\n');
    }
}
void linea(ofstream& report,int num,char c){
    for (int i = 0; i < num; i++)report<<c;    
    report<<endl;
}
void encabezado(int& distritoA,int& distritoB,int& hh,int& min,
           int& ss,int& hhD,int& minD,int& ssD,char& alimentos,
           ofstream& report){
    report<<right<<setw(70)<<"CINEPUTAS"<<endl;
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
    int sala,hhI,minI,ssI,hhF,minF,ssF;
    double costo;
    char aux_alimento,c;
    contPeliculas=0;
    report<<left<<setw(5)<<" "<<"DISTRITO: "<<aux_distrito<<" - ";
    impresionNombre(arch,report); report<<endl<<endl;
    encabezado2(report);
    while(arch.get()!='\n'){
        arch>>sala>>costo>>aux_alimento>>hhI>>c>>minI>>c>>ssI
            >>hhF>>c>>minF>>c>>ssF>>ws;
        if(condicionales(hh,min,ss,hhD,minD,ssD,alimentos,
                        aux_alimento,hhI,minI,ssI,hhF,minF,
                        ssF)){
            // procesoCineDatos();
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
    if(contPeliculas==0)
        report<<"NO HAY PELICULAS PARA ESAS CONDICIONES";
    else report<<"CANTIDAD DE PELICULAS: "<<contPeliculas;
    report<<endl;
    linea(report,MAX_LINEA,'-');
}
void impresionNombre(ifstream& arch,ofstream& report){
    bool mayuscula=true;
    char c;
    while(true){
        c=arch.get();
        if(c==' ')break;
        else if(c=='_')report<<" ";
        else report<<c;
    }
}
void encabezado2(ofstream& report){
    report<<left<<setw(5)<<" "<<setw(10)<<"SALA"
          <<setw(15)<<"PELICULA"
          <<setw(15)<<"COSTO"
          <<setw(15)<<"INICIA"
          <<setw(15)<<"TERMINA"
          <<setw(15)<<"DURACION"<<endl;
}
bool condicionales(int hh,int min,int ss,int hhD,int minD,int ssD,
                   char alimentos,char aux_alimento,int hhI,
                   int minI,int ssI,int hhF,int minF,int ssF){
    int disponibilidadInicial=convertirSeg(hh,min,ss);
    int duracion= convertirSeg(hhD,minD,ssD);
    int disponibilidadFinal= disponibilidadInicial+duracion;
    int inicioPelicula=convertirSeg(hhI,minI,ssI);
    int finalPelicula=convertirSeg(hhF,minF,ssF);
    if(alimentos==aux_alimento and inicioPelicula>=disponibilidadInicial
       and finalPelicula<=disponibilidadFinal)return true;
    else return false;
}
int convertirSeg(int hh,int min,int ss){
    return hh*3600+min*60+ss;
}