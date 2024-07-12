//Author: MAKO
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "header/funciones.h"
#include "header/ClienteNodo.h"
#include "header/LibroNodo.h"

#define MAX_LINEA 200
#define NO_ENCONTRADO -1 

void lecturaClientes(const char* nomClientes,
                     struct ClienteNodo *&listaCliente){
    ifstream arch(nomClientes,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomClientes<<endl;
        exit(1);
    }
    //Varibles
    struct Cliente cliente{};
    while(true){
        arch>>cliente.dni;
        if(arch.eof())break; arch.get();
        arch.getline(cliente.nombre,50,'\n');
        insertarNodoCliente(listaCliente,cliente);
    } 
}
void insertarNodoCliente(struct ClienteNodo *&listaCliente,
                  struct Cliente cliente){
    //Variables 
    struct ClienteNodo *nuevoNodo;
    nuevoNodo = new struct ClienteNodo;
    nuevoNodo->datoCliente = cliente;
    nuevoNodo->siguiente = listaCliente;
    listaCliente = nuevoNodo; 
}
void emitirClientes(const char* nompruebaClientes,
                    struct ClienteNodo *listaCliente){
    ofstream report(nompruebaClientes,ios::out);
    if(not report.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nompruebaClientes<<endl;
        exit(1);
    }
    report.precision(2); report<<fixed; encabezadoClientes(report);
    //Variables
    struct ClienteNodo *ptr = listaCliente;
    while(ptr){
        report<<left<<setw(10)<<ptr->datoCliente.dni
          <<setw(40)<<ptr->datoCliente.nombre
          <<right<<setw(15)<<ptr->datoCliente.montoComprado
          <<setw(20)<<ptr->datoCliente.descuentoFuturo<<endl;
        ptr = ptr->siguiente;
    } 
}
void encabezadoClientes(ofstream& report){
    report<<setw(50)<<"REPORTE DE CLIENTES"<<endl;
    linea(report,MAX_LINEA,'=');
    report<<left<<setw(10)<<"DNI"
          <<setw(47)<<"NOMBRE"
          <<setw(18)<<"MONTO COMPRADO"
          <<setw(20)<<"DESCUENTO FUTURO"<<endl;
    linea(report,MAX_LINEA,'-');
}
void linea(ofstream& report,int n,char c){
    for (int i = 0; i < n; i++)report<<c;
    report<<endl;
}
void lecturaLibros(const char* nomLibros,
                   struct LibroNodo *&listaLibro){
    ifstream arch(nomLibros,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomLibros<<endl;
        exit(1);
    }
    //Varibles
    struct Libro libro{};
    while(true){
        arch.getline(libro.codigo,8,',');
        if(arch.eof())break; 
        arch.getline(libro.titulo,80,',');
        arch.getline(libro.autor,50,','); 
        arch>>libro.precio; arch.get();
        insertarNodoLibro(listaLibro,libro);
    } 
}
void insertarNodoLibro(struct LibroNodo *&listaLibro,
                       struct Libro libro){
    // Variables
    struct LibroNodo *nuevoNodo;
    nuevoNodo = new struct LibroNodo;
    nuevoNodo->datoLibro = libro;
    nuevoNodo->siguiente = listaLibro;
    listaLibro = nuevoNodo; 
}
void emitirLibros(const char* nompruebaLibros,
                  struct LibroNodo *listaLibro){
    ofstream report(nompruebaLibros,ios::out);
    if(not report.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nompruebaLibros<<endl;
        exit(1);
    }
    report.precision(2); report<<fixed; encabezadoLibros(report);
    //Variables
    struct LibroNodo *ptr = listaLibro;
    int i = 1;
    while(ptr){
        report<<left<<setw(15)<<"LIBROS NO."<<i<<endl; encabezado(report);
        report<<left<<setw(10)<<ptr->datoLibro.codigo
          <<setw(60)<<ptr->datoLibro.titulo
          <<setw(32)<<ptr->datoLibro.autor
          <<right<<setw(10)<<ptr->datoLibro.precio
          <<setw(8)<<ptr->datoLibro.unidadesVendidas
          <<setw(17)<<ptr->datoLibro.totalVentas
          <<setw(18)<<ptr->datoLibro.sumaBuenasCalificaciones/
                      ptr->datoLibro.cantidadBuenasCalificaciones            
          <<setw(20)<<ptr->datoLibro.sumaMalasCalificaciones/
                      ptr->datoLibro.cantidadMalasCalificaciones
          <<setw(18)<<(ptr->datoLibro.sumaMalasCalificaciones+ptr->datoLibro.sumaBuenasCalificaciones)/
                      (ptr->datoLibro.cantidadMalasCalificaciones+ptr->datoLibro.cantidadMalasCalificaciones)<<endl;
        impresionLibrerias(report,ptr->datoLibro.librerias,
                           ptr->datoLibro.cantidadLibrerias);
        linea(report,MAX_LINEA,'=');
        ptr = ptr->siguiente; i++;
    } 
}
void encabezadoLibros(ofstream& report){
    report<<setw(60)<<"REPORTE DE VENTAS POR LIBROS Y LIBRERIAS"<<endl;
    linea(report,MAX_LINEA,'=');
}
void encabezado(ofstream& report){
    report<<left<<setw(10)<<"CODIGO"<<setw(60)<<"TITULO"
          <<setw(36)<<"AUTOR"<<setw(10)<<"PRECIO"
          <<setw(12)<<"VENDIDOS"<<setw(16)<<"TOTAL.VENTAS"
          <<setw(21)<<"PROM.BUENAS.CALIF"<<setw(21)<<"PROM.MALAS.CALIF"
          <<setw(10)<<"PROM.CALIF"<<endl;
}
void impresionLibrerias(ofstream& report,struct Libreria *librerias,
                        int cantidadLibrerias){
    for (int k = 0; k < cantidadLibrerias; k++){
        linea(report,MAX_LINEA,'-');
        report<<setw(10)<<left<<"LIBRERIA:"<<setw(10)<<librerias->codigo
            <<setw(20)<<"TOTAL DE VENTAS:"<<librerias->totalVentas<<endl;
        linea(report,MAX_LINEA,'-'); encabezadoVentas(report);
        for (int i = 0; i < librerias[k].cantidadVentas; i++){
            report<<setw(15)<<" "<<setw(5)<<i+1
                  <<setw(10)<<librerias[k].ventas[i].dniComprador
                  <<setw(43)<<librerias[k].ventas[i].nombreComprador
                  <<setw(12)<<librerias[k].ventas[i].calificacion
                  <<setw(10)<<librerias[k].ventas[i].fecha<<endl;
        } 
    }
}
void encabezadoVentas(ofstream& report){
    report<<setw(15)<<" "<<"VENTAS:"<<endl<<setw(15)<<" "
          <<setw(5)<<"No."<<setw(10)<<"DNI"
          <<setw(38)<<"NOMBRE"<<setw(18)<<"CALIFICACION"
          <<setw(10)<<"FECHA"<<endl;
}
void lecturaVentas(const char* nomVentas,struct ClienteNodo *&listaCliente,
                   struct LibroNodo *&listaLibro){
    ifstream arch(nomVentas,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomVentas<<endl;
        exit(1);
    }
    //Varibles
    int codigoLibreria,dd,mm,aa,dni,calificacion,fecha;
    char codigoLibro[8],c;
    while(true){
        arch>>codigoLibreria;
        if(arch.eof())break;
        arch>>dd>>c>>mm>>c>>aa; fecha = aa*10000+mm*100+dd;
        while(arch.get()!='\n'){
            arch>>ws; arch.getline(codigoLibro,8,' ');
            arch>>dni>>calificacion;
            ingresarDatos(codigoLibreria,codigoLibro,fecha,dni,
                          calificacion,listaCliente,listaLibro);
        }
    }
    descuentoFuturo(listaCliente);
}
int penes;
void ingresarDatos(int codigoLibreria,char* codigoLibro,
                   int fecha,int dni,int calificacion,
                   struct ClienteNodo *&listaCliente,
                   struct LibroNodo *&listaLibro){
    //Variables
    struct ClienteNodo *ptrCliente = listaCliente;
    struct LibroNodo *ptrLibro = listaLibro;
    double precioLibro;
    char nombreCliente[50];
    //Actualizar Libro 
    while(ptrLibro){
        if(strcmp(ptrLibro->datoLibro.codigo,codigoLibro)==0){
            precioLibro = ptrLibro->datoLibro.precio;
            //Actualizar Cliente y sacamos el nombre
            while(ptrCliente){
                if(ptrCliente->datoCliente.dni==dni){
                    ptrCliente->datoCliente.montoComprado += precioLibro;
                    strcpy(nombreCliente,ptrCliente->datoCliente.nombre);
                    break;
                }
                ptrCliente=ptrCliente->siguiente;
            }
            //Actualizar Librerias
            actualizarLibrerias(ptrLibro->datoLibro.librerias,
                                ptrLibro->datoLibro.cantidadLibrerias,
                                codigoLibreria,precioLibro,dni,
                                nombreCliente,fecha,calificacion);
            //Actualizar cantidades
            ptrLibro->datoLibro.totalVentas+=precioLibro;
            ptrLibro->datoLibro.unidadesVendidas++;
            //Actualizar Calificaciones
            if(calificacion>50){
                ptrLibro->datoLibro.sumaBuenasCalificaciones+=calificacion;
                ptrLibro->datoLibro.cantidadBuenasCalificaciones++;
            }else{
                ptrLibro->datoLibro.sumaMalasCalificaciones+=calificacion; 
                ptrLibro->datoLibro.cantidadMalasCalificaciones++; 
            }
            break;
        }
        ptrLibro=ptrLibro->siguiente;
    }
}
void actualizarLibrerias(struct Libreria *librerias,int& cantidadLibrerias,
                         int codigoLibreria,double precioLibro,int dni,
                         char* nombreCliente,int fecha,int calificacion){
    //Variables
    int posLibreria = buscarLibreria(librerias,cantidadLibrerias,codigoLibreria);
    int aux;
    if(posLibreria!=NO_ENCONTRADO){
        aux = librerias[posLibreria].cantidadVentas;
        librerias[posLibreria].totalVentas+=precioLibro;
        ingresarVenta(librerias[posLibreria].ventas,librerias[posLibreria].cantidadVentas,
                     calificacion,dni,fecha,nombreCliente);
    }else{
        aux = librerias[cantidadLibrerias].cantidadVentas;
        librerias[cantidadLibrerias].totalVentas += precioLibro;
        librerias[cantidadLibrerias].codigo = codigoLibreria;
        ingresarVenta(librerias[cantidadLibrerias].ventas,librerias[cantidadLibrerias].cantidadVentas,
                      calificacion,dni,fecha,nombreCliente);
        cantidadLibrerias++;
    }
}
void ingresarVenta(struct Venta *ventas,int& cantidad,
                   int calificacion,int dni,int fecha,
                   char* nombreCliente){
    ventas[cantidad].calificacion = calificacion;
    ventas[cantidad].dniComprador = dni;
    ventas[cantidad].fecha = fecha;
    strcpy(ventas[cantidad].nombreComprador,nombreCliente);
    cantidad++;
}
int buscarLibreria(struct Libreria *librerias,int cant,
                   int codigoLibreria){
    for (int i = 0; i < cant; i++){
        if(librerias[i].codigo == codigoLibreria)return i;
    }
    return NO_ENCONTRADO;
}
void descuentoFuturo(struct ClienteNodo *&listaCliente){
    //Variables
    struct ClienteNodo *ptr = listaCliente;
    while(ptr){
        if(ptr->datoCliente.montoComprado>5000)
            ptr->datoCliente.descuentoFuturo = descuento(ptr->datoCliente.montoComprado,30);
        else if(ptr->datoCliente.montoComprado>3000)
            ptr->datoCliente.descuentoFuturo = descuento(ptr->datoCliente.montoComprado,20);
        else ptr->datoCliente.descuentoFuturo = descuento(ptr->datoCliente.montoComprado,10);
        ptr = ptr->siguiente;
    } 
}
double descuento(double montoComprado,int porcentaje){
    return (montoComprado*porcentaje)/100;
}
void guardarClientes(const char* nomClientesBin,
                     struct ClienteNodo *listaCliente){
    ofstream arch(nomClientesBin,ios::out|ios::binary);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomClientesBin<<endl;
        exit(1);
    }
    //Variables
    struct ClienteNodo *ptr = listaCliente;
    struct Cliente cliente;
    int size = sizeof(struct Cliente);
    while(ptr){
        cliente = ptr->datoCliente;
        // cliente.dni = ptr->datoCliente.dni;
        // strcpy(cliente.nombre,ptr->datoCliente.nombre);
        // cliente.montoComprado = ptr->datoCliente.montoComprado;
        // cliente.descuentoFuturo = ptr->datoCliente.descuentoFuturo;
        arch.write(reinterpret_cast<const char*>(&cliente),size);
        ptr = ptr->siguiente;
    }
}
void guardarLibros(const char* nomLibros,
                  struct LibroNodo *listaLibro){
    ofstream arch(nomLibros,ios::out|ios::binary);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomLibros<<endl;
        exit(1);
    }
    //Variables
    struct LibroNodo *ptr = listaLibro;
    struct Libro libro;
    int size = sizeof(struct Libro);
    while(ptr){
        libro = ptr->datoLibro;
        // strcpy(libro.codigo,ptr->datoLibro.codigo);
        // strcpy(libro.titulo,ptr->datoLibro.titulo);
        // strcpy(libro.autor,ptr->datoLibro.autor);
        // libro.precio = ptr->datoLibro.precio;
        // copiarLibrerias(libro.librerias,ptr->datoLibro.librerias,
        //                 ptr->datoLibro.cantidadLibrerias);
        // libro.cantidadLibrerias = ptr->datoLibro.cantidadLibrerias;
        // libro.totalVentas = ptr->datoLibro.totalVentas;
        // libro.unidadesVendidas = ptr->datoLibro.unidadesVendidas;
        // libro.cantidadBuenasCalificaciones = ptr->datoLibro.cantidadBuenasCalificaciones;
        // libro.sumaBuenasCalificaciones = ptr->datoLibro.sumaBuenasCalificaciones;
        // libro.cantidadMalasCalificaciones = ptr->datoLibro.cantidadMalasCalificaciones;
        // libro.sumaMalasCalificaciones = ptr->datoLibro.sumaMalasCalificaciones;
        arch.write(reinterpret_cast<const char*>(&libro),size);
        ptr = ptr->siguiente;
    }
}
void copiarLibrerias(struct Libreria *librerias,struct Libreria *libreriasCP,
                     int cantidadLibrerias){
    for (int i = 0; i < cantidadLibrerias; i++){
        librerias[i].codigo = libreriasCP[i].codigo;
        librerias[i].cantidadVentas = libreriasCP[i].cantidadVentas;
        librerias[i].totalVentas =  libreriasCP[i].totalVentas;
        for(int k = 0;k < librerias[i].cantidadVentas;k++){
            librerias[i].ventas[k].calificacion = libreriasCP[i].ventas[k].calificacion;
            librerias[i].ventas[k].dniComprador = libreriasCP[i].ventas[k].dniComprador;
            librerias[i].ventas[k].fecha = libreriasCP[i].ventas[k].fecha;
            strcpy(librerias[i].ventas[k].nombreComprador,libreriasCP[i].ventas[k].nombreComprador);
        }
    }
}
void ordenarClientes(const char* nomClientes){
    fstream arch(nomClientes,ios::in|ios::out|ios::binary);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomClientes<<endl;
        exit(1);
    }
    //Variables
    struct Cliente clienteI,clienteK;
    int size = sizeof(struct Cliente);
    int numClientes = contStructs(arch,size);
    for (int i = 0; i < numClientes-1; i++){
        for (int k = i+1; k < numClientes; k++){
            arch.seekg(i*size);
            arch.read(reinterpret_cast<char*>(&clienteI),size);
            arch.seekg(k*size);
            arch.read(reinterpret_cast<char*>(&clienteK),size);
            if(strcmp(clienteI.nombre,clienteK.nombre)>0)
                cambiarCliente(clienteI,clienteK);
            arch.seekg(i*size);
            arch.write(reinterpret_cast<const char*>(&clienteI),size);
            arch.seekg(k*size);
            arch.write(reinterpret_cast<const char*>(&clienteK),size);
            arch.flush();
        }
    }
}
void cambiarCliente(struct Cliente &clienteI,struct Cliente &clienteK){
    struct Cliente aux = clienteI; clienteI = clienteK; clienteK = aux;     
}
int contStructs(fstream& arch,int size){
    //Varibles
    int num;
    arch.seekg(0,ios::end);
    num =  arch.tellg();
    arch.seekg(0,ios::beg);
    return num/size;
}
void ordenarLibros(const char* nomLibros){
    fstream arch(nomLibros,ios::in|ios::out|ios::binary);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomLibros<<endl;
        exit(1);
    }
    //Variables
    struct Libro libroI,libroK;
    int size = sizeof(struct Libro);
    int numLibro = contStructs(arch,size);
    double promedioI,promedioK;
    for (int i = 0; i < numLibro-1; i++){
        for (int k = i+1; k < numLibro; k++){
            arch.seekg(i*size);
            arch.read(reinterpret_cast<char*>(&libroI),size);
            arch.seekg(k*size);
            arch.read(reinterpret_cast<char*>(&libroK),size);
            promedioI = sacarPromedio(libroI);
            promedioK = sacarPromedio(libroK);
            if(promedioI<promedioK) cambiarLibro(libroI,libroK);
            arch.seekg(i*size);
            arch.write(reinterpret_cast<const char*>(&libroI),size);
            arch.seekg(k*size);
            arch.write(reinterpret_cast<const char*>(&libroK),size);
            arch.flush();
        }
    }
}
double sacarPromedio(struct Libro libro){
    return (libro.sumaBuenasCalificaciones+libro.sumaMalasCalificaciones)/
           (libro.cantidadBuenasCalificaciones+libro.cantidadMalasCalificaciones);
}
void cambiarLibro(struct Libro &libroI,struct Libro &libroK){
    struct Libro aux = libroI; libroI = libroK; libroK = aux; 
}
void emitirReporteClientes(const char* nomClientes,  
                           const char* nomReporte){
    fstream arch(nomClientes,ios::out|ios::in|ios::binary);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomClientes<<endl;
        exit(1);
    }
    ofstream report(nomReporte,ios::out);
    if(not report.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomReporte<<endl;
        exit(1);
    }
    report.precision(2); report<<fixed; encabezadoClientes(report);
    //Variables
    struct Cliente cliente;
    int size =  sizeof(struct Cliente);
    while(true){
        arch.read(reinterpret_cast<char*>(&cliente),size);
        if(arch.eof())break;
        report<<left<<setw(10)<<cliente.dni
          <<setw(40)<<cliente.nombre
          <<right<<setw(15)<<cliente.montoComprado
          <<setw(20)<<cliente.descuentoFuturo<<endl;
    } 
}
void emitirReporteLibros(const char* nomLibros,  
                        const char* nomReporte){
    fstream arch(nomLibros,ios::out|ios::in|ios::binary);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomLibros<<endl;
        exit(1);
    }
    ofstream report(nomReporte,ios::out);
    if(not report.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomReporte<<endl;
        exit(1);
    }
    report.precision(2); report<<fixed; encabezadoLibros(report);
    //Variables
    struct Libro libro;
    int size = sizeof(struct Libro);
    int i = 1;
    while(true){
        arch.read(reinterpret_cast<char*>(&libro),size);
        if(arch.eof())break;
        report<<left<<setw(15)<<"LIBROS NO."<<i<<endl; encabezado(report);
        report<<left<<setw(10)<<libro.codigo
          <<setw(60)<<libro.titulo
          <<setw(32)<<libro.autor
          <<right<<setw(10)<<libro.precio
          <<setw(8)<<libro.unidadesVendidas
          <<setw(17)<<libro.totalVentas
          <<setw(18)<<libro.sumaBuenasCalificaciones/
                      libro.cantidadBuenasCalificaciones            
          <<setw(20)<<libro.sumaMalasCalificaciones/
                      libro.cantidadMalasCalificaciones
          <<setw(18)<<(libro.sumaMalasCalificaciones+libro.sumaBuenasCalificaciones)/
                      (libro.cantidadMalasCalificaciones+libro.cantidadMalasCalificaciones)<<endl;
        impresionLibrerias(report,libro.librerias,
                           libro.cantidadLibrerias);
        linea(report,MAX_LINEA,'=');
        i++;
    } 
}