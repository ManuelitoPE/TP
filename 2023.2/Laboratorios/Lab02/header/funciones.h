//Author: MAKO
#ifndef FUNCIONES_H
#define FUNCIONES_H
void emitirReporte(const char* nomArch,
                   const char* Reporte);
void encabezado(ofstream& report);
void linea(ofstream& report,int num ,char c);
void lectura_impresion(ifstream& arch,ofstream& report,int& dni,
                       char& sexo,char& compania,int& dd,int& mm,
                       int& aa,int& tiempoTotal);
void impresionNombre(ifstream& arch,ofstream& report);
void impresionSexo(ofstream& report,char sexo);
void impresionCategoria(ofstream& report,char aa);
void impresionCompania(ofstream& report,char compania);
void lectura_impresionCanales(ifstream& arch,ofstream& report,
                              int& tiempoTotal);
void calculoImpresionDuracion(ofstream& report,int hhI,int minI,int ssI,int hhF,
                         int minF,int ssF,int& tiempoTotal);
int convertirSeg(int hh,int min,int ss);
void convertirHMS(int& hh,int& min,int& ss,int tiempoTotal);
void condicionales(int& cantMeAdu,int& tiempoMeAdu,int& cantMu,
                   int aa,char sexo,int tiempoTotal);
void calculoEstadisticas(int& tiempoPromedio,double& porcentajeMu,
                         int televidentes,int cantMeAdu,
                         int tiempoMeAdu,int cantMu);
void estadisticas(int televidentes,int tiempoPromedio,
                  double porcentajeMu,ofstream& report);
#endif