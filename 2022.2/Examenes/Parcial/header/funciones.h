#ifndef FUNCIONES_H 
#define FUNCIONES_H
void pedirDatos(int& ddI,int& mmI,int& aaI,int& ddF,int& mmF,
                int& aaF);
void emitirReporte(int ddI,int mmI,int aaI,int ddF,int mmF,int aaF,
                  const char* nomComentarios, const char* nomTikToks,
                  const char* nomPaises,const char* nomUsuarios,
                  const char* nomReporte);
void encabezado(ofstream& report,int ddI,int mmI,int aaI,
                int ddF,int mmF,int aaF);
void linea(ofstream& report,int n,char c);
bool condicionFecha(int ddI,int mmI,int aaI,int ddF,int mmF,
                    int aaF,int dd,int mm,int aa);
                    


#endif