//Author: Mako
#include <iostream>
#include <iomanip>
using namespace std;
#include "header/funciones.h"

int main(){
    //Variables
    int fechaI,fechaF;
    pedirDatos(fechaI,fechaF);
    emitirReporte("docs/Reporte.txt","docs/Comentarios.txt",
                  "docs/Paises.txt","docs/TikToks.txt",
                  "docs/Usuarios.txt",fechaI,fechaF);
    return 0;
}