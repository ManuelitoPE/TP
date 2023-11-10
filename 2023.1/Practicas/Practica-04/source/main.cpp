#include<iostream>
#include<iomanip>
using namespace std;
#include"../header/funciones.h"
#include"../header/Libros.h"
#include"../header/Solicitudes.h"   
#include"../header/Usuarios.h"
int main(int argc, char** argv){
    //Estructuras
    struct Usuarios *usuarios;
    struct Libros *libros;
    struct Solicitudes *solicitudes;
    usuarios= new struct Usuarios[70]{};
    libros= new struct Libros[40]{};
    solicitudes= new struct Solicitudes[300]{};   
    //Numero de estrucutras
    int num_Usuarios=0, num_Libros=0, num_Solicitudes=0;
    //Lectura de
    //Leemos las usuarios
    lecturaDeUsuarios(usuarios,num_Usuarios,
                    "source/docs/Usuarios.csv");
    //Leemos los libros
    lecturaDeLibros(libros,num_Libros,
                    "source/docs/Libros.csv");
    //Leemos las solicitudes
    lecturaDeSolicitudes(solicitudes,num_Solicitudes,
                    "source/docs/SolicitudesDePrestamo.txt");
    //Impresionde los datos
    impresionDeDatos(usuarios,libros,solicitudes,num_Usuarios,
                    num_Libros,num_Solicitudes,
                    "source/docs/DatosDeLosArreglos.txt");
    //Ordenamos los datos
    ordenandoSegunPolitica(usuarios,solicitudes,num_Usuarios,
                        num_Solicitudes);
    //Atender los pedidos
    atendiendoPedidos(usuarios,libros,solicitudes,num_Usuarios,
                   num_Libros,num_Solicitudes);
    //Emitiendo el segundo reporte
    impresionDeDatos(usuarios,libros,solicitudes,num_Usuarios,
                    num_Libros,num_Solicitudes,
                    "source/docs/DatosDeLosArreglos2.txt");
    return 0;
}