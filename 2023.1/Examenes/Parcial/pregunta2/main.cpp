//Author: MAKO
#include<iostream>
#include<iomanip>
using namespace std;
#include "header/funciones.h"
#define MAX_STOCKS 300

int main(){
    //Variables 
    int fechaI,fechaF,stocks=0;
    int ARRcod_pro[MAX_STOCKS],ARRcod_almacen[MAX_STOCKS],
        ARRstock[MAX_STOCKS],ARRingresos[MAX_STOCKS]{},
        ARRsalidas[MAX_STOCKS]{},ARRenviados[MAX_STOCKS]{},
        ARRrecibidos[MAX_STOCKS]{},ARRstockFinal[MAX_STOCKS]{};
    //Cargar datos de stocks
    cargarStocks(ARRcod_pro,ARRcod_almacen,ARRstock,stocks,
                 "docs/StockProductos.txt");
    pedirDatos(fechaI,fechaF);
    //Proceso de datos
    procesoDatos("docs/Transacciones.txt",ARRcod_pro,ARRcod_almacen,
                 ARRstock,ARRingresos,ARRsalidas,ARRenviados,
                 ARRrecibidos,ARRstockFinal,stocks,fechaI,fechaF); 
    ordenar(ARRcod_almacen,ARRcod_pro,ARRstock,ARRingresos,
            ARRsalidas,ARRenviados,ARRrecibidos,ARRstockFinal,
            stocks);
    emitirReporte(ARRcod_almacen,ARRcod_pro,ARRstock,ARRingresos,
            ARRsalidas,ARRenviados,ARRrecibidos,ARRstockFinal,
            stocks,"docs/Reporte.txt",fechaI,fechaF);
    return 0;
}