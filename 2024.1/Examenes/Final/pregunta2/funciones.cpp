//Author: MAKO
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "header/funciones.h"
#include "header/Libro.h"
#include "header/Cliente.h"
#define MAX_LINEA 120
#define NO_ENCONTRADO -1


void lecturaClientes(const char* nomClientes,
                     const char* nomClientesBin){
    ifstream arch(nomClientes,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomClientes<<endl;
        exit(1);
    }
    ofstream archBin(nomClientesBin,ios::out|ios::binary);
    if(not archBin.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomClientesBin<<endl;
        exit(1);
    }
    //Variables
    struct Cliente cliente{};
    int dni; char nombre[50]; 
    while(true){
        arch>>dni;
        if(arch.eof())break; arch.get();
        arch.getline(nombre,50,'\n');
        strcpy(cliente.nombre,nombre);
        cliente.dni=dni;
        archBin.write(reinterpret_cast<const char*>(&cliente),
                      sizeof(struct Cliente));
    }
}
void emitirClientes(const char* nomReporte,
                    const char* nomClientesBin){
    ifstream arch(nomClientesBin,ios::in|ios::binary);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomClientesBin<<endl;
        exit(1);
    }
    ofstream report(nomReporte,ios::out);
    if(not report.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomReporte<<endl;
        exit(1);
    }          
    report.precision(2); report<<fixed;
    encabezadoClientes(report);        
    //Variables
    struct Cliente cliente;
    int size = sizeof(struct Cliente);
    while(true){
        arch.read(reinterpret_cast<char*>(&cliente),size);
        if(arch.eof())break;
        report<<left<<setw(10)<<cliente.dni
              <<setw(38)<<cliente.nombre
              <<right<<setw(11)<<cliente.montoComprado
              <<setw(22)<<cliente.descuentoFuturo<<endl;
    } 
}
void encabezadoClientes(ofstream& report){
    report<<setw(50)<<"LISTADO DE CLIENTES"<<endl;
    linea(report,MAX_LINEA,'=');
    report<<left<<setw(10)<<"DNI"
          <<setw(40)<<"NOMBRE"
          <<setw(20)<<"MONTO COMPRADO"
          <<setw(20)<<"DESCUENTO FUTURO"<<endl;
}
void linea(ofstream& report,int n,char c){
    for (int i = 0; i < n; i++)report<<c;
    report<<endl;
}
void lecturaLibros(const char* nomLibros,
                   const char* nomLibrosBin){
    ifstream arch(nomLibros,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomLibros<<endl;
        exit(1);
    }
    ofstream archBin(nomLibrosBin,ios::out|ios::binary);
    if(not archBin.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomLibrosBin<<endl;
        exit(1);
    }
    //Variables
    struct Libro libro{};
    char code[8],titulo[80],autor[40]; double precio;
    while(true){
        arch.getline(code,8,',');
        if(arch.eof())break;
        arch.getline(titulo,80,',');
        arch.getline(autor,40,','); arch>>precio; arch.get();
        strcpy(libro.code,code);
        strcpy(libro.autor,autor);
        strcpy(libro.titulo,titulo); libro.precio=precio;
        archBin.write(reinterpret_cast<const char*>(&libro),
                      sizeof(struct Libro));
    }
}
void emitirReporte(const char* nomPruebaLibros,
                   const char* nomLibrosBin){
    ifstream arch(nomLibrosBin,ios::in|ios::binary);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomLibrosBin<<endl;
        exit(1);
    }
    ofstream report(nomPruebaLibros,ios::out);
    if(not report.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomPruebaLibros<<endl;
        exit(1);
    } 
    //Variables
    struct Libro libro;
    int size = sizeof(struct Libro), i=1,totalLibros=0; double totalVentas=0;
    encabezadoLibro(report);
    while(true){
        arch.read(reinterpret_cast<char*>(&libro),size);
        if(arch.eof())break; 
        report<<setw(10)<<"LIBRO NO."<<i<<endl;
        encabezado1(report);
        report<<setw(10)<<libro.code
          <<setw(60)<<libro.titulo
          <<setw(40)<<libro.autor
          <<setw(10)<<libro.precio
          <<setw(15)<<libro.unidadesVendidas
          <<setw(20)<<libro.totalVentas
          <<setw(25)<<libro.sumaBuenasCalificaciones/libro.cantidadBuenasCalificaciones
          <<setw(25)<<libro.sumaMalasCalificaciones/libro.cantidadMalasCalificaciones
          <<setw(25)<<(libro.sumaBuenasCalificaciones+libro.sumaMalasCalificaciones)/
                      (libro.cantidadBuenasCalificaciones+libro.cantidadMalasCalificaciones)<<endl;
        libro.cantidadLibrerias++;
        for (int k = 0; k < libro.cantidadLibrerias; k++){
            linea(report,MAX_LINEA,'-');
            report<<"LIBRERIA: "<<left<<setw(10)<<libro.librerias[k].code
                  <<"TOTAL DE VENTAS: "<<libro.librerias[k].totalVentas<<endl;
            linea(report,MAX_LINEA,'-');
            report<<setw(5)<<" "<<"VENTAS:"<<endl
                  <<setw(5)<<" "<<setw(5)<<"NO."<<setw(10)<<"DNI"<<setw(40)<<"NOMBRE"
                  <<setw(15)<<"CALIFICACION"<<setw(10)<<"FECHA"<<endl;
            for (int j = 0; j < libro.librerias[k].cantidadVentas; i++){
                report<<setw(5)<<" "<<setw(5)<<setfill('0')<<right<<setw(3)<<j+1<<") "
                      <<setfill(' ')<<left<<setw(10)<<libro.librerias[k].ventas[j].dniComprador
                      <<setw(40)<<libro.librerias[k].ventas[j].nombreComprador
                      <<setw(15)<<libro.librerias[k].ventas[j].calificacion
                      <<setw(10)<<libro.librerias[k].ventas[j].fecha<<endl;
            }
        }
        i++; totalLibros+=libro.unidadesVendidas; totalVentas+=libro.totalVentas;
    }
    linea(report,MAX_LINEA,'=');
    report<<"RESUMEN"<<endl<<setw(40)<<"TOTAL DE LIBROS VENDIDOS: "
          <<totalLibros<<endl<<setw(40)<<"TOTAL DE VENTAS:"<<totalVentas<<endl;
}
void encabezadoLibro(ofstream& report){
    report<<setw(50)<<"REPORTE DE VENTAS POR LIBROS Y LIBRERIAS"<<endl;
    linea(report,MAX_LINEA,'=');
}
void encabezado1(ofstream& report){
    report<<left<<setw(10)<<"CODIGO"
          <<setw(60)<<"TITULO"
          <<setw(40)<<"AUTOR"
          <<setw(10)<<"PRECIO"
          <<setw(15)<<"VENDIDOS"
          <<setw(20)<<"TOTAL.VENTAS"
          <<setw(25)<<"PROM.BUENAS.CALIF"
          <<setw(25)<<"PROM.MALAS.CALIF"
          <<setw(25)<<"PROM.CALIF"<<endl;
}
void actualizar(const char* nomLibros,const char* nomVentas,
                const char* nomClientes){
    ifstream arch(nomVentas,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se puede abrir "<<nomVentas<<endl;
        exit(1);
    }
    fstream archLibros(nomLibros,ios::in|ios::out|ios::binary);
    if(not archLibros.is_open()){
        cout<<"ERROR: No se puede abrir "<<nomLibros<<endl;
        exit(1);
    }
    fstream archClientes(nomClientes,ios::in|ios::out|ios::binary);
    if(not archClientes.is_open()){
        cout<<"ERROR: No se puede abrir "<<nomClientes<<endl;
        exit(1);
    }
    //Variables
    int codeLibreria,dd,mm,aa,fecha,dni,calif; 
    char codeLibro[8],c;
    while (true){
        arch>>codeLibreria;
        if(arch.eof())break;
        arch>>dd>>c>>mm>>c>>aa; fecha=aa*10000+mm*100+aa;
        while(arch.get()!='\n'){
            arch.getline(codeLibro,8,' ');
            arch>>dni>>calif;
            ingresarDatos(codeLibreria,codeLibro,fecha,dni,calif,
                          archLibros,archClientes);
        }
    }
}
void ingresarDatos(int codeLibreria,char* codeLibro,int fecha,
                   int dni,int calif,fstream& archLibros,
                   fstream& archClientes){
    //Variables
    struct Libro libro;
    struct Cliente cliente;
    int sizeLibro   = sizeof(struct Libro);
    int sizeCliente = sizeof(struct Cliente);
    int numLibros   = contStructs(archLibros,sizeLibro);
    int numClientes = contStructs(archClientes,sizeCliente);
    int posLibro    = buscarLibro(archLibros,numLibros,codeLibro);
    int posClientes = buscarCliente(archClientes,numClientes,dni);
    if(posClientes!=NO_ENCONTRADO and posLibro!=NO_ENCONTRADO){
        archLibros.seekg(posLibro*sizeLibro);
        archLibros.read(reinterpret_cast<char*>(&libro),sizeLibro);
        archClientes.seekg(posClientes*sizeCliente);
        archClientes.read(reinterpret_cast<char*>(&cliente),sizeCliente);
        update(cliente,libro,fecha,codeLibreria,calif);
        archLibros.seekg(posLibro*sizeLibro);
        archLibros.write(reinterpret_cast<const char*>(&libro),sizeLibro);
        archClientes.seekg(posClientes*sizeCliente);
        archClientes.write(reinterpret_cast<const char*>(&cliente),sizeCliente);
        archLibros.flush();
        archClientes.flush();
    }
}
int contStructs(fstream& arch,int size){
    //Variables
    int num;
    arch.seekg(0,ios::end);
    num=arch.tellg();
    arch.seekg(0,ios::beg);
    return num/size; 
}
int buscarLibro(fstream& archLibros,int numLibros,char* codeLibro){
    //Variables
    struct Libro libro;
    int size = sizeof(struct Libro);
    for (int i = 0; i < numLibros; i++){
        archLibros.read(reinterpret_cast<char*>(&libro),size);
        if(strcmp(libro.code,codeLibro)==0)return i;
    }
    return NO_ENCONTRADO;
}
int buscarCliente(fstream& archClientes,int numClientes,int dni){
    //Variables
    struct Cliente cliente;
    int size = sizeof(struct Cliente);
    for (int i = 0; i < numClientes; i++){
        archClientes.read(reinterpret_cast<char*>(&cliente),size);
    }
}
void update(struct Cliente& cliente,struct Libro &libro,
            int fecha,int codeLibreria,int calif){
    //Variables
    int cantVentas,cantLibrerias;
    int posLibreria = buscarLibreria(libro.librerias,libro.cantidadLibrerias,
                                     codeLibreria);
    if(posLibreria!=NO_ENCONTRADO){
        cantVentas = libro.librerias[posLibreria].cantidadVentas;
        //Ventas
        libro.librerias[posLibreria].ventas[cantVentas].calificacion=calif;
        libro.librerias[posLibreria].ventas[cantVentas].dniComprador=cliente.dni;
        libro.librerias[posLibreria].ventas[cantVentas].fecha=fecha;
        strcpy(libro.librerias[posLibreria].ventas[cantVentas].nombreComprador,cliente.nombre);
        //Libreria
        libro.librerias[posLibreria].cantidadVentas++;
        libro.librerias[posLibreria].totalVentas+=libro.precio;
    }else{
        cantLibrerias = libro.
        cantVentas = libro.librerias[posLibreria].cantidadVentas;
        //Ventas
        libro.librerias[posLibreria].ventas[cantVentas].calificacion=calif;
        libro.librerias[posLibreria].ventas[cantVentas].dniComprador=cliente.dni;
        libro.librerias[posLibreria].ventas[cantVentas].fecha=fecha;
        strcpy(libro.librerias[posLibreria].ventas[cantVentas].nombreComprador,cliente.nombre);
        //Libreria
        libro.librerias[posLibreria].cantidadVentas++;
        libro.librerias[posLibreria].totalVentas+=libro.precio;
    }
}
int buscarLibreria(struct Libreria *librerias,int num,
                   int codeLibreria){
    //Variables

    for (int i = 0; i < num; i++){
        if(librerias[i].code==codeLibreria)return i;
    }
    return NO_ENCONTRADO;
}