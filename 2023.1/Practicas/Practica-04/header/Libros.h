//Author: MAKO
#ifndef LIBROS_H
#define LIBROS_H
#include "UsuarioConLibro.h"
struct Libros{
    char *codigo;
    char *nombre;
    char *autor;
    int cantidad;
    double precio;
    struct UsuarioConLibro *UsuariosQueTieneUnEjemplar;
    int cant_prestado;
};

#endif