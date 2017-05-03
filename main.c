#include <stdio.h>

//Variables de automata
int caracter, operacion = '+';
int centinelaNegatividad = 0;
float valorAcumulado = 0;
//Prototipos
void automata       ();
void inicial        ();
void negativo       ();
void construirDigito(int caracter);
void operar         (int caracter);
void rechazo        ();
void aceptacion     ();
void crearNodo      (int operacion,float valor);

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
    if(caracter=='-')                     {negativo();};
    if((caracter>='1') && (caracter<='9')){construirDigito(caracter);return;}
    ///
    rechazo();
}

//Estado 1
void negativo(){
    if (centinelaNegatividad == 1){centinelaNegatividad = 0;}
    if (centinelaNegatividad == 0){centinelaNegatividad = 1;}
    //Trancisiones
    caracter = getchar();
    if((caracter>='1') && (caracter<='9')) {construirDigito(caracter);return;}
    ///
    rechazo();
};

//Estado 2 - Estado de Aceptacion
void construirDigito(int caracter){
    valorAcumulado = valorAcumulado*10 + (caracter - '0');
    //Trancisiones
    caracter = getchar();
    if((caracter>='0') && (caracter<='9')) {construirDigito(caracter);return;}
    if((caracter=='*') || (caracter=='/') 
    || (caracter=='+') || (caracter=='-')) {operar(caracter);return;}
    ///
    if (caracter == '\n'){aceptacion();return;}
    rechazo();
}

//Estado 0' - Estado de reingreso
void operar(int caracter){
    crearNodo(operacion,(valorAcumulado*centinelaNegatividad));
    operacion = caracter;
    centinelaNegatividad = 0;
    if (caracter == '-'){centinelaNegatividad = 1;operacion = '+';}
    valorAcumulado = 0;
    //Trancisiones
    caracter = getchar();
    if(caracter=='-')                     {negativo();return;};
    if((caracter>='1') && (caracter<='9')){construirDigito(caracter);return;}
    ///
    rechazo();
}

void rechazo(){
    printf("No se reconoce la cadena\n");
}
void aceptacion(){
    printf("Resultado: ...\n");
}

void crearNodo(int operacion,float valor){};