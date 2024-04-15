// Author: MAKO
#include <iostream>
#include <iomanip>
using namespace std;
#include "header/funciones.h"
int main(){
    //Variables
    int distritoA,distritoB,hh,min,ss,hhD,minD,ssD;
    char alimentos;
    datos(distritoA,distritoB,hh,min,ss,hhD,minD,ssD,
          alimentos);
    emitReporte("docs/CarteleraDeCines.txt",
                "docs/Reporte.txt",distritoA,distritoB,
                hh,min,ss,hhD,minD,ssD,alimentos);
}