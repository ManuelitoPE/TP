#ifndef FUNCIONES_H
#define FUNCIONES_H

void lecturalibros(const char* nomLibros,
              struct LibroNodo*& listaLibro);
void insertarNodo(struct LibroNodo *&listaLibro,
                  struct Libro libro);
#endif