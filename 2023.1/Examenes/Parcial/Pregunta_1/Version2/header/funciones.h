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
void impresionTransacciones(int almacen,int producto,int stock,
                            ifstream& archTransacciones,
                            ofstream& report);
void encabezado2(ofstream& report); 
void imprimirDatos(int almacen,int dd,int mm,int aa,int hh,int min,
                   int ss,int producto,int cant,int trans_almacen,
                   int& ingresosT,int& salidasT,
                   int& enviadasT,int& recibidasT,char tipo,
                   int aux_almacen,ofstream& report);
void determinacionTipo(char tipo,int cant,int& ingresosT,int& salidasT,
                       int& enviadasT,int& recibidasT,int trans_almacen,
                       int almacen,
                       int aux_almacen,ofstream& report);
void impresionTotales(int stock,int stockFinal,int ingresosT,
                      int salidasT,int enviadasT,int recibidasT,
                      ofstream& report);

#endif