#include<iostream>
#include<iomanip>
using namespace std;
#include"../header/funciones.h"
#define MAX_SALAS 10
#define MAX_PELICULAS 20
#define MAX_FUNCIONES 100

int main(int argc, char** argv){
    //Arreglos para el reporte
    int codPeli[MAX_PELICULAS],T_ButacasDis[MAX_PELICULAS]{},
        cantFunciones[MAX_PELICULAS]{},T_ButacasVend[MAX_PELICULAS]{},
        T_ButacasOcu[MAX_PELICULAS]{};
    //Arreglos 
    int num_Butacas[MAX_SALAS], peliFunciones[MAX_FUNCIONES],
        num_Salas_Funciones[MAX_FUNCIONES],horafunciones[MAX_FUNCIONES];
    //Numero de datos
    int numPeliculas=0,numeroButa=0,num_funciones=0;
    double recaudacionP[MAX_PELICULAS]{};
    // Venta y ocupacion no necesitan un arreglo
    int fecha;
    // Pedir la fecha
    ingresoDeFecha(fecha);
    //Leer codigo de peliculas (misma cantidad del total recaudado)
    lecturaDePelicualas(numPeliculas,codPeli,fecha,
                        "source/docs/peliculas.txt");
    for(int i=0;i<numPeliculas;i++){
        cout<<codPeli[i]<<endl;
    }
    //Leemos los datos de funciones
    lecturaDeFunciones(num_funciones,peliFunciones,
                    num_Salas_Funciones,horafunciones
                    ,"source/docs/funciones.txt");
    //Leemos el numero de butacas por sala
    lecturaNumButacas(num_Butacas,numeroButa,
                    "source/docs/salas.txt");
    //Lectura de ventas
    lecturaVentas("source/docs/ventas_y_ocupacion.txt",
                codPeli,T_ButacasDis,cantFunciones,T_ButacasVend,
                T_ButacasOcu,recaudacionP,num_Butacas,peliFunciones,
                num_Salas_Funciones,horafunciones,numPeliculas,
                numeroButa,num_funciones,fecha);
    //Emitir el reporte
    emitirReporte("source/docs/reporte.txt",fecha,codPeli,
                T_ButacasDis,cantFunciones,T_ButacasVend,
                T_ButacasOcu,recaudacionP,numPeliculas);
    return 0;
}
