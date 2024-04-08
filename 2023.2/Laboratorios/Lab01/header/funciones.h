//Author: MAKO
#ifndef FUNCIONES_H
#define FUNCIONES_H
void emitirReporte();
void encabezado();
void linea(int n,char c);
void impresionSexoCategoria(char sexo, int anio);
void impresionHoraDuracion(int horaI,int minI,int segI,int horaF,
                        int minF,int segF);
int convertirSegundos(int hora,int min,int seg);
void convertirHMS(int& hora,int& min,int& seg,double duracion);
void lecturaCanales(int canal1,int canal2,int canal3);
void impresionCompania(char compania);
void estadisticas(int televidentes);
void condicionales(int cantMenores,int cantMujAdult,int cantHomJove,
                   int cantCanales,double promeMenoAdul,double porcentaMujeres,
                   double porcentajeHombres,double porcentajeAdultos,
                   double promedioTelevidentes,int dni,int aa,int horaI,
                   int minI,int segI,int horaF,int minF,int segF,char sexo,
                   char compania);
#endif