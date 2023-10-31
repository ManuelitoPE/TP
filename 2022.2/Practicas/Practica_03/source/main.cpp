#include<iostream>
#include<iomanip>
using namespace std;
#include"../header/funciones.h"
#define MAX_USUARIOS 50
#define MAX_PAISES 10
#define MAX_COMENTARIO 50
// int main(int argc, char** argv){
    int main(){
    //ARREGLOS
    int ARRpaisUsuarios[MAX_USUARIOS],ARRcodigoUsuarios[MAX_USUARIOS],
        ARRseguidoresUsuarios[MAX_USUARIOS],ARRcodigoPaises[MAX_PAISES];
    int ARRfechaComentario[MAX_COMENTARIO], ARRlikesComentario[MAX_COMENTARIO],
        ARRpaisComentario[MAX_COMENTARIO],ARRcodigoComentario[MAX_COMENTARIO];
    char* ARRcomentarioComentario[MAX_COMENTARIO];
    char* ARRnombreUsuario[MAX_USUARIOS], ARRpublicoUsuario[MAX_USUARIOS];
    char* ARRpaisesPaises[MAX_PAISES];
    //Cantidad de datos
    int num_comentarios=0,num_usuarios=0,num_paises=0;
    //ARREGLOS PARA MI REPORTE
    char* ARRnombreComentario[MAX_COMENTARIO];
    char* ARRnombre_paisComentario[MAX_COMENTARIO];
    //
    //Cargar datos de usuarios
    leerArreglosUsuarios(ARRpaisUsuarios,ARRcodigoUsuarios,
                        ARRseguidoresUsuarios,ARRnombreUsuario,
                        ARRpublicoUsuario,num_usuarios
                        ,"source/docs/usuarios.txt");
    //Cargar datos de paises
    leerArrglosPaises(ARRcodigoPaises,ARRpaisesPaises,num_paises,
                    "source/docs/paises.txt");
    //Cargar comentarios
    leerComentarios(ARRfechaComentario, ARRlikesComentario,
                    ARRcomentarioComentario,ARRpaisComentario,
                    ARRcodigoComentario,num_comentarios,
                    "source/docs/comentarios.txt");
    //Actualizar los catos
    actualizarDatos(ARRpaisUsuarios,ARRcodigoUsuarios,
                    ARRseguidoresUsuarios,ARRnombreUsuario,
                    ARRpublicoUsuario,num_usuarios,
                    ARRcodigoPaises,ARRpaisesPaises,num_paises,
                    ARRfechaComentario, ARRlikesComentario,
                    ARRcomentarioComentario,ARRpaisComentario,
                    ARRcodigoComentario,num_comentarios
                    ,ARRnombreComentario,ARRnombre_paisComentario);
    //Ordenar los datos
    ordenarDatos(ARRfechaComentario,ARRcodigoComentario,
                ARRpaisComentario,ARRcomentarioComentario,
                ARRlikesComentario,num_comentarios
                ,ARRnombreComentario,ARRnombre_paisComentario);
    //Emitir reporte
    amitirReporte(ARRfechaComentario,ARRcodigoComentario,
                ARRpaisComentario,ARRcomentarioComentario,
                ARRlikesComentario,num_comentarios,
                "source/docs/Reporte.txt",
                ARRnombreComentario,ARRnombre_paisComentario);
    return 0;
}