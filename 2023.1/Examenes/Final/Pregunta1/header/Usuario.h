#ifndef USUARIO_H
#define USUARIO_H
#include "LibroEnSuPoder.h"
struct Usuario{
    int dni;
    char *nombre;
    char categoria;
    double clasificacion;
    struct LibroEnSuPoder *libros;
    int cantLibros;    
};
#endif