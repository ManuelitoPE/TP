//AUTHOR: MAKO
#ifndef LIBRONODO_H
#define LIBRONODO_H
#include "Libro.h"

struct LibroNodo{
    struct Libro datoLibro;
    struct LibroNodo *siguiente;
};


#endif