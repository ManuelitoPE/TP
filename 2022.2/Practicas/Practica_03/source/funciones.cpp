#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstring>
using namespace std;
#include"../header/funciones.h"
//Cargar datos de usuarios
void leerArreglosUsuarios(int* ARRpaisUsuarios,int* ARRcodigoUsuarios,
                        int* ARRseguidoresUsuarios,char** ARRnombreUsuario,
                        char* ARRpublicoUsuario,int& num_usuarios,
                        const char* nomArch){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"Error: se produjo un erro al abrir "<<nomArch<<endl;
        exit(1);
    }
    // Variables
    char c;
    while(true){
        arch>>ARRpaisUsuarios[num_usuarios]>>c>>ARRcodigoUsuarios[num_usuarios];
        arch>>ws;
        lecturaDeNombre(ARRnombreUsuario[num_usuarios],arch);
        arch>>ARRseguidoresUsuarios[num_usuarios]>>ARRpublicoUsuario[num_usuarios];
        if(arch.eof())break;
        num_usuarios++;
    }
}
void lecturaDeNombre(char* ARRnombreUsuario,ifstream& arch){
    int longitud;
    char buffer[20];
    arch.getline(buffer,20,' ');
    longitud=strlen(buffer);
    ARRnombreUsuario= new char[longitud+1];
    strcpy(ARRnombreUsuario,buffer);
}
    //Cargar datos de paises
void leerArrglosPaises(int* ARRcodigoPaises,char** ARRpaisesPaises,
                    int& num_paises,
                    const char* nomArch){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"Error: se produjo un erro al abrir "<<nomArch<<endl;
        exit(1);
    }
    // Variables
    while(true){
        arch>>ARRcodigoPaises[num_paises];
        arch>>ws;
        lecturaDeNombre(ARRpaisesPaises[num_paises],arch);
        if(arch.eof())break;
        num_paises++;
    }
}
    //Cargar comentarios
void leerComentarios(int* ARRfechaComentario,int* ARRlikesComentario,
                    char** ARRcomentarioComentario,int* ARRpaisComentario,
                    int* ARRcodigoComentario,int& num_comentarios,
                    const char* nomArch){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"Error: se produjo un erro al abrir "<<nomArch<<endl;
        exit(1);
    }
    int dd,mm,aa;
    char c;
    while(true){
        arch>>dd>>c>>mm>>c>>aa;
        ARRfechaComentario[num_comentarios]=convertir(aa,mm,dd);
        while(true){
            arch>>ARRpaisComentario[num_comentarios]>>c>>
                ARRcodigoComentario[num_comentarios];
            arch>>ws;
            lecturaDeNombre(ARRcomentarioComentario[num_comentarios]
                            ,arch);
            arch>>ARRlikesComentario[num_comentarios];
            if(arch.get()=='\n')break;
        }
        if(arch.eof())break;
        num_comentarios++;
    }                
}
int convertir(int aa,int mm,int dd){
    int fecha= aa*10000+mm*100+dd;
    //20201309
    return fecha;
}
    //Actualizar los catos
void actualizarDatos(int* ARRpaisUsuarios,int* ARRcodigoUsuarios,
                    int* ARRseguidoresUsuarios,char** ARRnombreUsuario,
                    char* ARRpublicoUsuario,int num_usuarios,
                    int* ARRcodigoPaises,char** ARRpaisesPaises,
                    int num_paises,int* ARRfechaComentario,int* ARRlikesComentario,
                    char** ARRcomentarioComentario,int* ARRpaisComentario,
                    int* ARRcodigoComentario,int num_comentarios,
                    char** ARRnombreComentario,
                    char** ARRnombre_paisComentario){
    //Poner los nombres de los usuarios y sus pauises
    int pos,pos1;
    for(int i=0;i<num_comentarios;i++){
        pos=buscarPos(ARRcodigoComentario[i],ARRcodigoUsuarios
                    ,num_usuarios);
        strcpy(ARRnombreComentario[i],ARRnombreUsuario[i]);
        pos1=buscarPos(ARRcodigoComentario[i],ARRcodigoPaises
                    ,num_paises);
        strcpy(ARRnombre_paisComentario[i],ARRpaisesPaises[i]);
    }
}
int buscarPos(int num,int* ARRcodigoUsuarios,int limit){
    int pos,i;
    for (i = 0; i < limit; i++){
        if(num==ARRcodigoUsuarios[i])break;
    }
    return i;
}
    //Ordenar los datos
void ordenarDatos(int* ARRfechaComentario,int* ARRcodigoComentario,
                int* ARRpaisComentario,char**ARRcomentarioComentario,
                int* ARRlikesComentario,int num_comentarios,
                char** ARRnombreComentario,
                    char** ARRnombre_paisComentario){

                    }
    //Emitir reporte
void amitirReporte(int* ARRfechaComentario,int* ARRcodigoComentario,
                int* ARRpaisComentario,char**ARRcomentarioComentario,
                int* ARRlikesComentario,int num_comentarios,
                const char* nomArch,char** ARRnombreComentario,
                char** ARRnombre_paisComentario){
    ofstream arch(nomArch,ios::out);
    if(not arch.is_open()){
        cout<<"Error: se produjo un erro al abrir "<<nomArch<<endl;
        exit(1);
    }
    for(int i=0; i<num_comentarios;i++){
        arch<<ARRfechaComentario[i]<<setw(4)<<" "<<
            ARRnombreComentario[i]<<setw(4)<<" "<<
            ARRnombre_paisComentario[i]<<setw(4)<<" "<<
            ARRcomentarioComentario[i]<<setw(4)<<" "<<
            ARRlikesComentario[i]<<endl;
    }
}