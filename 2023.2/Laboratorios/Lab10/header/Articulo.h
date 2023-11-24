//Author: MAKO
#ifndef ARTICULO_H
#define ARTICULO_H
struct Articulo{
    char codigo[8];
    char descripcion[70];
    double precio;
    int cantVendido;
    double montoVendido;
};
#endif