#ifndef FUNCIONES_H
#define FUNCIONES_H
void emitiReporte(const char*, const char*,const char*, const char*,const char*);
void encabezado(ofstream& Report);
void espaciado(ofstream& Report,int num,char signo );
void lecturaAlmacen(ifstream& Almacen,ofstream& Report,int& num_almacen);
void nombreAlmacen(ifstream& Almacen,ofstream& Report);
void lecturaProductoYStock(ifstream& Productos,ifstream& Stock,
                        ofstream& Report,int num_almacen,int& num_producto
                            ,double& stockInicial);
void nombreProducto(ifstream& Productos,ofstream& Report);


#endif