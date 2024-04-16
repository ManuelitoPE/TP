//Author: MAKO
#ifndef FUNCIONES_H
#define FUNCIONES_H
void emitirReporte();
void linea(int num,char c);
void encabezado();
void lecturaDeDatos(int& codigoCiudad,int& dd,int& mm,int& aa,
                    int& hhI,int& minI,int& ssI,int& hhF,int& minF,
                    int& ssF,int& error,double& volumen,char& inicialCiudad,
                    bool& statusRegistro);
void impresionDatos(int codigoCiudad,int dd,int mm,int aa,
                    int hhI,int minI,int ssI,int hhF,int minF,
                    int ssF,double& duracion,double volumen,char inicialCiudad,
                    bool statusRegistro);
void impresionStatus(bool statusRegistro);
void impresionDuracion(int hhI,int minI,int ssI,int hhF,
                       int minF,int ssF,double& duracion);
int convertirSeg(int hh,int min,int ss);
void convertirHMS(int& hh,int& min,int& ss,double duracion);
void procesoEstadistica(double& duracionMax,double duracion,
                        double& VolumenMax,double volumen);
void emitirEstadisticas(int error,double duracion,double volumenMax);
#endif