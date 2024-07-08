//Author: MAKO
#ifndef FUNCIONES_H
#define FUNCIONES_H
void crearLista(const char* nomdatos,struct Nodo*& lista);
void insertarNodo(struct Nodo *&lista,int dato);
int contarNodos(struct Nodo *lista);
void mostrarLista(const char* nomReporte, struct Nodo* lista, 
                  int cantNodos);
void eliminarDato(struct Nodo *&lista,int num);
#endif