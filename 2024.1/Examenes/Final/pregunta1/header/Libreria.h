//Author: MAKO
#ifndef LIBRERIA_H
#define LIBRERIA_H
#include "Venta.h"

struct Libreria{
    int code;
    struct Venta ventas[10]{};
    int cantidadVentas;
    double totalVentas;
};


#endif