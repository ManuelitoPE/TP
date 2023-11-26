//Author: MAKO
#include <iostream>
#include <iomanip>
using namespace std;
#include "../header/funciones.h"
int main(int argc,char** argv){
    //Crear un archivo Binario con "Farmacias.csv"
    crearFarmacias("source/docs/Farmacias.csv",
                    "source/docs/Farmacias.bin");
    crearReporteFarmacias("source/docs/Farmacias.bin",
                        "source/docs/ReporteSimpleFarmacia.txt");
    actualizarFarmacias("source/docs/Farmacias.bin",
                        "source/docs/Ventas.csv",
                        "source/docs/ProductosNoProcesados.bin");
    emitirReporte("source/docs/Farmacias.bin",
                "source/docs/ProductosNoProcesados.bin",
                "source/docs/ReporteVentas.txt");
    return 0;   
}