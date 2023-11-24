//Author: MAKO
#include <iostream>
#include <iomanip>
using namespace std;
#include"../header/funciones.h"
int main(int argc,char** argv){
    //Leer los datos de Articulos.csv
    leerDatosArticulos("source/docs/Articulos.csv",
                        "source/docs/Articulos.bin");
    //Leer los datos de Vendedores.csv
    leerDatosVendedores("source/docs/Vendedores.csv",
                        "source/docs/Vendedores.bin");
    //Leer el arch Ventas.txt
    actualizarEstrucutras("source/docs/Vendedores.bin",
                        "source/docs/Articulos.bin",
                        "source/docs/Ventas.txt");
    //Correccion de vendedores.bin
    correccionVendedores("source/docs/Vendedores.bin");
    ordenarVendedores("source/docs/Vendedores.bin");
    emitirReporte("source/docs/Vendedores.bin",
                "source/docs/Articulos.bin",
                "source/docs/ReporteDePagos.txt");
    return 0;
}