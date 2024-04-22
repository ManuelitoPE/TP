//Author: MAKO
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "header/funciones.h"
#define MAX_LINEA 87
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
    report<<setw(60)<<"DETALLE DE MOVIMIENTOS DE ALMACENES"<<endl;
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
    if(almacen)report<<setw(51-cont)<<" ";
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
        archProductos>>producto;
        if(archProductos.eof())break;
        report<<setw(8)<<" "<<setw(60)<<"PRODUCTO"<<"STOCK INICIAL"<<endl;
        archProductos>>ws; archProductos.get(); report<<producto<<" - ";
        impresionNombre(report,archProductos,false); 
        busquedaStock(almacen,producto,stock,archStockProductos);
        report<<stock<<endl; linea(report,MAX_LINEA,'-');
        encabezado2(report);
        impresionTransacciones(almacen,producto,stock,archTransacciones,
                               report);
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
void impresionTransacciones(int almacen,int producto,int stock,
                            ifstream& archTransacciones,
                            ofstream& report){
    //Variables
    int aux_almacen,dd,mm,aa,hh,min,ss,aux_producto,cant,trans_almacen=0;
    int stockFinal,ingresosT=0,salidasT=0,enviadasT=0,recibidasT=0;
    char tipo,c;
    //Reiniciamos el cursor
    archTransacciones.clear();
    archTransacciones.seekg(0,ios::beg);
    while(true){
        archTransacciones>>aux_almacen;
        if(archTransacciones.eof())break;
        archTransacciones>>dd>>c>>mm>>c>>aa;
        while(archTransacciones.get()!='\n'){
            trans_almacen=0;
            archTransacciones>>hh>>c>>min>>c>>ss
                             >>aux_producto>>cant>>tipo;
            if(tipo=='T')archTransacciones>>trans_almacen;
            if((almacen==aux_almacen or almacen==trans_almacen)
                and producto==aux_producto){
                imprimirDatos(almacen,dd,mm,aa,hh,min,ss,
                              producto,cant,trans_almacen,
                              ingresosT,salidasT,
                              enviadasT,recibidasT,tipo,
                              aux_almacen,report);
            }
        }
    }
    linea(report,MAX_LINEA,'-');
    impresionTotales(stock,stockFinal,ingresosT,salidasT,enviadasT,recibidasT,
                     report);
}
void imprimirDatos(int almacen,int dd,int mm,int aa,int hh,int min,
                   int ss,int producto,int cant,int trans_almacen,
                   int& ingresosT,int& salidasT,
                   int& enviadasT,int& recibidasT,char tipo,
                   int aux_almacen,ofstream& report){
    report<<right<<setfill('0')<<setw(2)<<dd<<'/'<<setw(2)<<mm
          <<'/'<<setw(4)<<aa<<setfill(' ')<<setw(3)<<" "
          <<setfill('0')<<setw(2)<<hh<<':'<<setw(2)<<min
          <<':'<<setw(2)<<ss<<setfill(' ')<<setw(6)<<" "
          <<left<<setw(10)<<cant;
    determinacionTipo(tipo,cant,ingresosT,salidasT,enviadasT,
                      recibidasT,trans_almacen,almacen,aux_almacen,report);
    report<<endl;
}
void encabezado2(ofstream& report){
    report<<"TRANSACCIONES"<<endl
          <<setw(15)<<"Fecha"
          <<setw(10)<<"Hora"
          <<setw(12)<<"Cantidad"
          <<setw(39)<<"Tipo"
          <<setw(10)<<"Almacen"<<endl;
}
void determinacionTipo(char tipo,int cant,int& ingresosT,int& salidasT,
                       int& enviadasT,int& recibidasT,int trans_almacen,
                       int almacen,int aux_almacen,ofstream& report){
    report<<setw(40);
    if(tipo=='I'){
        report<<"Ingreso";
        ingresosT+=cant;
    }else if(tipo=='S'){
        report<<"Salida";
        salidasT+=cant;
    }else if(tipo=='T' and trans_almacen!=almacen){
        report<<"Transferecnia a otro almacen"<<trans_almacen;
        enviadasT+=cant;
    }else{
        report<<"Transferencia desde otro almacen"<<aux_almacen;
        recibidasT+=cant;
    }
}
void impresionTotales(int stock,int stockFinal,int ingresosT,
                      int salidasT,int enviadasT,int recibidasT,
                      ofstream& report){
    report<<setw(70)<<"TOTAL DE INGRESOS DESDE EL PROVEEDOR:"<<ingresosT<<endl
          <<setw(70)<<"TOTAL DE SALIDAS HACIA EL CLIENTE:"<<salidasT<<endl
          <<setw(70)<<"TOTAL DE TRANSFERECNIAS ENVIADAS A OTROS ALMACENES:"<<enviadasT<<endl
          <<setw(70)<<"TOTAL DE TRANSFERECNIAS RECIBIDAS A OTROS ALMACENES:"<<recibidasT<<endl;
    stockFinal=stock+ingresosT-salidasT-enviadasT+recibidasT;
    linea(report,MAX_LINEA,'-');
    report<<"STOCK FINAL: "<<stockFinal<<endl;
    linea(report,MAX_LINEA,'=');
}