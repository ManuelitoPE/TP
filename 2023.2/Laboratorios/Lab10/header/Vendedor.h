//Author: MAKO
#ifndef VENDEDOR_H
#define VENDEDOR_H
#include "../header/ArticuloVendido.H"
struct Vendedor{
    int codigo;
    char nombre[40];
    double porcentaje;
    double cuotaMinima;
    struct ArticuloVendido articulosVendidos[100]{};
    int cantElementos;
    double montoTotal;
    bool SuperoCuotaMinima;
};
#endif