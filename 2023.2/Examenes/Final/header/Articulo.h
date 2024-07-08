#ifndef ARTICULO_H
#define ARTICULO_H

struct Articulo{
    char codigo[8];
    char description[100];
    int stock;
    double precio;
    int cantArticulosVendidos;
    double montoVendido;
    int cantArticulosPerdidos;
    double montoPerdido;
};

#endif