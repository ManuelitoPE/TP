//Author:MAKO
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstring>
using namespace std;
#include "../header/funciones.h"
#include "../header/Libro.h"
#include "../header/Usuario.h"
#define NO_ENCONTRADO -1
#define MAX_LINEA 125
//CREAR ARCHIVOS LIBROS
void crearArchLibros(const char* nomArch,const char* nomArchBin){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"Error al abrir "<<nomArch<<endl;
        exit(1);
    }
    ofstream archBin(nomArchBin, ios::out|ios::binary);
    if(not archBin.is_open()){
        cout<<"Error al abrir "<<nomArchBin<<endl;
        exit(1);
    }
    //Variables
    char codigo[8],titulo[40], nombre[60],c;
    int cantidad;
    double precio;
    struct Libro libro;
    while(true){
        arch.getline(codigo,10,',');
        if(arch.eof())break;
        arch.getline(titulo,40,',');
        arch.getline(nombre,60,',');
        arch>>cantidad>>c>>precio;
        strcpy(libro.autor,nombre);
        strcpy(libro.codigo,codigo);
        strcpy(libro.titulo,titulo);
        libro.cantidad=cantidad;
        libro.precio=precio;
        libro.cantidadUsuarios=0;
        leerUsuarios(libro.usuarios,arch,libro.cantidadUsuarios);
        archBin.write(reinterpret_cast<const char*>(&libro),
                    sizeof(struct Libro));
    }
}
void leerUsuarios(struct UsuarioConElLibro *usuarios,ifstream& arch,int& cant){
    //Variables
    int aa,mm,dd;
    char c;
    while(arch.get()!='\n'){
        arch>>usuarios[cant].dni>>c>>dd>>c>>mm>>c>>aa;
        usuarios[cant].fechaDeDevolucion=aa*10000+mm*100+dd;
        cant++;
    }
}
void pruebaLibrosBin(const char* nomArchBin,const char* nomArch){
    ofstream arch(nomArch,ios::out);
    if(not arch.is_open()){
        cout<<"Error al abrir "<<nomArch<<endl;
        exit(1);
    }
    ifstream archBin(nomArchBin, ios::in|ios::binary);
    if(not archBin.is_open()){
        cout<<"Error al abrir "<<nomArchBin<<endl;
        exit(1);
    }
    archBin.seekg(0,ios::beg);
    arch.precision(2);
    arch<<fixed;
    struct Libro libro;
    encabezado(arch);
    while(true){
        archBin.read(reinterpret_cast<char*>(&libro),
                    sizeof(struct Libro));
        if(archBin.eof())break;
        arch<<left<<setw(10)<<libro.codigo
            <<setw(35)<<libro.titulo
            <<setw(35)<<libro.autor
            <<setw(35)<<libro.cantidad
            <<setw(35)<<libro.precio<<endl;
        subEncabezado(arch);
        for(int i=0; i<libro.cantidadUsuarios;i++){
            arch<<setw(15)<<libro.usuarios[i].fechaDeDevolucion
                <<setw(15)<<libro.usuarios[i].dni<<endl;
        }
        linea(arch,'=');
    }
}
void encabezado(ofstream& arch){
    arch<<setw(50)<<"Prueba de Libro.bin"<<endl;
    linea(arch,'=');
    arch<<left<<setw(10)<<"CODIGO"
            <<setw(35)<<"TITULO"
            <<setw(35)<<"AUTOR"
            <<setw(35)<<"CANTIDAD"
            <<setw(35)<<"PRECIO"<<endl;
    linea(arch,'-');
}
void linea(ofstream& arch, char signo){
    for(int i=0;i<MAX_LINEA;i++){
        arch<<signo;
    }
    arch<<endl;
}
void subEncabezado(ofstream& arch){
    linea(arch,'-');
    arch<<setw(50)<<"USUARIOS CON LIBRO"<<endl;
    linea(arch,'=');
    arch<<left<<setw(15)<<"FECHA"
            <<setw(10)<<"DNI"<<endl;
    linea(arch,'-');
}
//CREAR ARCHIVOS USUARIOS
void crearArchUsuarios(const char* nomArch,const char* nomArchBin){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"Error al abrir "<<nomArch<<endl;
        exit(1);
    }
    ofstream archBin(nomArchBin, ios::out|ios::binary);
    if(not archBin.is_open()){
        cout<<"Error al abrir "<<nomArchBin<<endl;
        exit(1);
    }
    //Variables 
    struct Usuario usuario;
    int dni;
    char nombre[60];
    char categoria,c;
    double calificacion;
    while(true){
        arch>>dni;
        if(arch.eof())break;
        arch.get();
        arch.getline(nombre,60,',');
        arch>>categoria>>c>>calificacion>>c;
        usuario.dni=dni;
        strcpy(usuario.nombre,nombre);
        usuario.categoria=categoria;
        usuario.calificacion=calificacion;
        usuario.cantidadDeLibros=0;
        leerLibros(usuario.libros,arch,usuario.cantidadDeLibros);
        archBin.write(reinterpret_cast<const char*>(&usuario),
                    sizeof(struct Usuario));
    }
    
}
void leerLibros(struct LibrosEnSuPoder *libros,ifstream& arch,int& cant){
    while(true){
        arch>>libros[cant].codigo;
        cant++;
        if(arch.get()=='\n')break;
    }
}
void pruebaUsuariosBin(const char* nomArchBin,const char* nomArch){
    ofstream arch(nomArch,ios::out);
    if(not arch.is_open()){
        cout<<"Error al abrir "<<nomArch<<endl;
        exit(1);
    }
    ifstream archBin(nomArchBin, ios::in|ios::binary);
    if(not archBin.is_open()){
        cout<<"Error al abrir "<<nomArchBin<<endl;
        exit(1);
    }
    int i=0;
    archBin.seekg(0,ios::beg);
    arch.precision(2);
    arch<<fixed;
    struct Usuario usuario;
    encabezado_1(arch);
    while(true){
        archBin.read(reinterpret_cast<char*>(&usuario),
                    sizeof(struct Usuario));
        if(archBin.eof())break;
        arch<<left<<setw(10)<<usuario.dni
            <<setw(35)<<usuario.nombre<<" "<<i
            <<setw(35)<<usuario.categoria
            <<setw(35)<<usuario.calificacion<<endl;
        subEncabezado_1(arch);
        for(int i=0; i<usuario.cantidadDeLibros;i++){
            arch<<setw(15)<<usuario.libros[i].codigo<<endl;
        }
        linea(arch,'=');
        i++;
    }
}
void encabezado_1(ofstream& arch){
    arch<<setw(50)<<"Prueba de Usuario.bin"<<endl;
    linea(arch,'=');
    arch<<left<<setw(10)<<"DNI"
            <<setw(35)<<"NOMBRE"
            <<setw(10)<<"CATEGORIA"
            <<setw(10)<<"CALIFICACION"<<endl;
    linea(arch,'-');
}
void subEncabezado_1(ofstream& arch){
    linea(arch,'-');
    arch<<setw(50)<<"LIBRO EN SU PODER"<<endl;
    linea(arch,'=');
    arch<<left<<setw(15)<<"CODIGO"<<endl;
    linea(arch,'-');
}
void modificar(const char* nomArch,const char* nomArchLibros,
                const char* nomArchUsuarios){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"Error al abrir el archivo "<<nomArch<<endl;
        exit(1);
    }
    fstream archLibros(nomArchLibros, ios::in|ios::out|ios::binary);
    if(not archLibros.is_open()){
        cout<<"Error al abrir el archivo "<<nomArchLibros<<endl;
        exit(1);
    }
    fstream archUsuarios(nomArchUsuarios, ios::in|ios::out|ios::binary);
    if(not archUsuarios.is_open()){
        cout<<"Error al abrir el archivo "<<nomArchUsuarios<<endl;
        exit(1);
    }
    //Variables
    int aa,mm,dd,fecha,dni;
    char c,codigo[8];
    arch>>dd>>c>>mm>>c>>aa;
    fecha=aa*10000+mm*100+dd;
    while(true){
        arch>>dni;
        if(arch.eof())break;
        arch>>codigo;
        cout<<codigo<<" "<<dni<<endl;
        actualizarArchivos(codigo,dni,fecha,archLibros,archUsuarios);
    }
}
void actualizarArchivos(char* codigo,int dni,int fecha,
                        fstream& archLibros,fstream& archUsuarios){
    //VARIABLES 
    int sizeLibro,sizeUsuario,cantStructsLibro,cantStructsUsuario;
    int posUsuario,posLibro;
    bool castigo=false;
    struct Usuario usuario{};
    struct Libro libro{};
    //Tamanos de las estructuras
    sizeLibro=sizeof(struct Libro);
    sizeUsuario=sizeof(struct Usuario);
    //Cantidad de estructuras
    cantStructsLibro=cantidadEstructuras(archLibros,sizeLibro);
    cantStructsUsuario=cantidadEstructuras(archUsuarios,sizeUsuario);
    //BUSCAMOS A LOS USUARIOS
    posUsuario=buscarUsuario(cantStructsUsuario,archUsuarios,dni);
    posLibro=buscarLibro(cantStructsLibro,archLibros,codigo);
    cout<<posLibro<<" "<<posUsuario<<endl;
    if(posUsuario!=NO_ENCONTRADO and posLibro!=NO_ENCONTRADO){
        //Colocamos el puntero al inicion de ;a estructura
        archLibros.seekg(posLibro*sizeLibro,ios::beg);
        archUsuarios.seekg(posUsuario*sizeUsuario,ios::beg);
        //Leemos la estructura
        archUsuarios.read(reinterpret_cast<char*>(&usuario),
                        sizeof(struct Usuario));
        archLibros.read(reinterpret_cast<char*>(&libro),
                        sizeof(struct Libro));
        //Le quitamos al usuarios de la realcion y verificamos 
        // el castigo
        actualizacionLibros(fecha,dni,libro.usuarios,castigo,libro.cantidadUsuarios);
        //Le quitamos el libro del alumnos y 
        actualizacionUsuarios(codigo,usuario.libros,usuario.cantidadDeLibros);
        if(castigo)castigoUsuario(usuario);
        //Colocamos el puntero al inicion de ;a estructura
        archLibros.seekg(posLibro*sizeLibro,ios::beg);
        archUsuarios.seekg(posUsuario*sizeUsuario,ios::beg);
        //Leemos los cambios
        archLibros.write(reinterpret_cast<const char*>(&libro),
                        sizeLibro);
        archUsuarios.write(reinterpret_cast<const char*>(&usuario),
                        sizeUsuario);
        //Actualizamos
        archLibros.flush();
        archUsuarios.flush();
    }
}
int cantidadEstructuras(fstream& arch,int Structsize){
    int archSize, cantStructs;
    //Coloco el puntero en el final
    arch.seekg(0,ios::end);
    //Tamano de bytes
    archSize=arch.tellg();
    cantStructs=archSize/Structsize;
    //Devuelvo el puntero al inicio 
    arch.seekg(0,ios::beg);
    //Retornamos la cantidad de estructuras
    return cantStructs;
}
int buscarUsuario(int cantStructsUsuario,fstream& archUsuarios,int dni){
    //Variables
    struct Usuario usuario;
    archUsuarios.seekg(0,ios::beg);
    for(int i=0;i<cantStructsUsuario;i++){
        archUsuarios.read(reinterpret_cast<char*>(&usuario),sizeof(struct Usuario));
        if(usuario.dni==dni)return i;
    }
    return NO_ENCONTRADO;
}
int buscarLibro(int cantStructsLibro,fstream& archLibros,char* codigo){
    //Variables
    struct Libro libro;
    archLibros.seekg(0,ios::beg);
    for(int i=0;i<cantStructsLibro;i++){
        archLibros.read(reinterpret_cast<char*>(&libro),sizeof(struct Libro));
        if(strcmp(libro.codigo,codigo)==0)return i;
    }
    return NO_ENCONTRADO;
}
void actualizacionLibros(int fecha,int dni,struct UsuarioConElLibro *usuario,
                        bool& castigo,int& cant){
    for(int i=0; i<cant;i++){
        if(dni==usuario[i].dni){
            castigo=fecha>usuario[i].fechaDeDevolucion;
            usuario[i]=usuario[cant-1];
            cant--;
            break;
        }
    }
}
//Le quitamos el libro del alumnos y 
void actualizacionUsuarios(char* codigo,struct LibrosEnSuPoder *libro,int& cant){
    for(int i=0;i<cant;i++){
        if(strcmp(libro[i].codigo,codigo)==0){
            strcpy(libro[i].codigo,libro[cant-1].codigo);
            cant--;
            break;
        }
    }
}
void castigoUsuario(struct Usuario& usuario){
    switch (usuario.categoria)
    {
    case 'A':
        usuario.calificacion-=(usuario.calificacion*10)/100;
        break;
    case 'D':
        usuario.calificacion-=(usuario.calificacion*20)/100;
        break;
    case 'V':
        usuario.calificacion-=(usuario.calificacion*15)/100;
        break;
    }
}