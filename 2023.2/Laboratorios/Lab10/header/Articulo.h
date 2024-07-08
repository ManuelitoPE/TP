//Author: MAKO
#ifndef ARTICULO_H
#define ARTICULO_H

struct Articulo{
    char code[8];
    char description[100];
    double price;
    int cant;
    double montoVendido;
};

#endif