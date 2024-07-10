#ifndef LIBRONODO_H
#define LIBRONODO_H
#include "Libro.h"

struct LibroNodo{
    struct Libro libro{};
    struct LibroNodo *siguiente;
};


#endif