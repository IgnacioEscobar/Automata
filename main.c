#include <stdio.h>
#include <stdlib.h>
//Nodo de resolucion
struct nodo{
    float valor;
    struct nodo* padreDePista;
    struct nodo* padreDeOperacion; 
    struct nodo* hijoDePista;
    struct nodo* hijoDeOperacion;
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

//Resolucion
struct nodo* trackDeSuma           = NULL;
struct nodo* trackDeMultiplicacion = NULL;
struct nodo* trackDeDivision       = NULL;
struct nodo* punteroDeOperacion    = NULL;
struct nodo* nodoTemp              = NULL;

void crearNodo(int operacion,float valor){
    nodoTemp = nuevoNodo(valor);
    if (operacion == '+'){
        nodoTemp -> padreDePista = trackDeSuma;
        if (trackDeSuma == NULL){
            trackDeSuma = nodoTemp;
        }else{
            trackDeSuma -> hijoDePista = nodoTemp;
        }
    };
    if (operacion == '*'){
        nodoTemp -> padreDePista = trackDeMultiplicacion;
        if (trackDeSuma == NULL){
            trackDeMultiplicacion = nodoTemp;
        }else{
            trackDeMultiplicacion -> hijoDePista = nodoTemp;
        }

    };
    if (operacion == '/'){
        nodoTemp -> padreDePista = trackDeDivision;
        if (trackDeSuma == NULL){
            trackDeDivision = nodoTemp;
        }else{
            trackDeDivision -> hijoDePista = nodoTemp;
        }        
    };
    //if (operacion = "-"){printf("Error");};
    nodoTemp -> padreDeOperacion = punteroDeOperacion;
    if (punteroDeOperacion == NULL){
        punteroDeOperacion = nodoTemp;
    }else{
        punteroDeOperacion -> hijoDeOperacion = nodoTemp;
    }
    
};

struct nodo* nuevoNodo(float x){
    struct nodo* nuevoNodo = (struct nodo*)malloc(sizeof(struct nodo));
    nuevoNodo -> valor            = x;
    nuevoNodo -> padreDePista     = NULL;
    nuevoNodo -> padreDeOperacion = NULL; 
    nuevoNodo -> hijoDePista      = NULL;
    nuevoNodo -> hijoDeOperacion  = NULL;
    return nuevoNodo;
}