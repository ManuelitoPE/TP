//Author: MAKO
#include <iostream>
#include <iomanip>
using namespace std;
#include "header/funciones.h"
int main(){
    //Lectura los datos de archivo Articulos.csv
    lecturaArticulos("docs/Articulos.csv","docs/Articulos.bin");
    //emitirReporte de Prueba
    pruebaArticulos("docs/Articulos.bin","docs/PruebaArticulos.txt");
    //Lectura del archivo Vendedores.csv
    lecturaVendedores("docs/Vendedores.csv","docs/Vendedores.bin"); 
    //Emitir un reporte por primera vez
    emitirReporte("docs/PruebaReporte.txt","docs/Vendedores.bin",
                  "docs/Articulos.bin");
    //Actualizar los archivos binarios 
    actualizarArchivos("docs/Ventas.txt","docs/Vendedores.bin",
                       "docs/Articulos.bin");
    //Emitir un reporte por primera vez
    emitirReporte("docs/ReporteFinal.txt","docs/Vendedores.bin",
                  "docs/Articulos.bin");
    return 0;     
}