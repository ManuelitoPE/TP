//Author: MAKO
#include <iostream>
#include <iomanip>
using namespace std;
#include "header/funciones.h"
#include "header/Articulo.h"

int main(){
    //Lectura de datos del arch Articulos.csv
    lecturaArticulos("docs/Articulos.csv","docs/Articulos.bin"); 
    //Lectura de datos del archivo Vendedores 
    lecturaVendedores("docs/Vendedores.csv","docs/Vendedores.bin"); 
    //Lectura de Ventas y actualizacion de los archBin
    actualizacionVentas("docs/Ventas.txt","docs/Vendedores.bin",
                        "docs/Articulos.bin");
    //Correcion de vendedores
    correcionVendedores("docs/Vendedores.bin");
    //Ordenar los vendedores
    ordenamiento("docs/Vendedores.bin");
    //Finalmente
    emitirReporte("docs/Vendedores.bin","docs/ReporteDePagos.txt",
                  "docs/Articulos.bin"); 
    return 0;
}