//Author:MAKO
#ifndef LIBRO_H
#define LIBRO_H
#include "Libreria.h"

struct Libro{
    char code[8];
    char titulo[80];
    char autor[40];
    double precio;
    struct Libreria librerias[5]{};
    int cantidadLibrerias;
    double totalVentas;
    int unidadesVendidas;
    int cantidadBuenasCalificaciones;
    double sumaBuenasCalificaciones;
    int cantidadMalasCalificaciones;
    double sumaMalasCalificaciones;
};


#endif