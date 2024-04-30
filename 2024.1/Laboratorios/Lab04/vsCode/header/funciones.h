//Author: MAKO
#ifndef FUNCIONES_H
#define FUNCIONES_H

void emitirReporte(const char* nomCitasMedicas,const char* nomMedicinas,
                   const char* nomMedicos,const char* nomReporte);
void encabezado(ofstream& report);
void linea(ofstream& report,int n,char c);
void imprimirNombre(ofstream& report,ifstream& arch,
                    char delimitador,char aux);
void lecturaImpresionCitas(int codMedico,double tarifa,int& codMedicoMAX,
                           double& totalMedicoMAX,ifstream& archCitasMedicas,
                           ifstream& archMedicinas,ofstream& report);
bool condicion(int aux_codMed,int codMedico,int hhI,int minI,
               int ssI,int hhF,int minF,int ssF,int& duracion,
               double& duracionH);
int convertSeg(int hh,int min,int ss);
void imprimirCita(int dd,int mm,int aa,int dni,int hhI,int minI,
                  int ssI,int hhF,int minF,int ssF,int duracion,
                  double duracionH,double porcentaje,double tarifa,
                  ofstream& report,double& pagoCita);
void subEncabezado(ofstream& report);
void convertHMS(int& hh,int& min,int& ss,int duracion);
void imprimirMedicinas(ifstream& archCitasMedicas,ifstream& archMedicinas,
                       double porcentaje,double& pagoMedicinas,
                       ofstream& report);
void subEncabezado2(ofstream& report);
void imprimirMedicina(int codPRo,int cantPro,double porcentaje,
                      double& pago,ifstream& archMedicinas,
                      ofstream& report);
void imprimirMejorMedico(int codMedicoMAX,double totalMedicoMAX,
                         ifstream& archMedicos,ofstream& report);

#endif