//Auhtor: MAKO
#ifndef FUNCIONES_H
#define FUNCIONES_H
void ingresoDatosDireccion(struct Direccion *direccion,int& cant,
                            const char* nomArch);
void ingresoDatosPedido(struct Pedido *pedido,int& cant,
                            const char* nomArch);
void asignacionProductos(ifstream& arch, struct Pedido &pedido,int cant);
char* leeCadenaExacta(ifstream& arch,char delimitador);
void actualizarEstructuras(struct Pedido *pedido,
                        struct Direccion *direccion,int num_direccion,
                        int num_pedido,
                        const char* nomArch);
void ingresoDeDatos(int hh,int mm,int codigo,char *nombre,
                    char* codigoUsuario,struct Direccion* direccion,
                    struct Pedido* pedido,int num_direccion,
                    int num_pedido);
int buscarDireccion(struct Direccion *direccion,int num_direccion,
                    char* codigoUsuario);
int buscarPedido(struct Pedido *pedido,int num_pedido,int codigo);
void emitirReporte(struct Pedido *pedido,int num_pedido,
                const char* nomArch);
void encabezado(ofstream& arch);
void subEncabezado(ofstream& arch);
void linea(ofstream& arch,char signo);
void pieDeReporte(ofstream& arch,struct Pedido *pedido, int num);
#endif