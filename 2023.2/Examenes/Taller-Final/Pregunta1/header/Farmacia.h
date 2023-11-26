//Author: MAKO
#ifndef FARMACIA_H
#define FARMACIA_H
#include "../header/Producto.h"
struct Farmacia{
    int codigo;
    char distrito[30];
    struct Producto productosVendidos[10]{};
    int cantProductos;
    
};
#endif