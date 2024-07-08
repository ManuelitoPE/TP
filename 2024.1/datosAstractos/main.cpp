//Author: MAKO
#include <iostream>
#include <iomanip>
using namespace std;
#include "header/funciones.h"
#include "header/Nodo.h"
int main(){
    //Variables
    struct Nodo *lista=nullptr; 
    crearLista("docs/datos.txt",lista);
    int cantNodos = contarNodos(lista);
    eliminarDato(lista,7);
    mostrarLista("docs/Datos.txt",lista,cantNodos);
    return 0;
}