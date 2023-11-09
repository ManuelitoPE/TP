#ifndef LIBROS_H
#define LIBROS_H
#include "UsuarioConLibro.h"
struct Libros{
    char codigo[8];
    char nombre[80];
    char autor[40];
    int cantidad;
    double precio;
    struct UsuarioConLibro *UsuariosQueTieneUnEjemplar;
    int cant_prestado;
};

#endif