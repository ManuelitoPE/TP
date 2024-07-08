// Author: MAKO
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "header/funciones.h"
#include "header/Nodo.h"

void crearLista(const char* nomdatos,struct Nodo*& lista){
    ifstream arch(nomdatos,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomdatos<<endl;
        exit(1);
    }
    //Variables
    int dato;
    while(true){
        arch>>dato;
        if(arch.eof())break;
        insertarNodo(lista,dato);
    }
}
void insertarNodo(struct Nodo *&lista,int dato){
    struct Nodo *ptr=lista, *anterior=nullptr, *nuevo;
    nuevo= new struct Nodo;
    nuevo->dato=dato;
    while(ptr){
        if(ptr->dato>dato)break;
        anterior=ptr;
        ptr=ptr->siguiente;
    }
    nuevo->siguiente=ptr;
    if(anterior)anterior->siguiente=nuevo;
    else lista=nuevo;   
}
void eliminarDato(struct Nodo *&lista,int num){
    struct Nodo *ptr=lista,*anterior=nullptr;
    while(ptr){
        if(ptr->dato==num)break;
        anterior=ptr;
        ptr=ptr->siguiente;
    }
    if(anterior)anterior->siguiente=ptr->siguiente;
    else lista=ptr->siguiente;
}
void mostrarLista(const char* nomReporte, struct Nodo* lista,
                  int cantNodos){
    ofstream report(nomReporte,ios::out);
    if(not report.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomReporte<<endl;
        exit(1);
    }
    //Variable
    struct Nodo *ptr=lista; int i=1;
    while(ptr){
        report<<i<<") "<<ptr->dato<<endl;
        ptr=ptr->siguiente; i++;
    }
    report<<"La lista tiene "<<cantNodos<<" nodos."<<endl;
}
int contarNodos(struct Nodo *lista){
    //Variables
    int contador=0;
    struct Nodo *ptr=lista;
    while(ptr){
        ptr= ptr->siguiente;
        contador++;
    }   
    return contador;
}