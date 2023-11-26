//Author: MAKO
#include <iostream>
#include <iomanip>
using namespace std;
#include "../header/funciones.h"
#include "../header/Farmacia.h"
#include "../header/ProductoAux.h"
#define MAX_FARMACIAS 50
#define MAX_PRODUCTOS 100
int main(int argc, char** argv){
    //Estructuras
    struct Farmacia *farmacia;
    struct ProductoAux *productoAux;
    //Asignacion de espacio
    farmacia= new struct Farmacia[MAX_FARMACIAS]{};
    productoAux= new struct ProductoAux[MAX_PRODUCTOS]{};
    //Numero de estructuras 
    int num_farmacia=0,num_productoAux=0;
    //Leer el contenido de "Farmacias.csv"
    leerFarmacias(farmacia,"source/docs/Farmacias.csv",num_farmacia);
    emitirReporteFarmacias(farmacia,"source/docs/ReporteFarmacias.txt",
                            num_farmacia);
    actualizarFarmacias(farmacia,productoAux,num_farmacia,num_productoAux,
                        "source/docs/Ventas.csv");
    emitirReporte(farmacia, productoAux,num_farmacia,num_productoAux,
                "source/docs/ReporteVentas.txt");
    return 0;
}