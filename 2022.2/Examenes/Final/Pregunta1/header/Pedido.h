#ifndef PEDIDO_H
#define PEDIDO_H
#include "../header/ProductoPedido.h"
struct Pedido{
    int codigo;
    struct ProductoPedido *productos;
    int cantProductos;
    int hora;
    char* repartidorRappi;
    char* codigoUsuario;
    char* distrito;
    char* direccion;
    double montoTotal;
};
#endif