//Author: MAKO
#include<iostream>
#include<iomanip>
#include<fstream>
using namespace std;
#include "header/funciones.h"
#define MAX_LINEA 110
#define NO_ENCONTRADO -1

void pedirDatos(int& fechaI,int& fechaF){
    //Variables
    int ddI=1,mmI=1,aaI=2023,ddF=30,mmF=5,aaF=2023;
    char c;
    // cout<<setw(70)<<"CONSOLIDADO DE STOCKS DE PRODUCSTOS POR ALMACEN"<<endl;
    // for (int i = 0; i < MAX_LINEA; i++)cout<<'=';cout<<endl;
    // cout<<"Ingrese el intervalo de fechas(xx/xx/xxxx-xx/xx/xxxx): ";
    // cin>>ddI>>c>>mmI>>c>>aaI>>c>>ddF>>c>>mmF>>c>>aaF;
    fechaI= comprimir(ddI,mmI,aaI);
    fechaF= comprimir(ddF,mmF,aaF);
}
int comprimir(int dd,int mm,int aa){
    return aa*10000+mm*100+dd;
}
void cargarStocks(int* ARRcod_pro,int* ARRcod_almacen,
                  int* ARRstock,int& stocks,
                  const char* nomStockProductos){
    ifstream arch(nomStockProductos,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomStockProductos<<endl;
        exit(1);
    }
    //Variables
    int cod_almacen,cod_producto,stock;
    while(true){
        arch>>cod_producto;
        if(arch.eof())break;
        arch>>cod_almacen>>stock;
        ARRcod_almacen[stocks]=cod_almacen;
        ARRcod_pro[stocks]=cod_producto;
        ARRstock[stocks]=stock;
        stocks++;
    }
}
void procesoDatos(const char* nomTransacciones,int* ARRcod_pro,
                  int* ARRcod_almacen,int* ARRstock,int* ARRingresos,
                  int* ARRsalidas,int* ARRenviados,int* ARRrecibidos,
                  int* ARRstockFinal,int stocks,int fechaI,
                  int fechaF){
    ifstream arch(nomTransacciones,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomTransacciones<<endl;
        exit(1);
    }
    //Variables
    int aux_almacen,dd,mm,aa,n,aux_producto,cantidad,
        aux_almacen_t,pos,aux_pos,aux_fecha;
    char tipo,c;
    while(true){
        arch>>aux_almacen;
        if(arch.eof())break;
        arch>>dd>>c>>mm>>c>>aa; aux_fecha=comprimir(dd,mm,aa);
        if(aux_fecha>=fechaI and aux_fecha<=fechaF){
            while(arch.get()!='\n'){
                arch>>n>>c>>n>>c>>n>>aux_producto
                    >>cantidad>>tipo;
                if(tipo=='T')arch>>aux_almacen_t;
                else aux_almacen_t=0;
                pos=buscar(ARRcod_almacen,ARRcod_pro,aux_almacen,aux_producto,
                        stocks);
                aux_pos=buscar(ARRcod_almacen,ARRcod_pro,aux_almacen_t,aux_producto,
                        stocks);
                if(pos!=NO_ENCONTRADO){
                    if(tipo=='I')ARRingresos[pos]+=cantidad;
                    else if(tipo=='S')ARRsalidas[pos]+=cantidad;
                    else{
                        ARRenviados[pos]+=cantidad;
                        ARRrecibidos[aux_pos]+=cantidad;
                    }
                }
            }
        }else while(arch.get()!='\n');
    }
    for (int i = 0; i < stocks; i++)
        ARRstockFinal[i]=ARRstock[i]+ARRingresos[i]-ARRsalidas[i]
                         -ARRenviados[i]+ARRrecibidos[i];
}
int buscar(int* ARRcod_almacen,int* ARRcod_pro,int aux_almacen,
           int aux_producto,int stocks){
    for (int i = 0; i < stocks; i++){
        if(ARRcod_almacen[i]==aux_almacen and ARRcod_pro[i]==aux_producto){
            return i;
        }   
    }
    return NO_ENCONTRADO;
}
void ordenar(int* ARRcod_almacen,int* ARRcod_pro,int* ARRstock,
             int* ARRingresos,int* ARRsalidas,int* ARRenviados,
             int* ARRrecibidos,int* ARRstockFinal,int stock){
    for (int i = 0; i < stock-1; i++){
        for (int k = i+1; k < stock; k++){
            if(ARRcod_almacen[i]>ARRcod_almacen[k] or 
               (ARRcod_almacen[i]==ARRcod_almacen[k] and
               ARRcod_pro[i]<ARRcod_pro[k])){
                cambiarInt(ARRcod_almacen[i],ARRcod_almacen[k]);
                cambiarInt(ARRcod_pro[i],ARRcod_pro[k]);
                cambiarInt(ARRstock[i],ARRstock[k]);
                cambiarInt(ARRingresos[i],ARRingresos[k]);
                cambiarInt(ARRsalidas[i],ARRsalidas[k]);
                cambiarInt(ARRenviados[i],ARRenviados[k]);
                cambiarInt(ARRrecibidos[i],ARRrecibidos[k]);
                cambiarInt(ARRstockFinal[i],ARRstockFinal[k]);
               }
        }
    }
}
void cambiarInt(int& i,int& k){
    int aux; aux=i; i=k; k=aux;
}
void emitirReporte(int* ARRcod_almacen,int* ARRcod_pro,int* ARRstock,
                   int* ARRingresos,int* ARRsalidas,int* ARRenviados,
                   int* ARRrecibidos,int* ARRstockFinal,int stocks,
                   const char* nomReporte,int fechaI,int fechaF){
    ofstream report(nomReporte,ios::out);
    if(not report.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomReporte<<endl;
        exit(1);
    }
    encabezado(report,fechaI,fechaF);
    //Variables 
    int aux_almacen=0;
    for (int i = 0; i < stocks; i++){
        if(aux_almacen!=ARRcod_almacen[i]){
            if(i!=0)linea(report,MAX_LINEA,'=');
            subeEncabezado(report,ARRcod_almacen[i]);
            aux_almacen=ARRcod_almacen[i];
        }
        report<<setw(2)<<" "<<setw(13)<<ARRcod_pro[i]
          <<setw(16)<<ARRstock[i]
          <<setw(10)<<ARRingresos[i]
          <<setw(13)<<ARRsalidas[i]
          <<setw(18)<<ARRenviados[i]
          <<setw(17)<<ARRrecibidos[i]
          <<setw(10)<<ARRstockFinal[i];
        if(ARRstockFinal[i]<0)report<<"Trans.Incorrectas"<<endl;
        else report<<endl;
    }
    
}
void encabezado(ofstream& report,int fechaI,int fechaF){
    //Varibles
    int ddI,mmI,aaI,ddF,mmF,aaF;
    descomprimir(ddI,mmI,aaI,fechaI);
    descomprimir(ddF,mmF,aaF,fechaF);
    report<<setw(80)<<"CONSOLIDADO DE STOCKS DE PRODUCTOS POR ALMACEN"<<endl
          <<setw(45)<<"DEL "<<setfill('0')<<right<<setw(2)<<ddI<<'/'
          <<setw(2)<<mmI<<'/'<<setw(4)<<aaI<<" AL "<<setw(2)<<ddF<<'/'
          <<setw(2)<<mmF<<'/'<<setw(4)<<aaF<<setfill(' ')<<left<<endl;
    linea(report,MAX_LINEA,'=');
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
void subeEncabezado(ofstream& report,int almacen){
    report<<"ALMACEN: "<<almacen<<endl;
    linea(report,MAX_LINEA,'-');
    report<<setw(11)<<"PRODUCTO"
          <<setw(16)<<"STOCK INICIAL"
          <<setw(11)<<"INGRESOS"
          <<setw(10)<<"SALIDAS"
          <<setw(17)<<"ENVIADO A ALM."
          <<setw(19)<<"RECIBIDO DE ALM."
          <<setw(14)<<"STOCK FINAL"<<"OBSERVACION"<<endl;
    linea(report,MAX_LINEA,'-');
}




