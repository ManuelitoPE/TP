#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;
#include"../header/funciones.h"
#define n_title 50
#define lineas 80
#define almacen_title 30
#define producto_title 80
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
            lecturaProductoYStock(Productos,Stock,Report,num_almacen,num_producto);
            if(Productos.eof())break;
            // Debemos actualizar la lectura de stock
            Stock.clear();
            Stock.seekg(0,ios::beg);
            lecturaEImpresionStock(Report,Stock,num_almacen,num_producto, stockInicial);
            // Transferencias
            impresionTransacciones(Transacciones,Report,num_almacen,num_producto);
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
    Report<<setw(almacen_title-contBlancos)<<' ';   
}
void lecturaProductoYStock(ifstream& Productos,ifstream& Stock,
                        ofstream& Report,int num_almacen,int& num_producto){    
    // Leemos el numero del producto
    Productos>>num_producto;
    if(Productos.eof())return;
    // Imprimimos el encabezado
    Report<<setw(10)<<' '<<"PRODUCTO"<<right<<setw(60)<<"STOCK INICIAL"<<endl
            <<num_producto<<" - ";
    //Ahora leemos y imprimimos el nombre del producto
    Productos>>ws;
    Productos.get();
    nombreProducto(Productos,Report);
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
    Report<<left<<setw(producto_title-contBlancos)<<' ';
}
void lecturaEImpresionStock(ofstream& Report,ifstream& Stock,
                            int num_almacen,int num_producto, double& stockInicial){
    int almacenREF, productoREF;
    while(true){
        Stock>>productoREF>>almacenREF>>stockInicial;
        if(productoREF==num_producto && almacenREF==num_almacen)break;
    }
    Report<<right<<stockInicial<<left<<endl;
    espaciado(Report,lineas, '-');
}
void impresionTransacciones(ifstream& Transacciones,ofstream& Report,
                            int num_almacen, int num_producto){
    int producto,almacen, dd,mm,aa,hh,min,seg,cantidad,almacenT;
    char c,tipo;
    // ENCABEZADO
    Report<<left<<"TRANSACCIONES"<<endl<<setw(15)<<"Fecha"
                <<setw(15)<<"Hora"<<setw(15)<<"Cantidad"<<setw(20)<<"Tipo"
                <<setw(15)<<"Almacen"<<endl;
    // Reiniciamos el puntero
    Transacciones.clear();
    Transacciones.seekg(0, ios::beg);
    while(true){
        // Confirmamos que es del almacen
        Transacciones>>almacen;
        if(Transacciones.eof())break;
        Transacciones>>dd>>c>>mm>>c>>aa;
        while(true){
            if(Transacciones.get()=='\n')break;
            Transacciones>>hh>>c>>min>>c>>seg>>producto>>cantidad>>tipo;
            if(tipo=='T')Transacciones>>almacenT;
            if(producto==num_producto && (almacen==num_almacen or almacenT==num_almacen)){
                // IMPRIMIMOS LOS DATOS
                Report<<right<<setfill('0')<<setw(2)<<dd<<'/'<<setw(2)
                <<mm<<'/'<<setw(4)<<aa<<setfill(' ')<<setw(4)<<' '
                <<setfill('0')<<setw(2)<<hh<<':'<<setw(2)<<min<<':'
                <<setw(2)<<seg<<setfill(' ')<<setw(4)<<' '<<setw(8)<<cantidad
                <<setw(5)<<' ';
                impresionTIPO(Report,tipo, almacenT);
            } 
        }
    }
    espaciado(Report,lineas, '-');
}
void impresionTIPO(ofstream& Report,char tipo,int almacen){
    if(tipo=='I'){
        Report<<"Ingreso"<<setw(15)<<' '<<endl;
    }else if(tipo=='S'){
        Report<<"Salida"<<setw(15)<<' '<<endl;        
    }else{
        Report<<"Transferencia"<<setw(15)<<' '<<almacen<<endl;
    }
}

