//Author: MAKO
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "header/funciones.h"
#define MAX_LINEA 100
void emitirReporte(const char* nomAlmacen,const char* nomProductos,
                   const char* nomStockProductos,const char* nomTransacciones,
                   const char* nomReporte){
    ifstream archAlmacen(nomAlmacen,ios::in);
    if(not archAlmacen.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomAlmacen<<endl;
        exit(1);
    }
    ifstream archProductos(nomProductos,ios::in);
    if(not archProductos.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomProductos<<endl;
        exit(1);
    }
    ifstream archStockProductos(nomStockProductos,ios::in);
    if(not archStockProductos.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomStockProductos<<endl;
        exit(1);
    }
    ifstream archTransacciones(nomTransacciones,ios::in);
    if(not archTransacciones.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomTransacciones<<endl;
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
    int almacen;
    while (true){
        lecturAlmacen(almacen,report,archAlmacen);
        if(archAlmacen.eof())break;
        lecturaProductos(almacen,archProductos,archStockProductos,
                         archTransacciones,report);
    }
}
void encabezado(ofstream& report){
    report<<setw(65)<<"DETALLE DE MOVIMIENTOS DE ALMACENES"<<endl;
    linea(report,MAX_LINEA,'=');
}
void linea(ofstream& report,int n,char c){
    for (int i = 0; i < n; i++)report<<c;
    report<<endl;
}
void lecturAlmacen(int& almacen,ofstream& report,
                   ifstream& archAlmacen){
    //Variables
    int distrito;
    archAlmacen>>almacen; 
    if(archAlmacen.eof())return;
    archAlmacen>>ws; report<<"ALMACEN: "<<almacen<<" - "<<left;
    impresionNombre(report,archAlmacen,true);
    archAlmacen>>distrito; report<<"DISTRITO: "<<distrito<<endl;
    linea(report,MAX_LINEA,'=');
}
void impresionNombre(ofstream& report,ifstream& arch,
                     bool almacen){
    int cont=0;
    char c;
    bool mayuscula=true;
    while(true){
        c=arch.get();
        if(!almacen){
            if(c==')')break;
            if(c!=' ' and c>='A')c+=(mayuscula)?0:'a'-'A';
            mayuscula=false;
        }else{ 
            if(c==' ')break;
            if(c=='_'){
                report<<" ";
                cont++;
                continue;
            }
        }
        report<<c;
        cont++;
    }
    if(almacen)report<<setw(40-cont)<<" ";
    else report<<setw(64-cont)<<" "; 
}
void lecturaProductos(int almacen,ifstream& archProductos,
                      ifstream& archStockProductos,
                      ifstream& archTransacciones,
                      ofstream& report){
    //Variables
    int producto;
    int stock;
    //Reiniciamos le cursor
    archProductos.clear();
    archProductos.seekg(0,ios::beg);
    while(true){
        report<<setw(8)<<" "<<setw(60)<<"PRODUCTO"<<"STOCK INICIAL"<<endl;
        archProductos>>producto;
        if(archProductos.eof())break;
        archProductos>>ws; archProductos.get(); report<<producto<<" - ";
        impresionNombre(report,archProductos,false); 
        busquedaStock(almacen,producto,stock,archStockProductos);
        report<<stock<<endl; linea(report,MAX_LINEA,'-');

    }
    linea(report,MAX_LINEA,'=');
}
void busquedaStock(int almacen,int producto,int& stock,
                   ifstream& archStockProductos){
    //Variables
    int aux_producto,aux_almacen;
    //Reinicimos el cursor
    archStockProductos.clear();
    archStockProductos.seekg(0,ios::beg);
    while (true){
        archStockProductos>>aux_producto;
        if(archStockProductos.eof())break;
        archStockProductos>>aux_almacen;
        if(aux_almacen==almacen and aux_producto==producto){
            archStockProductos>>stock;
            break;
        }else while(archStockProductos.get()!='\n');
    }
}

