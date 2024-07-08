//Author: MAKO
#ifndef FUNCIONES_H
#define FUNCIONES_H

void lecturaArticulos(const char* nomArticulos,
                      const char* nomArticulosBin);
void lecturaVendedores(const char* nomVendedores,
                       const char* nomVendedoresBin); 
void actualizacionVentas(const char* nomVentas, 
                         const char* nomVendedoresBin,
                         const char* nomArticulosBin);
void ingresoDeDatos(fstream& archVendedores, fstream& archArticulos,
              char* codeArticulo,int codeVendedor,int cant);
int constSructs(fstream& arch, int size);
int buscarVendedor(fstream& archVendedores,int numVendedores,
                   int size,int codeVendedor);
int buscarArticulo(fstream& archArticulos ,int numArticulos ,
                   int size,char* codeArticulo);
void actualizacion(struct Articulo& articulo,struct Vendedor& vendedor,
                   int cant);
int buscarArticulos(struct ArticuloVendido* articulos,int cantidadArticulos,
                    char* code);
void correcionVendedores(const char* nomVendedoresBin);
void ordenamiento(const char* nomVendedoresBin);
double calcularMonto(struct Vendedor vendedor);
void cambiarStruct(struct Vendedor& vendedorI,struct Vendedor& vendedorK);
void emitirReporte(const char* nomVendedores,
                   const char* nomReporte,const char* nomArticulo); 
void encabezado(ofstream& report);
void encabezado1(ofstream& report);
void linea(ofstream& report,int n,char c);
void encabezado2(ofstream& report);
void modificarTexto(char* nombre);
void encabezado3(ofstream& report);


#endif
