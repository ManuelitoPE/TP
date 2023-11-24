#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "../header/funciones.h"
#include "../header/Articulo.h"
#include "../header/Vendedor.h"
#define NO_ENCONTRADO -1
#define MAX_LINEA 80
void leerDatosArticulos(const char* nomArch,const char* nomArchBin){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"Error: Se produjo un error al abrir "<<nomArch<<endl;
        exit(1);
    }
    ofstream archBin(nomArchBin,ios::out|ios::binary);
    if(not archBin.is_open()){
        cout<<"Error: Se produjo un error al abrir "<<nomArchBin<<endl;
        exit(1);
    }
    //Variables
    char codigo[8],descripcion[70];
    double precio;
    struct Articulo articulo;
    while(true){
        arch.getline(codigo,10,',');
        if(arch.eof())break;
        arch.getline(descripcion,70,',');
        arch>>precio;
        arch.get();
        strcpy(articulo.codigo,codigo);
        strcpy(articulo.descripcion,descripcion);
        articulo.precio=precio;
        articulo.cantVendido=0;
        articulo.montoVendido=0;
        archBin.write(reinterpret_cast<const char*>(&articulo),
                    sizeof(struct Articulo));
    }
}
void leerDatosVendedores(const char* nomArch,const char* nomArchBin){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"Error: Se produjo un error al abrir "<<nomArch<<endl;
        exit(1);
    }
    ofstream archBin(nomArchBin,ios::out|ios::binary);
    if(not archBin.is_open()){
        cout<<"Error: Se produjo un error al abrir "<<nomArchBin<<endl;
        exit(1);
    }
    //Variables
    char nombre[40],c;
    int codigo;
    double porcentaje,cuota;
    struct Vendedor vendedor;
    while(true){
        arch>>codigo;
        if(arch.eof())break;
        arch.get();
        arch.getline(nombre,40,',');
        arch>>porcentaje>>c>>cuota;
        arch.get();
        vendedor.codigo=codigo;
        strcpy(vendedor.nombre,nombre);
        vendedor.cuotaMinima=cuota;
        vendedor.porcentaje=porcentaje;
        vendedor.cantElementos=-1;
        vendedor.montoTotal=0;
        vendedor.SuperoCuotaMinima=true;
        archBin.write(reinterpret_cast<const char*>(&vendedor),
                    sizeof(struct Vendedor));
    }
}
void actualizarEstrucutras(const char* nomArchVendedores,
                    const char* nomArchArticulos,
                    const char* nomArch){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"Error: Se produjo un error al abrir "<<nomArch<<endl;
        exit(1);
    }
    fstream archVendedores(nomArchVendedores,ios::out|ios::in|ios::binary);
    if(not archVendedores.is_open()){
        cout<<"Error: Se produjo un error al abrir "<<nomArchVendedores<<endl;
        exit(1);
    }
    fstream archArticulos(nomArchArticulos,ios::out|ios::in|ios::binary);
    if(not archArticulos.is_open()){
        cout<<"Error: Se produjo un error al abrir "<<nomArchArticulos<<endl;
        exit(1);
    }
    //Variables
    char codigo[8];
    int codigoVendedor,cant;
    while(true){
        arch>>codigo;
        if(arch.eof())break;
        arch>>codigoVendedor>>cant;
        ingresoDeDatos(codigo,codigoVendedor,cant,archArticulos,
                    archVendedores);
    }
}
void ingresoDeDatos(char* codigo,int codigoVendedor,int cant,
                    fstream& archArticulos,fstream& archVendedores){
    //Variables
    int sizeArticulos,sizeVendedores,posVendedor,posArticulo;
    int cantArticulos,cantVendedores;
    struct Vendedor vendedor;
    struct Articulo articulo;
    sizeArticulos=sizeof(struct Articulo);
    sizeVendedores=sizeof(struct Vendedor);
    cantArticulos=cantidadEstructuras(archArticulos,sizeArticulos);
    cantVendedores=cantidadEstructuras(archVendedores,sizeVendedores);
    posArticulo=buscarArticulo(archArticulos,cantArticulos,codigo);
    posVendedor=buscarVendedor(archVendedores,cantVendedores,codigoVendedor);
    if(posArticulo!= NO_ENCONTRADO and posVendedor!=NO_ENCONTRADO){
        archArticulos.seekg(posArticulo*sizeArticulos,ios::beg);
        archVendedores.seekg(posVendedor*sizeVendedores,ios::beg);
        archArticulos.read(reinterpret_cast<char*>(&articulo),sizeArticulos);
        archVendedores.read(reinterpret_cast<char*>(&vendedor),sizeVendedores);
        actualizar(vendedor,articulo,cant);
        archArticulos.seekg(posArticulo*sizeArticulos,ios::beg);
        archVendedores.seekg(posVendedor*sizeVendedores,ios::beg);
        archArticulos.write(reinterpret_cast<const char*>(&articulo),
                            sizeArticulos);
        archVendedores.write(reinterpret_cast<const char*>(&vendedor),
                            sizeVendedores);
        archArticulos.flush();
        archVendedores.flush();
    }
}
int cantidadEstructuras(fstream& arch,int size){
    int cant;
    arch.seekg(0,ios::end);
    cant=arch.tellg();
    arch.seekg(0,ios::beg);
    return cant/size;
}
int buscarArticulo(fstream& archArticulos,int cantArticulos,char* codigo){
    struct Articulo articulo;
    for(int i=0;i<cantArticulos;i++){
        archArticulos.read(reinterpret_cast<char*>(&articulo),
                            sizeof(struct Articulo));
        if(archArticulos.eof())break;
        if(strcmp(articulo.codigo,codigo)==0)return i;
    }
    return NO_ENCONTRADO;
}
int buscarVendedor(fstream& archVendedores,int cantVendedores,int codigoVendedor){
    struct Vendedor vendedor;
    for(int i=0;i<cantVendedores;i++){
        archVendedores.read(reinterpret_cast<char*>(&vendedor),
                            sizeof(struct Vendedor));
        if(archVendedores.eof())break;
        if(vendedor.codigo==codigoVendedor)return i;
    }
    return NO_ENCONTRADO;
}
void actualizar(struct Vendedor& vendedor,struct Articulo &articulo,int cant){
    //Variables
    int posArticulo;
    posArticulo=buscarArticulo(vendedor.articulosVendidos,vendedor.cantElementos,
                                articulo.codigo);
    //Actualizamos Articulo
    articulo.cantVendido+=cant;
    articulo.montoVendido+=cant*articulo.precio;
    //Actualizamos Vendedor
    if(posArticulo==NO_ENCONTRADO){
        vendedor.cantElementos++;
        posArticulo=vendedor.cantElementos;
        strcpy(vendedor.articulosVendidos[posArticulo].codigo
                ,articulo.codigo);
    }
    vendedor.articulosVendidos[posArticulo].cantVendido+=cant;
    vendedor.articulosVendidos[posArticulo].montoTotalVendido+=
                cant*articulo.precio;
    vendedor.articulosVendidos[posArticulo].pagoVendedor+=
                (cant*articulo.precio*vendedor.porcentaje)/100;
    vendedor.montoTotal+=(cant*articulo.precio*vendedor.porcentaje)/100;
}
int buscarArticulo(struct ArticuloVendido *articulosVendidos,
                int cant, char* codigo){
    for(int i=0;i<cant;i++){
        if(strcmp(articulosVendidos[i].codigo,codigo)==0)return i;
    }
    return NO_ENCONTRADO;
}
void correccionVendedores(const char* nomArchBin){
    fstream archBin(nomArchBin,ios::out|ios::in|ios::binary);
    if(not archBin.is_open()){
        cout<<"Error: Se produjo un error al abrir "<<nomArchBin<<endl;
        exit(1);
    }
    //Variables
    int sizeVendedores,cantVendedores;
    struct Vendedor vendedor;
    sizeVendedores=sizeof(struct Vendedor);
    cantVendedores=cantidadEstructuras(archBin,sizeVendedores);
    for (int i = 0; i < cantVendedores; i++){
        archBin.seekg(i*sizeVendedores,ios::beg);
        archBin.read(reinterpret_cast<char*>(&vendedor),sizeVendedores);
        vendedor.SuperoCuotaMinima=vendedor.cuotaMinima<vendedor.montoTotal;
        if(vendedor.SuperoCuotaMinima){
            vendedor.montoTotal-=vendedor.cuotaMinima;
        }
        archBin.seekg(i*sizeVendedores,ios::beg);
        archBin.write(reinterpret_cast<const char*>(&vendedor),
                    sizeVendedores);
        archBin.flush();
    }
}
void ordenarVendedores(const char* nomArchBin){
    fstream archBin(nomArchBin,ios::out|ios::in|ios::binary);
    if(not archBin.is_open()){
        cout<<"Error: Se produjo un error al abrir "<<nomArchBin<<endl;
        exit(1);
    }
    int sizeVendedores,cantVendedores;
    struct Vendedor vendedorI,vendedorK;
    sizeVendedores=sizeof(struct Vendedor);
    cantVendedores=cantidadEstructuras(archBin,sizeVendedores);
    for(int i=0;i<cantVendedores-1;i++){
        for(int k=i+1;k<cantVendedores;k++){
            archBin.seekg(i*sizeVendedores,ios::beg);
            archBin.read(reinterpret_cast<char*>(&vendedorI),
                        sizeVendedores);
            archBin.seekg(k*sizeVendedores,ios::beg);
            archBin.read(reinterpret_cast<char*>(&vendedorK),
                        sizeVendedores);
            if(vendedorI.montoTotal<vendedorK.montoTotal){
                archBin.seekg(i*sizeVendedores,ios::beg);
                archBin.write(reinterpret_cast<const char*>(&vendedorK),
                        sizeVendedores);
                archBin.seekg(k*sizeVendedores,ios::beg);
                archBin.write(reinterpret_cast<const char*>(&vendedorI),
                        sizeVendedores);
                archBin.flush();
            }
        }
    } 
}
void emitirReporte(const char* nomArchBin,const char* nomArch){
    ifstream archBin(nomArchBin,ios::in|ios::binary);
    if(not archBin.is_open()){
        cout<<"Error: Se produjo un error al abrir "<<nomArchBin<<endl;
        exit(1);
    } 
    ofstream arch(nomArch,ios::out);
    if(not arch.is_open()){
        cout<<"Error: Se produjo un error al abrir "<<nomArch<<endl;
        exit(1);
    } 
    //Variables
    int num=1,num2=1;
    struct Vendedor vendedor;
    encabezado(arch);
    while(true){
        archBin.read(reinterpret_cast<char*>(&vendedor),
                            sizeof(struct Vendedor));
        if(archBin.eof())break;
        subEncabezado(arch);
        arch<<right<<setfill('0')<<setw(2)<<num<<")   "
            <<setfill(' ')<<left
            <<setw(10)<<vendedor.codigo
            <<setw(30)<<vendedor.nombre
            <<setw(10)<<vendedor.porcentaje
            <<setw(10)<<vendedor.cuotaMinima;
        if(!vendedor.SuperoCuotaMinima){
            arch<<"NO SUPERO LA CUOTA"<<endl;
        } else{
            num2=1;
            subEncabezado2(arch);
            for(int i=0;i<vendedor.cantElementos;i++){
                arch<<setw(10)<<" "<<right<<setfill('0')<<setw(2)<<num2<<")   "
                    <<setfill(' ')<<left
                    <<setw(10)<<vendedor.articulosVendidos[i].codigo
                    <<setw(60)<<" "
                    <<setw(10)<<vendedor.articulosVendidos[i].cantVendido
                    <<setw(10)<<vendedor.articulosVendidos[i].montoTotalVendido
                    <<setw(10)<<vendedor.articulosVendidos[i].pagoVendedor<<endl;
                }
            }
        linea(arch,'=');
        num++;
    }
}
void encabezado(ofstream& arch){
    arch<<setw(50)<<"TIENDA POR DEPARTAMENTOS TP"<<endl<<endl
        <<setw(50)<<"DETALLE DE PAGOS A LOS VENDEDORES"<<endl;
    linea(arch,'=');
}
void subEncabezado(ofstream& arch){
    arch<<setw(6)<<"No."<<setw(40)<<"VENDEDOR"<<"%"
            <<setw(10)<<"POR VENTAS"
            <<setw(20)<<"CUOTA MINIMA"
            <<setw(10)<<"OBSERVACION"<<endl;
    linea(arch,'-');   
}
void subEncabezado2(ofstream& arch){
    arch<<setw(6)<<"ARTICULOS VENDIDOS"<<endl
        <<setw(4)<<"No."<<setw(70)<<"ATICULO"
        <<setw(10)<<"CANTIDAD"
        <<setw(10)<<"TOTAL"
        <<setw(10)<<"PAGO POR VENTAS"<<endl;
}
void linea(ofstream& arch,char signo){
    for(int i=0;i<MAX_LINEA;i++){
        arch<<signo;
    }
    arch<<endl;
}