//Author: MAKO
#ifndef USUARIO_H
#define USUARIO_H
#include "../header/LibrosEnSuPoder.h"
struct Usuario{
    int dni;
    char nombre[60];
    char categoria;
    double calificacion;
    struct LibrosEnSuPoder libros[10];
    int cantidadDeLibros;
};
#endif