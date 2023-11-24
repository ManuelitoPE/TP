//Author: MAKO
#include <iostream>
#include <iomanip>
using namespace std;
#include "../header/funciones.h"
int main(int argc,char** argv){
    //Crear un archivo binarrio "direcciones.bin"
    crearDirecciones("source/docs/direcciones.bin",
                    "source/docs/direcciones.csv");
    //Crear "pedidos.bin" con "pedidos.csv"
    crearPedidos("source/docs/pedidos.bin",
                "source/docs/pedidos.csv");
    //Actualizamos los datos
    actualizacionDePedidos("source/docs/pedidos.bin",
                        "source/docs/direcciones.bin",
                        "source/docs/rappi.csv");
    ordenarPedidos("source/docs/pedidos.bin");
    emitirReporte("source/docs/pedidos.bin",
                "source/docs/Reporte_tp_rappi.txt");
    return 0;
}
    