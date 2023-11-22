//Author: MAKO
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstring>
using namespace std;
#include"../header/funciones.h"
#include "../header/Direccion.h"
#include "../header/Pedido.h"
#define NO_ENCONTRADO -1
#define MAX_LINEA 100
void ingresoDatosDireccion(struct Direccion *direccion,int& cant,
                            const char* nomArch){
    ifstream arch(nomArch, ios::in);
    if(not arch.is_open()){
        cout<<"Error al abrir el archivo "<<nomArch<<endl;
        exit(1);
    }
    //Variables 
    double num;
    char c;
    while(true){
        direccion[cant].codigoUsuarios=leeCadenaExacta(arch,',');
        if(arch.eof())break;
        direccion[cant].direccion=leeCadenaExacta(arch,',');
        direccion[cant].distrito=leeCadenaExacta(arch,',');
        arch>>num>>c>>num;
        arch.get(); //Retiro el salto de linea
        cant++;
    }
}
char* leeCadenaExacta(ifstream& arch,char delimitador){
    char buffer[100],*ptr;
    arch.getline(buffer,100,',');
    if(arch.eof())return nullptr;
    ptr=new char[strlen(buffer)+1];
    strcpy(ptr,buffer);
    return ptr;
}
void ingresoDatosPedido(struct Pedido *pedido,int& cant,
                            const char* nomArch){
    ifstream arch(nomArch, ios::in);
    if(not arch.is_open()){
        cout<<"Error al abrir el archivo "<<nomArch<<endl;
        exit(1);
    }
    //Variables 
    int  num,codigo,posPedido,aux=0;
    double monto;
    char c,*nombre;
    while(true){
        arch>>codigo;
        if(arch.eof())break;
        posPedido=buscarPedido(pedido,cant,codigo);
        if(posPedido!=NO_ENCONTRADO){
            asignacionProductos(arch,pedido[posPedido],posPedido);
        } else{
            pedido[cant].codigo=codigo;
            pedido[cant].productos=new struct ProductoPedido[10]{};
            asignacionProductos(arch,pedido[cant],cant);
            cant++;
        } 
    }
}
void asignacionProductos(ifstream& arch, struct Pedido &pedido,int cant){
    int num;
    char c;
    double monto;
    monto=pedido.montoTotal;
    while(arch.get()!='\n'){
            num=pedido.cantProductos;
            pedido.productos[num].nombre=leeCadenaExacta(arch,',');
            arch>>pedido.productos[num].cantidad>>c>>
                pedido.productos[num].precioUnitario;
            monto+=pedido.productos[num].cantidad*
                    pedido.productos[num].precioUnitario;
            pedido.cantProductos++;
        }
        pedido.montoTotal=monto;
}
void actualizarEstructuras(struct Pedido *pedido,
                        struct Direccion *direccion,int num_direccion,
                        int num_pedido,
                        const char* nomArch){
    ifstream arch(nomArch, ios::in);
    if(not arch.is_open()){
        cout<<"Error al abrir el archivo "<<nomArch<<endl;
        exit(1);
    }
    //Variables
    int hh,mm,codigo;
    char c,*nombre,*codigoUsuario;    
    while(true){
        arch>>hh;
        if(arch.eof())break;
        arch>>c>>mm>>c;
        nombre=leeCadenaExacta(arch,',');
        codigoUsuario=leeCadenaExacta(arch,',');
        arch>>codigo;
        ingresoDeDatos(hh,mm,codigo,nombre,codigoUsuario,direccion,
                        pedido,num_direccion,num_pedido);
    }            
}
void ingresoDeDatos(int hh,int mm,int codigo,char *nombre,
                    char* codigoUsuario,struct Direccion* direccion,
                    struct Pedido* pedido,int num_direccion,
                    int num_pedido){
    //Variables 
    int posDireccion,posPedido;
    posDireccion=buscarDireccion(direccion,num_direccion,codigoUsuario);
    posPedido=buscarPedido(pedido,num_pedido,codigo);
    //Ingreso de datos
    if(posDireccion!=NO_ENCONTRADO and posPedido!=NO_ENCONTRADO){
        pedido[posPedido].hora=hh*100+mm;
        pedido[posPedido].repartidorRappi=nombre;
        pedido[posPedido].codigoUsuario=codigoUsuario;
        pedido[posPedido].distrito=direccion[posDireccion].distrito;
        pedido[posPedido].direccion=direccion[posDireccion].direccion;
    }
}
int buscarDireccion(struct Direccion *direccion,int num_direccion,
                    char* codigoUsuario){
    for(int i=0; i<num_direccion;i++){
        if(strcmp(direccion[i].codigoUsuarios,codigoUsuario)==0)
            return i;
    }
    return NO_ENCONTRADO;
}
int buscarPedido(struct Pedido *pedido,int num_pedido,int codigo){
    for(int i=0; i<num_pedido;i++){
        if(pedido[i].codigo==codigo)
            return i;
    }
    return NO_ENCONTRADO;
}
void emitirReporte(struct Pedido *pedido,int num_pedido,
                const char* nomArch){
    ofstream arch(nomArch, ios::out);
    if(not arch.is_open()){
        cout<<"Error al abrir el archivo "<<nomArch<<endl;
        exit(1);
    }
    arch.precision(2);
    arch<<fixed;
    encabezado(arch);
    for(int i=0;i<num_pedido;i++){
        arch<<left<<"Pedido: "<<pedido[i].codigo<<" Nombre: "
            <<setw(30)<<pedido[i].repartidorRappi<<" Hora:"
            <<setw(2)<<right<<setfill('0')<<pedido[i].hora/100<<':'
            <<pedido[i].hora%100<<left<<setfill(' ')<<endl
            <<setw(10)<<" "<<"Destino: "<<pedido[i].distrito<<", "
            <<pedido[i].direccion<<endl
            <<setw(10)<<" "<<"Usuario: "<<pedido[i].codigoUsuario<<endl<<
            "Datos de la Boleta:"<<endl;
        subEncabezado(arch);
        for(int j=0;j<pedido[i].cantProductos;j++){
            arch<<setw(40)<<pedido[i].productos[j].nombre
                <<setw(15)<<pedido[i].productos[j].precioUnitario
                <<setw(10)<<pedido[i].productos[j].cantidad
                <<setw(10)<<pedido[i].productos[j].precioUnitario*
                            pedido[i].productos[j].cantidad<<endl;
        }
        linea(arch,'-');
        arch<<setw(50)<<"Resumen: "<<pedido[i].cantProductos<<" items"
            <<right<<setw(18)<<pedido[i].montoTotal<<endl<<left;
        linea(arch,'=');
    }
    pieDeReporte(arch,pedido,num_pedido);
}
void encabezado(ofstream& arch){
    arch<<setw(50)<<right<<"TP_RAPPI"<<left<<endl
        <<"REPORTE DE PEDIDOS PARA EL DIA DE HOY"<<endl;
    linea(arch,'=');
}
void subEncabezado(ofstream& arch){
    arch<<setw(35)<<"PRODUCTO"<<setw(18)<<"PRECIO UNITARIO"
        <<setw(10)<<"CANTIDAD"<<setw(10)<<"PRECIO TOTAL"<<endl;
    linea(arch,'-');
}
void linea(ofstream& arch,char signo){
    for(int i=0; i<MAX_LINEA;i++){
        arch<<signo;
    }
    arch<<endl;
}
void pieDeReporte(ofstream& arch,struct Pedido *pedido, int num){
    double montoTOTAl=0;
    for(int i=0; i<num;i++){
        montoTOTAl+=pedido[i].montoTotal;
    }
    arch<<"Total Vendido S/."<<montoTOTAl<<endl;
    linea(arch,'=');
}