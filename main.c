#include <stdio.h>
#include <stdlib.h>
//Variables de automata
int caracter, operacion = '+';
int centinelaNegatividad = 0;
float valorAcumulado = 0;
//Prototipos
void automata          ();
void inicial           ();
void negativo          ();
void construirDigito   ();
void operar            ();
void rechazo           ();
void aceptacion        ();


int main(){
    automata();
    return 0;
}

void automata(){
    printf("Ingresar expresion: ");
    inicial();
}

//Estado 0 - Estado inicial
void inicial(){
    //Trancisiones
    caracter = getchar();
    if(caracter=='-')                     {negativo(&centinelaNegatividad);};
    if((caracter>='1') && (caracter<='9')){construirDigito(caracter,&valorAcumulado);return;}
    ///
    rechazo();
}

//Estado 1
void negativo(){
    //Trancisiones
    caracter = getchar();
    if((caracter>='1') && (caracter<='9')) {construirDigito(caracter,&valorAcumulado);return;}
    ///
    rechazo();
};

//Estado 2 - Estado de Aceptacion
void construirDigito(){
    //Trancisiones
    caracter = getchar();
    if((caracter>='0') && (caracter<='9')) {construirDigito(caracter,valorAcumulado);return;}
    if((caracter=='*') || (caracter=='/') 
    || (caracter=='+') || (caracter=='-')) {operar(caracter,valorAcumulado,&centinelaNegatividad);return;}
    ///
    if (caracter == '\n'){aceptacion();return;}
    rechazo();
}

//Estado 0' - Estado de reingreso
void operar(){
    //Trancisiones
    caracter = getchar();
    if(caracter=='-')                     {negativo(centinelaNegatividad);return;};
    if((caracter>='1') && (caracter<='9')){construirDigito(caracter,valorAcumulado);return;}
    ///
    rechazo();
}

void rechazo(){
    printf("No se reconoce la cadena\n");
}
void aceptacion(){
    float r =resolver();
    printf("Resultado: %f \n",r);
}

