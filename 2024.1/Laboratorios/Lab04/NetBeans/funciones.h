
/* 
 * File:   funciones.h
 * Author: Sergio Manuel Sutta Pinedo 20210646
 *
 * Created on 29 de abril de 2024, 07:06 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H
void emitirReporte(const char* nomCitasMedicas,const char* nomMedicinas,
                   const char* nomMedicos,const char* nomReporte);
void encabezado(ofstream& report);
void linea(ofstream& report,int n,char c);
void impresionNombre(ofstream& report,ifstream& arch,
                     char delimitador,char aux);
void sub_encabezado(ofstream& report);
void lecturaDeCitas(int codigoMedico,double tarifa,int& codMedicoAporte,
                    double& totalMedico,ifstream& archCitasMedicas,
                    ifstream& archMedicinas,ofstream& report);
bool condicion(int codigoMedico,int aux_codigoMedico,double& duracionH,
               int& duracion,int hhI,int minI,int ssI,int hhF,int minF,int ssF);
void impresionDatosCita(int dd,int mm,int aa,int dni,int hhI,int minI,
                        int ssI,int hhF,int minF,int ssF,double tarifa,
                        int& duracion,
                        double duracionH,double porcentaje,double& pagoCita,
                        ofstream& report);
void convertHMS(int& hh,int& min,int& ss,int duracion);
void lecturaMedicinasRecetas(ifstream& archCitasMedicas,ifstream& archMedicinas,
                             double& pagoMedicinasTotal,
                             ofstream& report,double porcentaje);
void buscarImprimirMedicina(ofstream& report,ifstream& archMedicinas,
                            int codProducto,int cantPro,
                            double& pagoMedicinasTotal,double porcentaje);
void mejorMedico(ifstream& archMedicos,int codMedicoAporte,
                 double totalMedico, ofstream&  report);


#endif /* FUNCIONES_H */

