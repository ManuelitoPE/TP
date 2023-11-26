//Author: MAKO
#ifndef PRODUCTOSNOPROCESADOS_H
#define PRODUCTOSNOPROCESADOS_H
struct ProductosNoProcesados{
    int codigoFarmacia;
    char codigoProducto[8];
    char nombreProducto[40];
    int cantidadVendida;
    double precio;
};
#endif