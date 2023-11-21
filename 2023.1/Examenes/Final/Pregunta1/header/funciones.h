//Author: MAKO
#ifndef FUNCIONES_H
#define FUNCIONES_H
//LECTURA DE LIBROS
void leerLibros(struct Libro *libros,int & num_libros,
            const char* nomArch);
char* leerCadenaExacta(ifstream& arch,const char delimitador);
void lecturaLibrosUsuarios(ifstream& arch,
                        struct UsuariosConElLibro *usuarios,int& num);
void validacionDatos(struct Libro *libros,int num_libros,
                    const char* nomArch);
//IMPRESION DE REPORTE
void encabezado(ofstream& arch);
void sub_encabezado(ofstream& arch);
void sub_encabezado2(ofstream& arch);
void linea(ofstream& arch, char signo);
//LECTURA DE USUARIOS
void leerUsuarios(struct Usuario *usuarios,int & num_usuarios,
            const char* nomArch);
void lecturaUsuariosLibros(ifstream& arch,struct LibroEnSuPoder *libros,int& num);
void validacionDatosUsuarios(struct Usuario *usuarios,int num_usuarios,
                    const char* nomArch);
void encabezado1(ofstream& arch);
void sub_encabezado1(ofstream& arch);
void sub_encabezado2_1(ofstream& arch);
//DEVOLUCION
void devoluciones(struct Usuario *usuarios,struct Libro *libros,
                int num_usuarios,int num_libros,
                const char* nomArch);
int buscarUsuario(int dni,struct Usuario *usuarios,int num_usuarios);
int buscarLibro(char *codigo,struct Libro *libros,int num_libros);
int buscarUsuarioLibro(int dni,struct UsuariosConElLibro *usuarios,int cantUsuarios);
void disminucionCalificacion(double& clasificacion,char categoria);
void eliminarLibro(struct LibroEnSuPoder *libros,struct UsuariosConElLibro *usuarios,
                    int& cantLibros,int& cantUsuarios,
                    int dni,char *codigo);
#endif