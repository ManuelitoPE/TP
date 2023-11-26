#ifndef FUNCIONES_H
#define FUNCIONES_H
    // Pedir la fecha
void ingresoDeFecha(int& fecha);
int convertirFecha(int dd,int mm,int aa);

    //Leer codigo de peliculas (misma cantidad del total recaudado)
void lecturaDePelicualas(int& numPeliculas,int* codPeli,int fecha,
                        const char* nomArch);
    //Leemos los datos de funciones
void lecturaDeFunciones(int& num_funciones,int* peliFunciones,
                    int* num_Salas_Funciones,int* horafunciones
                    ,const char* nomArch);
int convertirHora(int hh,int min);

    //Leemos el numero de butacas por sala
void lecturaNumButacas(int* num_Butacas,int& numeroButa,
                    const char* nomArch);
    //Lectura de ventas
void lecturaVentas(const char* nomArch,int* codPeli,
                int* T_ButacasDis,int* cantFunciones,
                int* T_ButacasVend,int* T_ButacasOcu,
                double* recaudacionP,int* num_Butacas,
                int* peliFunciones,int* num_Salas_Funciones,
                int* horafunciones ,int numPeliculas,
                int numeroButa,int num_funciones,int fecha);
int buscarCodigo(int* peliFunciones,int* horafunciones,int horaREF,
            int salaREF,int* num_Salas_Funciones,int num_funciones);

int buscarPosicion(int codigoP,int* codPeli,int numPeliculas);
int numeroOcupadas(ifstream& arch);


    //Emitir el reporte
void emitirReporte(const char* nomArch,int fecha,int* codPeli,
                int* T_ButacasDis, int* cantFunciones,
                int* T_ButacasVend,int* T_ButacasOcu,
                double* recaudacionP,int numPeliculas);
void  encabezado(ofstream& arch,int fecha);
void linea(ofstream& arch,int num,char signo);
void calculoVentayOcupacion(double& venta,double& ocupacion,
                            int T_ButacasVend,int T_ButacasDis,
                            int T_ButacasOcu);
void estadisticas(ofstream& arch,double* recaudacionP,int numPeliculas,
                int* T_ButacasVend,int * T_ButacasDis,
                int* T_ButacasOcu);
int sumatotal(int num,int* arr);
double sumatotalDouble(int num,double* arr);
#endif