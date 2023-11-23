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
            archBin.seekg(0,ios::end);
            pedido.codigo=codigo;
            pedido.cantProductos=0;
            pedido.montoTotal=0;
            agregarProductos(arch,pedido);
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
    int sizePedido, cantPedido, posCodigo;
    sizePedido=sizeof(struct Direccion);
    cantPedido=cantidadEstructuras(archBin,sizePedido);
    archBin.seekg(0,ios::beg);
    for(int i=0;i<cantPedido;i++){
        archBin.read(reinterpret_cast<char*>(&pedido),
                    sizePedido);
        if(pedido.codigo==codigo)return i;
    }
    return NO_ENCONTRADO;
}
void emitirReporte(const char* nomArchBin){
    ifstream archBin(nomArchBin,ios::in|ios::binary);
    if(not archBin.is_open()){
        cout<<"Error al abrir el archivo "<<nomArchBin<<endl;
        exit(1);
    }
    //Variables
    struct Pedido pedido;
    int sizePedido, cantPedido;
    sizePedido=sizeof(struct Pedido);
    // cantPedido=cantidadEstructuras(archBin,sizePedido);
    archBin.seekg(0,ios::beg);
    while(true){
        archBin.read(reinterpret_cast<char*>(&pedido),
                    sizePedido);
        if(archBin.eof())break;
        cout<<pedido.codigo<<" "
            <<pedido.cantProductos<<" "
            <<pedido.montoTotal<<" "<<endl;
        for(int j=0;j<pedido.cantProductos;j++){
            cout<<pedido.productos[j].nombre<<" "
                <<pedido.productos[j].cantidad<<" "
                <<pedido.productos[j].precioUnitario<<" "<<endl;
        }
    }
    // //Variables
    // struct Direccion direccion;
    // int sizeDireccion, cantDireccion;
    // sizeDireccion=sizeof(struct Direccion);
    // cantDireccion=cantidadEstructuras(archBin,sizeDireccion);
    // archBin.seekg(0,ios::beg);
    // for(int i=0;i<cantDireccion;i++){
    //     archBin.read(reinterpret_cast<char*>(&direccion),
    //                 sizeDireccion);
    //     if(archBin.eof())break;
    //     cout<<direccion.codigoUsuarios<<" "
    //         <<direccion.direccion<<" "
    //         <<direccion.distrito<<" "
    //         <<direccion.latitud<<" "
    //         <<direccion.longitud<<endl;
    // }
}
int cantidadEstructuras(fstream& archBin,int size){
    int cant;
    archBin.seekg(0,ios::end);
    cant=archBin.tellg();
    archBin.seekg(0,ios::beg);
    return cant/size;
}

