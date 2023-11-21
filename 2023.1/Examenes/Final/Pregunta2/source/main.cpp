//Auhtor: MAKO
#include<iostream>
#include<iomanip>
using namespace std;
#include "../header/funciones.h"
int main(int argc, char** argv){
    //Crear Libros.bin 
    crearArchLibros("source/docs/Libros.csv","source/docs/Libros.bin");
    pruebaLibrosBin("source/docs/Libros.bin","source/docs/PruebaLibros.txt");
    //Crear Usuarios.csv
    crearArchUsuarios("source/docs/Usuarios.csv","source/docs/Usuarios.bin");
    pruebaUsuariosBin("source/docs/Usuarios.bin","source/docs/PruebaUsuarios.txt");
    //Modificar
    modificar("source/docs/DevolucionDeLibros.txt","source/docs/Libros.bin",
               "source/docs/Usuarios.bin");
    pruebaLibrosBin("source/docs/Libros.bin","source/docs/PruebaFINALLibros.txt");
    pruebaUsuariosBin("source/docs/Usuarios.bin","source/docs/PruebaFINALUsuarios.txt");
    return 0;
}