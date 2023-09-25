#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;
#include"../header/funciones.h"
#define n_title 50
#define lineas 80
#define al_pro_title 35
void emitiReporte(const char* nomAlmacen, const char* nomProductos,
                const char* nomStock, const char* nomTransacciones,
                const char* nomReporte){
    // Ahora tenemos que abrir y enlazar los archivos
    ifstream Almacen(nomAlmacen, ios::in);
    if(not Almacen.is_open()){
        cout<<"Error en abrir el archivo "<<nomAlmacen<<endl;
        exit(1);
    }
    ifstream Productos(nomProductos, ios::in);
    if(not Productos.is_open()){
        cout<<"Error en abrir el archivo "<<nomProductos<<endl;
        exit(1);
    }
    ifstream Stock(nomStock, ios::in);
    if(not Stock.is_open()){
        cout<<"Error en abrir el archivo "<<nomStock<<endl;
        exit(1);
    }
    ifstream Transacciones(nomTransacciones, ios::in);
    if(not Transacciones.is_open()){
        cout<<"Error en abrir el archivo "<<nomTransacciones<<endl;
        exit(1);
    }
    ofstream Report(nomReporte, ios::out);
    if(not Report.is_open()){
        cout<<"Error en abrir el archivo "<<nomReporte<<endl;
        exit(1);
    }
    // Luego ya enlazados los archivos
    // Designamos la presicion de nuestros decimales
    Report.precision(2);
    Report<<fixed;
    // Ahora creamos nuestras variables
    int num_almacen,num_producto;
    double stockInicial;
    // Imprimimos el encabezado
    encabezado(Report);
    //Realizamos la lectura de datos
    while (true){
        // Lectura de datos de almacen 
        lecturaAlmacen(Almacen,Report,num_almacen);
        if(Almacen.eof())break;
        // Debemos actualizar la lectura de productos
            Productos.clear();
            Productos.seekg(0,ios::beg);
        // Lectura del producto y el stock inicial
        while (true){   
            lecturaProductoYStock(Productos,Stock,Report,num_almacen,num_producto
                                ,stockInicial);
            if(Productos.eof())break;
        }
    }
       
}
void encabezado(ofstream& Report){
    Report<<setw(n_title)<<"DETALLE DE MOVIMIENTOS DE ALMACENES"<<endl;
    espaciado(Report,lineas, '=');
}
void espaciado(ofstream& Report,int num,char signo ){
    for(int i=0;i<num;i++){
        Report<<signo;
    }
    Report<<endl;
}
void lecturaAlmacen(ifstream& Almacen,ofstream& Report,int& num_almacen){
    int distrito;
    Almacen>>num_almacen;
    if(Almacen.eof())return;
    Report<<"ALMACEN: "<<num_almacen<<" - ";
    // Ahora leemos el nombre del almacen y lo imprimimos;
    Almacen>>ws; 
    nombreAlmacen(Almacen,Report);
    // Leemos el distrito y lo imprimimos
    Almacen>>distrito;
    Report<<"DISTRITO: "<<distrito<<endl;
    espaciado(Report,lineas, '=');
}
void nombreAlmacen(ifstream& Almacen,ofstream& Report){
    int contBlancos;
    char c;
    while(true){
        c=Almacen.get();
        if(c==' ')break;
        contBlancos++;
        if(c=='_'){
            Report<<' ';
            continue;
        }
        Report<<c;
    } 
    Report<<setw(al_pro_title-contBlancos)<<' ';   
}
void lecturaProductoYStock(ifstream& Productos,ifstream& Stock,
                        ofstream& Report,int num_almacen,int& num_producto
                            ,double& stockInicial){
    // Leemos el numero del producto
    Productos>>num_producto;
    if(Productos.eof())return;
    // Imprimimos el encabezado
    Report<<setw(10)<<' '<<"PRODUCTO"<<setw(10)<<"STOCK INICIAL"<<endl
            <<num_producto<<" - ";
    //Ahora leemos y imprimimos el nombre del producto
    Productos>>ws;
    Productos.get();
    nombreProducto(Productos,Report);
    Report<<endl;
    // Ahora buscamos el stock inicial 

}
void nombreProducto(ifstream& Productos,ofstream& Report){
    int contBlancos;
    bool primera =true;
    char c;
    while(true){
        c=Productos.get();
        if(c==')')break;
        contBlancos++;
        c+=(primera or c<'A')?0:'a'-'A';
        Report<<c;
        primera=false;
    } 
    Report<<setw(al_pro_title-contBlancos)<<' ';  
}
