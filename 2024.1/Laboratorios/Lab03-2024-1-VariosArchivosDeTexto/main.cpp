/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: Sergio Manuel Sutta Pinedo 20210646
 *
 * Created on 22 de abril de 2024, 07:08 PM
 */

#include <iostream>
#include <iomanip>
using namespace std;
#include "funciones.h"
int main(int argc, char** argv) {
    emitirReporte("Medicos.txt","CitasMedicas.txt",
                  "Reporte.txt");
    return 0;
}

