#ifndef USUARIOS_H
#define USUARIOS_H
#include "LibroPrestado.h"
struct Usuarios{
    int dni;
    char *nombre;
    char categoria;
    double calificacion;
    struct LibroPrestado *LibrosEntregados;
    int cant_prestado;
};
#endif