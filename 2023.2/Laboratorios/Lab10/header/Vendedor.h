//Author: MAKO
#ifndef VENDEDOR_H
#define VENDEDOR_H
#include "ArticuloVendido.h"

struct Vendedor{
    int codigo;
    char nombre[50];
    double porcentajeVentas;
    double cuotaMinima;
    struct ArticuloVendido articulosVendidos[100]{};
    int cant;
    double montoTotalVendido;
    bool superoCuotaMinima;    
};


#endif