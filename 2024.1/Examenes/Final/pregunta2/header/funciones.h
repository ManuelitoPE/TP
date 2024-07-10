//Author: MAKO
#ifndef FUNCIONES_H
#define FUNCIONES_H

void lecturaClientes(const char* nomClientes,const char* nomClientesBin);
void emitirClientes(const char* nomReporte,const char* nomClientesBin); 
void encabezadoClientes(ofstream& report);
void linea(ofstream& report,int n,char c);
void lecturaLibros(const char* nomLibros,
                   const char* nomLibrosBin);
void emitirReporte(const char* nomPruebaLibros,
                   const char* nomLibrosBin);
void encabezadoLibro(ofstream& report);
void encabezado1(ofstream& report);
void actualizar(const char* nomLibros,const char* nomVentas,
                const char* nomClientes);
void ingresarDatos(int codeLibreria,char* codeLibro,int fecha,
                    int dni,int calif,fstream& archLibros,
                    fstream& archClientes);
int contStructs(fstream& arch,int size);
int buscarLibro(fstream& archLibros,int numLibros,char* codeLibro);
int buscarCliente(fstream& archClientes,int numClientes,int dni);
void update(struct Cliente& cliente,struct Libro &libro,
            int fecha,int codeLibreria,int calif);
int buscarLibreria(struct Libreria *librerias,int num,
                   int codeLibreria);
#endif