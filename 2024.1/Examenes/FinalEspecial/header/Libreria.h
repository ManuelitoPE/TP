//AUTHOR: MAKO
#ifndef LIBRERIA_H
#define LIBRERIA_H
#include "Venta.h"

struct Libreria{
    int codigo;
    struct Venta ventas[10];
    int cantidadVentas;
    double totalVentas;
};

#endif
