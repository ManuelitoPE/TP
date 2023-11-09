#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstring>
using namespace std;
#include"../header/funciones.h"
#include"../header/LibroPrestado.h"
#include"../header/Libros.h"
#include"../header/Solicitudes.h"
#include"../header/UsuarioConLibro.h"
#include"../header/Usuarios.h"
void lecturaDeDatos(struct Usuarios *usuarios,
                    struct Libros *libros,
                    struct Solicitudes *solicitudes,
                    int& numLibros,int& numUsuarios,
                    int& numSolicitudes,
                    const char* nomLibros,
                    const char* nomUsuarios,
                    const char* nomSolicitudes){
    ifstream archLibros(nomLibros,ios::in);
    if(not archLibros.is_open()){
        cout<<"Error en abrir "<<nomLibros<<endl;
        exit(1);
    }
    ifstream archUsuarios(nomUsuarios,ios::in);
    if(not archUsuarios.is_open()){
        cout<<"Error en abrir "<<nomUsuarios<<endl;
        exit(1);
    }
    ifstream archSolicitudes(nomSolicitudes,ios::in);
    if(not archSolicitudes.is_open()){
        cout<<"Error en abrir "<<nomSolicitudes<<endl;
        exit(1);
    }
    //Leemos libros ahora
    //variables
    char codigo[8];
    char nombre[60];
    char autor[40];
    int cantidad;
    double precio;
    while(true){
        archLibros.getline(codigo,10,',');
        if(archLibros.eof())break;
        strcpy(libros[numLibros].codigo,codigo);
        archLibros.getline(nombre,60,',');
        strcpy(libros[numLibros].nombre,nombre);
        archLibros.getline(autor,40,',');
        strcpy(libros[numLibros].autor,autor);
        archLibros>>cantidad;
        archLibros.get();
        archLibros>>precio;
        archLibros.get();
        libros[numLibros].cantidad=cantidad;
        libros[numLibros].precio=precio;
        numLibros++;
    }
    //Leemos Usuarios ahora
    //variables
    int dni;
    char nombre_usuario[60];
    char categoria,c;
    double calificacion;
    while(true){
        archUsuarios>>dni;
        if(archUsuarios.eof())break;
        usuarios[numUsuarios].dni=dni;
        archUsuarios.get();
        archUsuarios.getline(nombre_usuario,60,',');
        strcpy(usuarios[numUsuarios].nombre,nombre_usuario);
        archUsuarios>>categoria>>c>>calificacion;
        archUsuarios.get();
        usuarios[numUsuarios].categoria=categoria;
        usuarios[numUsuarios].calificacion=calificacion;
        numUsuarios++;
    }
    //Leemos las Solicitudes ahora
    //variables
    int dni_solicitudes;
    char codigo_solicitudes[10];
    while(true){
        archSolicitudes>>dni_solicitudes;
        if(archSolicitudes.eof())break;
        solicitudes[numSolicitudes].dni=dni_solicitudes;
        archSolicitudes>>ws;
        archSolicitudes.getline(codigo_solicitudes,10);
        strcpy(solicitudes[numSolicitudes].codigo,codigo_solicitudes);
        archSolicitudes.get();
        numSolicitudes++;
    }
    for(int i=0;i<numSolicitudes;i++){
        cout<<solicitudes[i].codigo<<setw(3)<<" "
            <<solicitudes[i].dni<<setw(3)<<" "
            <<endl;
    }
}