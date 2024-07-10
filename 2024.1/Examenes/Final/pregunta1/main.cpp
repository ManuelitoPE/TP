//Author: MAKO
#include <iostream>
#include <iomanip>
using namespace std;
#include "header/funciones.h"
#include "header/LibroNodo.h"
int main(){
    struct LibroNodo *listaLibro;
    lecturalibros("docs/Libros.csv",listaLibro);
    
    return 0;
}