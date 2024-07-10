//Author: MAKO
#include <iostream>
#include <iomanip>
using namespace std;
#include "header/funciones.h"

int main(){
    //Lectura Clientes.csv
    lecturaClientes("docs/Clientes.csv","docs/Clientes.bin");
    //EmitirReporte Prueba clientes
    emitirClientes("docs/PruebaClientes.txt","docs/Clientes.bin"); 
    //Lectura de Libros.csv
    lecturaLibros("docs/Libros.csv","docs/Libros.bin");
    //Emitir Reporte Solicitado
    emitirReporte("docs/PruebaLibros.txt","docs/Libros.bin");
    //Leer los datos del archivo Ventas
    actualizar("docs/Libros.bin","docs/Ventas.txt",
               "docs/Clientes.bin");    
    return 0;
}