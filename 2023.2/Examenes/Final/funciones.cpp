#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "header/funciones.h"
#include "header/Articulo.h"
#include "header/Vendedor.h"

#define MAX_LINEA 120
#define NO_ENCONTRADO -1

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
    char code[8],description[100],c; int stock; double precio;
    while(true){
        arch.getline(code,8,',');
        if(arch.eof())break;
        arch.getline(description,100,',');
        arch>>stock>>c>>precio; arch.get();
        strcpy(articulo.codigo,code);
        strcpy(articulo.description,description);
        articulo.stock=stock; articulo.precio=precio;
        articulo.cantArticulosVendidos=0; articulo.montoVendido=0;
        articulo.cantArticulosPerdidos=0; articulo.montoPerdido=0;
        archBin.write(reinterpret_cast<const char*>(&articulo),
                      sizeof(struct Articulo));
    }
}
void pruebaArticulos(const char* nomArticulosBin,
                     const char* nomReport){
    ofstream report(nomReport,ios::out);
    if(not report.is_open()){
        cout<<"ERROR: No se puedo abrir "<<nomReport<<endl;
        exit(1);
    }
    fstream arch(nomArticulosBin,ios::in|ios::out|ios::binary);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomArticulosBin<<endl;
        exit(1);
    }
    report.precision(2); report<<fixed;
    encabezadoPrueba(report);
    //Variables
    struct Articulo articulo;
    int sizeArticulo = sizeof(struct Articulo);
    int numArticulos = contadorStucts(arch,sizeArticulo);
    for(int i=0;i<numArticulos;i++){
        arch.seekg(i*sizeArticulo,ios::beg);
        arch.read(reinterpret_cast<char*>(&articulo),sizeArticulo);
        report<<right<<setfill('0')<<setw(3)<<i+1<<") "<<setfill(' ')
              <<left<<setw(10)<<articulo.codigo
              <<setw(56)<<articulo.description
              <<right<<setw(5)<<articulo.stock
              <<setw(14)<<articulo.precio<<endl;
    }
}
void encabezadoPrueba(ofstream& report){
    report<<setw(50)<<"LISTA DE ARTICULOS Y SUS STOCKS"<<endl;
    linea(report,MAX_LINEA,'=');
    report<<left<<setw(5)<<"No."
          <<setw(10)<<"CODIGO"
          <<setw(56)<<"DESCRIPCION"
          <<setw(12)<<"STOCK"
          <<setw(10)<<"PRECIO"<<endl;
    linea(report,MAX_LINEA,'-');
}
void encabezado(ofstream& report){
    report<<left<<setw(5)<<"No."
          <<setw(55)<<"VENDEDOR"
          <<setw(12)<<"% VENTAS"
          <<setw(16)<<"CUOTA MINIMA"
          <<setw(17)<<"TOTAL VENDIDO"
          <<setw(17)<<"TOTAL NO VENDIDO"<<endl;
}
void encabezado2(ofstream& report){
    report<<left<<setw(5)<<" "<<setw(5)<<"No."
          <<setw(68)<<"ARTICULO"
          <<setw(13)<<"CANTIDAD"
          <<setw(9)<<"MONTO"
          <<setw(10)<<"FECHA MAS RECIENTES"<<endl;
}
void linea(ofstream& report,int n,char c){
    for(int i=0;i<n;i++)report<<c;
    report<<endl;
}
int contadorStucts(fstream& arch,int size){
    //Varibles
    int num;
    arch.seekg(0,ios::end);
    num=arch.tellg();
    arch.seekg(0,ios::beg);
    return num/size; 
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
        arch>>code;
        if(arch.eof())break; arch.get();
        arch.getline(nombre,50,',');
        arch>>porcentaje>>c>>cuotaMinima; arch.get();
        vendedor.codigo=code;
        strcpy(vendedor.nombre,nombre);
        vendedor.porcentaje=porcentaje; vendedor.cuotaMinima=cuotaMinima;
        vendedor.cantArticulosVendidos=0; vendedor.montoTotalVendido=0;
        vendedor.cantArticulosPerdidos=0; vendedor.monoTotalPerdido=0;
        archBin.write(reinterpret_cast<const char*>(&vendedor),
                      sizeof(struct Vendedor));
    }
}
void emitirReporte(const char* nomPruebaReporte,
                   const char* nomVendedores,const char* nomArticulos){
    ofstream report(nomPruebaReporte,ios::out);
    if(not report.is_open()){
        cout<<"ERROR: No se puedo abrir "<<nomPruebaReporte<<endl;
        exit(1);
    }
    fstream arch(nomVendedores,ios::in|ios::out|ios::binary);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomVendedores<<endl;
        exit(1);
    }
    fstream archArticulos(nomArticulos,ios::in|ios::out|ios::binary);
    if(not archArticulos.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomArticulos<<endl;
        exit(1);
    }
    report.precision(2); report<<fixed;
    report<<setw(50)<<"LISTA DE VENDEDORES"<<endl;
    //Varibles 
    struct Vendedor vendedor;
    int sizeVendedor = sizeof(struct Vendedor);
    int numVendedores = contadorStucts(arch,sizeVendedor);
    double montoPagado, montoPagadoConPerdidas, montoStockPerdido;
    for(int i=0;i<numVendedores;i++){ 
        arch.seekg(i*sizeVendedor,ios::beg);
        arch.read(reinterpret_cast<char*>(&vendedor),sizeVendedor);
        encabezado(report);
        report<<right<<setfill('0')<<setw(3)<<i+1<<") "<<setfill(' ')
              <<left<<setw(10)<<vendedor.codigo
              <<setw(48)<<vendedor.nombre
              <<right<<vendedor.porcentaje
              <<setw(15)<<vendedor.cuotaMinima
              <<setw(17)<<vendedor.montoTotalVendido
              <<setw(14)<<vendedor.monoTotalPerdido<<endl;
        report<<left<<setw(5)<<" "<<"ARTICULOS VENDIDOS"<<endl;
        //Imprimimos los articulos Vendidos
        imprimirVentas(report,archArticulos,vendedor.articulosVendidos,
                       vendedor.cantArticulosVendidos);
        report<<left<<setw(5)<<" "<<"ARTICULOS NO VENDIDOS"<<endl;
        //Imprimimos los artiuclos Perdidos
        imprimirVentas(report,archArticulos,vendedor.articulosPerdidos,
                       vendedor.cantArticulosPerdidos);
        montoPagado=((vendedor.montoTotalVendido-vendedor.cuotaMinima)*vendedor.porcentaje)/100;
        montoPagadoConPerdidas=((vendedor.montoTotalVendido+vendedor.monoTotalPerdido-vendedor.cuotaMinima)*vendedor.porcentaje)/100;
        montoStockPerdido=montoPagadoConPerdidas-montoPagado;
        report<<endl<<left<<setw(70)<<"TOTAL PAGADO AL VENDEDOR: "<<right<<setw(10)<<montoPagado<<endl<<left
              <<setw(70)<<"TOTAL PAGADO AL VENDEDOR SI SE UBIERAN VENDIDO TODOS LOS PRODUCTOS: "<<right<<setw(10)<<montoPagadoConPerdidas<<endl<<left
              <<setw(70)<<"TOTAL PERDIDO POR FALTA DE STOCK"<<right<<setw(10)<<montoStockPerdido<<left<<endl;
        linea(report,MAX_LINEA,'=');
    }
}
void imprimirVentas(ofstream& report,fstream& archArticulos,
                    struct ArticuloPedido* articuloPedido,int cant){
    //Variables
    struct Articulo articulo;
    int sizeArticulo = sizeof(struct Articulo);
    int numArticulos  = contadorStucts(archArticulos,sizeArticulo);
    int posArticulo;
    encabezado2(report);
    for(int k=0;k<cant;k++){
        posArticulo=buscarArticulo(archArticulos,numArticulos,articuloPedido[k].codigo);
        archArticulos.seekg(posArticulo*sizeArticulo,ios::beg);
        archArticulos.read(reinterpret_cast<char*>(&articulo),sizeArticulo);
        report<<setw(5)<<" "<<right<<setfill('0')<<setw(3)<<k+1<<") "<<setfill(' ')
              <<left<<setw(10)<<articuloPedido[k].codigo
              <<setw(56)<<articulo.description
              <<right<<setw(7)<<articuloPedido[k].cant
              <<right<<setw(13)<<articuloPedido[k].montoTotal
              <<right<<setw(17)<<articuloPedido[k].fechaUltimoPedido<<endl;
    }
}
int buscarArticulo(fstream& archArticulos,int numArticulos,
                    char* code){
    //Variables 
    struct Articulo articulo;
    int size= sizeof(struct Articulo);
    for (int i = 0; i < numArticulos; i++){
        archArticulos.seekg(i*size,ios::beg);
        archArticulos.read(reinterpret_cast<char*>(&articulo),size);
        if(strcmp(articulo.codigo,code)==0)return i;
    }
    return NO_ENCONTRADO;
}
void actualizarArchivos(const char* nomVentas,const char* nomVendedores,
                        const char* nomArticulos){
    ifstream arch(nomVentas,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se puedo abrir "<<nomVentas<<endl;
        exit(1);
    }
    fstream archVendedores(nomVendedores,ios::in|ios::out|ios::binary);
    if(not archVendedores.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomVendedores<<endl;
        exit(1);
    }
    fstream archArticulos(nomArticulos,ios::in|ios::out|ios::binary);
    if(not archArticulos.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nomArticulos<<endl;
        exit(1);
    }
    //Variables
    char codeArticulo[8],c; int codeVendedor,cant,dd,mm,aa;
    while(true){
        arch.getline(codeArticulo,8,' ');
        if(arch.eof())break;
        arch>>codeVendedor>>cant>>dd>>c>>mm>>c>>aa; arch.get();
        ingresoDeDatos(archVendedores,archArticulos,codeVendedor,
                       codeArticulo,cant,dd,mm,aa);
    } 
}
void ingresoDeDatos(fstream& archVendedores,fstream& archArticulos,
                    int codeVendedor,char* codeArticulo,
                    int cant,int dd,int mm,int aa){
    //Variables
    struct Articulo articulo;
    struct Vendedor vendedor;
    int sizeArticulo = sizeof(struct Articulo); 
    int sizeVendedor = sizeof(struct Vendedor); 
    int numArticulos = contadorStucts(archArticulos,sizeArticulo);
    int numVendedores = contadorStucts(archVendedores,sizeVendedor);
    int posArticulo = buscarArticulo(archArticulos,numArticulos,codeArticulo);
    int posVendedor = buscarVendedor(archVendedores,numVendedores,codeVendedor);
    if(posArticulo!=NO_ENCONTRADO and posVendedor!=NO_ENCONTRADO){
        archVendedores.seekg(posVendedor*sizeVendedor);
        archVendedores.read(reinterpret_cast<char*>(&vendedor),sizeVendedor);
        archArticulos.seekg(posArticulo*sizeArticulo);
        archArticulos.read(reinterpret_cast<char*>(&articulo),sizeArticulo);
        actualizar(articulo,vendedor,cant,dd,mm,aa);
        archVendedores.seekg(posVendedor*sizeVendedor);
        archVendedores.write(reinterpret_cast<const char*>(&vendedor),sizeVendedor);
        archArticulos.seekg(posArticulo*sizeArticulo);
        archArticulos.write(reinterpret_cast<const char*>(&articulo),sizeArticulo);
        archArticulos.flush();
        archVendedores.flush();
    }
}
int buscarVendedor(fstream& archVendedores,int numVendedores,
                   int code){
    //Variables
    struct Vendedor vendedor; 
    int size = sizeof(struct Vendedor); 
    for (int i = 0; i < numVendedores; i++){
        archVendedores.seekg(i*size);
        archVendedores.read(reinterpret_cast<char*>(&vendedor),size);
        if(vendedor.codigo==code)return i;
    }
    return NO_ENCONTRADO;
}
void actualizar(struct Articulo& articulo,struct Vendedor& vendedor,
                int cant,int dd,int mm,int aa){
    //Variables
    int posArticulo; double monto= cant*articulo.precio;
    if(articulo.stock-cant>0){
        //ingreso datos de articulos vendidos
        //Vendedores 
        posArticulo=buscarArticuloPedido(vendedor.articulosVendidos,
                                         vendedor.cantArticulosVendidos,
                                         articulo.codigo);
        updateDatosVendedores(posArticulo,articulo.codigo,vendedor.articulosVendidos,
                              vendedor.cantArticulosVendidos,cant,dd,mm,aa,monto);
        vendedor.montoTotalVendido+=monto;
        //Articulos 
        articulo.stock-=cant;
        articulo.cantArticulosVendidos+=cant;
        articulo.montoVendido+=monto;
    }else{
        //Ingreso datos de articulos perdidos
        //Vendedores
        posArticulo=buscarArticuloPedido(vendedor.articulosPerdidos,
                                         vendedor.cantArticulosPerdidos,
                                         articulo.codigo);
        updateDatosVendedores(posArticulo,articulo.codigo,vendedor.articulosPerdidos,
                              vendedor.cantArticulosPerdidos,cant,dd,mm,aa,monto);
        vendedor.monoTotalPerdido+=monto;
        //Articulos
        articulo.cantArticulosPerdidos+=cant;
        articulo.montoPerdido+=monto;
    }
}
int buscarArticuloPedido(struct ArticuloPedido* articulosPerdidos,
                         int cant,char* code){
    for (int i = 0; i < cant; i++){
        if(strcmp(articulosPerdidos[i].codigo,code)==0)return i;
    }
    return NO_ENCONTRADO;
}
void updateDatosVendedores(int posArticulo,char* code,struct ArticuloPedido* articulo,
                           int& num,int cant,int dd,int mm,int aa,double monto){
    //Variables
    int fecha=aa*10000+mm*100+dd; 
    if(posArticulo!=NO_ENCONTRADO){
        articulo[posArticulo].cant+=cant;
        articulo[posArticulo].montoTotal+=monto;
        if(fecha>articulo[posArticulo].fechaUltimoPedido)
            articulo[posArticulo].fechaUltimoPedido=fecha;
    }else{
        strcpy(articulo[num].codigo,code);
        articulo[num].cant+=cant;
        articulo[num].montoTotal+=monto;
        articulo[num].fechaUltimoPedido=fecha;
        num++;
    }
}