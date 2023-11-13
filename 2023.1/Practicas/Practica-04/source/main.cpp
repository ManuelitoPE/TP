//Author: MAKO
#include<iostream>
#include<iomanip>
using namespace std;
#include"../header/funciones.h"
#include"../header/Libros.h"
#include"../header/Solicitudes.h"   
#include"../header/Usuarios.h"
int main(int argc, char** argv){
    //ESTRUCTURAS
    struct Usuarios *usuarios;
    struct Libros *libros;
    struct Solicitudes *solicitudes;
    //ASIGNAMOS ESPACIO
    usuarios= new struct Usuarios[70]{};
    libros= new struct Libros[40]{};
    solicitudes= new struct Solicitudes[300]{};   
    //NUMERO DE ESTRUCTURAS
    int num_Usuarios=0, num_Libros=0, num_Solicitudes=0;
    //LECTURA DE DATOS
    //Leemos los usuarios
    lecturaDeUsuarios(usuarios,num_Usuarios,
                    "source/docs/Usuarios.csv");
    //Leemos los libros
    lecturaDeLibros(libros,num_Libros,
                    "source/docs/Libros.csv");
    //Leemos las solicitudes
    lecturaDeSolicitudes(solicitudes,num_Solicitudes,
                    "source/docs/SolicitudesDePrestamo.txt");
    //IMPRESION DE DATOS
    impresionDeDatos(usuarios,libros,solicitudes,num_Usuarios,
                    num_Libros,num_Solicitudes,
                    "source/docs/DatosDeLosArreglos.txt");
    //ORDENAMOS LOS USUARIOS
    ordenandoSegunPolitica(usuarios,num_Usuarios);
    ordenandoSolicitudes(usuarios,solicitudes,num_Usuarios,
                       num_Solicitudes);
    //ATENDEMOS LOS PEDIDOS 
    atendiendoPedidos(usuarios,libros,solicitudes,num_Usuarios,
                  num_Libros,num_Solicitudes);
    //IMPRESION DE DATOS
    impresionDeDatos(usuarios,libros,solicitudes,num_Usuarios,
                    num_Libros,num_Solicitudes,
                    "source/docs/DatosDeLosArreglos2.txt");
    return 0;
}