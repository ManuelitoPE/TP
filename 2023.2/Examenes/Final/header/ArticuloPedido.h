#ifndef ARTICULOPEDIDO_H
#define ARTICULOPEDIDO_H

struct ArticuloPedido{
    char codigo[8];
    int cant;
    int fechaUltimoPedido;
    double montoTotal;
};


#endif