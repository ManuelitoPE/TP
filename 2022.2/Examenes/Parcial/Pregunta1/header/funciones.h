#ifndef FUNCIONES_H
#define FUNCIONES_H

void pedirDatos(int& fechaI,int& fechaF);
void emitirReporte(const char* nomReporte,const char* nomComentarios,
                   const char* nomPaises,const char* nomTikToks,
                   const char* nomUsuarios,int fechaI,int fechaF);
void encabezado(ofstream& report,int fechaI,int fechaF);
void descomprimir(int& dd,int& mm,int& aa,int fecha);
void linea(ofstream& report,int n,char c);
int comprimir(int dd,int mm,int aa);
void procesoDeTiktoks(int fecha,int cant_repro,int cant_like_repro,
                      int& codigo,int& ident,ifstream& archComentarios,
                      ifstream& archUsuarios,ifstream& archPaises,
                      ofstream& report);
void subencabezado(ofstream& report,int fecha,int cont);
void imprimirString(ofstream& report,ifstream& arch,char deli,char aux);
void procesarAutor(int cod_aux,int ident_aux,int likes,
                   int& cant_seguidores,int& cant_seguidoresN,
                   ifstream& archPaises,ifstream& archUsuarios,
                   ofstream& report);
void buscarPais(int cod,ifstream& archPaises,ofstream& report);
void resumenTiktok(int cant_comentarios,int cant_seguidores,
                   int cant_seguidoresN,int likes_total,
                   int cant_repro,int cant_like_repro,
                   ofstream& report);
void mejorTiktok(ofstream& report,int fechaMejor,int codMejor,
                 int idenMejor,ifstream& arch);






#endif