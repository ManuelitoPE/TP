//Author: Mako
#ifndef FUNCIONES_H
#define FUNCIONES_H
void lecturaDeAlumnos(int& alumnos,int* ARRalumnosCod,
                      int* ARRalumnosEsc,const char* nomAlumnos);
void lecturaDeCursos(int& cursos,int* ARRcursosCod,double* ARRcursosCre,
                     const char* nomCursos);
void lecturaDeEscalas(int& escalas,double* ARRescalasCos,
                      const char* nomEscalas);
void calculos(int alumnos,int cursos,int escalas,int* ARRalumnosCod,
              int* ARRalumnosEsc,int* ARRcursosCod,double* ARRcursosCre,
              double* ARRescalasCos,double* ARRtotalCreditos,
              int* ARRtotalCursos,double* ARRtotalIngresos,
              int *ARRtotalMatriculados,double* ARRtotalPagar,
              const char* nomMatricula);
int buscar(int codigo,int* arr,int n);
void ordenarAlumnos(int* ARRalumnosCod,int* ARRalumnosEsc,
                    double* ARRtotalCreditos,int* ARRtotalCursos,
                    double* ARRtotalPagar,int alumnos);
void cambiarINT(int& a,int& b);
void cambiarDOUBLE(double& a,double& b);
void ordenarCursos(int* ARRcursosCod,double* ARRcursosCre,
                   int* ARRtotalMatriculados,double* ARRtotalIngresos,
                   int cursos);
void emitirReporte(int* ARRalumnosCod,int* ARRalumnosEsc,
                   double* ARRtotalCreditos,int* ARRtotalCursos,
                   double* ARRtotalPagar,int alumnos,
                   int* ARRcursosCod,double* ARRcursosCre,
                   int* ARRtotalMatriculados,double* ARRtotalIngresos,
                   int cursos,const char* nomReporte);
void encabezado(ofstream& report);
void linea(ofstream& report,int n,char c);
void encabezado2(ofstream& report);

#endif