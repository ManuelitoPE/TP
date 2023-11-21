//Author: MAKO
#include<iostream>
#include<iomanip>

using namespace std;

#include "../header/Usuario.h"
#include "../header/Libro.h"
#include "../header/funciones.h"

#define MAX_LIBRO 50
#define MAX_USUARIO 100
int main(int argc, char** argv){
    //ESTRUCTURAS
    struct Libro libros[MAX_LIBRO]{};
    struct Usuario usuarios[MAX_USUARIO]{};
    //Numero de estructuras
    int num_libros=0, num_usuarios=0;
    //ASIGNACION DE MEMORIA

    //LEER DATOS 
    //Lectura de los libros
    leerLibros(libros,num_libros,"source/docs/Libros.csv");
    //VALIDACION DE DATOS
    validacionDatos(libros,num_libros,"source/docs/ArregloInicialLibros.txt");
    //Lectura de los Usuarios
    leerUsuarios(usuarios,num_usuarios,"source/docs/Usuarios.csv");
    //VALIDACION DE DATOS u
    validacionDatosUsuarios(usuarios,num_usuarios,
                            "source/docs/ArregloInicialUsuario.txt");
    //DEVOLUCIONES
    devoluciones(usuarios,libros,num_usuarios,num_libros,
                "source/docs/DevolucionDeLibros.txt");
    //VALIDACIONES FINALES
    validacionDatos(libros,num_libros,"source/docs/ArregloFinalLibros.txt");
    validacionDatosUsuarios(usuarios,num_usuarios,
                            "source/docs/ArregloFinalUsuario.txt");
    return 0;
 }