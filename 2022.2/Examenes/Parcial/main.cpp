//Author: Mako
#include <iostream>
#include <iomanip>
using namespace std;
#include "header/funciones.h"

int main(){
    //Variables
    int ddI,mmI,aaI,ddF,mmF,aaF;
    pedirDatos(ddI,mmI,aaI,ddF,mmF,aaF);
    emitirReporte(ddI,mmI,aaI,ddF,mmF,aaF,
                  "docs/Comentarios.txt","docs/TikToks.txt",
                  "docs/Paises.txt","docs/Usuarios.txt",
                  "docs/Reporte.txt");
    return 0;
}