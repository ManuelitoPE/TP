//Author: MAKO
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "../header/funciones.h"
#include "../header/Farmacia.h"
#include "../header/ProductosNoProcesados.h"
#define MAX_LINEA 80
#define NO_ENCONTRADO -1
void crearFarmacias(const char* nomArch,const char* nomArchBin){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: Se produjo un error al abrir el archivo "<<nomArch<<endl;
        exit(1);
    }
    ofstream archBin(nomArchBin,ios::out|ios::binary);
    if(not archBin.is_open()){
        cout<<"ERROR: Se produjo un error al abrir el archivo "<<nomArchBin<<endl;
        exit(1);
    }
    //Variables
    int codigo;
    char c,distrito[20];
    struct Farmacia farmacia{};
    while(true){
        arch>>codigo;
        if(arch.eof())break;
        arch.get();
        arch.getline(distrito,20,'\n');
        farmacia.codigo=codigo;
        strcpy(farmacia.distrito,distrito);
        farmacia.cantProductos=0;
        archBin.write(reinterpret_cast<const char*>(&farmacia),
                    sizeof(struct Farmacia));
    }
}
void crearReporteFarmacias(const char* nomArchBin,
                            const char* nomArch){
    ifstream archBin(nomArchBin,ios::in);
    if(not archBin.is_open()){
        cout<<"ERROR: Se produjo un error al abrir el archivo "<<nomArchBin<<endl;
        exit(1);
    }
    ofstream arch(nomArch,ios::out);
    if(not arch.is_open()){
        cout<<"ERROR: Se produjo un error al abrir el archivo "<<nomArch<<endl;
        exit(1);
    }
    //Variables
    int i=0;
    struct Farmacia farmacia{};
    encabezado(arch);
    while(true){
        archBin.read(reinterpret_cast<char*>(&farmacia),
                    sizeof(struct Farmacia));
        if(archBin.eof())break;
        arch<<right<<setfill('0')<<setw(2)<<i+1<<") "<<setfill(' ')
            <<left<<setw(10)<<farmacia.codigo
            <<setw(20)<<farmacia.distrito<<endl;
        i++;
    }
}
void encabezado(ofstream& arch){
    arch<<right<<setw(30)<<"REPORTE SIMPLE FARMACIA"<<left<<endl;
    linea(arch,'=',MAX_LINEA-40);
    arch<<setw(15)<<"CODIGO"<<setw(20)<<"DISTRITO"<<endl;
    linea(arch,'-',MAX_LINEA-40);
}
void linea(ofstream& arch, char signo, int num){
    for(int i=0;i<num;i++){
        arch<<signo;
    }
    arch<<endl;
}
void actualizarFarmacias(const char* nomArchFarmacia,
                    const char* nomArch,
                    const char* nomArchProductoNoProcesados){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: Se produjo un error al abrir el archivo "<<nomArch<<endl;
        exit(1);
    }
    crearArchBinario(nomArchProductoNoProcesados);
    fstream archFarmacia(nomArchFarmacia,ios::out|ios::in|ios::binary);
    if(not archFarmacia.is_open()){
        cout<<"ERROR: Se produjo un error al abrir el archivo "<<nomArchFarmacia<<endl;
        exit(1);
    }
    fstream archNoProcesados(nomArchProductoNoProcesados,
                            ios::out|ios::in|ios::binary);
    if(not archNoProcesados.is_open()){
        cout<<"ERROR: Se produjo un error al abrir el archivo "
            <<nomArchProductoNoProcesados<<endl;
        exit(1);
    }
    //Variables
    int codigoFarmacia,cantidad;
    double precio;
    char c,codigoProducto[8],nombre[40];
    while(true){
        arch>>codigoFarmacia;
        if(arch.eof())break;
        arch.get();
        arch.getline(codigoProducto,20,',');
        arch.getline(nombre,40,',');
        arch>>cantidad>>c>>precio;
        arch.get();
        ingresarDatosFarmacia(codigoFarmacia,cantidad,
                precio,codigoProducto,nombre,archFarmacia,
                archNoProcesados);
    }
}
void crearArchBinario(const char* nomArchBin){
    ofstream archBin(nomArchBin,ios::out|ios::binary);
    if(not archBin.is_open()){
        cout<<"ERROR: Se produjo un error al abrir el archivo "<<nomArchBin<<endl;
        exit(1);
    }
}
void ingresarDatosFarmacia(int codigoFarmacia,int cantidad,
                double precio,char* codigoProducto,char* nombre,
                fstream& archFarmacia,fstream& archNoProcesados){
    //Variables 
    int sizeFarmacia,cantFarmacias,posFarmacia,posProducto;
    struct Farmacia farmacia{};
    struct ProductosNoProcesados noProcesado{};
    sizeFarmacia=sizeof(struct Farmacia);
    cantFarmacias=cantidadEstructuras(archFarmacia,sizeFarmacia);
    posFarmacia=buscarFarmacia(archFarmacia,cantFarmacias,
                            codigoFarmacia);
    if(posFarmacia!=NO_ENCONTRADO){
        archFarmacia.seekg(posFarmacia*sizeFarmacia,ios::beg);
        archFarmacia.read(reinterpret_cast<char*>(&farmacia),sizeFarmacia);
        posProducto=buscarProducto(farmacia.cantProductos,
                                farmacia.productosVendidos,codigoProducto);
        if(farmacia.cantProductos>=10){
            ingresoDeNoProcesadoss(noProcesado,codigoFarmacia,cantidad,
                                precio,codigoProducto,nombre);
            archNoProcesados.write(reinterpret_cast<const char*>(&noProcesado),
                    sizeof(struct ProductosNoProcesados));
            archNoProcesados.flush();
        }else{
            if(posProducto==NO_ENCONTRADO){
                posProducto=farmacia.cantProductos;
                farmacia.cantProductos++;
            }
            ingresoDeProductos(farmacia.productosVendidos[posProducto],
                            cantidad,precio,codigoProducto,
                            nombre);
            archFarmacia.seekg(posFarmacia*sizeFarmacia,ios::beg);
            archFarmacia.write(reinterpret_cast<const char*>(&farmacia),
                        sizeFarmacia);
            archFarmacia.flush();
        }
    }else{
        cout<<"La farmacia "<<codigoFarmacia<<" no fue encontrada"<<endl;
    }
}
int cantidadEstructuras(fstream& arch,int size){
    int cant;
    arch.seekg(0,ios::end);
    cant=arch.tellg();
    arch.seekg(0,ios::beg);
    return cant/size;
}
int buscarFarmacia(fstream& archFarmacia,int cantFarmacias,
                int codigoFarmacia){
    //Variables
    struct Farmacia farmacia{};
    archFarmacia.seekg(0,ios::beg);
    for(int i=0;i<cantFarmacias;i++){
        archFarmacia.read(reinterpret_cast<char*>(&farmacia),
                        sizeof(struct Farmacia));
        if(farmacia.codigo==codigoFarmacia)return i;
    }
    return NO_ENCONTRADO;
}
int buscarProducto(int cantProductos,
            struct Producto *productosVendidos,char* codigoProducto){
    //Variables
    for(int i=0;i<cantProductos;i++){
        if(strcmp(productosVendidos[i].codigo,codigoProducto)==0)return i;
    }
    return NO_ENCONTRADO;
}
void ingresoDeProductos(struct Producto &producto,int cantidad,
                        double precio,char* codigoProducto,
                        char* nombre){
    producto.cantidad+=cantidad;
    strcpy(producto.codigo,codigoProducto);
    strcpy(producto.nombre,nombre);
    producto.recaudado+= cantidad*precio;
}
void ingresoDeNoProcesadoss(struct ProductosNoProcesados &noProcesado,
                        int codigoFarmacia,int cantidad,
                        double precio,char* codigoProducto,
                        char* nombre){
    noProcesado.cantidadVendida=cantidad;
    noProcesado.codigoFarmacia=codigoFarmacia;
    strcpy(noProcesado.codigoProducto,codigoProducto);
    strcpy(noProcesado.nombreProducto,nombre);
    noProcesado.precio=precio;
}
void emitirReporte(const char* nomArchFarmacia,
                    const char* nomArchProductoNoProcesados,
                    const char* nomArch){
    ofstream arch(nomArch,ios::out);
    if(not arch.is_open()){
        cout<<"ERROR: Se produjo un error al abrir el archivo "<<nomArch<<endl;
        exit(1);
    }
    ifstream archFarmacia(nomArchFarmacia,ios::in|ios::binary);
    if(not archFarmacia.is_open()){
        cout<<"ERROR: Se produjo un error al abrir el archivo "<<nomArchFarmacia<<endl;
        exit(1);
    }
    ifstream archNoProcesados(nomArchProductoNoProcesados,
                            ios::in|ios::binary);
    if(not archNoProcesados.is_open()){
        cout<<"ERROR: Se produjo un error al abrir el archivo "
            <<nomArchProductoNoProcesados<<endl;
        exit(1);
    }
    imprimirDatosFarmacias(archFarmacia,arch);
    imprimirDatosProductosNoProcesados(archNoProcesados,arch);
}
void imprimirDatosFarmacias(ifstream& archFarmacia,ofstream& arch){
    //Variables
    struct Farmacia farmacia{};
    encabezado1(arch);
    while(true){
        archFarmacia.read(reinterpret_cast<char*>(&farmacia),
                        sizeof(struct Farmacia));
        if(archFarmacia.eof())break;
        arch<<left<<"CODIGO: "<<setw(30)<<farmacia.codigo
            <<"DISTRITO: "<<farmacia.distrito<<endl;
        linea(arch,'-',MAX_LINEA);
        subEncabezado(arch);
        for(int i=0;i<farmacia.cantProductos;i++){
            arch<<setw(10)<<farmacia.productosVendidos[i].codigo
                <<setw(38)<<farmacia.productosVendidos[i].nombre
                <<setw(12)<<farmacia.productosVendidos[i].cantidad
                <<setw(10)<<farmacia.productosVendidos[i].recaudado<<endl;
        }
        linea(arch,'=',MAX_LINEA);
    }
}
void encabezado1(ofstream& arch){
    arch<<setw(40)<<right<<"CADENA DE FARMACIAS_TP"<<left<<endl;
    linea(arch,'=',MAX_LINEA);
    arch<<"LISTADO DE FARMACIAS"<<endl;
    linea(arch,'-',MAX_LINEA);
}
void subEncabezado(ofstream& arch){
    arch<<setw(10)<<"CODIGO"
        <<setw(35)<<"DESCRIPCION"
        <<setw(13)<<"CANTIDAD"
        <<setw(10)<<"MONTO TOTAL"<<endl;
}
void imprimirDatosProductosNoProcesados(ifstream& archNoProcesados,
                                        ofstream& arch){
    //Variables
    struct ProductosNoProcesados noProcesado{};
    encabezado2(arch);
    while(true){
        archNoProcesados.read(reinterpret_cast<char*>(&noProcesado),
                        sizeof(struct ProductosNoProcesados));
        if(archNoProcesados.eof())break;
        arch<<setw(10)<<noProcesado.codigoFarmacia
            <<setw(10)<<noProcesado.codigoProducto
            <<setw(38)<<noProcesado.nombreProducto
            <<setw(10)<<noProcesado.cantidadVendida
            <<setw(10)<<noProcesado.precio<<endl;
    }
    linea(arch,'=',MAX_LINEA);
}
void encabezado2(ofstream& arch){
    linea(arch,'=',MAX_LINEA);
    linea(arch,'=',MAX_LINEA);
    arch<<"PRODUCTOS NO PROCESADOS"<<endl;
    linea(arch,'-',MAX_LINEA);
    arch<<setw(10)<<"FARMACIA"
            <<setw(10)<<"CODIGO"
            <<setw(35)<<"DESCRIPCION"
            <<setw(13)<<"CANTIDAD"
            <<setw(10)<<"PRECIO"<<endl;
}
