// Author: MAKO
#ifndef FUNCIONES_H
#define FUNCIONES_H
void datos(int& distritoA,int& distritoB,int& hh,int& min,
           int& ss,int& hhD,int& minD,int& ssD,char& alimentos);
void emitReporte(const char* nomArch,const char* nomReport,
                 int& distritoA,int& distritoB,int& hh,int& min,
                 int& ss,int& hhD,int& minD,int& ssD,
                 char& alimentos);
void linea(ofstream& report,int num,char c);
void encabezado(int& distritoA,int& distritoB,int& hh,int& min,
           int& ss,int& hhD,int& minD,int& ssD,char& alimentos,
           ofstream& report);
void determinarAlimentos(char food,ofstream& report);
void lecturaImpresionDatos(ifstream& arch,ofstream& report,int hh,
                      int min,int ss,int hhD,int minD,
                      int ssD,char alimentos,int aux_distrito,
                      int& contPeliculas);
void impresionNombre(ifstream& arch,ofstream& report);
void encabezado2(ofstream& report);

bool condicionales(int hh,int min,int ss,int hhD,int minD,int ssD,
                   char alimentos,char aux_alimento,int hhI,
                   int minI,int ssI,int hhF,int minF,int ssF);
int convertirSeg(int hh,int min,int ss);
#endif