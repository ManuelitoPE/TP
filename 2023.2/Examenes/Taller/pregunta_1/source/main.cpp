#include<iostream>
#include<iomanip>
using namespace std;
#include"../header/funciones.h"
int main(int argc, char** argv){
    // Variables
    int fecha;
    // Pedimos la fecha
    pedirFecha(fecha);
    // Ahora emitimos el reporte
    emitirReporte("source/docs/funciones.txt","source/docs/peliculas.txt","source/docs/reporte.txt"
                ,"source/docs/salas.txt","source/docs/ventas_y_ocupacion.txt",fecha); 
    return 0;
}
