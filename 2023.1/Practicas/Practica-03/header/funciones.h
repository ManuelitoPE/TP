#ifndef FUNCIONES_H
#define FUNCIONES_H
#include<fstream>
void leerDatoAlmacen(const char* nomArch,char** ARRcodigoAlmacen,
                    char** ARRnombreAlmacen,int* ARRpostalAlmacen,
                    int& num_almacen);
char* leerCadenaExacta(ifstream& arch,char delimitador);

void ordenar(int& num_almacen,char** ARRcodigoAlmacen,
            char** ARRnombreAlmacen,int* ARRpostalAlmacen,
            char* nombre,int postal,char* codigo);
void leerDatosProductos(const char* nomArch,char** ARRcodigoProducto,
                    char** ARRnombreProducto,int& num_producto);
void reportePruebaAlamcenes(const char* nomArch,char** ARRcodigoAlmacen,
                    char** ARRnombreAlmacen,int* ARRpostalAlmacen,
                    int num_almacen);
void leerStockProductos(const char* nomArch,
                    char** ARRcodigo_productoStock,
                    char** ARRcodigo_almacenStock
                    ,double* ARRstockInicialStock,int& num_stock);
void reporteSimpleStock(const char* nomArch,
                    char** ARRcodigo_productoStock,
                    char** ARRcodigo_almacenStock
                    ,double* ARRstockInicialStock,int num_stock); 
void actualizacionDatos(int num_almacen,int num_producto,int num_stock,
                    int* ARRpostalAlmacen,char** ARRnombreAlmacen,
                    char** ARRcodigoAlmacen,
                    char** ARRcodigoProducto,char**ARRnombreProducto,
                    char** ARRcodigo_productoStock,
                    char** ARRcodigo_almacenStock,
                    double* ARRstockInicialStock,
                    double* ARRingreso,double* ARRsalida,
                    double* ARRenviado,
                    double* ARRrecibido,double* ARRstockFinal,
                    char** observaciones,const char* nomArch);
int buscarPosicion(char* almacenREF,char* codigoREF,
                    char** ARRcodigo_productoStock,
                    char** ARRcodigo_almacenStock,int num_stock);
void sumamosCategoria(int pos,char tipo,double* ARRingreso,
                    double* ARRsalida,double* ARRenviado,
                    double* ARRrecibido,char** observaciones,double cantidad,
                    char* almacenREF,char* codigoREF,
                    char** ARRcodigo_productoStock,
                    char** ARRcodigo_almacenStock,int num_stock);
void calculoStockFinal(double* ARRingreso,double* ARRsalida,
                    double* ARRenviado,
                    double* ARRrecibido,double* ARRstockFinal,
                    char** observaciones,int num_stock,
                    double* ARRstockInicialStock);


#endif