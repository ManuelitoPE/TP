//Author: MAKO
#ifndef FUNCIONES_H
#define FUNCIONES_H
void crearFarmacias(const char* nomArch,const char* nomArchBin);
void crearReporteFarmacias(const char* nomArchBin,
                            const char* nomArch);
void encabezado(ofstream& arch);
void linea(ofstream& arch, char signo, int num);
void actualizarFarmacias(const char* nomArchFarmacia,
                    const char* nomArch,
                    const char* nomArchProductoNoProcesados);
void crearArchBinario(const char* nomArchBin);
void ingresarDatosFarmacia(int codigoFarmacia,int cantidad,
                double precio,char* codigoProducto,char* nombre,
                fstream& archFarmacia,fstream& archNoProcesados);
int cantidadEstructuras(fstream& arch,int size);
int buscarFarmacia(fstream& archFarmacia,int cantFarmacias,
                int codigoFarmacia);
int buscarProducto(int cantProductos,
            struct Producto *productosVendidos,char* codigoProducto);
void ingresoDeProductos(struct Producto &producto,int cantidad,
                        double precio,char* codigoProducto,
                        char* nombre);
void ingresoDeNoProcesadoss(struct ProductosNoProcesados& noProcesado,
                        int codigoFarmacia,int cantidad,
                        double precio,char* codigoProducto,
                        char* nombre);
void emitirReporte(const char* nomArchFarmacia,
                    const char* nomArchProductoNoProcesados,
                    const char* nomArch);
void imprimirDatosFarmacias(ifstream& nomArchFarmacia,ofstream& arch);
void imprimirDatosProductosNoProcesados(ifstream& nomArchProductoNoProcesados,
                                        ofstream& arch);
void encabezado1(ofstream& arch);
void subEncabezado(ofstream& arch);
void encabezado2(ofstream& arch);
#endif
