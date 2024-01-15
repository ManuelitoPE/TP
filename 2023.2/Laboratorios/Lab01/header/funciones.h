// Author: Mako
#ifndef FUNCIONES_H
#define FUNCIONES_H
void emitirReporte();
void encabezado();
void linea(char signo);
void determinacionSexo(char sexo);
void determinacionCategoria(int anio, int hora_p, int min_p,
                            int seg_p, int hora_a, int min_a,
                            int seg_a, char sexo, int &cant_mujeres,
                            int &cant_menor);
void determinacionDuracion(int hora_p, int min_p, int seg_p,
                           int hora_a, int min_a, int seg_a,
                           char sexo, int anio, int &cant_hombres);
void determinarCanales(int &cant_personas);
void determinarCompania(char compania);
#endif