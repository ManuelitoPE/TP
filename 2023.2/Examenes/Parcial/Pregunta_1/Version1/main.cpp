// Author: MAKO
#include <iostream>
#include <iomanip>
using namespace std;
#include "header/funciones.h"

int main(){
    //Variables
    int aa,ciclo;
    datosReporte(aa,ciclo);
    emitirReporte("docs/Alumnos.txt","docs/Cursos.txt",
                  "docs/Escalas.txt","docs/Matricula.txt",
                  "docs/Reporte.txt",aa,ciclo);
    return 0;
}