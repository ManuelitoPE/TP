//Author: MAKO
#ifndef FUNCIONES_H
#define FUNCIONES_H
#include<fstream>
//Leer los datos de libros
void lecturaDeLibros(int& num_libro,int* ARRcodigoLibro,
                    double* ARRprecioLibro,
                    const char* nomArch);
// Leer los datos de Autores
void lecturaDeAutores(int& num_autores,int* ARRcodigoAutores,
                    int* ARRcodigo_libroAutores,
                    double* ARRporcentajeAutores,const char* nomArch);
    // Solicitarle al usuario dos fechas en el formato dd/mm/aa
void datosUsuario(int& fechaI,int& fechaF);
int comprimirFecha(int dd,int mm,int aa);
    // De ventas, determinar por cada libro la cantidad total vendida
    // Determinar por cada autor y por cada uno de suslibros vendidos 
    // el monto que recibira por su vental
void actualizacionPorVentas(int fechaI,int fechaF,int num_libro,
                        int num_autores,int* ARRcodigoLibro, 
                        double* ARRprecioLibro,int* ARRcodigoAutores,
                        int* ARRcodigo_libroAutores,
                        double* ARRporcentajeAutores,
                        int* ARRcantidad,double* ARRrecaudado,
                        double* ARRautor_recibido,const char* nomArch);
int buscarLibro(int codigoLibro,int* ARRcodigoLibro,int num_libro);
    // Emitir reporte
void emitirReporte(int fechaI,int fechaF,int num_libro,
                int num_autores,int* ARRcodigoLibro, 
                double* ARRprecioLibro,int* ARRcodigoAutores,
                int* ARRcodigo_libroAutores,
                double* ARRporcentajeAutores,
                int* ARRcantidad,double* ARRrecaudado,
                double* ARRautor_recibido,const char* nomArch);
void encabezado(ofstream& arch,int fechaF,int fechaI);
void linea(ofstream& arch,int num,char signo);
void sub_encabezado(ofstream& arch,int ARRcodigoLibro,int ARRcantidad,
                    double ARRprecioLibro,double ARRrecaudado,int i);
void sub_encabezado_2(ofstream& arch);
void decomprimirFechas(int& dd,int& mm,int& aa,int fecha);
#endif