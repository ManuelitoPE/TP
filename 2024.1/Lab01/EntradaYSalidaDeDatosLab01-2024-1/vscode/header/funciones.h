//Author: MAKO
#ifndef FUNCIONES_H
#define FUNCIONES_H
void emitirReporte();
void encabezado();
void linea(int n,char c);
void lecturaDeDatos(int& dd,int& mm,int& aa,int& dni,int& hhI,
                    int& minI,int& ssI,int& hhF,int& minF,int& ssF,
                    double& tarifa,double& medicamentos,
                    char& especialidad,char& receta);
void impresionDeDatos(int dd,int mm,int aa,int dni,int hhI,
                    int minI,int ssI,int hhF,int minF,int ssF,
                    double tarifa,double medicamentos,
                    char especialidad,char receta,
                    double& duracionH,double& totalDeIngresos);
void impresionDuracion(int hhI,int minI,int ssI,
                       int hhF,int minF,int ssF,
                       double& duracionH);
int convertirS(int hh,int min,int ss);
void convertirHMS(int& hh,int& min,int& ss,int duracion);
void impresionEspecialidad(char especialidad);
void impresionPagos(double tarifa,double medicamentos,
                    double duracionH,double& totalDeIngresos);
void impresionEstadisticas(double totalDeIngresos,double promGastos,
                      double promGastosD,double porcentajeNoA,
                      double porcentajePedia,double porcentaje350,
                      int pacientesCardio);
void conteoDeCondicioanales(int dd,int mm,int aa,int dni,int hhI,
                    int minI,int ssI,int hhF,int minF,int ssF,
                    double tarifa,double medicamentos,
                    char especialidad,char receta,
                    double duracionH,int& pacientes,int& pacientesAten,
                    int& pacientesAtenD,int& pacientesNo,int& pacientesPedia,
                    int& pacientesCardio,int& pacientes350,
                    double& gastosMedicina,double& gastosMedicinaD);
void procesosEstadisticos(int pacientes,int pacientesAten,int pacientesAtenD,
                    int pacientesNo,int pacientesPedia,int pacientes350,
                    double& promGastos,double& promGastosD,
                    double& porcentajeNoA,double& porcentajePedia,
                    double& porcentaje350,double gastosMedicina,
                    double gastosMedicinaD);
#endif