//Author: MAKO
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "header/funciones.h"
#define MAX_LINEA 110
#define NO_ENCONTRADO -1

void pedirFecha(int& fechaI,int& fechaF){
    //Variables
    int ddI,mmI,aaI,ddF,mmF,aaF;
    char c;
    // cout<<setw(40)<<"@TikTok_tp"<<endl
    //     <<setw(60)<<"REPORTE PARA LA CAMAPANA: Parcial 2022-1"<<endl;
    // for (int i = 0; i < MAX_LINEA; i++)cout<<'=';cout<<endl;
    // cout<<"Ingrese el intervalo de fechas(xx/xx/xxxx-xx/xx/xxxx): ";
    // cin>>ddI>>c>>mmI>>c>>aaI>>c>>ddF>>c>>mmF>>c>>aaF;
    ddI=15;mmI=3;aaI=2022;ddF=3;mmF=10;aaF=2022;
    fechaI=comprimir(ddI,mmI,aaI);
    fechaF=comprimir(ddF,mmF,aaF);
}
int comprimir(int dd,int mm,int aa){
    return aa*10000+mm*100+dd;
}
void cargarTiktoks(const char* nomTikToks,int& titoks,int* ARRfechas,
                   double* ARRratioViral,int* ARRcantRepro,int fechaI,
                   int fechaF){
    ifstream arch(nomTikToks,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomTikToks<<endl;
        exit(1);
    }
    //Variables
    int dd,mm,aa,fecha,cant_repro,cant_repro_likes;
    char c;
    while(true){
        arch>>dd;
        if(arch.eof())break;
        arch>>c>>mm>>c>>aa;
        fecha=comprimir(dd,mm,aa);
        if(fecha>=fechaI and fecha<=fechaF){
            arch>>cant_repro_likes>>cant_repro;
            ARRfechas[titoks]=fecha;
            ARRratioViral[titoks]=(double)(cant_repro/cant_repro_likes);
            ARRcantRepro[titoks]=cant_repro;
            titoks++;
        }else while(arch.get()!='\n');
    }
}
void cargarUsuarios(const char* nomUsuarios,int& usuarios,char* ARRpublico,
                    int* ARRcodPais,int* ARRident){
    ifstream arch(nomUsuarios,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomUsuarios<<endl;
        exit(1);
    }
    //Variables
    int cod_pais,ident,n;
    char c,publico;
    while(true){
        arch>>cod_pais;
        if(arch.eof())break;
        arch>>c>>ident>>ws; while(arch.get()!=' ');
        arch>>n>>publico;
        ARRcodPais[usuarios]=cod_pais;
        ARRident[usuarios]=ident;
        ARRpublico[usuarios]=publico;
        usuarios++;
    }
}
void procesoDeComentarios(const char* nomComentarios,int *ARRfechas,
                          int* ARRcantComentario,int* ARRlikesComentarios,
                          int* ARRcantRepro,double* ARRratioComentario,
                          double* ARRratioViral,char* ARRviral,int* ARRcantSeguiP,
                          int* ARRcodPais,int* ARRident,char* ARRpublico,int usuarios,
                          int titoks){
    ifstream arch(nomComentarios,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomComentarios<<endl;
        exit(1);
    }
    //Variables
    int dd,mm,aa,fecha,pos,cod,ident,likes,posU;
    char c;
    while (true){
        arch>>dd;
        if(arch.eof())break;
        arch>>c>>mm>>c>>aa;
        fecha=comprimir(dd,mm,aa);
        pos=buscar(ARRfechas,fecha,titoks);
        if(pos!=NO_ENCONTRADO){
            while(arch.get()!='\n'){
                arch>>cod>>c>>ident>>ws; while(arch.get()!=' ');
                arch>>likes;
                ARRcantComentario[pos]++;
                ARRlikesComentarios[pos]+=likes;
                posU=buscarPersona(ARRcodPais,ARRident,cod,ident,usuarios);
                if(ARRpublico[posU]=='V')ARRcantSeguiP[pos]++;
            }
        }else while(arch.get()!='\n');
    }
    procesoRatioViral(ARRcantRepro,ARRlikesComentarios,ARRratioComentario,
                      ARRcantComentario,ARRratioViral,ARRviral,titoks);
}                          
int buscar(int* arr,int busca,int n){
    for (int i = 0; i < n; i++)if(arr[i]==busca)return i;
    return NO_ENCONTRADO;
}
int buscarPersona(int *ARRcodPais,int* ARRident,int cod,int ident,
                  int usuarios){
    for (int i = 0; i < usuarios; i++)
        if(ARRcodPais[i]==cod and ARRident[i]==ident)return i;
    return NO_ENCONTRADO;
}
void procesoRatioViral(int* ARRcantRepro,int* ARRlikesComentarios,
                       double* ARRratioComentario,int* ARRcantComentario,
                       double* ARRratioViral,char* ARRviral,int titoks){
    for (int i = 0; i < titoks; i++){
        ARRratioComentario[i]=((double)ARRcantRepro[i]/ARRlikesComentarios[i])*100;
        if(ARRcantComentario[i]>ARRratioViral[i])ARRviral[i]='S';
        else ARRviral[i]='N';
    }
    
}
void ordenarReporte(int titoks,int* ARRfechas,
                    int* ARRcantComentario,int* ARRlikesComentarios,
                    int* ARRcantRepro,double* ARRratioComentario,
                    char* ARRviral,int* ARRcantSeguiP){
    for (int i = 0; i < titoks-1; i++){
        for (int k = i+1; k < titoks; k++){
            if(ARRcantRepro[i]<ARRcantRepro[k] or (ARRcantRepro[i]==ARRcantRepro[k] and
               ARRfechas[i]>ARRfechas[k])){
                cambiarInt(ARRfechas[i],ARRfechas[k]);
                cambiarInt(ARRcantComentario[i],ARRcantComentario[k]);
                cambiarInt(ARRlikesComentarios[i],ARRlikesComentarios[k]);
                cambiarInt(ARRcantRepro[i],ARRcantRepro[k]);
                cambiarDouble(ARRratioComentario[i],ARRratioComentario[k]);
                cambiarChar(ARRviral[i],ARRviral[k]);
                cambiarInt(ARRcantSeguiP[i],ARRcantSeguiP[k]);
            }
        }
    }
}
void cambiarDouble(double& i,double& k){
    double aux; aux=i; i=k; k=aux;
}
void cambiarChar(char& i,char& k){
    char aux; aux=i; i=k; k=aux;
}
void cambiarInt(int& i,int& k){
    int aux; aux=i; i=k; k=aux;
}
void emitirReporte(const char* nomReporte,int titoks,int* ARRfechas,
                  int* ARRcantComentario,int* ARRlikesComentarios,
                  int* ARRcantRepro,double* ARRratioComentario,
                  char* ARRviral,int* ARRcantSeguiP,int fechaI,
                  int fechaF){
    ofstream report(nomReporte,ios::out);
    if(not report.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomReporte<<endl;
        exit(1);
    }
    report.precision(2);
    report<<fixed;
    encabezado(report,fechaI,fechaF);
    //Variables
    int dd,mm,aa;
    int contViral=0,contNoViral=0; 
    for (int i = 0; i < titoks; i++){
        descomprimir(dd,mm,aa,ARRfechas[i]);
        report<<right<<setfill('0')<<setw(2)<<dd<<'/'
              <<setw(2)<<mm<<'/'<<setw(4)<<aa<<setfill(' ')<<left
              <<setw(7)<<" "<<setw(13)<<ARRcantComentario[i]
              <<setw(20)<<ARRlikesComentarios[i]
              <<setw(17)<<ARRcantRepro[i]
              <<setw(14)<<ARRratioComentario[i]<<setw(17);
        if (ARRviral[i]=='S'){
            report<<"Si";
            contViral++;
        }else{ 
            report<<"No";
            contNoViral++;
        } report<<ARRcantSeguiP[i]<<endl;
    }
    linea(report,MAX_LINEA,'=');
    report<<"RESUMEN"<<endl<<setw(30)<<"CANTIDAD VIRALES:"<<contViral<<endl
          <<setw(30)<<"CANTIDAD NO VIRALES: "<<contNoViral<<endl;
    linea(report,MAX_LINEA,'=');
    
}
void encabezado(ofstream& report,int fechaI,int fechaF){
    //Variables
    int ddI,mmI,aaI,ddF,mmF,aaF;
    descomprimir(ddI,mmI,aaI,fechaI);
    descomprimir(ddF,mmF,aaF,fechaF);
    report<<setw(60)<<"@TikTok_tp"<<endl
          <<setw(76)<<"REPORTE PARA LA CAMPANA: Parcial 2022-1"<<endl
          <<setw(48)<<"Fecha Inicial: "<<setfill('0')<<setw(2)
          <<ddI<<'/'<<setw(2)<<mmI<<'/'<<setw(4)<<aaI<<" Fecha Final:"
          <<setw(2)<<ddF<<'/'<<setw(2)<<mmF<<'/'<<setw(4)<<aaF<<endl
          <<setfill(' ');
    linea(report,MAX_LINEA,'=');
    report<<left<<setw(12)<<"Fecha del"
          <<setw(14)<<"Cantidad de"
          <<setw(20)<<"Cantidad de likes"
          <<setw(18)<<"Cantidad de "
          <<setw(14)<<"Ratio de "
          <<setw(12)<<"Es viral? "
          <<setw(15)<<"Cantidad de"<<endl
          <<setw(12)<<"Tiktok"
          <<setw(14)<<"Comentarios"
          <<setw(20)<<"de comentarios"
          <<setw(18)<<"Reproducciones"
          <<setw(26)<<"Comentarios"
          <<setw(20)<<"seguidores publicos"<<endl;
    linea(report,MAX_LINEA,'-');
}
void descomprimir(int& dd,int& mm,int& aa,int fecha){
    aa=fecha/10000;
    fecha-=aa*10000;
    mm=fecha/100;
    fecha-=mm*100;
    dd=fecha;
}
void linea(ofstream& report,int n,char c){
    for (int i = 0; i < n; i++)report<<c;
    report<<endl;
}