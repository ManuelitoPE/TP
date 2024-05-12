//Authot: Mako
#include<iostream>
#include<iomanip>
#include<fstream>
using namespace std;
#include "header/funciones.h"
#define MAX_LINEA 100
#define NO_ENCONTRADO -1

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
    int cod_almacen,cod_postal;
    while (true){
        archAlmacen>>cod_almacen;
        if(archAlmacen.eof())break;
        report<<"ALMACEN: "<<cod_almacen<<" - ";archAlmacen>>ws;
        imprimirString(report,archAlmacen,' ','A'); archAlmacen>>cod_postal;
        report<<"DISTRITO: "<<cod_postal<<endl;
        linea(report,MAX_LINEA,'=');
        procesoDeDatos(cod_almacen,cod_postal,archProductos,
                       archStockProductos,archTransacciones,
                       report);
    }
    
}
void encabezado(ofstream& report){
    report<<setw(50)<<"DETALLE DE MOVIMIENTO DE ALMACENES"<<endl;
    linea(report,MAX_LINEA,'=');
}
void linea(ofstream& report,int n,char c){
    for (int i = 0; i < n; i++)report<<c;
    report<<endl;
}
void imprimirString(ofstream& report,ifstream& arch,
                    char deli,char aux){
    //Variables
    int cont=0;
    char c;
    while(true){
        c=arch.get();
        if(c==deli)break;
        if(aux=='A' and c=='_'){
            report<<" ";
            cont++;
            continue;
        }else if(aux=='B' and cont!=0){
            c+=('A'<= c and c<='Z')?'a'-'A':0;
        }
        report<<c;
        cont++;
    }
    if(aux=='A')report<<setw(35-cont)<<" ";
    else if(aux=='B')report<<setw(60-cont)<<" ";
}
void procesoDeDatos(int cod_almacen,int cod_postal,
                    ifstream& archProductos,ifstream& archStockProductos,
                    ifstream& archTransacciones,ofstream& report){
    //Variables
    int cod_producto,stock_producto;

    //Reiniciar el cursor
    archProductos.clear();
    archProductos.seekg(0,ios::beg);
    while(true){
        archProductos>>cod_producto;
        if(archProductos.eof())break;
        stock_producto=buscarStock(archStockProductos,cod_producto,cod_almacen);
        report<<setw(10)<<" "<<left<<setw(55)<<"PRODUCTO"<<"STOCK INICIAL"<<endl
              <<cod_producto<<"  -  "; archProductos>>ws; archProductos.get();
        imprimirString(report,archProductos,')','B'); report<<stock_producto<<endl;
        procesoDeTransacciones(cod_almacen,cod_postal,cod_producto,stock_producto,
                               archTransacciones,report);
    }
}
int buscarStock(ifstream& archStockProductos,int cod_producto,
                int cod_almacen){
    //Variables
    int aux_cod_producto,aux_cod_almacen,aux_stock;
    //Reiniciamos el cursor 
    archStockProductos.clear();
    archStockProductos.seekg(0,ios::beg);
    while (true){
        archStockProductos>>aux_cod_producto;
        if(archStockProductos.eof())break;
        archStockProductos>>aux_cod_almacen>>aux_stock;
        if(aux_cod_almacen==cod_almacen and aux_cod_producto == cod_producto){
            return aux_stock;
        }
    }
    return 0;
}
void procesoDeTransacciones(int cod_almacen,int cod_postal,
                            int cod_producto,int stock_producto,
                            ifstream& archTransacciones,ofstream& report){
    //Variables
    int aux_almacen,dd,mm,aa,hh,min,ss,aux_producto,cantidad,
        aux_almacen_t;
    int totalI=0,totalS=0,totalTE=0,totalTR=0,totalStock=0;
    char c,tipo;
    //Reiniciar el cursor
    archTransacciones.clear();
    archTransacciones.seekg(0,ios::beg);
    subEncabezado(report);
    while(true){
        archTransacciones>>aux_almacen;
        if(archTransacciones.eof())break;
        archTransacciones>>dd>>c>>mm>>c>>aa;
        while(archTransacciones.get()!='\n'){
            aux_almacen_t=0;
            archTransacciones>>hh>>c>>min>>c>>ss>>aux_producto
                             >>cantidad>>tipo;
            if(tipo=='T')archTransacciones>>aux_almacen_t;
            if(aux_producto==cod_producto and (aux_almacen==cod_almacen 
               or aux_almacen_t==cod_almacen)){
                imprimirT(aux_almacen,dd,mm,aa,hh,min,ss,cantidad,
                          aux_almacen_t,totalI,totalS,totalTE,totalTR,
                          totalStock,tipo,cod_almacen,report);
            }
        }
    }
    impresionResumen(totalI,totalS,totalTE,totalTR,totalStock,stock_producto,
                     report);
}
void subEncabezado(ofstream& report){
    linea(report,MAX_LINEA,'-');
    report<<"TRANSACCIONES"<<endl<<setw(2)<<" "<<setw(13)<<"Fecha"
          <<setw(9)<<"Hora"
          <<setw(12)<<"Cantidad"
          <<setw(40)<<"Tipo"<<"Almacen"<<endl;
}
void imprimirT(int almacen,int dd,int mm,int aa,int hh,int min,
               int ss,int cantidad,int almacen_t,int& totalI,
               int& totalS,int& totalTE,int& totalTR,int& totalStock,char tipo,
               int cod_almacen,ofstream& report){
    report<<setfill('0')<<right<<setw(2)<<dd<<'/'<<setw(2)<<mm
          <<'/'<<setw(4)<<aa<<setfill(' ')<<left<<setw(3)<<" "
          <<setfill('0')<<right<<setw(2)<<hh<<':'<<setw(2)<<min
          <<':'<<setw(2)<<ss<<setfill(' ')<<left<<setw(5)<<" "
          <<setw(10)<<cantidad;
    if(tipo=='I'){
        report<<"Ingreso";totalI+=cantidad;
    }else if(tipo=='S'){
        report<<"Salida"; totalS+=cantidad;
    }else if(almacen_t==cod_almacen){
        report<<setw(40)<<"Transferencia desde otro almacen "<<almacen;
        totalTR+=cantidad;
    }else{
        report<<setw(40)<<"Transferencia a otro almacen "<<almacen_t;
        totalTE+=cantidad;
    }
    report<<endl;
}
void impresionResumen(int totalI,int totalS,int totalTE,int totalTR,
                      int totalStock,int stock_producto,
                      ofstream& report){
    linea(report,MAX_LINEA,'-');
    report<<setw(78)<<"TOTAL DE INGRESOS DESDE EL PROVEEDOR:"<<totalI<<endl
          <<setw(78)<<"TOTAL DE SALIDAS HACIA EL CLIENTE:"<<totalS<<endl
          <<setw(78)<<"TOTAL DE TRANSFERENCIAS ENVIADAS A OTROS ALMACENES:"<<totalTE<<endl
          <<setw(78)<<"TOTAL DE TRANSFERENCIAS RECIBIDAS DESDE OTROS ALMACENES:"<<totalTR<<endl;
    linea(report,MAX_LINEA,'-');
    totalStock= stock_producto+totalI-totalS-totalTE+totalTR;
    report<<"STOCK FINAL: "<<totalStock;
    if(totalStock<0)report<<" (ERROR EN TRANSACCIONES)"<<endl;
    else report<<endl;
    linea(report,MAX_LINEA,'-');
}