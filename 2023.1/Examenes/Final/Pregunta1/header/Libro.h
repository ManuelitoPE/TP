//Author: MAKO
#ifndef LIBRO_H
#define LIBRO_H
#include "UsuariosConElLibro.h"
struct Libro{
    char *codigo;
    char *titulo;
    char *autor;
    int cantidad;
    double precio;
    struct UsuariosConElLibro *usuarios;
    int cantUsuarios;
};
#endif