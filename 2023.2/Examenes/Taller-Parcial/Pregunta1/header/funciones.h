#ifndef FUNCIONES_H
#define FUNCIONES_H
#include<fstream>
// Pedimos la fecha
void pedirFecha(int& fecha);
// Ahora emitimos el reporte
void emitirReporte(const char*,const char*,const char*,const char*,const char*,int fecha);
void encabezado(ofstream& report,int fecha);
void linea(ofstream& report,int num,char sgino); 
void LecturaVerificacionEImpresion(ofstream& report,ifstream& peliculas,int fecha,int& codigoPeli);
void sub_encabezado(ofstream& report);
void lecturaEImpresionSub_encabezado(ofstream& report,ifstream& funciones,ifstream& salas,ifstream& ventas,
                                    int codigoPeli,double& totalRecaudado,int& totalButacasDis,int& totalButacasVen,
                                    int& totalButacasOcu,int fecha);
void estadisticas(int totalRecaudado,int totalButacasDis,int totalButacasVen,int totalButacasOcu,ofstream& report, int );
void lecturaDelNombre(ofstream& report,ifstream& peliculas);
int convertirHora(int hh,int min);
int buscadorHORA(ifstream& funciones,int codigoPeli,int n_sala);
int buscadorButacas(ifstream& salas,int n_sala);
int contOcupados(ifstream& ventas);
void calculoVentaYOcupacion(double& p_ventas,double& p_ocupados,int t_vendido,int contButacas,int t_ocupados);
void impresionDatos(ofstream& report,int contFunciones,int contButacas,double t_Recaudado,int t_vendido,int t_ocupados);




#endif