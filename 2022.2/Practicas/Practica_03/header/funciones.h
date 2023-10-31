#ifndef FUNCIONES_H
#define FUNCIONES_H
#include<fstream>
//Cargar datos de usuarios
void leerArreglosUsuarios(int* ARRpaisUsuarios,int* ARRcodigoUsuarios,
                        int* ARRseguidoresUsuarios,char** ARRnombreUsuario,
                        char* ARRpublicoUsuario,int& num_usuarios,
                        const char* nomArch);
void lecturaDeNombre(char* ARRnombreUsuario,ifstream& nomArch);
    //Cargar datos de paises
void leerArrglosPaises(int* ARRcodigoPaises,char** ARRpaisesPaises,
                    int& num_paises,
                    const char* nomArch);
    //Cargar comentarios
void leerComentarios(int* ARRfechaComentario,int* ARRlikesComentario,
                    char** ARRcomentarioComentario,int* ARRpaisComentario,
                    int* ARRcodigoComentario,int& num_comentarios,
                    const char* nomArch);
int convertir(int aa,int mm,int dd);
    //Actualizar los catos
void actualizarDatos(int* ARRpaisUsuarios,int* ARRcodigoUsuarios,
                    int* ARRseguidoresUsuarios,char** ARRnombreUsuario,
                    char* ARRpublicoUsuario,int num_usuarios,
                    int* ARRcodigoPaises,char** ARRpaisesPaises,
                    int num_paises,int* ARRfechaComentario,int* ARRlikesComentario,
                    char** ARRcomentarioComentario,int* ARRpaisComentario,
                    int* ARRcodigoComentario,int num_comentarios,
                    char** ARRnombreComentario,
                    char** ARRnombre_paisComentario);
int buscarPos(int num,int* ARRcodigoUsuarios,int limit);
    //Ordenar los datos
void ordenarDatos(int* ARRfechaComentario,int* ARRcodigoComentario,
                int* ARRpaisComentario,char**ARRcomentarioComentario,
                int* ARRlikesComentario,int num_comentarios,
                char** ARRnombreComentario,
                char** ARRnombre_paisComentario);
    //Emitir reporte
void amitirReporte(int* ARRfechaComentario,int* ARRcodigoComentario,
                int* ARRpaisComentario,char**ARRcomentarioComentario,
                int* ARRlikesComentario,int num_comentarios,
                const char* nomArch
                ,char** ARRnombreComentario,
                char**ARRnombre_paisComentario);
#endif