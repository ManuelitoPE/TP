//Author: MAKO
#ifndef FUNCIONES_H
#define FUNCIONES_H

void lecturaClientes(const char* nomClientes,
                     struct ClienteNodo *&listaCliente);
void insertarNodoCliente(struct ClienteNodo *&listaCliente,
                  struct Cliente cliente);
void emitirClientes(const char* nompruebaClientes,
                    struct ClienteNodo *listaCliente);
void encabezadoClientes(ofstream& report);
void linea(ofstream& report,int n,char c);
void lecturaLibros(const char* nomLibros,
                   struct LibroNodo *&listaLibro);
void insertarNodoLibro(struct LibroNodo *&listaLibro,
                       struct Libro libro);
void emitirLibros(const char* nompruebaLibros,
                  struct LibroNodo *listaLibro);
void encabezadoLibros(ofstream& report);
void encabezado(ofstream& report);
void impresionLibrerias(ofstream& report,struct Libreria *librerias,
                        int cantidadLibrerias);
void encabezadoVentas(ofstream& report);
void lecturaVentas(const char* nomVentas,struct ClienteNodo *&listaCliente,
                    struct LibroNodo *&listaLibro);
void ingresarDatos(int codigoLibreria,char* codigoLibro,
                   int fecha,int dni,int calificacion,
                   struct ClienteNodo *&listaCliente,
                   struct LibroNodo *&listaLibro);
void actualizarLibrerias(struct Libreria *librerias,int& cantidadLibrerias,
                         int codigoLibreria,double precioLibro,int dni,
                         char* nombreCliente,int fecha,int calificacion);
int buscarLibreria(struct Libreria *librerias,int cant,
                   int codigoLibreria);
void ingresarVenta(struct Venta *ventas,int& cantidad,
                   int calificacion,int dni,int fecha,
                   char* nombreCliente);
void descuentoFuturo(struct ClienteNodo *&listaCliente);
double descuento(double montoComprado,int porcentaje);
void guardarClientes(const char* nomClientesBin,
                     struct ClienteNodo *listaCliente);
void guardarLibros(const char* nomLibros,
                  struct LibroNodo *listaLibro);
void copiarLibrerias(struct Libreria *librerias,struct Libreria *libreriasCP,
                     int cantidadLibrerias);
void ordenarClientes(const char* nomClientes);
void ordenarLibros(const char* nomLibros);
int contStructs(fstream& arch,int size);
void cambiarCliente(struct Cliente &clienteI,struct Cliente &clienteK);
void cambiarLibro(struct Libro &libroI,struct Libro &libroK);
double sacarPromedio(struct Libro libro);   
void emitirReporteClientes(const char* nomClientes,  
                           const char* nomReporte);
void emitirReporteLibros(const char* nomLibros,  
                        const char* nomReporte);



#endif