#ifndef FUNCIONES_H
#define FUNCIONES_H
void emitirReporte(const char* archCanales,
                   const char* archRegistro,
                   const char* archTelevidentes,
                   const char* reporte);
void encabezado(ofstream& report);
void linea(ofstream& report,int n,char c);
void lecturaYImpresionCanal(ifstream& archCanales,
                            ofstream& report,int& canal);
void impresionCanalNombre(ifstream& archCanales,ofstream& report);
void encabezado2(ofstream& report);
void impresionPersonas(int canal,int& totalPersonas,int& duracionTotal,
                       int& contMenores,int& contJovenes,int& contAdultos,
                       ifstream& archRegistro,ifstream& archTelevidentes,
                       ofstream& report);
void impresionDatos(int dni,int hhI,int minI,int ssI,int hhF,
                    int minF,int ssF,int& duracionTotal,
                    int& contMenores,int& contJovenes,
                    int& contAdultos,ifstream& archTelevidentes,
                    ofstream& report);
void impresionTelevidenteNombre(ifstream& archTelevidentes,
                                ofstream& report);
void impresionSexo(ofstream& report,char sexo);
void impresionCategoria(ofstream& report,int aa,
                        int& contAdultos,int& contJovenes,
                        int& contMenores);
void impresionCompania(ofstream& report,char compania);
void impresionRangoYDuracion(int hhI,int minI,int ssI,int hhF,
                             int minF,int ssF,
                             int& duracionTotal,ofstream& report);
int convertSeg(int hh,int min,int ss);
void convertHMS(int& hh,int& min,int& ss,int duracion);
void estadisticas(int totalPersonas,int duracionTotal,int contMenores,
                  int contAdultos,int contJovenes,ofstream& report);
#endif