//Authot: Mako
#include<iostream>
#include<iomanip>
using namespace std;
#include "header/funciones.h"
int main(){
    emitirReporte("docs/Almacen.txt","docs/Productos.txt",
                  "docs/StockProductos.txt","docs/Transacciones.txt",
                  "docs/Reporte.txt");
    return 0;
}