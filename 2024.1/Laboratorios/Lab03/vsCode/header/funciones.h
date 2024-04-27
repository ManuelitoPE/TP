//Author: MAKO 
#ifndef FUNCIONES_H
#define FUNCIONES_H
void emitirReporte(const char* nomCitasMedicas,const char* nomMedicos,
                   const char* nomReporte);
void encabezado(ofstream& report);
void linea(ofstream& report,int n,char c);
void lecturaDeDatos(int& dd,int& mm,int& aa,int& dni,
                    int& hhI,int& minI,int& ssI,
                    int& hhF,int& minF,int& ssF,int& medico,
                    double& porcentaje,double& medicamentos,
                    char& receta,ifstream& arch);
void impresionDatos(int dd,int mm,int aa,int dni,
                    int hhI,int minI,int ssI,
                    int hhF,int minF,int ssF,int medico,
                    double porcentaje,double medicamentos,
                    char receta,double& totalIngresos,
                    double& montoGastado,int& paciente,
                    ifstream& archMedicos,ofstream& report);
void impresionDuracion(int hhI,int minI,int ssI,int hhF,int minF,
                       int ssF,double& duracionH,ofstream& report);
int convertSeg(int hh,int min,int ss);
void convertHMS(int& hh,int& min,int& ss,int duracion);
void impresionDatosMedico(int medico,double& tarifa,
                          ifstream& archMedicos,ofstream& report);
void impresionNombre(ifstream& archMedicos,ofstream& report,
                     bool mayuscula);
void impresionPago(double duracionH,double tarifa,double porcentaje,int dni,
                   int& paciente,double& montoGastado,double medicamentos,
                   double& totalIngresos,ofstream& report);                  
#endif