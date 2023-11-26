//Author: MAKO
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "../header/funciones.h"
#include "../header/Farmacia.h"
#include "../header/ProductoAux.h"
#define MAX_LINEA 100
#define NO_ENCONTRADO -1
void leerFarmacias(struct Farmacia *farmacia,const char* nomArch,
                int& num_farmacia){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"Error: Se produjo un error al abrir el archivo"<<nomArch<<endl;
        exit(1);
    }
    //Variables
    int codigo;
    char c;
    while(true){
        arch>>codigo;
        if(arch.eof())break;
        arch.get();
        farmacia[num_farmacia].distrito=leeExacto(arch,'\n');
        farmacia[num_farmacia].codigo=codigo;
        farmacia[num_farmacia].productoVendidos=new struct Producto[10]{};
        num_farmacia++;
    }
}
char* leeExacto(ifstream& arch,char deli){
    char *ptr, buffer[100];
    arch.getline(buffer,100,deli);
    if(arch.eof())return nullptr;
    ptr=new char[strlen(buffer)+1];
    strcpy(ptr, buffer);
    return ptr;
}
void emitirReporteFarmacias(struct Farmacia *farmacia,const char* nomArch,
                            int num_farmacia){
    ofstream arch(nomArch,ios::out);
    if(not arch.is_open()){
        cout<<"Error: Se produjo un error al abrir el archivo"<<nomArch<<endl;
        exit(1);
    }                          
    encabezado(arch);
    for(int i=0;i<num_farmacia;i++){
        arch<<setw(10)<<farmacia[i].codigo
            <<setw(10)<<farmacia[i].distrito<<endl;
    }
}
void encabezado(ofstream& arch){
    arch<<right<<setw(30)<<"REPORTE SIMPLE DE FARMACIAS"<<left<<endl;
    linea(arch,'=',MAX_LINEA-60);
    arch<<setw(10)<<"CODIGO"
        <<setw(10)<<"DISTRITO"<<endl;
    linea(arch,'-',MAX_LINEA-60);
}
void linea(ofstream& arch, char signo, int num){
    for(int i=0;i<num;i++){
        arch<<signo;
    }
    arch<<endl;
}
void actualizarFarmacias(struct Farmacia *farmacia,
        struct ProductoAux *productoAux,int num_farmacia,
        int& num_productoAux,const char* nomArch){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"Error: Se produjo un error al abrir el archivo"<<nomArch<<endl;
        exit(1);
    }
    //Variables
    int codigoFarmacia,cant;
    char* codigoProducto, *nombre,c;
    double precio;
    while(true){
        arch>>codigoFarmacia;
        if(arch.eof())break;
        arch.get();
        codigoProducto=leeExacto(arch,',');
        nombre=leeExacto(arch,',');
        arch>>cant>>c>>precio;
        arch.get();
        incluirDatos(codigoFarmacia,cant,codigoProducto,nombre,
                    precio, farmacia,productoAux, num_farmacia,
                    num_productoAux);
    }    
}
void incluirDatos(int codigoFarmacia,int cant,char* codigoProducto,
                    char *nombre,double precio,struct Farmacia *farmacia,
                    struct ProductoAux *productoAux,int num_farmacia,
                    int& num_productoAux){
    //Variables 
    int posFarmacia, posProducto;
    posFarmacia=buscarFarmacia(farmacia,num_farmacia,codigoFarmacia);
    if(posFarmacia!=NO_ENCONTRADO){
        if(farmacia[posFarmacia].cantidadProductos>=10){
            //Se agrega a la estructura de prod
            productoAux[num_productoAux].cantidadVendida=cant;
            productoAux[num_productoAux].codigoFarmacia=codigoFarmacia;
            productoAux[num_productoAux].codigoProducto=codigoProducto;
            productoAux[num_productoAux].nombre=nombre;
            productoAux[num_productoAux].precio=precio;
            num_productoAux++;
        }else{
            posProducto=buscarProducto(farmacia[posFarmacia].productoVendidos,
                                    farmacia[posFarmacia].cantidadProductos,
                                    codigoProducto);
            if(posProducto==NO_ENCONTRADO){
                posProducto=farmacia[posFarmacia].cantidadProductos;
                farmacia[posFarmacia].productoVendidos[posProducto].codigo=codigoProducto;
                farmacia[posFarmacia].productoVendidos[posProducto].nombre=nombre;
                farmacia[posFarmacia].cantidadProductos++;
            }
            farmacia[posFarmacia].productoVendidos[posProducto].cantidadTotal+=cant;
            farmacia[posFarmacia].productoVendidos[posProducto].recaudado+=cant*precio;
        }
    }else{
        cout<<"La farmacio "<<codigoFarmacia<<" no se encontro"<<endl;
    }
}
int buscarFarmacia(struct Farmacia *farmacia,int num_farmacia,
                int codigoFarmacia){
    for(int i=0;i<num_farmacia;i++){
        if(farmacia[i].codigo==codigoFarmacia)return i;
    }
    return NO_ENCONTRADO;
}
int buscarProducto(struct Producto *productos,int num_producto,
                    char* codigoProducto){
    for(int i=0;i<num_producto;i++){
        if(strcmp(productos[i].codigo,codigoProducto)==0)return i;
    }
    return NO_ENCONTRADO;
}
void emitirReporte(struct Farmacia *farmacia,struct ProductoAux *productoAux,
            int num_farmacia,int num_productoAux,
            const char* nomArch){
    ofstream arch(nomArch,ios::out);
    if(not arch.is_open()){
        cout<<"Error: Se produjo un error al abrir el archivo"<<nomArch<<endl;
        exit(1);
    }
    //Variables
    encabezado1(arch);
    for(int i=0;i<num_farmacia;i++){
        arch<<left<<"CODIGO: "<<setw(37)<<farmacia[i].codigo
            <<"DISTRITO: "<<farmacia[i].distrito<<endl;
        linea(arch,'-',MAX_LINEA);
        subEncabezado(arch);
        for(int j=0;j<farmacia[i].cantidadProductos;j++){
            arch<<setw(10)<<farmacia[i].productoVendidos[j].codigo
                <<setw(35)<<farmacia[i].productoVendidos[j].nombre
                <<setw(12)<<farmacia[i].productoVendidos[j].cantidadTotal
                <<setw(10)<<farmacia[i].productoVendidos[j].recaudado<<endl;
        }
        linea(arch,'=',MAX_LINEA);
    }
    encabezado2(arch);
    for(int i=0;i<num_productoAux;i++){
        arch<<setw(10)<<productoAux[i].codigoFarmacia
            <<setw(10)<<productoAux[i].codigoProducto
            <<setw(35)<<productoAux[i].nombre
            <<setw(12)<<productoAux[i].cantidadVendida
            <<setw(10)<<productoAux[i].precio<<endl;
    }
    linea(arch,'=',MAX_LINEA);
}
void encabezado1(ofstream& arch){
    arch<<right<<setw(50)<<"CADENA DE FARMACIAS_TP"<<endl;
    linea(arch,'=',MAX_LINEA);
    arch<<left<<"LISTADO DE FARMACIAS"<<endl;
    linea(arch,'-',MAX_LINEA);
}
void subEncabezado(ofstream& arch){
    arch<<setw(10)<<"CODIGO"
        <<setw(35)<<"DESCRIPCION"
        <<setw(12)<<"CANTIDAD"
        <<setw(10)<<"MONTO TOTAL"<<endl;
}
void encabezado2(ofstream& arch){
    arch<<endl<<left<<"PRODUCTOS NO PROCESADOS"<<endl;
    linea(arch,'=',MAX_LINEA);
    arch<<setw(10)<<"FARMACIA"
        <<setw(10)<<"CODIGO"
        <<setw(35)<<"DESCRIPCION"
        <<setw(12)<<"CANTIDAD"
        <<setw(10)<<"PRECIO"<<endl;
    linea(arch,'-',MAX_LINEA);
}