#ifndef FUNCIONES_H
#define FUNCIONES_H
void crearDirecciones(const char* nomArchBin,const char* nomArch);
void crearPedidos(const char* nomArchBin,const char* nomArch);
void crearArchivoBinario(const char* nomArchBin);
int buscarCodigo(fstream& archBin,int codigo);
void agregarProductos(ifstream& arch,struct Pedido &pedido);
void actualizacionDePedidos(const char* nomArchPedidos,
                        const char* nomArchDirecciones,
                        const char* nomArch);
void ingresoDeDatosEnPedidos(fstream& archPedidos,
                            fstream& archDirecciones,int hh,int mm,
                            int codigo,char* codigoUsuario,char* nombre);
void ingresoYcambioDatos(struct Pedido &pedido,struct Direccion &direccion,
                        int hh,int mm,int codigo,char* codigoUsuario,
                        char* nombre);
int buscarCodigoUsuario(fstream& archBin,char* codigoUsuario);
double calcularDistancia(double latitud,double longitud);   
void ordenarPedidos(const char* nomArchBin);
void emitirReporte(const char* nomArchBin,const char* nomArch);
void encabezado(ofstream& arch);
void subencabezado(ofstream& arch);
void subencabezado2(ofstream& arch);
void linea(ofstream& arch,char signo);
int cantidadEstructuras(fstream& archBin,int sizeDireccion);
#endif