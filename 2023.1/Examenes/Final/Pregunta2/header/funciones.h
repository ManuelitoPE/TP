//Author: MAKO
#ifndef FUNCIONES_H
#define FUNCIONES_H
void crearArchLibros(const char* nomArch,const char* nomArchBin);
void leerUsuarios(struct UsuarioConElLibro *usuarios,ifstream& arch,int& cant);
void pruebaLibrosBin(const char* nomArchBin,const char* nomArch);
void encabezado(ofstream& arch);
void linea(ofstream& arch, char signo);
void subEncabezado(ofstream& arch);
void crearArchUsuarios(const char* nomArch,const char* nomArchBin);
void leerLibros(struct LibrosEnSuPoder *libros,ifstream& arch,int& cant);
void pruebaUsuariosBin(const char* nomArchBin,const char* nomArch);
void encabezado_1(ofstream& arch);
void subEncabezado_1(ofstream& arch);
void modificar(const char* nomArch,const char* nomArchLibros,
                const char* nomArchUsuarios);
void actualizarArchivos(char* codigo,int dni,int fecha,
                        fstream& archLibros,fstream& archUsuarios);
int cantidadEstructuras(fstream& arch,int Structsize);
int buscarUsuario(int cantStructsUsuario,fstream& archUsuarios,int dni);
int buscarLibro(int cantStructsLibro,fstream& archLibros,char* codigo);
void actualizacionLibros(int fecha,int dni,struct UsuarioConElLibro *usuario,
                        bool& castigo,int& cant);
void actualizacionUsuarios(char* codigo,struct LibrosEnSuPoder *libro,int& cant);
void castigoUsuario(struct Usuario &usuario);
#endif