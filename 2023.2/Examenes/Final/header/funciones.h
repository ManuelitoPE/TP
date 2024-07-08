#ifndef FUNCIONES_H
#define FUNCIONES_H

void lecturaArticulos(const char* nomArticulos,
                      const char* nomArticulosBin);
void pruebaArticulos(const char* nomArticulosBin,
                     const char* nomReport);
void encabezadoPrueba(ofstream& report);
void linea(ofstream& report,int n,char c);
int contadorStucts(fstream& arch,int size);
void lecturaVendedores(const char* nomVendedores,
                       const char* nomVendedoresBin);
void emitirReporte(const char* nomPruebaReporte,
                   const char* nomVendedores,const char* nomArticulos);
void encabezado(ofstream& report);
void encabezado2(ofstream& report);
void imprimirVentas(ofstream& report,fstream& archArticulos,
                    struct ArticuloPedido* articuloPedido,int cant);
int buscarArticulo(fstream& archArticulos,int numArticulos,
                    char* code);
void actualizarArchivos(const char* nomVentas,const char* nomVendedores,
                        const char* nomArticulos);
void ingresoDeDatos(fstream& archVendedores,fstream& archArticulos,
                    int codeVendedor,char* codeArticulo,
                    int cant,int dd,int mm,int aa);
int buscarVendedor(fstream& archVendedores,int numVendedores,
                   int code);
void actualizar(struct Articulo& articulo,struct Vendedor& vendedor,
                int cant,int dd,int mm,int aa);
int buscarArticuloPedido(struct ArticuloPedido* articulosPerdidos,
                         int cant,char* code);
void updateDatosVendedores(int posArticulo,char* code,struct ArticuloPedido* articulo,
                           int& num,int cant,int dd,int mm,int aa,double monto);


#endif