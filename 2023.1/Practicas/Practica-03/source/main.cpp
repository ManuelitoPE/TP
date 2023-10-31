#include<iostream>
#include<iomanip>
using namespace std;
#include"../header/funciones.h"
#define MAX_ALMACEN 10
#define MAX_PRODUCTO 60
#define MAX_STOCK 300
int main(int argc, char** argv){
    //Numero de datos
    int num_almacen=0,num_producto=0,num_stock=0;
    //ARREGLOS DE ALMACEN
    int ARRpostalAlmacen[MAX_ALMACEN];
    char *ARRnombreAlmacen[MAX_ALMACEN],
        *ARRcodigoAlmacen[MAX_ALMACEN];
    //ARREGLSO DE PRODUCTOS
    char* ARRcodigoProducto[MAX_PRODUCTO], *ARRnombreProducto[MAX_PRODUCTO];
    //ARREGLOS DE STOCK
    char* ARRcodigo_productoStock[MAX_STOCK],
        *ARRcodigo_almacenStock[MAX_STOCK];
    double ARRstockInicialStock[MAX_STOCK];
    //ARREGLOS PARA REPORTE
    double ARRingreso[MAX_STOCK]{},ARRsalida[MAX_STOCK]{},ARRenviado[MAX_STOCK]{},
            ARRrecibido[MAX_STOCK]{},ARRstockFinal[MAX_STOCK]{};
    char* observaciones[MAX_STOCK];
    //Ordenar por ascendente por el distrito, descendente por nombre
    //almacen
    leerDatoAlmacen("source/docs/Almacen.csv",ARRcodigoAlmacen,
                    ARRnombreAlmacen,ARRpostalAlmacen,num_almacen);
    leerDatosProductos("source/docs/Productos.csv",ARRcodigoProducto,
                    ARRnombreProducto,num_producto);
    reportePruebaAlamcenes("source/docs/AlmacenesOrdenados.txt",
                    ARRcodigoAlmacen,
                    ARRnombreAlmacen,ARRpostalAlmacen,num_almacen);
    leerStockProductos("source/docs/stockProductos.txt",
                    ARRcodigo_productoStock,ARRcodigo_almacenStock
                    ,ARRstockInicialStock,num_stock);
    reporteSimpleStock("source/docs/reportStock.txt",
                    ARRcodigo_productoStock,ARRcodigo_almacenStock
                    ,ARRstockInicialStock,num_stock); 
    actualizacionDatos(num_almacen,num_producto,num_stock,
                    ARRpostalAlmacen,ARRnombreAlmacen,ARRcodigoAlmacen,
                    ARRcodigoProducto,ARRnombreProducto,
                    ARRcodigo_productoStock,ARRcodigo_almacenStock,
                    ARRstockInicialStock,
                    ARRingreso,ARRsalida,ARRenviado,
                    ARRrecibido,ARRstockFinal,observaciones,
                    "source/docs/Transacciones.txt");
    return 0;
}