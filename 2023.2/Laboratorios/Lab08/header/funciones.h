//Author: MAKO
#ifndef FUNCIONES_H
#define FUNCIONES_H

//SOLICITAR DATOS
void solicarDatosUsuario(int& anio,int& ciclo);
//LECTURA ALUMNOS
void lecturaAlumnos(struct Alumno *alumnos,int& numAlumnos,const char* nomArch);
//LECTURA DE CURSOS 
void lecturaCursos(struct Curso *cursos,int& numCursos,const char* nomArch);
void mayusculas(struct Curso *cursos,int numCursos);
//LECTURA DE ESCALAS
void lecturaEscalas(struct Escala *escalas,int& numEscalas,const char* nomArch);
//ACTUALIZACION DE DATOS
void actulizacionDatos(double &total,struct Alumno *alumnos,
                        struct Curso *cursos,
                        struct Escala *escalas,int numAlumnos,int numCursos,
                        int numEscalas,int anio,int ciclo,
                        const char* nomArch);
void procesarDatos(struct Alumno *alumnos,struct Curso *cursos,
                    struct Escala *escalas,int numAlumnos,int numCursos,
                    int numEscalas,int codigo_AlumnoREF,
                    int anio,int ciclo,ifstream& arch);
void calcularTOTAL(double& total,struct Curso *cursos,int numCursos);
int BuscarPoscionAlumno(struct Alumno *alumnos,int numAlumnos,
                        int codigo_AlumnoREF);
int BuscarPosicionCurso(struct Curso *cursos,int  numCursos,
                        int codigo_curso);
int BuscarPosicionEscala(struct Escala *escalas,int numEscalas,
                        int anio,int ciclo,char escala);
//ORDENANDO DATOS
void ordenarCursos(struct Curso *cursos,int  numCursos);
void cambiarStructua(struct Curso &cursoA,struct Curso &cursoB);
//EMITIMOS REPORTE
void emitirReporte(double total,int anio,int ciclo,
                    struct Curso *cursos,
                    int  numCursos,const char* nomArch);
void encabezado(int anio,int ciclo,ofstream& arch);
void linea(ofstream& arch,int num ,char signo);
#endif /* FUNCIONES_H */

