//Author: MAKO
#include<iostream>
#include<iomanip>
#include<cstring>
#include<fstream>
using namespace std;

#include "../header/Usuario.h"
#include "../header/Libro.h"
#include "../header/funciones.h"
#define MAX_LINEA 110
#define NO_ENCONTRADO -1
void leerLibros(struct Libro *libros,int & num_libros,
            const char* nomArch){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: Se produjo un error al abrir "<<nomArch<<endl;
        exit(1);
    }
    //VARIABLES
    int cantidad;
    double precio;
    char c;
    while(true){
        libros[num_libros].codigo=leerCadenaExacta(arch,',');
        if(arch.eof())break;
        libros[num_libros].titulo=leerCadenaExacta(arch,',');
        libros[num_libros].autor=leerCadenaExacta(arch,',');
        arch>>cantidad>>c>>precio;
        libros[num_libros].cantidad=cantidad;
        libros[num_libros].precio=precio;
        libros[num_libros].usuarios=new struct UsuariosConElLibro[cantidad]{};
        lecturaLibrosUsuarios(arch,libros[num_libros].usuarios,libros[num_libros].cantUsuarios);
        num_libros++;
    }
}
char* leerCadenaExacta(ifstream& arch,const char delimitador){
    //Variables
    char* ptr, buffer[100];
    arch.getline(buffer,100,delimitador);
    ptr=new char[strlen(buffer)+1];
    strcpy(ptr,buffer);
    return ptr;
}
void lecturaLibrosUsuarios(ifstream& arch,
                        struct UsuariosConElLibro *usuarios, int& num){
    //Variables
    int dni,fecha,dd,mm,aa;
    char c;
    while(arch.get()!='\n'){
        arch>>dni>>c>>dd>>c>>mm>>c>>aa;
        usuarios[num].dni=dni;
        //2020 11 20
        fecha=aa*10000+mm*100+dd;
        usuarios[num].fechaDeDevolucion=fecha;
        num++;
    }
}
void validacionDatos(struct Libro *libros,int num_libros,
                    const char* nomArch){
    ofstream arch(nomArch,ios::out);
    if(not arch.is_open()){
        cout<<"ERROR: Se produjo un error al abrir "<<nomArch<<endl;
        exit(1);
    }
    //Encabezado
    encabezado(arch);
    for(int i=0;i<num_libros;i++){
        sub_encabezado(arch);
        arch<<left<<setw(10)<<libros[i].codigo
            <<setw(40)<<libros[i].titulo
            <<setw(40)<<libros[i].autor
            <<setw(10)<<libros[i].cantidad
            <<setw(10)<<libros[i].precio<<endl;
            sub_encabezado2(arch);
            for(int k=0;k<libros[i].cantUsuarios;k++){
                arch<<left<<setw(10)<<libros[i].usuarios[k].dni
                    <<setw(10)<<libros[i].usuarios[k].fechaDeDevolucion<<endl;
            }
            linea(arch,'=');
    }
}
void encabezado(ofstream& arch){
    arch<<right<<setw(70)<<"REPORTE DE VALIDACION LECTURA DE LIBROS"<<endl
        <<endl;
    linea(arch,'=');
}
void sub_encabezado(ofstream& arch){
    arch<<left<<setw(10)<<"CODIGO"
        <<setw(40)<<"TITULO"
        <<setw(40)<<"AUTORA"
        <<setw(10)<<"CANTIDAD"
        <<setw(10)<<"PRECIO"<<endl;
    linea(arch,'-');
}
void sub_encabezado2(ofstream& arch){
    linea(arch,'-');
    arch<<right<<setw(60)<<"USUARIOS CON EL LIBRO"<<endl;
    linea(arch,'-');
    arch<<left<<setw(10)<<"DNI"
        <<setw(10)<<"FECHA"<<endl;
    linea(arch,'-');

}
void linea(ofstream& arch, char signo){
    for(int i=0;i<MAX_LINEA;i++){
        arch<<signo;
    }
    arch<<endl;
}
void leerUsuarios(struct Usuario *usuarios,int & num_usuarios,
            const char* nomArch){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: Se produjo un error al abrir "<<nomArch<<endl;
        exit(1);
    }
    //VARIABLES
    int dni;
    double precio;
    char c;
    while(true){
        arch>>usuarios[num_usuarios].dni;
        if(arch.eof())break;
        arch.get();//Saca la coma
        usuarios[num_usuarios].nombre=leerCadenaExacta(arch,',');
        arch>>usuarios[num_usuarios].categoria>>c
            >>usuarios[num_usuarios].clasificacion;
        arch.get();//Saca la coma
        usuarios[num_usuarios].libros=new struct LibroEnSuPoder[6]{};
        lecturaUsuariosLibros(arch,usuarios[num_usuarios].libros,usuarios[num_usuarios].cantLibros);
        num_usuarios++;
    }
}
void lecturaUsuariosLibros(ifstream& arch,struct LibroEnSuPoder *libros,int& num){
    char buffer[10];
    while(true){
        arch.get(buffer,8,' ');
        libros[num].codLibro=new char[strlen(buffer)+1];
        strcpy(libros[num].codLibro,buffer);
        num++;
        if(arch.get()=='\n')break;
    }
}
void validacionDatosUsuarios(struct Usuario *usuarios,int num_usuarios,
                    const char* nomArch){
    ofstream arch(nomArch,ios::out);
    if(not arch.is_open()){
        cout<<"ERROR: Se produjo un error al abrir "<<nomArch<<endl;
        exit(1);
    }
    // Encabezado
    encabezado1(arch);
    for(int i=0;i<num_usuarios;i++){
        sub_encabezado1(arch);
        arch<<left<<setw(10)<<usuarios[i].dni
            <<setw(40)<<usuarios[i].nombre
            <<setw(40)<<usuarios[i].categoria
            <<setw(10)<<usuarios[i].clasificacion<<endl;
            sub_encabezado2_1(arch);
            for(int k=0;k<usuarios[i].cantLibros;k++){
                arch<<left<<setw(10)<<usuarios[i].libros[k].codLibro<<endl;
            }
            linea(arch,'=');
    }
}
void encabezado1(ofstream& arch){
    arch<<right<<setw(70)<<"REPORTE DE VALIDACION LECTURA DE USUARIOS"<<endl
        <<endl;
    linea(arch,'=');
}
void sub_encabezado1(ofstream& arch){
    arch<<left<<setw(10)<<"DNI"
        <<setw(40)<<"NOMBRE"
        <<setw(40)<<"CATEGORIA"
        <<setw(10)<<"CLASIFICACION"<<endl;
    linea(arch,'-');
}
void sub_encabezado2_1(ofstream& arch){
    linea(arch,'-');
    arch<<right<<setw(60)<<"LIBROS EN SU PODER"<<endl;
    linea(arch,'-');
    arch<<left<<setw(10)<<"CODIGO"<<endl;
    linea(arch,'-');
}
void devoluciones(struct Usuario *usuarios,struct Libro *libros,
                int num_usuarios,int num_libros,
                const char* nomArch){
    ifstream arch(nomArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: Se produjo un error al abrir "<<nomArch<<endl;
        exit(1);
    }
    //VARIABLES
    int dd,mm,aa,fecha,dni,posUsuario,posLibro,posLibroUsuario;
    char codigo[8],c;
    //FECHA
    arch>>dd>>c>>mm>>c>>aa;
    arch.get();
    fecha=aa*10000+mm*100+dd;
    while(true){    
        arch>>dni;
        if(arch.eof())break;
        arch>>codigo;
        //Buscamos la posicion
        posUsuario=buscarUsuario(dni,usuarios,num_usuarios);
        posLibro=buscarLibro(codigo,libros,num_libros);
        posLibroUsuario=buscarUsuarioLibro(dni,
                        libros[posLibro].usuarios,
                        libros[posLibro].cantUsuarios);
        if(posLibro!=NO_ENCONTRADO and posLibroUsuario!=NO_ENCONTRADO
            and posUsuario!=NO_ENCONTRADO){
           if(libros[posLibro].usuarios[posLibroUsuario].fechaDeDevolucion<
            fecha){
            disminucionCalificacion(usuarios[posUsuario].clasificacion,usuarios[posUsuario].categoria);
            }
            eliminarLibro(usuarios[posUsuario].libros,libros[posLibro].usuarios,
                usuarios[posUsuario].cantLibros,libros[posLibro].cantUsuarios,
                dni,codigo); 
        }
    }
}
int buscarUsuario(int dni,struct Usuario *usuarios,int num_usuarios){
    int i;
    for( i=0;i<num_usuarios;i++){
        if(dni==usuarios[i].dni)return i;
    }   
    return NO_ENCONTRADO;
}
int buscarLibro(char *codigo,struct Libro *libros,int num_libros){
    int i;
    for( i=0;i<num_libros;i++){
        if(strcmp(codigo,libros[i].codigo)==0)return i;
    }   
    return NO_ENCONTRADO;
}
int buscarUsuarioLibro(int dni,struct UsuariosConElLibro *usuarios,int cantUsuarios){
    int i;
    for( i=0;i<cantUsuarios;i++){
        if(usuarios[i].dni == dni)return i;
    }   
    return NO_ENCONTRADO;
}
void disminucionCalificacion(double& clasificacion,char categoria){
    double descuento;
    switch (categoria)
    {
    case 'A':
        descuento=10;
        break;
    case 'D':
        descuento=20;
        break;
    case 'V':
        descuento=15;
        break;    
    }
    descuento=(descuento*clasificacion)/100;
    clasificacion-=descuento;
    if(clasificacion<0)clasificacion=0;
}
void eliminarLibro(struct LibroEnSuPoder *libros,struct UsuariosConElLibro *usuarios,
                    int& cantLibros,int& cantUsuarios,
                    int dni,char *codigo){
    //Eliminamos de libros
    for(int i=0;i<cantLibros;i++){
        if(strcmp(libros[i].codLibro,codigo)==0){
            libros[i].codLibro=libros[cantLibros-1].codLibro;
            cantLibros--;
            break;
        };
    }  
    //Eliminamos del usuarios
    for(int i=0;i<cantUsuarios;i++){
        if(usuarios[i].dni==dni){
            usuarios[i]=usuarios[cantUsuarios-1];
            cantUsuarios--;
            break;
        };
    } 
}