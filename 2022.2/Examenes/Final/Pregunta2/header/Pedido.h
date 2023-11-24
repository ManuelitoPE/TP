//Author: MAKO
#ifndef PEDIDO_H
#define PEDIDO_H
#include "../header/Direccion.h"
#include"../header/ProductoPedido.h"
struct Pedido{
    int codigo;
    struct ProductoPedido productos[10];
    int cantProductos;
    int hora;
    char repartidorRappi[30];
    char codigoUsuarios[7];
    struct Direccion direccionRappi;
    double distancia;
    double montoTotal;
};

#endif