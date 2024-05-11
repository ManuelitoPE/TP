#ifndef FUNCIONES_H
#define FUNCIONES_H

void pedirFecha(int& fechaI,int& fechaF);
void cargarTiktoks(const char* nomTikToks,int& titoks,int* ARRfechas,
                   double* ARRratioViral,int* ARRcantRepro,int fechaI,
                   int fechaF);
int comprimir(int dd,int mm,int aa);
void cargarUsuarios(const char* nomUsuarios,int& usuarios,char* ARRpublico,
                    int* ARRcodPais,int* ARRident);
void procesoDeComentarios(const char* nomComentarios,int *ARRfechas,
                          int* ARRcantComentario,int* ARRlikesComentarios,
                          int* ARRcantRepro,double* ARRratioComentario,
                          double* ARRratioViral,char* ARRviral,int* ARRcantSeguiP,
                          int* ARRcodPais,int* ARRident,char* ARRpublico,int usuarios,
                          int titoks);
int buscar(int* arr,int busca,int n);
int buscarPersona(int *ARRcodPais,int* ARRident,int cod,int ident,
                  int usuarios);
void procesoRatioViral(int* ARRcantRepro,int* ARRlikesComentarios,
                       double* ARRratioComentario,int* ARRcantComentario,
                       double* ARRratioViral,char* ARRviral,int titoks);
void ordenarReporte(int titoks,int* ARRfechas,
                    int* ARRcantComentario,int* ARRlikesComentarios,
                    int* ARRcantRepro,double* ARRratioComentario,
                    char* ARRviral,int* ARRcantSeguiP);
void cambiarDouble(double& i,double& k);
void cambiarChar(char& i,char& k);
void cambiarInt(int& i,int& k);
void emitirReporte(const char* nomReporte,int titoks,int* ARRfechas,
                  int* ARRcantComentario,int* ARRlikesComentarios,
                  int* ARRcantRepro,double* ARRratioComentario,
                  char* ARRviral,int* ARRcantSeguiP,int fechaI,
                  int fechaF);
void descomprimir(int& dd,int& mm,int& aa,int fecha);
void encabezado(ofstream& report,int fechaI,int fechaF);
void linea(ofstream& report,int n,char c);
#endif