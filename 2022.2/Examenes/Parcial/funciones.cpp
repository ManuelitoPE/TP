//Author: Mako
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "header/funciones.h"
#define MAX_LINEA 100

void pedirDatos(int& ddI,int& mmI,int& aaI,int& ddF,int& mmF,
                int& aaF){
    //Variables
    char c;
    // cout<<setw(60)<<"@TikTok_tp"<<endl
    //     <<setw(50)<<"REPORTE PARA LA CAMPANA: Parcial 2022-1"<<endl<<endl
    //     <<"Ingresar la fecha Inicial y final en formato (xx/xx/xxxx-xx/xx/xxxx):";
    // cin>>ddI>>c>>mmI>>c>>aaI>>c>>ddF>>c>>mmF>>c>>aaF;
    ddI=15;mmI=3;aaI=2022;ddF=3;mmF=10;aaF=2022;
}
void emitirReporte(int ddI,int mmI,int aaI,int ddF,int mmF,int aaF,
                  const char* nomComentarios, const char* nomTikToks,
                  const char* nomPaises,const char* nomUsuarios,
                  const char* nomReporte){
    ifstream archComentarios(nomComentarios,ios::in);
    if(not archComentarios.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomComentarios<<endl;
        exit(1);
    }
    ifstream archTikToks(nomTikToks,ios::in);
    if(not archTikToks.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomTikToks<<endl;
        exit(1);
    }
    ifstream archPaises(nomPaises,ios::in);
    if(not archPaises.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomPaises<<endl;
        exit(1);
    }
    ifstream archUsuarios(nomUsuarios,ios::in);
    if(not archUsuarios.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomUsuarios<<endl;
        exit(1);
    }
    ofstream report(nomReporte,ios::out);
    if(not report.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomReporte<<endl;
        exit(1);
    }
    encabezado(report,ddI,mmI,aaI,ddF,mmF,aaF);
    //Variables
    int dd,mm,aa,cant_likeReproduccion,cant_Reproduccion;
    int cont=1;
    char c;
    //Variables Resumem
    int ddM,mmM,aaM,codigo,identificador,likes;
    while(true){
        archTikToks>>dd;
        if(archTikToks.eof())break;
        archTikToks>>c>>mm>>c>>aa;
        if(condicionFecha(ddI,mmI,aaI,ddF,mmF,aaF,dd,mm,aa)){
            report<<"TikTok "<<cont<<") "<<setfill('0')<<setw(2)
            <<dd<<'/'<<setw(2)<<mm<<'/'<<setw(4)<<aa<<endl;
            archTikToks>>cant_likeReproduccion>>cant_Reproduccion;
            impresionDatos(dd,mm,aa,ddM,mmM,aaM,codigo,identificador,
                           likes,archComentarios,archPaises,
                           archUsuarios,report);
            cont++;
        }else while(archTikToks.get()!='\n');

    }
}
void encabezado(ofstream& report,int ddI,int mmI,int aaI,
                int ddF,int mmF,int aaF){
    report<<setw(60)<<"@TikToks_tp"<<endl
          <<setw(74)<<"REPORTE PARA LA CAMPANA: Parcial 2022-1"<<endl
          <<setw(45)<<"Fecha Inicial: "
          <<setfill('0')<<setw(2)<<ddI<<'/'<<setw(2)<<mmI<<'/'
          <<setw(4)<<aaI<<" Fecha Final: "<<setw(2)<<ddF<<'/'
          <<setw(2)<<mmF<<'/'<<setw(4)<<aaF<<setfill(' ')<<endl;
    linea(report,MAX_LINEA,'=');
}
void linea(ofstream& report,int n,char c){
    for (int i = 0; i < n; i++)report<<c;
    report<<endl;
}
bool condicionFecha(int ddI,int mmI,int aaI,int ddF,int mmF,
                    int aaF,int dd,int mm,int aa){
    int fechaI=aaI*10000+mmI*100+ddI;
    int fechaF=aaF*10000+mmF*100+ddF;
    int fecha=aa*10000+mm*100+dd;
    if(fecha>=fechaI and fecha<=fechaF)return true;
    else return false;
}
void impresionDatos(int dd,int mm,int aa,int& ddM,int& mmM,int& aaM,
                    int& codigo,int& identificador,int& likes,
                    ifstream& archComentarios,ifstream& archPaises,
                    ifstream& archUsuarios,ofstream& report){
    report<<left<<setw(40)<<"COMENTARIO"
          <<setw(40)<<"AUTOR DEL COMENTATIO"
          <<setw(40)<<"CANTIDAD DE LIKES"
          <<setw(40)<<"PAIS DEL AUTOR"<<endl;
    linea(report,MAX_LINEA,'=');
    //Varibles
    int aux_dd,aux_mm,aux_aa,aux_codigo,aux_indentificador;
    char c;
    //Reiniciamos el cursor
    archComentarios.clear();
    archComentarios.seekg(0,ios::beg);
    while(true){
        archComentarios>>aux_dd;
        if(archComentarios.eof())break;
        archComentarios>>c>>aux_mm>>c>>aux_aa;
        if(aux_dd==dd and aux_mm==mm and aux_aa==aa){
            impresionDe
            archComentarios>>ws>>aux_codigo>>c>>aux_indentificador>>ws;

        }else while(archComentarios.get()!='\n');
    }
}