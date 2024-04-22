//Author: MAKO
#ifndef FUNCIONES_H
#define FUNCIONES_H

void emitirReporte(const char* nomAlmacen,const char* nomProductos,
                   const char* nomStockProductos,const char* nomTransacciones,
                   const char* nomReporte);
void encabezado(ofstream& report);
void linea(ofstream& report,int n,char c);
void lecturAlmacen(int& almacen,ofstream& report,
                   ifstream& archAlmacen);
void impresionNombre(ofstream& report,ifstream& arch,
                     bool almacen);
void lecturaProductos(int almacen,ifstream& archProductos,
                      ifstream& archStockProductos,
                      ifstream& archTransacciones,
                      ofstream& report);
void busquedaStock(int almacen,int producto,int& stock,
                   ifstream& archStockProductos);
#endif