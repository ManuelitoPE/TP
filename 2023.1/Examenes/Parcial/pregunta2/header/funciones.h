#ifndef FUNCIONES_H
#define FUNCIONES_H
void pedirDatos(int& fechaI,int& fechaF);
int comprimir(int dd,int mm,int aa);
void cargarStocks(int* ARRcod_pro,int* ARRcod_almacen,
                  int* ARRstock,int& stocks,
                  const char* nomStockProductos);
void procesoDatos(const char* nomTransacciones,int* ARRcod_pro,
                  int* ARRcod_almacen,int* ARRstock,int* ARRingresos,
                  int* ARRsalidas,int* ARRenviados,int* ARRrecibidos,
                  int* ARRstockFinal,int stocks,int fechaI,
                  int fechaF);
int buscar(int* ARRcod_almacen,int* ARRcod_pro,int aux_almacen,
           int aux_producto,int stocks);
void ordenar(int* ARRcod_almacen,int* ARRcod_pro,int* ARRstock,
             int* ARRingresos,int* ARRsalidas,int* ARRenviados,
             int* ARRrecibidos,int* ARRstockFinal,int stocks);
void cambiarInt(int& i,int& k);
void emitirReporte(int* ARRcod_almacen,int* ARRcod_pro,int* ARRstock,
                   int* ARRingresos,int* ARRsalidas,int* ARRenviados,
                   int* ARRrecibidos,int* ARRstockFinal,int stocks,
                   const char* nomReporte,int fechaI,int fechaF);
void encabezado(ofstream& report,int fechaI,int fechaF);
void descomprimir(int& ddF,int& mmF,int& aaF,int fecha);
void linea(ofstream& report,int n,char c);
void subeEncabezado(ofstream& report,int almacen);

#endif