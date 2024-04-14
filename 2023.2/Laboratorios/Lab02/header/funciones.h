//Author: MAKO
#ifndef FUNCIONES_H
#define FUNCIONES_H
void emitirReporte(const char* nomArch,
                   const char* Reporte);
void encabezado(ofstream& report);
void linea(ofstream& report,int num ,char c);
void lectura_impresion(ifstream& arch,ofstream& report,int& dni,
                       char& sexo,char& compania,int& dd,int& mm,
                       int& aa);
void impresionNombre(ifstream& arch,ofstream& report);
void impresionSexo(ofstream& report,char sexo);
void impresionCategoria(ofstream& report,char aa);
void impresionCompania(ofstream& report,char compania);
void lectura_impresionCanales(ifstream& arch,ofstream& report,
                              int& tiempoTotal);

#endif