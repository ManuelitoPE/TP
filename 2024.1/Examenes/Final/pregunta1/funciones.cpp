#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "header/funciones.h"
#include "header/LibroNodo.h"

void lecturalibros(const char* nomLibros,
              struct LibroNodo *&listaLibro){
    ifstream arch(nomLibros,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomLibros<<endl;
        exit(1);
    }
    //Variables
    struct Libro libro{};
    while(true){
        arch.getline(libro.code,8,',');
        if(arch.eof())break;
        arch.getline(libro.titulo,80,',');
        arch.getline(libro.autor,40,',');
        arch>>libro.precio; arch.get();
        insertarNodo(listaLibro,libro);
    }
    struct LibroNodo *ptr=listaLibro;
    while(ptr){
        cout<<ptr->libro.autor<<" "<<ptr->libro.precio<<endl;
        ptr=ptr->siguiente;
    }
}
void insertarNodo(struct LibroNodo *&listaLibro,
                  struct Libro libro){
    struct LibroNodo *ptr=listaLibro,*anterior=nullptr,*nuevo;
    nuevo=new struct LibroNodo;
    nuevo->libro=libro;
    while(ptr){
        if(ptr->libro.precio>libro.precio)break;
        anterior=ptr;
        ptr=ptr->siguiente;
    }
    nuevo->siguiente=ptr;
    if(anterior)anterior->siguiente=nuevo;
    else listaLibro=nuevo;
}
