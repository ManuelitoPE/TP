//Author: MAKO
#ifndef FUNCIONES_H
#define FUNCIONES_H
//Leer el contenido de "Farmacias.csv"
void leerFarmacias(struct Farmacia *farmacia,const char* nomArch, 
                int& num_farmacia);
char* leeExacto(ifstream& arch,char deli);
void emitirReporteFarmacias(struct Farmacia *farmacia,
                const char* nomArch,int num_farmacia);
void linea(ofstream& arch, char signo, int num);
void encabezado(ofstream& arch);
void actualizarFarmacias(struct Farmacia *farmacia,
            struct ProductoAux *productoAux,int num_farmacia,
            int& num_productoAux,const char* nomArch);
void incluirDatos(int codigoFarmacia,int cant,char* codigoProducto,
                    char *nombre,double precio,struct Farmacia *farmacia,
                    struct ProductoAux *productoAux,int num_farmacia,
                    int& num_productoAux);
int buscarFarmacia(struct Farmacia *farmacia,int num_farmacia,
                int codigoFarmacia);
int buscarProducto(struct Producto *productos,int num_producto,
                    char* codigoProducto);
void emitirReporte(struct Farmacia *farmacia,struct ProductoAux *productoAux,
            int num_farmacia,int num_productoAux,
            const char* nomArch);
void encabezado1(ofstream& arch);
void subEncabezado(ofstream& arch);
void encabezado2(ofstream& arch);
#endif
