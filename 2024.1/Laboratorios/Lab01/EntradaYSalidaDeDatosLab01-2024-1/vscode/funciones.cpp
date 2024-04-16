//Auhtor: MAKO
#include<iostream>
#include<iomanip>
using namespace std;
#include "header/funciones.h"
#define MAX_LINEA 113

void emitirReporte(){
    cout.precision(2);
    cout<<fixed;
    //Variables
    int dd,mm,aa,dni,hhI,minI,ssI,hhF,minF,ssF;
    double tarifa,medicamentos,duracionH,totalDeIngresos=0;
    char especialidad,receta;
    //Variables estadisticas
    int pacientes=0,pacientesAten=0,pacientesAtenD=0,
        pacientesNo=0,pacientesPedia=0,pacientesCardio=0,
        pacientes350=0;
    double promGastos,promGastosD,porcentajeNoA,
           porcentajePedia,porcentaje350,
           gastosMedicina=0,gastosMedicinaD=0;
    encabezado();
    while(true){
        lecturaDeDatos(dd,mm,aa,dni,hhI,minI,ssI,hhF,minF,ssF,
                       tarifa,medicamentos,especialidad,receta);
        if(cin.eof())break;
        pacientes++;
        impresionDeDatos(dd,mm,aa,dni,hhI,minI,ssI,hhF,minF,ssF,
                       tarifa,medicamentos,especialidad,receta,
                       duracionH,totalDeIngresos);
        conteoDeCondicioanales(dd,mm,aa,dni,hhI,minI,ssI,hhF,minF,ssF,
                       tarifa,medicamentos,especialidad,receta,
                       duracionH,pacientes,pacientesAten,pacientesAtenD,
                       pacientesNo,pacientesPedia,pacientesCardio,
                       pacientes350,gastosMedicina,gastosMedicinaD);
    }
    procesosEstadisticos(pacientes,pacientesAten,pacientesAtenD,
                         pacientesNo,pacientesPedia,
                         pacientes350,promGastos,promGastosD,
                         porcentajeNoA,porcentajePedia,
                         porcentaje350,gastosMedicina,gastosMedicinaD);
    linea(MAX_LINEA,'=');
    impresionEstadisticas(totalDeIngresos,promGastos,promGastosD,porcentajeNoA,
                          porcentajePedia,porcentaje350,
                          pacientesCardio);
    linea(MAX_LINEA,'=');
}
void encabezado(){
    cout<<right<<setw(60)<<"EMPRESA DE SALUD S.A."<<endl;
    linea(MAX_LINEA,'=');
    cout<<setw(5)<<" "<<"REGISTRO DE CITAS DE LAS CONSULTAS MEDICAS"<<endl;
    linea(MAX_LINEA,'=');
    cout<<left<<setw(13)<<"Fecha"
        <<setw(12)<<"Paciente"
        <<setw(12)<<"Inicio"
        <<setw(8)<<"Fin"
        <<setw(18)<<"Duracion(H:M:S)"
        <<setw(14)<<"Duracion(H)"
        <<setw(15)<<"Especialidad"
        <<setw(10)<<"Pago(Cita+Medicinas)"<<endl;
    linea(MAX_LINEA,'-');
}
void linea(int n,char c){
    for (int i = 0; i < n; i++){
        cout<<c;
    }
    cout<<endl;
}
void lecturaDeDatos(int& dd,int& mm,int& aa,int& dni,int& hhI,
                    int& minI,int& ssI,int& hhF,int& minF,int& ssF,
                    double& tarifa,double& medicamentos,
                    char& especialidad,char& receta){
    //Variables
    char c;
    cin>>dd;
    if(cin.eof())return;
    cin>>c>>mm>>c>>aa>>dni>>hhI>>c>>minI>>c>>ssI>>hhF>>c>>minF
       >>c>>ssF>>tarifa>>especialidad>>receta;
    if(receta=='S')cin>>medicamentos;
}
void impresionDeDatos(int dd,int mm,int aa,int dni,int hhI,
                    int minI,int ssI,int hhF,int minF,int ssF,
                    double tarifa,double medicamentos,
                    char especialidad,char receta,
                    double& duracionH,double& totalDeIngresos){
    cout<<right<<setfill('0')<<setw(2)<<dd<<'/'<<setw(2)<<mm
        <<'/'<<setw(4)<<aa<<setfill(' ')<<setw(3)<<" "<<left
        <<setw(11)<<dni<<right<<setfill('0')<<setw(2)<<hhI
        <<':'<<setw(2)<<minI<<':'<<setw(2)<<ssI<<setfill(' ')
        <<setw(3)<<" "<<setfill('0')<<setw(2)<<hhF
        <<':'<<setw(2)<<minF<<':'<<setw(2)<<ssF<<setfill(' ')
        <<setw(5)<<" "<<left;
    //Duracion
    impresionDuracion(hhI,minI,ssI,hhF,minF,ssF,duracionH);
    //Especialidad
    impresionEspecialidad(especialidad);
    //Pago(cita+medicinas)
    if(receta=='N')medicamentos=0;
    impresionPagos(tarifa,medicamentos,duracionH,totalDeIngresos);
}
void impresionDuracion(int hhI,int minI,int ssI,
                       int hhF,int minF,int ssF,
                       double& duracionH){
    int inicio= convertirS(hhI,minI,ssI);
    int fin= convertirS(hhF,minF,ssF);
    int duracion= fin-inicio;
    duracionH= (double)duracion/3600;
    //Variables
    int hh,min,ss;
    convertirHMS(hh,min,ss,duracion);
    cout<<right<<setfill('0')<<setw(2)<<hh
        <<':'<<setw(2)<<min<<':'<<setw(2)<<ss<<setfill(' ')
        <<setw(10)<<" "<<left<<setw(11)<<duracionH;
}
int convertirS(int hh,int min,int ss){
    return hh*3600+min*60+ss;
}
void convertirHMS(int& hh,int& min,int& ss,int duracion){
    hh=(int)duracion/3600;
    duracion-=hh*3600;
    min=(int)duracion/60;
    duracion-=min*60;
    ss=(int)duracion;
}
void impresionEspecialidad(char especialidad){
    cout<<setw(15);
    switch (especialidad){
    case 'C':
        cout<<"Cardiologia";
        break;
    case 'P':
        cout<<"Pediatria";
        break;
    default:
        cout<<"Dermatologia";
        break;
    }
}
void impresionPagos(double tarifa,double medicamentos,
                    double duracionH,double& totalDeIngresos){
    double pago= (duracionH*tarifa)+medicamentos;
    totalDeIngresos+=pago;
    cout<<right<<setw(13)<<pago<<left<<endl;
}
void conteoDeCondicioanales(int dd,int mm,int aa,int dni,int hhI,
                    int minI,int ssI,int hhF,int minF,int ssF,
                    double tarifa,double medicamentos,
                    char especialidad,char receta,
                    double duracionH,int& pacientes,int& pacientesAten,
                    int& pacientesAtenD,int& pacientesNo,int& pacientesPedia,
                    int& pacientesCardio,int& pacientes350,
                    double& gastosMedicina,double& gastosMedicinaD){
    if(receta=='S'){
        pacientesAten++;
        gastosMedicina+=medicamentos;
        if(especialidad=='D'){
            pacientesAtenD++;
            gastosMedicinaD+=medicamentos;
        }
    }else{
        pacientesNo++;
        if(duracionH*tarifa>350)pacientes350++;
    }
    if(especialidad=='P')pacientesPedia++;
    else if(especialidad=='C' and aa*10000+mm*100+dd>20240115)pacientesCardio++;

}
void procesosEstadisticos(int pacientes,int pacientesAten,int pacientesAtenD,
                    int pacientesNo,int pacientesPedia,int pacientes350,
                    double& promGastos,double& promGastosD,
                    double& porcentajeNoA,double& porcentajePedia,
                    double& porcentaje350,double gastosMedicina,
                    double gastosMedicinaD){
    //Medicina Promedio
    promGastos=gastosMedicina/pacientesAten;
    //Medicina Promedio Dermatolodia
    promGastosD=gastosMedicinaD/pacientesAtenD;
    //Poecentaje de pacientes no recetados
    porcentajeNoA=(pacientesNo*100)/pacientes;
    //Porcentaje de pacientes que se atendieron en pediatia
    porcentajePedia=(pacientesPedia*100)/pacientes;
    //Porcentaje de pacientes que no fueron recetados y gasto mas de 350
    porcentaje350=(pacientes350*100)/pacientes;
}
void impresionEstadisticas(double totalDeIngresos,double promGastos,
                      double promGastosD,double porcentajeNoA,
                      double porcentajePedia,double porcentaje350,
                      int pacientesCardio){
    cout<<"Total de ingresos: "<<totalDeIngresos<<endl;
    linea(MAX_LINEA,'=');
    cout<<setw(5)<<" "<<setw(95)<<"ESTADISTICAS OBTENIDAS:"<<endl
        <<setw(5)<<" "<<setw(95)<<"Promedio de gastos por medicina de los pacientes que le recetaron medicinas"<<promGastos<<endl
        <<setw(5)<<" "<<setw(95)<<"Promedio de gastos por medicina de los pacientes que se atendieron en dermatologia"<<promGastosD<<endl
        <<setw(5)<<" "<<setw(95)<<"Porcentaje de pacientes que no le recetaron medicinas"<<porcentajeNoA<<'%'<<endl
        <<setw(5)<<" "<<setw(95)<<"Porcentaje de pacientes que se atendieron en pediatria"<<porcentajePedia<<'%'<<endl
        <<setw(5)<<" "<<setw(95)<<"Cantidad de pacientes que se atendieron en cardiologia despues 15/01/2024"<<pacientesCardio<<endl
        <<setw(5)<<" "<<setw(95)<<"Porcentje de pacientes que no le recetaron medicinas y que gasto mas de 350.00"<<porcentaje350<<"%"<<endl;
}