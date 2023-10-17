#include<iostream>
#include<iomanip>
using namespace std;
#include"../header/funciones.h"
int main(int argc, char** argv){
    //Solicitar al ususario el ano y el ciclo para el cual se emitira
    //el reporte
    int ano,ciclo;
    pedirDatos(ano,ciclo);
    //Emitimos el reporte
    emitirReporte("source/docs/Alumnos.txt","source/docs/Cursos.txt",
                "source/docs/Escalas.txt","source/docs/Matricula.txt",
                "source/docs/Reporte.txt",ano,ciclo);

    return 0;
}
