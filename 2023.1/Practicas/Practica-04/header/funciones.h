#ifndef FUNCIONES_H
#define FUNCIONES_H
//Leemos las usuarios
void lecturaDeUsuarios(struct Usuarios *usuarios,int& num_Usuarios,
                    const char* nomArch);
void creandoEspacioLibrosPrestados(char categoria, struct LibroPrestado *&libro);
//Leemos los libros
void lecturaDeLibros(struct Libros *libros,int& num_Libros,
                    const char* nomArch);
//Leemos las solicitudes
void lecturaDeSolicitudes(struct Solicitudes *solicitudes,
                    int& num_Solicitudes,
                    const char* nomArch);
void impresionDeDatos(struct Usuarios *usuarios,struct Libros *libros,
                struct Solicitudes *solicitudes,int num_Usuarios,
                int num_Libros,int num_Solicitudes,
                const char* nomArch);
void linea(ofstream& arch, char signo);
void impresionDatosUsuarios(ofstream& arch,struct Usuarios *usuarios,
                            int num_Usuarios);
void impresionDatosLibros(ofstream& arch,struct Libros *libros,
                            int num_Usuarios);
void impresionDatosSolicitudes(ofstream& arch,struct Solicitudes *solicitudes,
                            int num_Usuarios);
void ordenandoSegunPolitica(struct Usuarios *usuarios,
                struct Solicitudes *solicitudes,int num_Usuarios,
                int num_Solicitudes);
bool politica(int dniA,int dniB, struct Usuarios *usuarios,
            int num_Usuarios);
int BuscarUsuario(struct Usuarios *usuarios,int num_Usuarios,int dni);
int BuscarLibro(struct Libros *libros,int num_Libros,
                char *codigo);
void cambiarStructura(struct Solicitudes &solicitudesA,
                    struct Solicitudes &solicitudesB);
void atendiendoPedidos(struct Usuarios *usuarios,struct Libros *libros,
                struct Solicitudes *solicitudes,int num_Usuarios,
                int num_Libros,int num_Solicitudes);
bool verificacion(int cantPrestado_Usuaio,char categoria,
                int cantPrestado_Libro,int cantidad);

#endif