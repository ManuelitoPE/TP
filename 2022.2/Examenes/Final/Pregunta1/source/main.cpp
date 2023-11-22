//Author: MAKO
#include<iostream>
#include<iomanip>
using namespace std;
#include"../header/funciones.h"
#include "../header/Direccion.h"
#include "../header/Pedido.h"
#define MAX_DIRECCIONES 50
#define MAX_PEDIDO 100
int main(int argc, char** argv){
    //Estructuras 
    struct Direccion direccion[MAX_DIRECCIONES]{};
    struct Pedido pedido[MAX_PEDIDO]{};
    //Numero de estructuras
    int num_direccion=0,num_pedido=0;
    //Cargar los datos de direccion.csv
    ingresoDatosDireccion(direccion,num_direccion,
                        "source/docs/direcciones.csv");
    //Cargar los datos de pedido.csv
    ingresoDatosPedido(pedido,num_pedido,
                        "source/docs/pedidos.csv");
    //Cargar los datos completos con rappi.csv
    actualizarEstructuras(pedido, direccion,num_direccion,num_pedido
                        ,"source/docs/rappi.csv");
    emitirReporte(pedido,num_pedido,"source/docs/ReportePedidos.txt");
    return 0;
}