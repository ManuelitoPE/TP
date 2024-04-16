//Author: MAKO
#ifndef FUNCIONES_H
#define FUNCIONES_H
void emitirReporte(const char* nomArch,
                   const char* reporte);
void encabezado(ofstream& report);
void linea(ofstream& report,int num, char c);
void lecturaDeDatos(int& dd,int& mm,int& aa,int& dni,
                    int& hhI,int& minI,int& ssI,
                    int& hhF,int& minF,int& ssF,
                    double& porcentajeDescuento,
                    double& tarifa,double& medicamentos,
                    char& especialidad,char& receta,
                    ifstream& arch);
bool condicionYCalculoDuracion(int hhI,int minI,int ssI,
        int hhF,int minF,int ssF,int& duracion,
        char especialidad);
int convertSeg(int hh,int min,int ss);
void impresionDatos(int dd,int mm,int aa,int dni,
                    int hhI,int minI,int ssI,
                    int hhF,int minF,int ssF,
                    double porcentajeDescuento,
                    double tarifa,double medicamentos,
                    char especialidad,char receta,
                    int duracion,int& totalIngresos,
                    ofstream& report);
void impresionDuracion(int duracion,double& duracionH,
                       ofstream& report);
void convertHMS(int& hh,int& min,int& ss,int duracion);
void impresionPago(double tarifa,double medicamentos,
                   double porcentajeDescuento,
                   double duracionH,int& totalIngresos,
                   ofstream& report);
void estadisticas(int registros,int registrosP,
                  ofstream& report);
#endif