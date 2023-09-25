#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;
#include"../header/funciones.h"
int main(int argc, char** argv){
    emitiReporte("../source/docs/Almacen.txt","../source/docs/Productos.txt",
            "../source/docs/StockProductos.txt","../source/docs/Transacciones.txt"
            ,"../source/docs/Reporte.txt");
    return 0;
}