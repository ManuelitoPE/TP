#ifndef VENDEDOR_H
#define VENDEDOR_H
#include "ArticuloPedido.h"
struct Vendedor{
    int codigo;
    char nombre[80];
    double porcentaje;
    double cuotaMinima;
    struct ArticuloPedido articulosVendidos[100]{};
    int cantArticulosVendidos;
    struct ArticuloPedido articulosPerdidos[100]{};
    int cantArticulosPerdidos;
    double montoTotalVendido;
    double monoTotalPerdido;
};


#endif