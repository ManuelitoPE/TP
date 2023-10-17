#ifndef FUNCIONES_H
#define FUNCIONES_H
void emitiReporte(const char*, const char*,const char*, const char*,const char*);
void encabezado(ofstream& Report);
void espaciado(ofstream& Report,int num,char signo );
void lecturaAlmacen(ifstream& Almacen,ofstream& Report,int& num_almacen);
void nombreAlmacen(ifstream& Almacen,ofstream& Report);
void lecturaProductoYStock(ifstream& Productos,ifstream& Stock,
                        ofstream& Report,int num_almacen,int& num_producto);
void nombreProducto(ifstream& Productos,ofstream& Report);
void lecturaEImpresionStock(ofstream& Report,ifstream& Stock,
                            int num_almacen,int num_producto, double& );
void impresionTransacciones(ifstream& Transacciones,ofstream& Report,
                            int num_almacen, int num_producto);
void TransaccionDeProducto(ifstream& Transacciones,ofstream& Report,
                            int num_producto);
void impresionTIPO(ofstream& Report,char tipo, int almacen);




#endif