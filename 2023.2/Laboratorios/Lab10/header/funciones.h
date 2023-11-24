//Auhtor: MAKO
#ifndef FUNCIONES_H
#define FUNCIONES_H
void leerDatosArticulos(const char* nomArch,const char* nomArchBin);
void cambiarMayusculas(char* codigo);
void leerDatosVendedores(const char* nomArch,const char* nomArchBin);
void cambiarNombre(char* nombre);
void actualizarEstrucutras(const char* nomArchVendedores,
                    const char* nomArchArticulos,
                    const char* nomArch);
void ingresoDeDatos(char* codigo,int codigoVendedor,int cant,
                    fstream& archArticulos,fstream& archVendedores);
int cantidadEstructuras(fstream& arch,int size);
int buscarArticulo(fstream& archArticulos,int cantArticulos,char* codigo);
int buscarVendedor(fstream& archVendedores,int cantVendedores,int codigoVendedor);
void actualizar(struct Vendedor& vendedor,struct Articulo &articulo,int cant);
int buscarArticulo(struct ArticuloVendido *articulosVendidos,
                int cant, char* codigo);
void correccionVendedores(const char* nomArchBin);
void ordenarVendedores(const char* nomArchBin);
void emitirReporte(const char* nomArchVendedores,
                    const char* nomArchArticulos,
                    const char* nomArch);
void impresionVendedores(ofstream& arch,ifstream& archVendedores,double& pago,
                        fstream& archArticulos);
void impresionArticulos(ofstream& arch,fstream& archArticulos,double pago);
void linea(ofstream& arch,char signo);
void encabezado(ofstream& arch);
void encabezadoA(ofstream& arch);
void subEncabezado(ofstream& arch);
void subEncabezado2(ofstream& arch);

#endif