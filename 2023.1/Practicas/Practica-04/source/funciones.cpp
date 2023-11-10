//Author:MAKO
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstring>
using namespace std;
#include"../header/funciones.h"
#include"../header/Libros.h"
#include"../header/Solicitudes.h"
#include"../header/Usuarios.h"
#define MAX_LINEA 95    
void lecturaDeUsuarios(struct Usuarios *usuarios,int& num_Usuarios,
                    const char* nomArch){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"Error en abrir "<<nomArch<<endl;
        exit(1);
    }
    //variables
    int dni;
    char nombre_usuario[60];
    char categoria,c;
    double calificacion;
    while(true){
        arch>>dni;
        if(arch.eof())break;
        usuarios[num_Usuarios].dni=dni;
        arch.get();
        arch.getline(nombre_usuario,60,',');
        strcpy(usuarios[num_Usuarios].nombre,nombre_usuario);
        arch>>categoria>>c>>calificacion;
        arch.get();
        usuarios[num_Usuarios].categoria=categoria;
        usuarios[num_Usuarios].calificacion=calificacion;
        //Cantidad de 4 a alumno, 6 profesor y 2 por visitante
        creandoEspacioLibrosPrestados(categoria, usuarios[num_Usuarios].LibrosEntregados);
        num_Usuarios++;
    }
}
void creandoEspacioLibrosPrestados(char categoria, struct LibroPrestado *&libro){
    switch (categoria){
        case 'A':
        libro= new struct LibroPrestado[4]{};
        break;
        case 'D':
        libro= new struct LibroPrestado[6]{};
        break;
        case 'V':
        libro= new struct LibroPrestado[2]{};
        break;
    }
}
//Leemos los libros
void lecturaDeLibros(struct Libros *libros,int& num_Libros,
                    const char* nomArch){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"Error en abrir "<<nomArch<<endl;
        exit(1);
    }
    //variables
    char codigo[8];
    char nombre[60];
    char autor[40];
    int cantidad;
    double precio;
    while(true){
        arch.getline(codigo,10,',');
        if(arch.eof())break;
        strcpy(libros[num_Libros].codigo,codigo);
        arch.getline(nombre,60,',');
        strcpy(libros[num_Libros].nombre,nombre);
        arch.getline(autor,40,',');
        strcpy(libros[num_Libros].autor,autor);
        arch>>cantidad;
        arch.get();
        arch>>precio;
        arch.get();
        libros[num_Libros].cantidad=cantidad;
        libros[num_Libros].precio=precio;
        //Cantidad
        libros[num_Libros].UsuariosQueTieneUnEjemplar=new struct UsuarioConLibro[cantidad]{};
        num_Libros++;
    }
}
//Leemos las solicitudes
void lecturaDeSolicitudes(struct Solicitudes *solicitudes,
                    int& num_Solicitudes,
                    const char* nomArch){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"Error en abrir "<<nomArch<<endl;
        exit(1);
    }
    //variables
    int dni_solicitudes;
    char codigo_solicitudes[10];
    while(true){
        arch>>dni_solicitudes;
        if(arch.eof())break;
        solicitudes[num_Solicitudes].dni=dni_solicitudes;
        arch>>ws;
        arch.getline(codigo_solicitudes,10,'\n');
        strcpy(solicitudes[num_Solicitudes].codigo,codigo_solicitudes);
        num_Solicitudes++;
    }
}
void impresionDeDatos(struct Usuarios *usuarios,struct Libros *libros,
                struct Solicitudes *solicitudes,int num_Usuarios,
                int num_Libros,int num_Solicitudes,
                const char* nomArch){
    ofstream arch(nomArch,ios::out);
    if(not arch.is_open()){
        cout<<"Error en abrir "<<nomArch<<endl;
        exit(1);
    }
    linea(arch,'=');
    arch<<setw(50)<<right<<"IMPRESION DE DATOS"<<left<<endl;
    linea(arch,'=');
    impresionDatosUsuarios(arch,usuarios,num_Usuarios);
    linea(arch,'=');
    impresionDatosLibros(arch,libros,num_Libros);
    linea(arch,'=');
    impresionDatosSolicitudes(arch,solicitudes,num_Solicitudes);
    linea(arch,'=');
}
void linea(ofstream& arch, char signo){
    for(int i=0; i<MAX_LINEA; i++){
        arch<<signo;
    }
    arch<<endl;
}
void impresionDatosUsuarios(ofstream& arch,struct Usuarios *usuarios,
                            int num_Usuarios){
    arch<<"Datos del usuarios"<<endl;
    for(int i=0;i<num_Usuarios;i++){
        linea(arch,'=');
        arch<<setw(10)<<"DNI"<<setw(38)<<"NOMBRE"<<setw(15)<<"CATEGORIA"
        <<setw(15)<<"CALIFICACION"<<endl;
        arch<<setw(10)<<usuarios[i].dni
            <<setw(42)<<usuarios[i].nombre
            <<setw(14)<<usuarios[i].categoria
            <<setw(15)<<usuarios[i].calificacion
            <<endl;
        linea(arch,'-');
        arch<<right<<setw(50)<<"LIBROS PRESTADOS"<<left<<endl;
        linea(arch,'-');
        arch<<setw(10)<<"CODIGO"<<setw(15)<<"PRECIO"<<endl;
        for(int k=0;k<usuarios[i].cant_prestado;k++){
            arch<<setw(10)<<usuarios[i].LibrosEntregados[k].codigo
                <<setw(42)<<usuarios[i].LibrosEntregados[k].precio
                <<endl;
        }
    } 
}
void impresionDatosLibros(ofstream& arch,struct Libros *libros,
                            int num_Usuarios){
    arch<<"Datos de los libros"<<endl;
    for(int i=0;i<num_Usuarios;i++){
        linea(arch,'=');
        arch<<setw(10)<<"CODIGO"<<setw(32)<<"NOMBRE"<<setw(28)<<"AUTOR"
            <<setw(15)<<"CANTIDAD"<<setw(10)<<"PRECIO"<<endl;
        arch<<setw(10)<<libros[i].codigo
            <<setw(32)<<libros[i].nombre
            <<setw(31)<<libros[i].autor
            <<setw(13)<<libros[i].cantidad
            <<libros[i].precio
            <<endl;
        linea(arch,'-');
        arch<<right<<setw(50)<<"USUARIOS CON LIBRO"<<left<<endl;
        linea(arch,'-');
        arch<<setw(12)<<"DNI"<<setw(15)<<"CATEGORIA"
            <<setw(10)<<"CALIFICACION"<<endl;
        for(int k=0;k<libros[i].cant_prestado;k++){
            arch<<setw(16)<<libros[i].UsuariosQueTieneUnEjemplar[k].dni
                <<setw(15)<<libros[i].UsuariosQueTieneUnEjemplar[k].categoria
                <<setw(10)<<libros[i].UsuariosQueTieneUnEjemplar[k].calificacion_usuario
                <<endl;
        }
    } 
}
void impresionDatosSolicitudes(ofstream& arch,struct Solicitudes *solicitudes,
                            int num_Usuarios){
    arch<<"Datos de las Solicitudes"<<endl;
    linea(arch,'-');
    arch<<setw(10)<<"DNI"<<setw(38)<<"CODIGO"<<endl;
    for(int i=0;i<num_Usuarios;i++){
        arch<<setw(10)<<solicitudes[i].dni
            <<setw(42)<<solicitudes[i].codigo
            <<endl;
    } 
}
void ordenandoSegunPolitica(struct Usuarios *usuarios,
                struct Solicitudes *solicitudes,int num_Usuarios,
                int num_Solicitudes){
    //Ordenamos primero alumnos, docentes y visitantes
    //despues mayor calificacion
    for(int i=0;i<num_Solicitudes-1;i++){
        for(int k=i+1;k<num_Solicitudes;k++){
            if(politica(solicitudes[i].dni,solicitudes[k].dni,
                        usuarios,num_Usuarios)){
                cambiarStructura(solicitudes[i],solicitudes[k]);
            }
        }
    }
}
bool politica(int dniA,int dniB, struct Usuarios *usuarios,
            int num_Usuarios){
    int posUsuarioA,posUsuarioB;
    bool valor;
    //Buscamos la posicion
    posUsuarioA=BuscarUsuario(usuarios,num_Usuarios,dniA);
    posUsuarioB=BuscarUsuario(usuarios,num_Usuarios,dniB);

    valor=(usuarios[posUsuarioA].categoria-usuarios[posUsuarioB].categoria)>0 
            or (usuarios[posUsuarioA].categoria-usuarios[posUsuarioB].categoria)==0
            and usuarios[posUsuarioA].calificacion<usuarios[posUsuarioB].calificacion;
    return valor;
}
int BuscarUsuario(struct Usuarios *usuarios,int num_Usuarios,int dni){
    int i;
    for(i=0;i<num_Usuarios;i++){
        if(usuarios[i].dni==dni)break;
    }
    return i;
}
void cambiarStructura(struct Solicitudes &solicitudesA,
                    struct Solicitudes &solicitudesB){
    struct Solicitudes aux;
    aux=solicitudesA;
    solicitudesA=solicitudesB;
    solicitudesB=aux;
}
void atendiendoPedidos(struct Usuarios *usuarios,struct Libros *libros,
                struct Solicitudes *solicitudes,int num_Usuarios,
                int num_Libros,int num_Solicitudes){
    int posUsuario, posLibro,cantidad_usuario,cant_libro;
    char codigo[8];
    double precio;
    for(int i=0;i<num_Solicitudes;i++){
        //Leemos la primera solicitud 
        posUsuario=BuscarUsuario(usuarios,num_Usuarios,solicitudes[i].dni);
        posLibro=BuscarLibro(libros,num_Libros,solicitudes[i].codigo);
        if(verificacion(usuarios[posUsuario].cant_prestado,
                        usuarios[posUsuario].categoria,
                        libros[posLibro].cant_prestado,
                        libros[posLibro].cantidad)){
            //COMPLETAMOS LA ESTRUCUTRA DE LIBRO PRESTADO
            //CANTIDAD DE LO PRESTADO
            cantidad_usuario=usuarios[posUsuario].cant_prestado;
            //ASIGNAMOS EL CODIGO A UNA VARIABLE
            strcpy(codigo,solicitudes[i].codigo);
            //ASIGNAMOS EL PRECIO A UNA VARIABLE
            precio=libros[posLibro].precio;
            strcpy(usuarios[posUsuario].LibrosEntregados[cantidad_usuario].codigo,codigo);
            usuarios[posUsuario].LibrosEntregados[cantidad_usuario].precio=precio;
            usuarios[posUsuario].cant_prestado++;
            //COMPLETAMOS LA ESTRUCTURA DE USUARIO CON LIBRO
            cant_libro=libros[posLibro].cant_prestado;
            libros[posLibro].UsuariosQueTieneUnEjemplar[cant_libro].calificacion_usuario=usuarios[posUsuario].calificacion;
            libros[posLibro].UsuariosQueTieneUnEjemplar[cant_libro].categoria=usuarios[posUsuario].categoria;
            libros[posLibro].UsuariosQueTieneUnEjemplar[cant_libro].dni=usuarios[posUsuario].dni;
            libros[posLibro].cant_prestado++;
        }
    }
}
int BuscarLibro(struct Libros *libros,int num_Libros,
                char *codigo){
    int i;
    for(i=0;i<num_Libros;i++){
        if(strcmp(libros[i].codigo,codigo)==0)break;
    }
    return i;
}

bool verificacion(int cantPrestado_Usuaio,char categoria,
                int cantPrestado_Libro,int cantidad){
    bool verification;
    switch (categoria){
        case 'A':
        verification=(cantPrestado_Usuaio<4 and cantPrestado_Libro<cantidad);
        break;
        case 'D':
        verification=cantPrestado_Usuaio<6 and cantPrestado_Libro<cantidad;
        break;
        case 'V':
        verification=cantPrestado_Usuaio<2 and cantPrestado_Libro<cantidad;
        break;
    }
    return verification;
}