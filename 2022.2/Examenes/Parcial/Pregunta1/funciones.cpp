//Author: Mako
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "header/funciones.h"
#define MAX_LINEA 195

void pedirDatos(int& fechaI,int& fechaF){
    //Varaibles 
    int ddI=15,mmI=3,aaI=2022,ddF=3,mmF=10,aaF=2022;
    char c;

    // cout<<setw(50)<<"@TikTok_tp"<<endl
    //     <<setw(66)<<"REPORTE PARA LA CAMPANA: PARCIAL 2022-1"<<endl<<endl;
    // for(int i=0;i<MAX_LINEA;i++)cout<<'-'; cout<<endl;
    // cout<<"Ingresa el rango de fechas (xx/xx/xxxx-xx/xx/xxxx): ";
    // cin>>ddI>>c>>mmI>>c>>aaI>>c>>ddF>>c>>mmF>>c>>aaF;
    fechaI=aaI*10000+mmI*100+ddI;
    fechaF=aaF*10000+mmF*100+ddF;
}
void emitirReporte(const char* nomReporte,const char* nomComentarios,
                   const char* nomPaises,const char* nomTikToks,
                   const char* nomUsuarios,int fechaI,int fechaF){
    ofstream report(nomReporte,ios::out);
    if(not report.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomReporte<<endl;
        exit(1);
    }
    ifstream archPaises(nomPaises,ios::in);
    if(not archPaises.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomPaises<<endl;
        exit(1);
    }
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
    ifstream archUsuarios(nomUsuarios,ios::in);
    if(not archUsuarios.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomUsuarios<<endl;
        exit(1);
    }
    report.precision(2);
    report<<fixed;
    encabezado(report,fechaI,fechaF);
    //Variables
    int fecha,dd,mm,aa,cant_repro,cant_like_repro,codigo,ident,
        fechaMejor,codMejor,idenMejor,cont=1;
    char c;
    double ratioViralidad=0,ratioPrueba;
    while(true){
        archTikToks>>dd;
        if(archTikToks.eof())break;
        archTikToks>>c>>mm>>c>>aa;
        fecha=comprimir(dd,mm,aa);
        if(fecha>=fechaI and fecha<=fechaF){
            archTikToks>>cant_like_repro>>cant_repro;
            subencabezado(report,fecha,cont);
            procesoDeTiktoks(fecha,cant_repro,cant_like_repro,
                             codigo,ident,archComentarios,
                             archUsuarios,archPaises,report);
            ratioPrueba=(cant_repro/cant_like_repro)*100;
            if(ratioPrueba>ratioViralidad){
                ratioViralidad=ratioPrueba;
                fechaMejor=fecha;
                codMejor=codigo;
                idenMejor=ident;
            }
            cont++;
        }else while(archTikToks.get()!='\n');
    }
    mejorTiktok(report,fechaMejor,codMejor,idenMejor,archUsuarios);
}
void encabezado(ofstream& report,int fechaI,int fechaF){
    int ddI,mmI,aaI,ddF,mmF,aaF;
    descomprimir(ddI,mmI,aaI,fechaI);
    descomprimir(ddF,mmF,aaF,fechaF);
    report<<right<<setw(90)<<"@TikTok_tp"<<endl
          <<setw(106)<<"REPORTE PARA LA CAMPANA: Parcial 2022-1"<<endl
          <<setw(77)<<"Fecha Inicial: "<<setfill('0')<<setw(2)
          <<ddI<<'/'<<setw(2)<<mmI<<'/'<<setw(4)<<aaI<<" Fecha Final: "
          <<setw(2)<<ddF<<'/'<<setw(2)<<mmF<<'/'<<setw(4)<<aaF<<endl
          <<setfill(' ')<<left;
    linea(report,MAX_LINEA,'=');
}
int comprimir(int dd,int mm,int aa){
    return aa*10000+mm*100+dd;
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
void procesoDeTiktoks(int fecha,int cant_repro,int cant_like_repro,
                      int& codigo,int& ident,ifstream& archComentarios,
                      ifstream& archUsuarios,ifstream& archPaises,
                      ofstream& report){
    //Variables
    int dd,mm,aa,fecha_aux,cod_aux,ident_aux,likes,likes_total=0,
        cant_comentarios=0,cant_seguidoresN=0,cant_seguidores=0,like_mayor=0;
    char c;
    //Reiniciar el cursor
    archComentarios.clear();
    archComentarios.seekg(0,ios::beg);
    while(true){
        archComentarios>>dd;
        if(archComentarios.eof())break;
        archComentarios>>c>>mm>>c>>aa;
        fecha_aux=comprimir(dd,mm,aa);
        if(fecha==fecha_aux){
            while(archComentarios.get()!='\n'){
                archComentarios>>cod_aux>>c>>ident_aux>>ws;
                imprimirString(report,archComentarios,' ','A');
                archComentarios>>likes;
                procesarAutor(cod_aux,ident_aux,likes,
                              cant_seguidores,cant_seguidoresN,
                              archPaises,archUsuarios,report);
                if(like_mayor<likes){
                    like_mayor=likes;
                    codigo=cod_aux;
                    ident=ident_aux;
                }
                likes_total+=likes;
                cant_comentarios++;
            }
        }else while(archComentarios.get()!='\n');
    }
    resumenTiktok(cant_comentarios,cant_seguidores,cant_seguidoresN,
                  likes_total,cant_repro,cant_like_repro,report); 
}
void subencabezado(ofstream& report,int fecha,int cont){
    //Variables
    int dd,mm,aa;
    descomprimir(dd,mm,aa,fecha);
    report<<"Tiktok "<<cont<<") "<<right<<setfill('0')<<setw(2)
          <<dd<<'/'<<setw(2)<<mm<<'/'<<setw(4)<<aa<<left<<setfill(' ')
          <<endl<<endl<<setw(125)<<"COMENTARIO"
          <<setw(23)<<"AUTOR DEL COMENTARIO"
          <<setw(20)<<"CANTIDAD DE LIKES"
          <<setw(10)<<"PAIS DEL AUTOR"<<endl;
    linea(report,MAX_LINEA,'-');
}
void imprimirString(ofstream& report,ifstream& arch,char deli,char aux){
    //Variables
    int cont=0;
    char c;
    while(true){
        c=arch.get();
        if(c==deli)break;
        if(c=='_')report<<" ";
        else report<<c;
        cont++;
    }
    if(aux=='A')report<<setw(133-cont)<<" ";
    else if(aux=='B') report<<setw(22-cont)<<" ";
    else report<<setw(10-cont)<<" ";
}
void procesarAutor(int cod_aux,int ident_aux,int likes,
                   int& cant_seguidores,int& cant_seguidoresN,
                   ifstream& archPaises,ifstream& archUsuarios,
                   ofstream& report){
    //Variables
    int cod,ident,n;
    char c,publico;
    //Reiniciamos el cursor
    archUsuarios.clear();
    archUsuarios.seekg(0,ios::beg);
    while(true){
        archUsuarios>>cod;
        if(archUsuarios.eof())break;
        archUsuarios>>c>>ident>>ws;
        if(cod==cod_aux and ident==ident_aux){
            imprimirString(report,archUsuarios,' ','B');
            archUsuarios>>n>>publico;
            report<<setw(17)<<likes;
            if(publico=='V'){
                cant_seguidores++;
                buscarPais(cod,archPaises,report);
            }else{
                cant_seguidoresN++;
                report<<"Informacion NO publica"<<endl;
            }
            break;
        }else while(archUsuarios.get()!='\n');
    }
}
void buscarPais(int cod,ifstream& archPaises,ofstream& report){
    //Variables
    int cod_aux;
    //Reiniciamos el cursor
    archPaises.clear();
    archPaises.seekg(0,ios::beg);
    while(true){
        archPaises>>cod_aux;
        if(archPaises.eof())break;
        if(cod_aux==cod){
            archPaises>>ws;
            imprimirString(report,archPaises,'\n','C');
            report<<endl;
            break;
        }else while(archPaises.get()!='\n');
    }
}
void resumenTiktok(int cant_comentarios,int cant_seguidores,
                   int cant_seguidoresN,int likes_total,
                   int cant_repro,int cant_like_repro,
                   ofstream& report){
    //Variables
    bool viral=cant_comentarios>(cant_repro/cant_like_repro);
    linea(report,MAX_LINEA,'-');
    report<<setw(60)<<"RESUMEN TIKTOK"
          <<"LIKES:"<<likes_total<<setw(60)<<" " 
          <<"REPRODUCCIONES:"<<cant_repro<<endl 
          <<"Seguidores Publicos:"<<cant_seguidores<<endl
          <<"Seguidores No Publicos:"<<cant_seguidoresN<<setw(106)<<" "
          <<"TIKTOK ";
    if(viral)report<<"VIRAL";
    else report<<"NO VIRAL";
    report<<endl;
    linea(report,MAX_LINEA,'=');
}
void mejorTiktok(ofstream& report,int fechaMejor,int codMejor,
                 int idenMejor,ifstream& arch){
    //Variables
    int aa,dd,mm,cod_aux,ident_aux;
    char c;
    descomprimir(dd,mm,aa,fechaMejor); 
    report<<"RESUMEN MEJOR TIKTOK"<<endl<<setw(15)<<"FECHA: "
          <<right<<setfill('0')<<setw(2)<<dd<<'/'<<setw(2)<<mm
          <<'/'<<setw(4)<<aa<<endl<<setfill(' ')<<left
          <<setw(50)<<"Seguidor que obtuvo mayor numero de likes: ";
    //Reiniciar el cursor
    arch.clear();
    arch.seekg(0,ios::beg);
    while(true){
        arch>>cod_aux;
        if(arch.eof())break;
        arch>>c>>ident_aux;
        if(codMejor==cod_aux and idenMejor==ident_aux){
            arch>>ws;
            imprimirString(report,arch,' ','B');
            break;
        }else while(arch.get()!='\n');
    }

}