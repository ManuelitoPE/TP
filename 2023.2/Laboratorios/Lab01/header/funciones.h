//Author: MAKO
#ifndef FUNCIONES_H
#define FUNCIONES_H
void emitirReporte();
void encabezado();
void lecturaDeDatos(int& dni,int& aa,int& horaI,int& minI,
               int& segI,int& horaF,int& minF,int& segF,
               int& canal1,int& canal2,int& canal3,char& sexo,
               char& compania,int& televidentes);
void linea(int n,char c);
void impresionSexoCategoria(char sexo, int anio);
void impresionHoraDuracion(int horaI,int minI,int segI,int horaF,
                        int minF,int segF,double& duracionH);
int convertirSegundos(int hora,int min,int seg);
void convertirHMS(int& hora,int& min,int& seg,double duracion);
void lecturaCanales(int canal1,int canal2,int canal3);
void impresionCompania(char compania);
void condicionales(int& cantMenores,int& cantMujAdult,int& cantHomJove,
                   int& cantCanales,int& cantMenoAdult,double& duracionTotal,
                   int& personasTVPUCP,
                   int&  mujeTVPUCP,int& personasTPVIsion,int& hombJoveTPVision,
                   int& adultos,int& canales,int dni,int aa,int horaI,
                   int minI,int segI,int horaF,int minF,int segF,char sexo,
                   char compania,double duracionH,int canal1,int canal2,
                   int canal3);
void estadisticas(int televidentes,int cantMenores, int cantMujAdult,
                  int cantHombreJove,int cantCanales,int hora,int min,
                  int ss,double porcentaMujeres,double porcentajeHombres,
                  double porcentajeAdultos,double promedioTelevidentes);
#endif