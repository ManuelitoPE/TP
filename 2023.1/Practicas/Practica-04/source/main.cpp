#include<iostream>
#include<iomanip>
using namespace std;
#include"../header/funciones.h"
#include"../header/LibroPrestado.h"
#include"../header/Libros.h"
#include"../header/Solicitudes.h"
#include"../header/UsuarioConLibro.h"
#include"../header/Usuarios.h"
int main(int argc, char** argv){
    //Estructuras
    struct Usuarios usuarios[70]{};
    struct Libros libros[50]{};
    struct Solicitudes solicitudes[300];{}
    //Numero de estrucutras
    int numUsuarios=0, numLibros=0, numSolicitudes=0;
    //Leemos las estructuras
    lecturaDeDatos(usuarios,libros,solicitudes,numLibros
                    ,numUsuarios,numSolicitudes,
                    "source/docs/Libros.csv",
                    "source/docs/Usuarios.csv",
                    "source/docs/SolicitudesDePrestamo.txt");
    return 0;
}