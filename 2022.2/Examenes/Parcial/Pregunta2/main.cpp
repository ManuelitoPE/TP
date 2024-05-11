//Author: MAKO
#include <iostream>
#include <iomanip>
using namespace std;
#include "header/funciones.h"
#define MAX_TIKTOKS 1000
#define MAX_USUARIOS 10

int main(){
    //Variables
    int fechaI,fechaF,titoks=0,usuarios=0;
    int ARRfechas[MAX_TIKTOKS],ARRcantRepro[MAX_TIKTOKS],
        ARRcodPais[MAX_USUARIOS],ARRident[MAX_USUARIOS];
    char ARRpublico[MAX_USUARIOS];
    int ARRcantComentario[MAX_TIKTOKS]{},ARRlikesComentarios[MAX_TIKTOKS]{},
        ARRcantSeguiP[MAX_TIKTOKS]{};
    char ARRviral[MAX_TIKTOKS];
    double ARRratioComentario[MAX_TIKTOKS],ARRratioViral[MAX_TIKTOKS];
    pedirFecha(fechaI,fechaF);

    //Cargar Datos
    cargarTiktoks("docs/TikToks.txt",titoks,ARRfechas,
                  ARRratioViral,ARRcantRepro,fechaI,fechaF);
    cargarUsuarios("docs/Usuarios.txt",usuarios,ARRpublico,
                    ARRcodPais,ARRident);
    //Proceso
    procesoDeComentarios("docs/Comentarios.txt",ARRfechas,ARRcantComentario,
                         ARRlikesComentarios,ARRcantRepro,ARRratioComentario,
                         ARRratioViral,ARRviral,ARRcantSeguiP,ARRcodPais,
                         ARRident,ARRpublico,usuarios,titoks);
    //Ordenar arreglos
    ordenarReporte(titoks,ARRfechas,ARRcantComentario,ARRlikesComentarios,
                  ARRcantRepro,ARRratioComentario,ARRviral,ARRcantSeguiP);

    //Emitir Reporte
    emitirReporte("docs/Reporte.txt",titoks,ARRfechas,ARRcantComentario,ARRlikesComentarios,
                  ARRcantRepro,ARRratioComentario,ARRviral,ARRcantSeguiP,
                  fechaI,fechaF);
    return 0;
}