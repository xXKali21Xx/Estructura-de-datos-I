#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED
#include "prestador.h"


//structs principales
typedef struct Nodo{ //como se representa el nodo
    Prest P;
    struct Nodo *D;
    struct Nodo *I;
}nodo;

typedef struct Arbol{ //forma del arbol
    nodo *raiz;
    nodo *aux;
    nodo *cursor;
    int cantABB;
}arbol;

void inicializarABB(arbol *a){//inicializador del arbol
    a->raiz = NULL;
    a->aux = NULL;
    a->cursor = NULL;
    a->cantABB = 0;
}

//structs auxiliares

typedef struct NodoPila{
    nodo *valor;
    struct NodoPila *next;
}nodopila;

typedef struct Pila{
    nodopila *tope;
}pila;

pila* crearPila(){
    pila *pila1 = (pila*)malloc(sizeof(pila));
    pila1->tope = NULL;
    return pila1;
}

void pushP(pila *p, nodo *d){
    nodopila *n = (nodopila*)malloc(sizeof(nodopila));
    n->valor = d;
    n->next = p->tope;
    p->tope = n;
}

int popP(pila *p,nodo **d){
    if(p->tope == NULL)
        return -1;
    nodopila *nPop = p->tope;
    *d = nPop->valor;
    p->tope = p->tope->next;
    free(nPop);
    return 1;
}

void freeP(pila *p){
    nodo *aux;
    int d;
    while(p->tope != NULL){
        d = popP(p,&aux);
    }
    free(p);
}
//funciones auxiliares
nodo* nuevonodoABB(Prest x){
    nodo* n = (nodo*)malloc(sizeof(nodo)); //crea memoria para un nuevo nodo
	if (n == NULL){
        return n;
	}
	n->P = x; //le asigna el valor al nodo
	n->I = NULL;
	n->D = NULL; //sin hijos
	return n;
}

arbol nuevoarbol(){
    arbol a;
    a.aux = NULL;
    a.raiz = NULL;
    a.cursor = NULL;
    a.cantABB = 0;
    return a;//crea un arbol y lo devuelve
}

void localizarABB(arbol *a, int DNI, int *exito, float *costo){
    a->cursor = a->raiz;
    a->aux = a->raiz;//hacemos que el cursor se posiciones en la raiz para empezar a buscar
    while((a->cursor != NULL) && (a->cursor->P.dni != DNI)){ //va a iterar hasta que el cursor quede en null o no se encuentre el DNI
        if(a->cursor->P.dni > DNI){ //busca en el hijo izquierdo
            a->aux = a->cursor;
            a->cursor = a->cursor->I;
            //*costo = *costo + 2;
        }else{
            if(a->cursor->P.dni < DNI){//busca en el hijo derecho
                a->aux = a->cursor;
                a->cursor = a->cursor->D;
                //*costo = *costo + 2;
            }
        }
        *costo = *costo + 2;
    }
    if(a->cursor != NULL){
        if(a->cursor->P.dni == DNI){
            *exito = 1; //lo encontro
        }else{
            *exito = 0;//no lo encontro
        }
        *costo = *costo + 2;
    }else{
        *exito = 0;
    }
}

void altaABB(arbol *a, Prest x, int *exito, float *costo){
    int exitoL;
    float costoL;
    localizarABB(a,x.dni,&exitoL,&costoL);
    if(exitoL == 1){
        *exito = 0;
    }else{
        nodo* nuevo = nuevonodoABB(x);//creamos un nodo nuevo
        if(nuevo != NULL){
            if(a->raiz == NULL){// si la raiz no tiene valor se ingresa el dato como la raiz
                a->raiz = nuevo;
                a->cantABB = a->cantABB + 1;
                *costo = *costo + 0.5;
            }else{
                if(a->aux->P.dni < x.dni){// caso que sea mayor se ingresa a la derecha
                    a->aux->D = nuevo;
                    a->cantABB = a->cantABB + 1;
                    *costo = *costo + 0.5;
                }else{// caso que sea menor se ingresa a la izquierda
                    a->aux->I = nuevo;
                    a->cantABB = a->cantABB + 1;
                    *costo = *costo + 0.5;
                }
            }
        *exito = 1;
        }
    }
}

Prest evocarABB(arbol *a, int *exito, float *costo, int DNI){
    int exitoL;
    Prest x;
    localizarABB(a,DNI,&exitoL,costo);
    if(exitoL){
        x.dni = a->cursor->P.dni;
        strcpy(x.correo,a->cursor->P.correo);
        strcpy(x.domicilio, a->cursor->P.domicilio);
        strcpy(x.nombreapellido, a->cursor->P.nombreapellido);
        strcpy(x.servicios, a->cursor->P.servicios);
        strcpy(x.telefono, a->cursor->P.telefono);
        *exito = 1;
        return x;//cambios
    }else{
        *exito = 0;
        return x; //no valido
    }
}

void muestraABB1(arbol *a){
    int d,i;
    i = 0;
    if (a->raiz == NULL){
        return;
    }
    pila *pila1 = crearPila();
    pushP(pila1,a->raiz);
    while(pila1->tope != NULL){
        nodo *act;
        d = popP(pila1,&act);
        if(act != NULL){
        printf("---------------------------[%d]--------------------------\n",i + 1);
        printf(" \t Numero de documento: %d \n", (act->P).dni);
        printf(" \t Nombre y Apellido: %s \n", (act->P).nombreapellido);
        printf(" \t Domicilio : %s \n", (act->P).domicilio);
        printf(" \t Correo electronico: %s \n", (act->P).correo);
        printf(" \t Servicio: %s \n", act->P.servicios);
        printf(" \t Numero de telefono: %s \n", (act->P).telefono);
        printf("-----------------------------------------------------\n");
        if(act->D != NULL){
            printf("Hijo der: %d\n",act->D->P.dni);
            pushP(pila1,act->D);
        }else
            printf("Hijo der: NULO\n");
        if(act->I != NULL){
            printf("Hijo izq: %d\n",act->I->P.dni);
            pushP(pila1,act->I);
        }else
            printf("Hijo izq: NULO\n");
        system("PAUSE");
        }
        i++;
    }
    freeP(pila1);
}
/*void muestraABB(arbol *a){
    if(a != NULL){
        printf("---------------------------[%d]--------------------------\n",a->cantABB+1);
        printf(" \t Numero de documento: %d \n", a->cursor->P.dni );
        printf(" \t Nombre y Apellido: %s \n", a->cursor->P.nombreapellido );
        printf(" \t Domicilio : %s \n", a->cursor->P.domicilio);
        printf(" \t Correo electronico: %s \n", a->cursor->P.correo);
        printf(" \t Servicio: %s \n", a->cursor->P.servicios);
        printf(" \t Numero de telefono: %s \n", a->cursor->P.telefono);
        printf("-----------------------------------------------------\n");
        system("PAUSE");
        muestraABB(a->cursor->I);
        muestraABB(a->cursor->D);
    }
}*/

void bajaABB(arbol *a,Prest x,float *costo,int *exito){
    int exitoL;
    float c;
    localizarABB(a,x.dni,&exitoL,&c);
    if(exitoL){
        if((strcmpi(a->cursor->P.correo,x.correo) == 0) &&
           (strcmpi(a->cursor->P.domicilio,x.domicilio) == 0) &&
           (a->cursor->P.dni == x.dni) &&
           (strcmpi(a->cursor->P.nombreapellido,x.nombreapellido) == 0) &&
           (strcmpi(a->cursor->P.servicios,x.servicios) == 0) &&
           (strcmpi(a->cursor->P.telefono,x.telefono) == 0)){
        if((a->cursor->D == NULL) && (a->cursor->I == NULL)){ // Sin Hijos
            if(a->cursor == a->raiz){        //RAIZ
                a->raiz = NULL;
                a->aux = NULL;
            }
            else{
                if(a->aux->I == a->cursor){     //Padre a la Izq
                    a->aux->I = NULL;
                }
                else{                      //Padre a la der
                    a->aux->D = NULL;
                }
            }
            free((void*)(a->cursor));
            a->cantABB = a->cantABB - 1;
            *costo = *costo + 0.5;
        }else{
        if((a->cursor->D == NULL)&&(a->cursor->I != NULL)){ // Con hijo izquierdo
            if(a->cursor == a->raiz){ //raiz
                a->raiz = a->cursor->I;
            }
            if(a->aux->I == a->cursor){ //Padre Izq
                a->aux->I = a->cursor->I;
            }
            else{                              //Padre Der
                 a->aux->D = a->cursor->I;
            }
            free((void*)(a->cursor));
            a->cantABB = a->cantABB - 1;
            *costo = *costo + 0.5;
        }else{
        if((a->cursor->D != NULL) && (a->cursor->I == NULL)){ //Con Hijo Der
             if(a->cursor == a->raiz){       //raiz
                a->raiz = a->cursor->D;
                //falta costo
            }
            if(a->aux->I == a->cursor){         //Padre Izq
                a->aux->I = a->cursor->D;
                //falta costo
            }
            else{                              //Padre Der
                 a->aux->D = a->cursor->D;
                //falta costo
            }
            free((void*)(a->cursor));
            *costo = *costo + 0.5;
            a->cantABB--;
        }else{
        if((a->cursor->D != NULL) && (a->cursor->I != NULL)){ //Con dos hijo,Politica de Remplazo menor de los mayores
            /*arbol arbAux;
            arbAux.cursor = a->cursor;
            a->cursor = a->cursor->I; //ir al subarbol izquierdo
            while(a->cursor->D != NULL){ //buscar el mayor de los menores
                a->aux = a->cursor;
                a->cursor = a->cursor->D;
            }
            //a->cursor->P = arbAux.cursor->P;
            arbAux.cursor->P = a->cursor->P;//reemplazar el elemento
            if(a->aux->D == a->cursor){
                a->aux->D = a->cursor->I;
                *costo = *costo + 0.5;
            }
            free((void*)(a->cursor));//eliminar el nodo*/
            nodo *mayor = a->cursor->I; //Toma hijo izq de nodo a reemplazar
            nodo *aux = NULL; //Inicializa padre de candidato a mdlM
            while(mayor->D !=NULL){ //recorre subarbol derecho
                aux = mayor;
                mayor = mayor->D;
            }
            a->cursor->P = mayor->P; //copia dato en nodo a reemplazar (c + 1)
            if(aux != NULL){ //si el padre del candidato es distinto de null
                aux->D = mayor->I; //reconecta hijo izq del candidato
            }else{ //si es null el hijo izq de cursor ya es mdlM
                a->cursor->I = mayor->I; //reconecta hijos izqs
            }//c + 0.5
            free((void*)(mayor)); //libera memoria del candidato
            *costo = *costo + 1.5; //
            a->cantABB--;
        }
        }
        }
        }
        *exito = 1;
        }else
            *exito = 2; //no coincidente
    }else
        *exito = 0;
}

void freeABB(nodo *raiz){
    if(raiz == NULL)
        return;
    freeABB(raiz->I);
    freeABB(raiz->D);
    free(raiz);
}

#endif // ABB_H_INCLUDED
