//Author: MAKO
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cmath>
using namespace std;
#include "../header/funciones.h"
#include "../header/Direccion.h"
#include "../header/Pedido.h"
#define NO_ENCONTRADO -1
#define LONGITUD_PSM -77.0833
#define LATITUD_PSM -12.0766
#define MAX_LINEA 80
void crearDirecciones(const char* nomArchBin,const char* nomArch){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"Error al abrir el archivo "<<nomArch<<endl;
        exit(1);
    }
    ofstream archBin(nomArchBin,ios::out|ios::binary);
    if(not archBin.is_open()){
        cout<<"Error al abrir el archivo "<<nomArchBin<<endl;
        exit(1);
    }
    //Variables
    struct Direccion direccion{};
    char c;
    while (true){
        arch.getline(direccion.codigoUsuarios,10,',');
        if(arch.eof())break;
        arch.getline(direccion.direccion,50,',');
        arch.getline(direccion.distrito,20,',');
        arch>>direccion.latitud>>c>>direccion.longitud;
        arch.get();//Retiramos la coma
        archBin.write(reinterpret_cast<const char*>(&direccion),
                    sizeof(struct Direccion));
    }
}
void crearPedidos(const char* nomArchBin,const char* nomArch){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"Error al abrir el archivo "<<nomArch<<endl;
        exit(1);
    }
    //Creamos antes el archivo binario
    crearArchivoBinario(nomArchBin);
    fstream archBin(nomArchBin,ios::in|ios::out|ios::binary);
        if(not archBin.is_open()){  
        cout<<"Error al abrir A el archivo "<<nomArchBin<<endl;
        exit(1);
    }
    //Variables
    int codigo, posCodigo; 
    struct Pedido pedido;
    while(true){
        arch>>codigo;
        if(arch.eof())break;
        //Buscar el codigo
        posCodigo=buscarCodigo(archBin,codigo);
        if(posCodigo!=NO_ENCONTRADO){
            archBin.seekg(posCodigo*sizeof(struct Pedido),ios::beg);
            archBin.read(reinterpret_cast<char*>(&pedido),
                        sizeof(struct Pedido));
            agregarProductos(arch,pedido);
            archBin.seekg(posCodigo*sizeof(struct Pedido),ios::beg);
        }else{
            pedido.codigo=codigo;
            pedido.cantProductos=0;
            pedido.montoTotal=0;
            agregarProductos(arch,pedido);
            archBin.seekg(0,ios::end);
        }
        archBin.write(reinterpret_cast<char*>(&pedido),
                        sizeof(struct Pedido));
        archBin.flush();
    }
}
void crearArchivoBinario(const char* nomArchBin){
    ofstream archBin(nomArchBin,ios::out|ios::binary);
        if(not archBin.is_open()){
        cout<<"Error al abrir A el archivo "<<nomArchBin<<endl;
        exit(1);
    }
}
void agregarProductos(ifstream& arch,struct Pedido &pedido){
    int num;
    double montotal;
    char c;
    while(arch.get()!='\n'){
        num=pedido.cantProductos;
        arch.getline(pedido.productos[num].nombre,90,',');
        arch>>pedido.productos[num].cantidad>>c
            >>pedido.productos[num].precioUnitario;
        montotal=pedido.productos[num].cantidad*
                pedido.productos[num].precioUnitario;
        pedido.montoTotal+=montotal;
        pedido.cantProductos++;
    }
}
int buscarCodigo(fstream& archBin,int codigo){
    //Variables
    struct Pedido pedido;
    int sizePedido, cantPedido;
    sizePedido=sizeof(struct Pedido);
    cantPedido=cantidadEstructuras(archBin,sizePedido);
    for(int i=0;i<cantPedido;i++){
        archBin.read(reinterpret_cast<char*>(&pedido),
                    sizePedido);
        if(archBin.eof())break;
        if(pedido.codigo==codigo)return i;
    }
    return NO_ENCONTRADO;
}
void actualizacionDePedidos(const char* nomArchPedidos,
                        const char* nomArchDirecciones,
                        const char* nomArch){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"Error al abrir el archivo "<<nomArch<<endl;
        exit(1);
    }
    fstream archPedidos(nomArchPedidos,ios::in|ios::out|ios::binary);
        if(not archPedidos.is_open()){  
        cout<<"Error al abrir A el archivo "<<nomArchPedidos<<endl;
        exit(1);
    }
    fstream archDirecciones(nomArchDirecciones,ios::in|ios::binary);
        if(not archDirecciones.is_open()){  
        cout<<"Error al abrir A el archivo "<<nomArchDirecciones<<endl;
        exit(1);
    }
    //Variables
    int hh,mm,codigo;
    char codigoUsuario[7],nombre[30],c;
    while(true){
        arch>>hh;
        if(arch.eof())break;
        arch>>c>>mm>>c;
        arch.getline(nombre,30,',');
        arch.getline(codigoUsuario,8,',');
        arch>>codigo;
        arch.get();//Le quitamos el salto de linea
        ingresoDeDatosEnPedidos(archPedidos,archDirecciones,
                                hh,mm,codigo,codigoUsuario,nombre);
    }
}
void ingresoDeDatosEnPedidos(fstream& archPedidos,
                            fstream& archDirecciones,int hh,int mm,
                            int codigo,char* codigoUsuario,char* nombre){
    //Variables
    int sizePedido, sizeDirecciones, cantPedidos,cantDirecciones;
    int posCodigo, posCodigoUsuario;
    struct Pedido pedido{};
    struct Direccion direccion{};

    sizeDirecciones=sizeof(struct Direccion);
    sizePedido=sizeof(struct Pedido);
    posCodigo=buscarCodigo(archPedidos,codigo); 
    posCodigoUsuario=buscarCodigoUsuario(archDirecciones,codigoUsuario);
    
    if(posCodigo!=NO_ENCONTRADO and posCodigoUsuario!=NO_ENCONTRADO){
        archPedidos.seekg(posCodigo*sizePedido,ios::beg);
        archDirecciones.seekg(posCodigoUsuario*sizeDirecciones,ios::beg);
        archPedidos.read(reinterpret_cast<char*>(&pedido),sizePedido);
        archDirecciones.read(reinterpret_cast<char*>(&direccion),
                        sizeDirecciones);    
        ingresoYcambioDatos(pedido,direccion,hh,mm,codigo,codigoUsuario,
                            nombre);
        archPedidos.seekg(posCodigo*sizePedido,ios::beg);
        archPedidos.write(reinterpret_cast<const char*>(&pedido),
                        sizePedido);
        archPedidos.flush();
    }
}
int buscarCodigoUsuario(fstream& archBin,char* codigoUsuario){
    struct Direccion direccion;
    int sizeDirecciones, cantDirecciones;
    sizeDirecciones=sizeof(struct Direccion);
    cantDirecciones=cantidadEstructuras(archBin,sizeDirecciones);
    for(int i=0;i<cantDirecciones;i++){
        archBin.read(reinterpret_cast<char*>(&direccion),
                    sizeDirecciones);
        if(archBin.eof())break;
        if(strcmp(direccion.codigoUsuarios,codigoUsuario)==0)return i;
    }
    return NO_ENCONTRADO;
}
void ingresoYcambioDatos(struct Pedido &pedido,struct Direccion &direccion,
                        int hh,int mm,int codigo,char* codigoUsuario,
                        char* nombre){
    
    strcpy(pedido.codigoUsuarios,codigoUsuario);
    strcpy(pedido.repartidorRappi,nombre);
    pedido.direccionRappi=direccion;
    pedido.hora=hh*100+mm;
    pedido.distancia=calcularDistancia(direccion.latitud,direccion.longitud);
}
double calcularDistancia(double latitud,double longitud){
    double distancia,componente1,componente2;
    componente1=latitud-LATITUD_PSM;
    componente2=longitud-LONGITUD_PSM;
    distancia=sqrt(pow(componente1,2)+pow(componente2,2));
    return distancia;
}
void ordenarPedidos(const char* nomArchBin){
    fstream archBin(nomArchBin,ios::in|ios::out|ios::binary);
        if(not archBin.is_open()){  
        cout<<"Error al abrir A el archivo "<<nomArchBin<<endl;
        exit(1);
    }
    //Variables
    struct Pedido pedidoI,pedidoK;
    int sizePedido, cantPedido;
    sizePedido=sizeof(struct Pedido);
    cantPedido=cantidadEstructuras(archBin,sizePedido);
    for(int i=0;i<cantPedido-1;i++){
        for(int k=i+1;k<cantPedido;k++){
            archBin.seekg(i*sizePedido,ios::beg);
            archBin.read(reinterpret_cast<char*>(&pedidoI),
                        sizePedido);
            archBin.seekg(k*sizePedido,ios::beg);
            archBin.read(reinterpret_cast<char*>(&pedidoK),sizePedido);
            if(pedidoI.hora>pedidoK.hora or
                pedidoI.hora==pedidoK.hora and 
                pedidoI.distancia<pedidoK.distancia){
                    archBin.seekg(i*sizePedido,ios::beg);
                    archBin.write(reinterpret_cast<const char*>(&pedidoK),
                                sizePedido);
                    archBin.seekg(k*sizePedido,ios::beg);
                    archBin.write(reinterpret_cast<const char*>(&pedidoI),
                                sizePedido);
                    archBin.flush();
                }
        }
    }
}
void emitirReporte(const char* nomArchBin,const char* nomArch){
    ifstream archBin(nomArchBin,ios::in|ios::binary);
    if(not archBin.is_open()){
        cout<<"Error al abrir el archivo "<<nomArchBin<<endl;
        exit(1);
    }
    ofstream arch(nomArch,ios::out);
        if(not arch.is_open()){
        cout<<"Error al abrir A el archivo "<<nomArch<<endl;
        exit(1);
    }
    //Variables
    struct Pedido pedido;
    archBin.seekg(0,ios::beg);
    encabezado(arch);
    while(true){
        archBin.read(reinterpret_cast<char*>(&pedido),
                    sizeof(struct Pedido));
        if(archBin.eof())break;
        arch<<setw(10)<<pedido.codigo
            <<setw(20)<<pedido.repartidorRappi
            <<setfill('0')<<right<<setw(2)<<pedido.hora/100<<":"
            <<pedido.hora%100<<left<<setfill(' ')<<setw(10)<<" "
            <<setw(25)<<pedido.distancia
            <<setw(10)<<pedido.montoTotal<<endl;
        linea(arch,'-');
        arch<<setw(8)<<" "<<"Codigo de Usuario: "
            <<pedido.codigoUsuarios<<endl;
        linea(arch,'-');
        subencabezado(arch);
            arch<<setw(8)<<" "<<setw(20)<<pedido.direccionRappi.direccion
                <<setw(15)<<pedido.direccionRappi.distrito
                <<setw(10)<<pedido.direccionRappi.latitud
                <<setw(10)<<pedido.direccionRappi.longitud<<endl;
        linea(arch,'-');
        subencabezado2(arch);
        for(int j=0;j<pedido.cantProductos;j++){
            arch<<setw(8)<<" "<<setfill('0')<<right<<setw(2)<<j+1<<") "<<left
                <<setfill(' ')<<setw(35)<<pedido.productos[j].nombre
                <<setw(15)<<pedido.productos[j].cantidad
                <<setw(10)<<pedido.productos[j].precioUnitario<<endl;
        }
        linea(arch,'=');
    }
}
void encabezado(ofstream& arch){
    arch<<right<<setw(40)<<"RAPPI_TP"<<endl
        <<setw(45)<<"REPORTE DE PEDIDOS"<<left<<endl;
    linea(arch,'=');
    arch<<setw(10)<<"PEDIDO"
            <<setw(20)<<"NOMBRE RAPPI"
            <<setw(10)<<"HORA"
            <<setw(25)<<"DISTANCIA EUCLIDIANA"
            <<setw(10)<<"PRECIO TOTAL"<<endl;
    linea(arch,'=');
}
void subencabezado(ofstream& arch){
    arch<<setw(8)<<" "<<setw(20)<<"DIRECCION"
        <<setw(15)<<"DISTRITO"
        <<setw(10)<<"LATITUD"
        <<setw(10)<<"LONGITUD"<<endl;
    linea(arch,'-');
}
void subencabezado2(ofstream& arch){
    arch<<right<<setw(40)<<"PRODUCTOS"<<left<<endl;
    linea(arch,'-');
    arch<<setw(8)<<" "<<setw(35)<<"NOMBRE"
        <<setw(15)<<"CANTIDAD"
        <<setw(10)<<"PRECIO UNITARIO"<<endl;
    linea(arch,'-');
}
void linea(ofstream& arch,char signo){
    for(int i=0;i<MAX_LINEA;i++){
        arch<<signo;
    }
    arch<<endl;
}
int cantidadEstructuras(fstream& archBin,int size){
    int cant;
    archBin.seekg(0,ios::end);
    cant=archBin.tellg();
    archBin.seekg(0,ios::beg);
    return cant/size;
}

