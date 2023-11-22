//Author: MAKO
#ifndef FUNCIONES_H
#define FUNCIONES_H
//Leemos las usuarios
void lecturaDeUsuarios(struct Usuarios *usuarios,int& num_Usuarios,
                    const char* nomArch);
void creandoEspacioLibrosPrestados(char categoria, struct LibroPrestado *&libro);
char* leeCadenaExacta(ifstream& arch,const char deli);
//Leemos los libros
void lecturaDeLibros(struct Libros *libros,int& num_Libros,
                    const char* nomArch);
//Leemos las solicitudes
void lecturaDeSolicitudes(struct Solicitudes *solicitudes,int& num_Solicitudes,
                    const char* nomArch);
//Impresion de datos
void impresionDeDatos(struct Usuarios *usuarios,struct Libros *libros,
                struct Solicitudes *solicitudes,int num_Usuarios,
                int num_Libros,int num_Solicitudes,
                const char* nomArch);
void linea(ofstream& arch, char signo);
void impresionDatosUsuarios(ofstream& arch,struct Usuarios *usuarios,
                            int num_Usuarios);
void impresionDatosLibros(ofstream& arch,struct Libros *libros,
                            int num_Libros);
void impresionDatosSolicitudes(ofstream& arch,struct Solicitudes *solicitudes,
                            int num_Solicitudes);
//Ordenando segun politica
void ordenandoSegunPolitica(struct Usuarios *usuarios,int num_Usuarios);
void ordenandoSolicitudes(struct Usuarios *usuarios,
                struct Solicitudes *solicitudes,int num_Usuarios,
                int num_Solicitudes);
bool politica(int dniA,int dniB, struct Usuarios *usuarios,
            int num_Usuarios);
void cambiarStructura(struct Usuarios &usuarioA,
                    struct Usuarios &usuarioB);
void cambiarSoli(struct Solicitudes &usuarioA,
                    struct Solicitudes &usuarioB);
//ATENDIENDO PEDIDOS
void atendiendoPedidos(struct Usuarios *usuarios,struct Libros *libros,
                struct Solicitudes *solicitudes,int num_Usuarios,
                int num_Libros,int num_Solicitudes);
int BuscarUsuario(struct Usuarios *usuarios,int num_Usuarios,int dni);
int BuscarLibro(struct Libros *libros,int num_Libros,
                char *codigo);
bool verificacion(int cantPrestado_Usuaio,char categoria,
                int cantPrestado_Libro,int cantidad);
void aperturaLibrosBin(const char* nomArch,
                    const char* nomArchBin);
void pruebaDeLibrosBin(const char* nomArchBin,
                    const char* nomArch);
#endif