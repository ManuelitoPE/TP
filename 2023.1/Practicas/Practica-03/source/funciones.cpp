#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstring>
using namespace std;
#include"../header/funciones.h"
//Ordenar por ascendente por el distrito, descendente por nombre
//almacen
void leerDatoAlmacen(const char* nomArch,char** ARRcodigoAlmacen,
                    char** ARRnombreAlmacen,int* ARRpostalAlmacen,
                    int& num_almacen){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"Error: Se produjo un error al abrir el arch "<<nomArch<<endl;
        exit(1);
    }
    while(true){
        ARRcodigoAlmacen[num_almacen]=leerCadenaExacta(arch,',');
        if(arch.eof())break;
        ARRnombreAlmacen[num_almacen]=leerCadenaExacta(arch,',');
        arch>>ARRpostalAlmacen[num_almacen];
        arch.get();  
        ordenar(num_almacen,ARRcodigoAlmacen,ARRnombreAlmacen,
                ARRpostalAlmacen,ARRnombreAlmacen[num_almacen],
                ARRpostalAlmacen[num_almacen],
                ARRcodigoAlmacen[num_almacen]);
    }
}
char* leerCadenaExacta(ifstream& arch,char delimitador){
    char buff[100],*ptr;
    arch.getline(buff,60,delimitador);
    ptr=new char[strlen(buff)+1];
    strcpy(ptr,buff);
    return ptr;
}
//Ordenar por ascendente por el distrito, descendente por nombre
//almacen
void ordenar(int& num_almacen,char** ARRcodigoAlmacen,
            char** ARRnombreAlmacen,int* ARRpostalAlmacen,
            char* nombre,int postal,char* codigo){
    // int i=num_almacen-1;
    // while(i>=0 and ARRpostalAlmacen[i]>postal or
    //         ARRpostalAlmacen[i]==postal &&  
    //         strcmp(ARRnombreAlmacen[i],nombre)<0){
    //             ARRcodigoAlmacen[i+1]=ARRcodigoAlmacen[i];
    //             ARRnombreAlmacen[i+1]=ARRnombreAlmacen[i];
    //             ARRpostalAlmacen[i+1]=ARRpostalAlmacen[i];
    //             i--;
    // }
    int i;
    for(i=num_almacen-1;i>=0;i--){
        if(ARRpostalAlmacen[i]<postal or
            ARRpostalAlmacen[i]==postal &&  
            strcmp(ARRnombreAlmacen[i],nombre)>0)break;

            ARRcodigoAlmacen[i+1]=ARRcodigoAlmacen[i];
            ARRnombreAlmacen[i+1]=ARRnombreAlmacen[i];
            ARRpostalAlmacen[i+1]=ARRpostalAlmacen[i];
        
    }
    ARRcodigoAlmacen[i+1]=codigo;
    ARRnombreAlmacen[i+1]=nombre;
    ARRpostalAlmacen[i+1]=postal;
    num_almacen++;
}
void leerDatosProductos(const char* nomArch,char** ARRcodigoProducto,
                    char** ARRnombreProducto,int& num_producto){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"Error: Se produjo un error al abrir el arch "<<nomArch<<endl;
        exit(1);
    }

    while(true){
        ARRcodigoProducto[num_producto]=leerCadenaExacta(arch,',');
        if(arch.eof())break;
        ARRnombreProducto[num_producto]=leerCadenaExacta(arch,'\n');
        arch.get();  
        num_producto++;
    }

}
void reportePruebaAlamcenes(const char* nomArch,char** ARRcodigoAlmacen,
                    char** ARRnombreAlmacen,int* ARRpostalAlmacen,
                    int num_almacen){
    ofstream arch(nomArch,ios::out);
    if(not arch.is_open()){
        cout<<"Error: Se produjo un error al abrir el arch "<<nomArch<<endl;
        exit(1);
    }
    arch<<"Reporte de almacenes ordenado"<<endl;
    arch<<"ALMACENES"<<setw(20)<<"NOMBRE"<<setw(23)<<"POSTAL"<<endl;
    for(int i=0;i<num_almacen;i++){
            arch<<setw(5)<<ARRcodigoAlmacen[i]
                <<setw(5)<<" "<<setw(35)<<left<<ARRnombreAlmacen[i]
                <<setw(10)<<ARRpostalAlmacen[i]<<endl;
    }
}
void leerStockProductos(const char* nomArch,
                    char** ARRcodigo_productoStock,
                    char** ARRcodigo_almacenStock
                    ,double* ARRstockInicialStock,int& num_stock){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"Error: Se produjo un error al abrir el arch "<<nomArch<<endl;
        exit(1);
    }
    while (true){
        ARRcodigo_productoStock[num_stock]=leerCadenaExacta(arch,' ');
        if(arch.eof())break;
        arch>>ws;
        ARRcodigo_almacenStock[num_stock]=leerCadenaExacta(arch,' ');
        arch>>ARRstockInicialStock[num_stock];
        arch.get(); 
        num_stock++;
    }
}
void reporteSimpleStock(const char* nomArch,
                    char** ARRcodigo_productoStock,
                    char** ARRcodigo_almacenStock
                    ,double* ARRstockInicialStock,int num_stock){
    ofstream arch(nomArch,ios::out);
    if(not arch.is_open()){
        cout<<"Error: Se produjo un error al abrir el arch "<<nomArch<<endl;
        exit(1);
    }
    arch<<"Reporte de Stock"<<endl;
    arch<<"CODIGO PRODUCTO"<<setw(20)<<"CODIGO ALMACEN"
        <<setw(23)<<"STOCK"<<endl;
    for(int i=0;i<num_stock;i++){
            arch<<setw(4)<<" "<<setw(10)<<ARRcodigo_productoStock[i]
                <<setw(10)<<" "<<setw(30)<<left<<ARRcodigo_almacenStock[i]
                <<ARRstockInicialStock[i]<<endl<<right;
    }
}
void actualizacionDatos(int num_almacen,int num_producto,int num_stock,
                    int* ARRpostalAlmacen,char** ARRnombreAlmacen,
                    char** ARRcodigoAlmacen,
                    char** ARRcodigoProducto,char**ARRnombreProducto,
                    char** ARRcodigo_productoStock,
                    char** ARRcodigo_almacenStock,
                    double* ARRstockInicialStock,
                    double* ARRingreso,double* ARRsalida,
                    double* ARRenviado,
                    double* ARRrecibido,double* ARRstockFinal,
                    char** observaciones,const char* nomArch){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"Error: Se produjo un error al abrir el arch "<<nomArch<<endl;
        exit(1);
    }
    //Variables
    char almacenREF[20],c,codigoREF[20],tipo,almacenDEST[20];
    int dd,mm,aa,hh,min,ss,pos;
    double cantidad;
    while(true){
        arch>>almacenREF;
        if(arch.eof())break;
        arch>>ws>>dd>>c>>mm>>c>>aa;
        while(true){
            arch>>ws>>hh>>c>>min>>c>>ss>>ws;
            arch>>codigoREF>>cantidad>>tipo;
            if(tipo=='T')arch>>almacenDEST;
            //Buscamos posicion 
            pos=buscarPosicion(almacenREF,codigoREF,
                        ARRcodigo_productoStock,
                        ARRcodigo_almacenStock,num_stock);
            sumamosCategoria(pos,tipo,ARRingreso,ARRsalida,
                             ARRenviado,
                            ARRrecibido,observaciones,cantidad,
                            almacenDEST,codigoREF,
                            ARRcodigo_productoStock,
                            ARRcodigo_almacenStock,num_stock);
            if(arch.get()=='\n')break;
        }
    }
    calculoStockFinal( ARRingreso, ARRsalida,
                    ARRenviado,
                    ARRrecibido, ARRstockFinal,
                    observaciones, num_stock,ARRstockInicialStock);
}
void calculoStockFinal(double* ARRingreso,double* ARRsalida,
                    double* ARRenviado,
                    double* ARRrecibido,double* ARRstockFinal,
                    char** observaciones,int num_stock,
                    double* ARRstockInicialStock){
    for(int i=0;i<num_stock;i++){
        ARRstockFinal[i]=ARRstockInicialStock[i]+ARRingreso[i]-
                        ARRsalida[i]-ARRenviado[i]+ARRrecibido[i];
    }
}
int buscarPosicion(char* almacenREF,char* codigoREF,
                    char** ARRcodigo_productoStock,
                    char** ARRcodigo_almacenStock,int num_stock){
    int i;
    for(i=0;i<num_stock;i++){
        if(strcmp(ARRcodigo_almacenStock[i],almacenREF)==0
        and strcmp(ARRcodigo_productoStock[i],codigoREF)==0)break;
    }
    return i;
}
void sumamosCategoria(int pos,char tipo,double* ARRingreso,
                    double* ARRsalida,double* ARRenviado,
                    double* ARRrecibido,char** observaciones,
                    double cantidad,
                    char* almacenREF,char* codigoREF,
                    char** ARRcodigo_productoStock,
                    char** ARRcodigo_almacenStock,int num_stock){
    int pos2;
    if(tipo=='I'){
        ARRingreso[pos]+=cantidad;
    }else if(tipo=='S'){
        ARRsalida[pos]+=cantidad;
    }else {
        pos=buscarPosicion(almacenREF,codigoREF,
                        ARRcodigo_productoStock,
                        ARRcodigo_almacenStock,num_stock);
        ARRenviado[pos]+=cantidad;
        ARRrecibido[pos2]+=cantidad;
    }
}


