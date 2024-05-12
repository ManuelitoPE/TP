#ifndef FUNCIONES_H
#define FUNCIONES_H

void emitirReporte(const char* nomAlmacen,const char* nomProductos,
                  const char* nomStockProductos,const char* nomTransacciones,
                  const char* nomReporte);
void encabezado(ofstream& report);
void linea(ofstream& report,int n,char c);
void imprimirString(ofstream& report,ifstream& arch,
                    char deli,char aux);
void procesoDeDatos(int cod_almacen,int cod_postal,
                    ifstream& archProductos,ifstream& archStockProductos,
                    ifstream& archTransacciones,ofstream& report);
int buscarStock(ifstream& archStockProductos,int cod_producto,
                int cod_almacen);
void procesoDeTransacciones(int cod_almacen,int cod_postal,
                            int cod_producto,int stock_producto,
                            ifstream& archTransacciones,ofstream& report);
void subEncabezado(ofstream& report);
void imprimirT(int almacen,int dd,int mm,int aa,int hh,int min,
               int ss,int cantidad,int almacen_t,int& totalI,
               int& totalS,int& totalTE,int& totalTR,int& totalStock,char tipo,
               int cod_almacen,ofstream& report);
void impresionResumen(int totalI,int totalS,int totalTE,int totalTR,
                      int totalStock,int stock_producto,
                      ofstream& report);
#endif