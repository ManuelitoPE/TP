// Author: MAKO
#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;
#include"../header/funciones.h"
#define MAX_LINEA 70    
//Leer los datos de libros
void lecturaDeLibros(int& num_libro,int* ARRcodigoLibro,
                    double* ARRprecioLibro,
                    const char* nomArch){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: se produjo un error al abrir el archivo "<<nomArch<<endl;
        exit(1);
    }
    //Variables

    while(true){
        arch>>ARRcodigoLibro[num_libro];
        if(arch.eof())break;
        arch>>ws;
        while(arch.get()!=' ');
        arch>>ARRprecioLibro[num_libro];
        num_libro++;
    }   
}
// Leer los datos de Autores
void lecturaDeAutores(int& num_autores,int* ARRcodigoAutores,
                    int* ARRcodigo_libroAutores,
                    double* ARRporcentajeAutores,const char* nomArch){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: se produjo un error al abrir el archivo "<<nomArch<<endl;
        exit(1);
    }
    //Variables

    while(true){
        arch>>ARRcodigoAutores[num_autores];
        if(arch.eof())break;
        arch>>ARRcodigo_libroAutores[num_autores]
            >>ARRporcentajeAutores[num_autores];
        num_autores++;
    }
}
void datosUsuario(int& fechaI,int& fechaF){
    // Variables
    int dd,mm,aa,ddf,mmf,aaf;
    char c;
    // cout<<setw(30)<<"LIBRERIA LOS LIBROS_TP"<<endl<<endl<<left
    //     <<setw(40)<<"Ingrese dos fechas para el reporte en el formato "
    //     <<"(dd/mm/aaaa)"<<endl;
    // do{
    //     cout<<"Primera fecha: ";
    //     cin>>dd>>c>>mm>>c>>aa;
    //     cout<<"Segunda fecha: ";
    //     cin>>ddf>>c>>mmf>>c>>aaf;
    //     fechaI=comprimirFecha(dd,mm,aa);
    //     fechaF=comprimirFecha(ddf,mmf,aaf);
    // }while(fechaI>fechaF);
    fechaI=20230101;
    fechaF=20231230;
}
int comprimirFecha(int dd,int mm,int aa){
    int fecha=aa*10000+mm*100+dd;
    return fecha;
    //20230911
}
    // De ventas, determinar por cada libro la cantidad total vendida
    // Determinar por cada autor y por cada uno de suslibros vendidos 
    // el monto que recibira por su vental
void actualizacionPorVentas(int fechaI,int fechaF,int num_libro,
                        int num_autores,int* ARRcodigoLibro, 
                        double* ARRprecioLibro,int* ARRcodigoAutores,
                        int* ARRcodigo_libroAutores,
                        double* ARRporcentajeAutores,
                        int* ARRcantidad,double* ARRrecaudado,
                        double* ARRautor_recibido,const char* nomArch){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: se produjo un error al abrir el archivo "<<nomArch<<endl;
        exit(1);
    }
    //Variables
    int fecha,dd,mm,aa,codigoLibro,cantidad;
    int pos;
    char c;
    while(true){    
        arch>>dd>>c>>mm>>c>>aa;
        if(arch.eof())break;
        fecha=comprimirFecha(dd,mm,aa);
        if(fecha>=fechaI and fecha<=fechaF){
            arch>>codigoLibro>>cantidad;
            //Buscamos la posicion del libro
            pos=buscarLibro(codigoLibro,ARRcodigoLibro,num_libro);
            ARRcantidad[pos]+=cantidad;
            ARRrecaudado[pos]+=ARRprecioLibro[pos]*cantidad;
        }
        while(arch.get()!='\n');
    }
}
int buscarLibro(int codigoLibro,int* ARRcodigoLibro,int num_libro){
    int i;
    for(i=0;i<num_libro;i++){
        if(ARRcodigoLibro[i]==codigoLibro)break;
    }
    return i;
}
    // Emitir reporte
void emitirReporte(int fechaI,int fechaF,int num_libro,
                int num_autores,int* ARRcodigoLibro, 
                double* ARRprecioLibro,int* ARRcodigoAutores,
                int* ARRcodigo_libroAutores,
                double* ARRporcentajeAutores,
                int* ARRcantidad,double* ARRrecaudado,
                double* ARRautor_recibido,const char* nomArch){
    ofstream arch(nomArch,ios::out);
    if(not arch.is_open()){
        cout<<"ERROR: se produjo un error al abrir el archivo "<<nomArch<<endl;
        exit(1);
    }    
    arch.precision(2);
    arch<<fixed;
    encabezado(arch,fechaF,fechaI);
    for(int i=0;i<num_libro;i++){
        sub_encabezado(arch,ARRcodigoLibro[i],ARRcantidad[i],
                    ARRprecioLibro[i],ARRrecaudado[i],i);
        sub_encabezado_2(arch);
        for(int j=0;j<num_autores;j++){
            if(ARRcodigo_libroAutores[j]==ARRcodigoLibro[i]){
                arch<<setw(5)<<" "<<ARRcodigoAutores[j]<<setw(17)<<" "
                    <<setw(20)<<ARRporcentajeAutores[j]
                    <<(ARRporcentajeAutores[j]*ARRrecaudado[i])/100
                    <<endl;
            }
        }
        linea(arch,MAX_LINEA,'=');  
    }
}
void encabezado(ofstream& arch,int fechaF,int fechaI){
    int dd,mm,aa,ddf,mmf,aaf;
    decomprimirFechas(dd,mm,aa,fechaI);
    decomprimirFechas(ddf,mmf,aaf,fechaF);
    //2023-12-22
    arch<<setw(45)<<"LIBRERIA LOS LIBROS_TP"<<endl<<right<<endl
        <<setw(35)<<"VENTA DE LIBROS EN EL RANGO "
        <<setfill('0')<<right<<setw(2)<<dd<<'/'<<mm<<'/'
        <<aa<<setfill(' ')<<left<<" AL "<<setfill('0')<<right
        <<ddf<<'/'<<mmf<<'/'<<aaf<<endl<<setfill(' ')<<left;
    linea(arch,MAX_LINEA,'=');
}
void linea(ofstream& arch,int num,char signo){
    for (int i = 0; i < num; i++){
        arch<<signo;
    }
    arch<<endl;
}
void decomprimirFechas(int& dd,int& mm,int& aa,int fecha){
    aa=fecha/10000;
    fecha%=10000;
    mm=fecha/100;
    fecha%=100;
    dd=fecha;
}
void sub_encabezado(ofstream& arch,int ARRcodigoLibro,int ARRcantidad,
                    double ARRprecioLibro,double ARRrecaudado,int i){
    arch<<setfill('0')<<right<<setw(2)<<i+1<<")"<<setfill(' ')<<left
        <<setw(2)<<" "<<setw(15)<<"LIBRO"<<setw(15)<<"CANTIDAD"
        <<setw(15)<<"PRECIO"<<setw(15)<<"MONTO RECAUDADO"<<endl
        <<setw(5)<<" "<<setw(15)<<ARRcodigoLibro<<setw(15)<<ARRcantidad
        <<setw(15)<<ARRprecioLibro<<setw(15)<<ARRrecaudado<<endl;
}
void sub_encabezado_2(ofstream& arch){
    linea(arch,MAX_LINEA,'-');
    arch<<setw(5)<<" "<<"REGALIAS PARA LOS AUTORES"<<endl;
    linea(arch,MAX_LINEA,'-');
    arch<<setw(5)<<" "<<setw(15)<<"AUTOR"<<setw(25)<<"PORCENTAJE A RECIBIR"
        <<setw(15)<<"MONTO A RECIBIR"<<endl;
}