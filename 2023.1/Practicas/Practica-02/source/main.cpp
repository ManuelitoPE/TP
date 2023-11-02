//Author: MAKO
#include<iostream>
#include<iomanip>
using namespace std;
#include"../header/funciones.h"
#define MAX_LIBRO 100
#define MAX_AUTORES 400
int main(int argc, char** argv){
    //Variables
    int fechaI,fechaF;
    // Numeros de datos
    int num_libro=0,num_autores=0;
    // ARREGLOS DE LIBROS
    int ARRcodigoLibro[MAX_LIBRO];
    double ARRprecioLibro[MAX_LIBRO];
    // ARREGLOS DE AUTORES
    int ARRcodigoAutores[MAX_AUTORES],ARRcodigo_libroAutores[MAX_AUTORES];
    double ARRporcentajeAutores[MAX_AUTORES];
    //ARREGLOS PARA EL REPORTE
    int ARRcantidad[MAX_LIBRO]{};
    double ARRrecaudado[MAX_LIBRO]{};
    double ARRautor_recibido[MAX_AUTORES]{};
    //Leer los datos de libros
    lecturaDeLibros(num_libro,ARRcodigoLibro,ARRprecioLibro,
                    "source/docs/Libros.txt");
    // Leer los datos de Autores
    lecturaDeAutores(num_autores,ARRcodigoAutores,ARRcodigo_libroAutores,
                    ARRporcentajeAutores,"source/docs/Autores.txt");
    // Solicitarle al usuario dos fechas en el formato dd/mm/aa
    datosUsuario(fechaI,fechaF);
    // De ventas, determinar por cada libro la cantidad total vendida
    // Determinar por cada autor y por cada uno de suslibros vendidos 
    // el monto que recibira por su vental
    actualizacionPorVentas(fechaI,fechaF,num_libro,num_autores,
                        ARRcodigoLibro, ARRprecioLibro,ARRcodigoAutores,
                        ARRcodigo_libroAutores,ARRporcentajeAutores,
                        ARRcantidad,ARRrecaudado,
                        ARRautor_recibido,"source/docs/Ventas.txt");
    // Emitir reporte
    emitirReporte(fechaI,fechaF,num_libro,num_autores,
                ARRcodigoLibro, ARRprecioLibro,ARRcodigoAutores,
                ARRcodigo_libroAutores,ARRporcentajeAutores,
                ARRcantidad,ARRrecaudado,
                ARRautor_recibido,"source/docs/Reporte.txt");
    return 0;
}