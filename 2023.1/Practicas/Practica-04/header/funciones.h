#ifndef FUNCIONES_H
#define FUNCIONES_H
void lecturaDeDatos(struct Usuarios *usuarios,
                    struct Libros *libros,
                    struct Solicitudes *solicitudes,
                    int& numLibros,int& numUsuarios,
                    int& numSolicitudes,
                    const char* nomLibros,
                    const char* nomUsuarios,
                    const char* nomSolicitudes);
#endif