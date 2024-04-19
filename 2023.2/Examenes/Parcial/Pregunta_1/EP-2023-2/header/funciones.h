#ifndef FUNCIONES_H
#define FUNCIONES_H
void datosReporte(int& aa,int& ciclo);
void emitirReporte(const char* nomAlumnos,const char* nomCursos,
                  const char* nomEscalas,const char* nomMatricula,
                  const char* nomReporte,int aa,int ciclo);
void encabezado(ofstream& report,int aa,int ciclo);
void linea(ofstream& report,int n,char c);
void lecturaDeDatos(int aa,int ciclo,double& montoTotalPagado,
                    ifstream& archMatricula,ifstream& archAlumnos,
                    ifstream& archCursos,ifstream& archEscalas,
                    ofstream& report);
void busquedaNombreEscala(ofstream& report,ifstream& archAlumnos,
                          int codigoAlumno,char& escala);
void impresionNombre(ifstream& archAlumnos,bool mayuscula,
                     ofstream& report);
void encabezadoC(ofstream& report);
void busquedaNombreCreditos(ofstream& report,ifstream& archCursos,   
                       int curso,double& credito);
void busquedaPrecioCredito(int aa,int ciclo,char escala,
                           ifstream& archEscalas,double& precio);

#endif