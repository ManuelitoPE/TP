//Author: MAKO
#ifndef LIBRO_H
#define LIBRO_H
#include "../header/UsuarioConElLibro.h"
struct Libro{
    char codigo[8];
    char titulo[90];
    char autor[60];
    int cantidad;
    double precio;
    struct UsuarioConElLibro usuarios[50];
    int cantidadUsuarios;
};
#endif