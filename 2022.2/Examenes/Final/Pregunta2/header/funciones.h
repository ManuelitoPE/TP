#ifndef FUNCIONES_H
#define FUNCIONES_H
void crearDirecciones(const char* nomArchBin,const char* nomArch);
void crearPedidos(const char* nomArchBin,const char* nomArch);
void crearArchivoBinario(const char* nomArchBin);
int buscarCodigo(fstream& archBin,int codigo);
void agregarProductos(ifstream& arch,struct Pedido &pedido);
void emitirReporte(const char* nomArchBin);
int cantidadEstructuras(fstream& archBin,int sizeDireccion);
#endif