// Author: Mako
#include <iostream>
#include <iomanip>
using namespace std;
#include "header/funciones.h"
#define MAX_LINEA 125
void emitirReporte()
{
    cout.precision(4);
    cout << fixed;
    // Variables
    int dni, anio, hora_p, min_p, seg_p, hora_a, min_a, seg_a;
    char sexo, categoria, compania, c;
    // Cantidades
    int cant_tele = 0, cant_menor = 0, cant_mujeres = 0, cant_hombres = 0,
        cant_personas = 0;
    int prom_menoAdul;
    double porcentaje_tvPUCP, porcentaje_TPVision, adultos_registrados,
        prom_televidentes;
    // Imprimimos el encabezado
    encabezado();
    // Lectura de Datos
    while (true)
    {
        cin >> dni;
        if (cin.eof())
            break;
        //? Cantidad de televidentes
        cant_tele++;
        cin >> sexo >> anio >> c >> anio >> c >> anio >>
            hora_p >> c >> min_p >> c >> seg_p >> hora_a >>
            c >> min_a >> c >> seg_a;
        //* DNI
        cout << setw(12) << dni;
        //* SEXO
        determinacionSexo(sexo);
        //* CATEGORIA
        determinacionCategoria(anio, hora_p, min_p, seg_p,
                               hora_a, min_a, seg_a, sexo, cant_mujeres,
                               cant_menor);
        //* HORAS
        cout << setfill('0') << right << setw(2) << hora_p << ":"
             << setw(2) << min_p << ':' << setw(2) << seg_p << setfill(' ')
             << setw(5) << " " << setfill('0') << setw(2) << hora_a << ":"
             << setw(2) << min_a << ':' << setw(2) << seg_a << setfill(' ')
             << left << setw(5) << " ";
        //* DURACIONES
        determinacionDuracion(hora_p, min_p, seg_p, hora_a,
                              min_a, seg_a, sexo, anio, cant_hombres);
        //* CANAL
        determinarCanales(cant_personas);
        //* COMPANIA
        cin >> compania;
        determinarCompania(compania);
        //* ESTADISTICAS
    }
    linea('=');
    cout << setw(10) << ' ' << "ESTADISTICAS OBTENIDAS:" << endl
         << setw(10) << ' ' << setw(90) << "Cantidad de televidentes registrados: " << cant_tele << endl
         << setw(10) << ' ' << setw(90) << "Cantidad de menores que ven entre las 14:00:00 y las 19:00:00: " << cant_menor << endl
         << setw(10) << ' ' << setw(90) << "Cantidad de mujeres adultas que NO ven television entre las 9:30:00 y las 12:45: " << cant_mujeres << endl
         << setw(10) << ' ' << setw(90) << "Cantidad de hombres jovenes que ve mas de 3 horas y media: " << cant_hombres << endl
         << setw(10) << ' ' << setw(90) << "Cantidad de personas que ven los canales 770, 312 0 577 pero no 314 ni 555: " << cant_personas << endl
         << setw(10) << ' ' << setw(90) << "Tiempo promedio que ven los menores y adultos: " << prom_menoAdul << endl
         << setw(10) << ' ' << setw(90) << "Porcentaje de mujeres que ve TVPUCP: " << porcentaje_tvPUCP << endl
         << setw(10) << ' ' << setw(90) << "Porcentaje de hombres jovenes que ve TPVision: " << porcentaje_TPVision << endl
         << setw(10) << ' ' << setw(90) << "Porcentaje de adultos registrados: " << adultos_registrados << endl
         << setw(10) << ' ' << setw(90) << "Promedio de canales que ven los televidentes: " << prom_televidentes << endl;
    linea('=');
}
void encabezado()
{
    cout << setw(80) << "EMPRESA DE OPINION DE MERCADOD S.A." << endl;
    linea('=');
    cout << setw(50) << "REGISTO DE PREFRENCIAS DE LOS TELEVIDENTES" << endl;
    linea('=');
    cout << left << setw(12) << "DNI No." << setw(12) << "Sexo" << setw(12)
         << "Categoria" << setw(12) << "Hora(P)" << setw(12) << "Hora(A)"
         << setw(12) << "Duracion(H:M:S)" << setw(12) << "Duracion(H)"
         << setw(12) << "Canales" << setw(12) << "Compania" << endl;
    linea('-');
}
void linea(char signo)
{
    for (int i = 0; i < MAX_LINEA; i++)
    {
        cout << signo;
    }
    cout << endl;
}
void determinacionSexo(char sexo)
{
    if (sexo == 'M')
    {
        cout << setw(12) << "Maculino";
    }
    else
    {
        cout << setw(12) << "Femenino";
    }
}
void determinacionCategoria(int anio, int hora_p, int min_p,
                            int seg_p, int hora_a, int min_a,
                            int seg_a, char sexo, int &cant_mujeres,
                            int &cant_menor)
{
    int hora_prendido = hora_p * 10000 + min_p * 100 + seg_p;
    int hora_apagado = hora_a * 10000 + min_a * 100 + seg_a;
    if (anio > 2009)
    {
        cout << setw(12) << "Menor";
        if ((hora_prendido >= 140000) and (hora_apagado <= 190000))
        {
            cant_menor++;
        }
    }
    else if (anio > 1988)
    {
        cout << setw(12) << "Joven";
    }
    else
    {
        cout << setw(12) << "Adulto";
        if (sexo == 'F' and (hora_apagado < 93000 or hora_prendido > 124500))
        {
            cant_mujeres++;
        }
    }
}
void determinacionDuracion(int hora_p, int min_p, int seg_p, int hora_a,
                           int min_a, int seg_a,
                           char sexo, int anio, int &cant_hombres)
{
    double tiempoI, tiempoF, tiempoT;
    //? Pasamos todo a segundos
    tiempoI = hora_p * 3600 + min_p * 60 + seg_p;
    tiempoF = hora_a * 3600 + min_a * 60 + seg_a;
    tiempoT = tiempoF - tiempoI;
    // todo DURACION (H:M:S)
    int hora, min, seg;
    hora = tiempoT / 3600;
    min = (tiempoT - (hora * 3600)) / 60;
    seg = (tiempoT - (hora * 3600) - (min * 60));
    cout << setfill('0') << right << setw(2) << hora << ":"
         << setw(2) << min << ':' << setw(2) << seg << setfill(' ')
         << setw(5) << " " << left;
    // todo DURACION(H)
    double duracion_h;
    duracion_h = tiempoT / 3600;
    cout << setw(12) << duracion_h;
    if (anio > 1988 and sexo == 'M' and duracion_h > 3.30)
    {
        cant_hombres++;
    }
}
void determinarCanales(int &cant_personas)
{
    int i = 0;
    int canal, cantCanales = 0;
    bool canalNo_permitido = false, canalVisto = false;
    do
    {
        cin >> canal;
        if (canal != 0)
        {
            if (i != 0)
            {
                cout << '/';
            }
            cout << canal;
            if (!canalNo_permitido and (canal == 770 or canal == 312 or canal == 577) and !canalVisto)
            {
                cant_personas++;
                canalVisto = true;
            }
            else if (canal == 314 or canal == 555)
            {
                if (canalVisto and !canalNo_permitido)
                {
                    cant_personas--;
                }
                canalNo_permitido = true;
            }
            cantCanales++;
        }
        i++;
    } while (i < 3);
    cout << setw(17 - (cantCanales * 4)) << " ";
}
void determinarCompania(char compania)
{
    switch (compania)
    {
    case 'A':
        cout << "TVPUCP";
        break;
    case 'B':
        cout << "CableMas";
        break;
    default:
        cout << "TPVision";
        break;
    }
    cout << endl;
}