//Author: MAKO
#include <iostream>
#include <iomanip>
using namespace std;
#include "header/funciones.h"
#include "header/ClienteNodo.h"
#include "header/LibroNodo.h"
int main(){
    //Variables
    struct ClienteNodo *listaCliente = nullptr;
    struct LibroNodo *listaLibro = nullptr;
    //Lea los datos del arch Clientes.csv
    lecturaClientes("docs/Clientes.csv",listaCliente);
    // Imprimimos pruebaClientes.txt
    emitirClientes("docs/pruebaClientes.txt",listaCliente);
    //Lectura data de libros
    lecturaLibros("docs/Libros.csv",listaLibro);
    // Imprimimos pruebaLibros
    emitirLibros("docs/pruebaLibros.txt",listaLibro);
    // Lectura de ventas
    lecturaVentas("docs/Ventas.txt",listaCliente,
                  listaLibro);  
    // Imprimimos ReporteFinalClientes.txt
    emitirClientes("docs/ReporteFinalCliente.txt",listaCliente);
    // Imprimimos ReporteFinalLibros
    emitirLibros("docs/ReporteFinalLibros.txt",listaLibro);
    //Guardamos en archBin la lista clientes
    guardarClientes("docs/Clientes.bin",listaCliente); 
    //Guardamos en archBin la lista libro
    guardarLibros("docs/Libros.bin", listaLibro); 
    //Ordenar el arch de Clientes
    ordenarClientes("docs/Clientes.bin");
    //Ordenar el arch de Libros
    ordenarLibros("docs/Libros.bin");
    //Emitir Reporte de Clientes 
    emitirReporteClientes("docs/Clientes.bin",  
                         "docs/ReporteBinarioClientes.bin");
    //Emitir Reporte de libros
    emitirReporteLibros("docs/Libros.bin",  
                        "docs/ReporteBinarioLibros.bin");
    return 0;   
}