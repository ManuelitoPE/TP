//Author: MAKO  
#ifndef FARMACIA_H
#define FARMACIA_H
#include "../header/Producto.h"
struct Farmacia{
    int codigo;
    char* distrito;
    struct Producto *productoVendidos;
    int cantidadProductos;
};
#endif