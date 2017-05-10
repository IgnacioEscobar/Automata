#include <stdio.h>
#include <stdlib.h>
//Nodo de resolucion
struct nodo{
    float valor;
    struct nodo* padre; 
    struct nodo* hijo;
};
//Variables de automata
int caracter, operacion = '+';
int centinelaNegatividad = 0;
float valorAcumulado = 0;
//Prototipos
void automata          ();
void inicial           ();
void negativo          ();
void construirDigito   (int caracter);
void operar            (int caracter);
void rechazo           ();
void aceptacion        ();
void crearNodo         (int operacion,float valor);
struct nodo* nuevoNodo (float x);
void resolver();

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
    resolver();
    printf("Resultado: ...\n");
}

//Resolucion
struct nodo* frenteDeSuma           = NULL;
struct nodo* fondoDeSuma            = NULL;
struct nodo* frenteDeMultiplicacion = NULL;
struct nodo* fondoDeMultiplicacion  = NULL;
struct nodo* frenteDeDivision       = NULL;
struct nodo* fondoDeDivision        = NULL;
struct nodo* punteroDeOperacion     = NULL;
struct nodo* nodoTemp               = NULL;

void crearNodo(int operacion,float valor){
    nodoTemp = nuevoNodo(valor);
    if (operacion == '+'){
        if (frenteDeSuma == NULL){
            frenteDeSuma = nodoTemp;
        }else{
            fondoDeSuma -> hijo = nodoTemp;
            fondoDeSuma = nodoTemp;
        }
    };
    if (operacion == '*'){
        if (frenteDeMultiplicacion == NULL){
            frenteDeMultiplicacion = nodoTemp;
        }else{
            fondoDeMultiplicacion -> hijo = nodoTemp;
            fondoDeMultiplicacion = nodoTemp;
        }
    };
    if (operacion == '/'){
        if (frenteDeDivision == NULL){
            frenteDeDivision = nodoTemp;
        }else{
            fondoDeDivision -> hijo = nodoTemp;
            fondoDeDivision = nodoTemp;
        }
    };
    nodoTemp -> padre = punteroDeOperacion;
    if (punteroDeOperacion == NULL){
        punteroDeOperacion = nodoTemp;
    }    
};

struct nodo* nuevoNodo(float x){
    struct nodo* nuevoNodo = (struct nodo*)malloc(sizeof(struct nodo));
    nuevoNodo -> valor = x;
    nuevoNodo -> padre = NULL; 
    nuevoNodo -> hijo  = NULL;
    return nuevoNodo;
}
 
void resolver(){
    struct nodo* iterador = frenteDeMultiplicacion;
    struct nodo* temporal;
    float  resultado;
    while(iterador != NULL){
        iterador -> padre -> valor = (iterador -> padre -> valor)*(iterador -> valor); 
        iterador -> hijo -> padre  =  iterador -> padre;
        temporal = iterador;
        iterador = iterador -> hijo;
        free(temporal);
    }
    iterador = frenteDeDivision;
    while(iterador != NULL){
        iterador -> padre -> valor = (iterador -> padre -> valor)/(iterador -> valor); 
        iterador -> hijo -> padre  =  iterador -> padre;
        temporal = iterador;
        iterador = iterador -> hijo;
        free(temporal);
    }
    iterador = frenteDeSuma;
    while(iterador != NULL){
        // iterador -> padre -> valor = (iterador -> padre -> valor)+(iterador -> valor); 
        // iterador -> hijo -> padre  =  iterador -> padre;
        // temporal = iterador;
        // iterador = iterador -> hijo;
        // free(temporal);
    }
}