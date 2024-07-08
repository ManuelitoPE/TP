//Author: MAKO
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "header/funciones.h"
#include "header/Articulo.h"
#include "header/Vendedor.h"
#define NO_ENCONTRADO -1
#define MAX_LINEA 130
void lecturaArticulos(const char* nomArticulos,
                      const char* nomArticulosBin){
    ifstream arch(nomArticulos,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomArticulos<<endl;
        exit(1);
    }
    ofstream archBin(nomArticulosBin,ios::out|ios::binary);
    if(not archBin.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomArticulosBin<<endl;
        exit(1);
    }
    //Variables
    struct Articulo articulo;
    char code[8],description[100]; double price;
    while(true){
        arch.getline(code,8,',');
        if(arch.eof())break;
        arch.getline(description,100,','); 
        arch>>price; arch.get();
        strcpy(articulo.code,code);
        strcpy(articulo.description,description);
        articulo.price=price; articulo.cant=0; 
        articulo.montoVendido=0;
        archBin.write(reinterpret_cast<const char*>(&articulo),
                      sizeof(struct Articulo));
    }
}
void lecturaVendedores(const char* nomVendedores,
                       const char* nomVendedoresBin){
    ifstream arch(nomVendedores,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomVendedores<<endl;
        exit(1);
    }
    ofstream archBin(nomVendedoresBin,ios::out|ios::binary);
    if(not archBin.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomVendedoresBin<<endl;
        exit(1);
    }
    //Variables
    struct Vendedor vendedor;
    int code; char nombre[50],c; double porcentaje,cuotaMinima;
    while(true){
        arch>>code; if(arch.eof())break; arch.get();
        arch.getline(nombre,50,','); 
        arch>>porcentaje>>c>>cuotaMinima; arch.get();
        strcpy(vendedor.nombre,nombre);
        vendedor.codigo=code; 
        vendedor.porcentajeVentas=porcentaje; 
        vendedor.cuotaMinima=cuotaMinima;
        vendedor.cant=0; vendedor.montoTotalVendido=0;
        vendedor.superoCuotaMinima=true;
        archBin.write(reinterpret_cast<const char*>(&vendedor),
                      sizeof(struct Vendedor));
    }
} 
void actualizacionVentas(const char* nomVentas, 
                         const char* nomVendedoresBin,
                         const char* nomArticulosBin){
    ifstream arch(nomVentas,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomVentas<<endl;
        exit(1);
    }
    fstream archVendedores(nomVendedoresBin,ios::out|ios::in|ios::binary);
    if(not archVendedores.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomVendedoresBin<<endl;
        exit(1);
    }
    fstream archArticulos(nomArticulosBin,ios::out|ios::in|ios::binary);
    if(not archArticulos.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomArticulosBin<<endl;
        exit(1);
    }
    //Variables
    char codeArticulo[8]; int codeVendedor,cant; 
    while (true){
        arch.getline(codeArticulo,8,' '); 
        if(arch.eof())break; 
        arch>>ws>>codeVendedor>>cant; arch.get();
        ingresoDeDatos(archVendedores,archArticulos,codeArticulo,
                 codeVendedor,cant);
    }
}
void ingresoDeDatos(fstream& archVendedores, fstream& archArticulos,
              char* codeArticulo,int codeVendedor,int cant){
    //Variables
    struct Vendedor vendedor;
    struct Articulo articulo;
    int sizeVendedores= sizeof(struct Vendedor);
    int sizeArticulos = sizeof(struct Articulo);
    int numVendedores = constSructs(archVendedores,sizeVendedores);
    int numArticulos  = constSructs(archArticulos,sizeArticulos);
    int posVendedor   = buscarVendedor(archVendedores,numVendedores,
                                       sizeVendedores,codeVendedor);
    int posArticulo   = buscarArticulo(archArticulos ,numArticulos ,
                                       sizeArticulos ,codeArticulo);
    if(posArticulo!=NO_ENCONTRADO and posVendedor!=NO_ENCONTRADO){
        archVendedores.seekg(posVendedor*sizeVendedores,ios::beg);
         archArticulos.seekg(posArticulo*sizeArticulos ,ios::beg);
        archVendedores.read(reinterpret_cast<char*>(&vendedor),sizeVendedores);
         archArticulos.read(reinterpret_cast<char*>(&articulo),sizeArticulos );
        actualizacion(articulo,vendedor,cant);
        archVendedores.seekg(posVendedor*sizeVendedores,ios::beg);
         archArticulos.seekg(posArticulo*sizeArticulos ,ios::beg);
        archVendedores.write(reinterpret_cast<const char*>(&vendedor),sizeVendedores);
         archArticulos.write(reinterpret_cast<const char*>(&articulo),sizeArticulos );
        archVendedores.flush();
         archArticulos.flush();
    }
}
int constSructs(fstream& arch, int size){
    //Variables 
    int num;
    arch.seekg(0,ios::end);
    num= arch.tellg();
    arch.seekg(0,ios::beg);
    return num/size;
}
int buscarVendedor(fstream& archVendedores,int numVendedores,
                   int size,int codeVendedor){
    //Variables
    struct Vendedor vendedor;
    for (int i = 0; i < numVendedores; i++){
        archVendedores.seekg(i*size);
        archVendedores.read(reinterpret_cast<char*>(&vendedor),size);
        if(vendedor.codigo==codeVendedor)return i;
    }
    return NO_ENCONTRADO;
}
int buscarArticulo(fstream& archArticulos ,int numArticulos ,
                   int size,char* codeArticulo){
    //Variables
    struct Articulo articulo;
    for (int i = 0; i < numArticulos; i++){
        archArticulos.seekg(i*size);
        archArticulos.read(reinterpret_cast<char*>(&articulo),size);
        if(strcmp(articulo.code,codeArticulo)==0)return i;
    }
    return NO_ENCONTRADO;
}
void actualizacion(struct Articulo& articulo,struct Vendedor& vendedor,
                   int cant){
    //Articulo
    articulo.cant+=cant;
    articulo.montoVendido+=cant*articulo.price;
    //Vendedores
    int cantidadArticulos=vendedor.cant; 
    int pos=buscarArticulos(vendedor.articulosVendidos,cantidadArticulos,
                    articulo.code);
    if(pos!=NO_ENCONTRADO){
        vendedor.articulosVendidos[pos].cant+=cant;
        vendedor.articulosVendidos[pos].montoTotalVendido+=cant*articulo.price;
        vendedor.articulosVendidos[pos].pagoAvendedor+=(cant*articulo.price*vendedor.porcentajeVentas)/100;
    }else{
        strcpy(vendedor.articulosVendidos[cantidadArticulos].code,articulo.code);
        vendedor.articulosVendidos[cantidadArticulos].cant+=cant;
        vendedor.articulosVendidos[cantidadArticulos].montoTotalVendido+=cant*articulo.price;
        vendedor.articulosVendidos[cantidadArticulos].pagoAvendedor+=(cant*articulo.price*vendedor.porcentajeVentas)/100;
        vendedor.cant++;
    }
    vendedor.montoTotalVendido+=cant*articulo.price;
}
int buscarArticulos(struct ArticuloVendido* articulos,int cantidadArticulos,
                    char* code){
    for (int i = 0; i < cantidadArticulos; i++){
        if(strcmp(articulos->code,code)==0)return i;
    }
    return NO_ENCONTRADO;
}
void correcionVendedores(const char* nomVendedoresBin){
    fstream archVendedores(nomVendedoresBin,ios::out|ios::in|ios::binary);
    if(not archVendedores.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomVendedoresBin<<endl;
        exit(1);
    }
    //Variables
    struct Vendedor vendedor;
    int sizeVendedores= sizeof(struct Vendedor);
    int numVendedores = constSructs(archVendedores,sizeVendedores);
    for(int i=0;i<numVendedores;i++){
        archVendedores.seekg(i*sizeVendedores,ios::beg);
        archVendedores.read(reinterpret_cast<char*>(&vendedor),sizeVendedores);
        if(vendedor.montoTotalVendido<vendedor.cuotaMinima){
            vendedor.superoCuotaMinima=false;
            for(int i=0;i<vendedor.cant;i++)
                vendedor.articulosVendidos[i].pagoAvendedor=0;
        }
        archVendedores.seekg(i*sizeVendedores,ios::beg);
        archVendedores.write(reinterpret_cast<const char*>(&vendedor),sizeVendedores);
        archVendedores.flush();
    }    
}
void ordenamiento(const char* nomVendedoresBin){
    fstream archVendedores(nomVendedoresBin,ios::out|ios::in|ios::binary);
    if(not archVendedores.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomVendedoresBin<<endl;
        exit(1);
    }
    //Variables
    struct Vendedor vendedorI,vendedorK; double montoI,montoK;
    int sizeVendedores= sizeof(struct Vendedor);
    int numVendedores = constSructs(archVendedores,sizeVendedores);
    for(int i=0;i<numVendedores-1;i++){
        for (int k = i+1; k < numVendedores; k++){
            archVendedores.seekg(i*sizeVendedores,ios::beg);
            archVendedores.read(reinterpret_cast<char*>(&vendedorI),sizeVendedores);   
            archVendedores.seekg(k*sizeVendedores,ios::beg);
            archVendedores.read(reinterpret_cast<char*>(&vendedorK),sizeVendedores);
            montoI=calcularMonto(vendedorI); montoK=calcularMonto(vendedorK);
            if(montoI<montoK)cambiarStruct(vendedorI,vendedorK);
            archVendedores.seekg(i*sizeVendedores,ios::beg);
            archVendedores.write(reinterpret_cast<const char*>(&vendedorI),sizeVendedores);   
            archVendedores.seekg(k*sizeVendedores,ios::beg);
            archVendedores.write(reinterpret_cast<const char*>(&vendedorK),sizeVendedores);
            archVendedores.flush();
        }
    }
}
double calcularMonto(struct Vendedor vendedor){
    // Variables
    double monto=0;
    for(int i=0;i<vendedor.cant;i++)
        monto+=vendedor.articulosVendidos[i].pagoAvendedor;
    return monto;
}
void cambiarStruct(struct Vendedor& vendedorI,struct Vendedor& vendedorK){
    struct Vendedor aux; aux=vendedorI; vendedorI=vendedorK; vendedorK=aux;
}
void emitirReporte(const char* nomVendedores,
                   const char* nomReporte, const char* nomArticulo){
    ofstream report(nomReporte,ios::out);
    if(not report.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomReporte<<endl;
        exit(1);
    }
    fstream archVendedor(nomVendedores,ios::out|ios::in|ios::binary);
    if(not archVendedor.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomVendedores<<endl;
        exit(1);
    }
    fstream archArticulo(nomArticulo,ios::out|ios::in|ios::binary);
    if(not archArticulo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomArticulo<<endl;
        exit(1);
    }
    report.precision(2); report<<fixed;
    encabezado(report);    
    //Variables
    struct Vendedor vendedor;
    struct Articulo articulo;
    int sizeArticulos = sizeof(struct Articulo);
    int sizeVendedores= sizeof(struct Vendedor);
    int numArticulos  = constSructs(archArticulo,sizeArticulos);
    int numVendedores = constSructs(archVendedor,sizeVendedores);
    int posArticulo, totalDePagosPorVentas;
    for(int i=0;i<numVendedores;i++){
        archVendedor.seekg(i*sizeVendedores,ios::beg);
        archVendedor.read(reinterpret_cast<char*>(&vendedor),sizeVendedores);
        modificarTexto(vendedor.nombre); //Modificamos el nombre
        encabezado1(report);
        report<<right<<setfill('0')<<setw(3)<<i+1<<")"<<setfill(' ')
              <<setw(10)<<vendedor.codigo<<"  "
              <<left<<setw(40)<<vendedor.nombre
              <<right<<setw(10)<<vendedor.porcentajeVentas
              <<setw(20)<<vendedor.cuotaMinima<<left<<setw(6)<<" ";
        if(!vendedor.superoCuotaMinima)report<<"NO SUPERO LA CUOTA";
        report<<endl<<setw(6)<<" "<<"ARTICULOS VENDIDOS"<<endl;
        encabezado2(report); totalDePagosPorVentas=0;
        for(int k=0;k<vendedor.cant;k++){
            //Buscamor el nombre de los artiuclos
            posArticulo= buscarArticulo(archArticulo,numArticulos,
                                        sizeArticulos,vendedor.articulosVendidos[k].code);
            archArticulo.seekg(posArticulo*sizeArticulos,ios::beg);
            archArticulo.read(reinterpret_cast<char*>(&articulo),sizeArticulos);
            report<<setw(6)<<" "<<right<<setfill('0')<<setw(2)<<k+1<<")  "
                  <<setfill(' ')<<left<<setw(10)<<vendedor.articulosVendidos[k].code
                  <<setw(60)<<articulo.description<<right
                  <<setw(7)<<vendedor.articulosVendidos[k].cant
                  <<setw(13)<<vendedor.articulosVendidos[k].montoTotalVendido
                  <<setw(16)<<vendedor.articulosVendidos[k].pagoAvendedor<<endl;
            totalDePagosPorVentas+=vendedor.articulosVendidos[k].pagoAvendedor;
        }
        report<<"TOTAL DE PAGOS POR VENTAS: "<<totalDePagosPorVentas<<endl<<endl;
    }
    report<<right<<setw(60)<<"DETALLE DE INGRESOS POR ARTICULO"<<endl;
    linea(report,MAX_LINEA,'='); encabezado3(report);
    for(int k=0;k<numArticulos;k++){
        archArticulo.seekg(k*sizeArticulos,ios::beg);
        archArticulo.read(reinterpret_cast<char*>(&articulo),sizeArticulos);
        report<<setfill('0')<<right<<setw(3)<<k+1<<")   "<<setfill(' ')
              <<left<<setw(10)<<articulo.code
              <<setw(60)<<articulo.description
              <<right<<setw(10)<<articulo.price
              <<setw(13)<<articulo.cant
              <<setw(25)<<articulo.montoVendido<<endl;
    }

}
void modificarTexto(char* nombre){
    //Variable
    bool primeraLetra=true; 
    for(int i=0;nombre[i];i++){
        if(nombre[i]=='/' or nombre[i]=='-'){
            nombre[i]=' ';
            primeraLetra=true;
        }
        else {
            nombre[i]+=(primeraLetra)?0:'a'-'A';
            primeraLetra=false;
        }
    }
}
void encabezado(ofstream& report){
    report<<setw(60)<<"TIENDA POR DEPARTAMENTOS TP"<<endl<<endl
          <<setw(60)<<"DETALLE DE PAGOS A LOS VENDEDORES"<<endl;
}
void encabezado1(ofstream& report){
    linea(report,MAX_LINEA,'=');
    report<<left<<setw(5)<<"No."
          <<setw(52)<<"VENDEDOR"
          <<setw(18)<<"% POR VENTAS"
          <<setw(20)<<"CUOTA MINIMA"<<"OBSERVACION"<<endl;
    linea(report,MAX_LINEA,'-');
}
void linea(ofstream& report,int n,char c){
    for (int i = 0; i < n; i++)report<<c;
    report<<endl;
}
void encabezado2(ofstream& report){
    report<<setw(6)<<" "<<setw(5)<<"No. "
          <<setw(72)<<"ARTICULO"
          <<setw(13)<<"CANTIDAD"
          <<setw(10)<<"TOTAL"<<"PAGO POR VENTAS"<<endl;
}
void encabezado3(ofstream& report){
    report<<left<<setw(5)<<"No. "
          <<setw(76)<<"ARTICULO"
          <<setw(10)<<"PRECIO"
          <<setw(20)<<"CANTIDAD VENDIDA"<<"INGRESOS POR VENTAS"<<endl;
    linea(report,MAX_LINEA,'-');

}
