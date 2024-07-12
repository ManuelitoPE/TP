//AUTHOR: MAKO
#ifndef CLIENTENODO_H
#define CLIENTENODO_H
#include "Cliente.h"

struct ClienteNodo{
    struct Cliente datoCliente;
    struct ClienteNodo *siguiente;
};

#endif