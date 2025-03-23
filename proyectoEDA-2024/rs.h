#ifndef RS_H_INCLUDED
#define RS_H_INCLUDED
#include <string.h>
#include "prestador.h"
// 1.74 = N/M = 110/M

typedef struct Nodo{
    Prest dato;
    struct Nodo *sig;
}nodo;

/*typedef struct{
    nodo *head;
}balde;*/

typedef struct RebalseS{
    nodo T[64];
    //nodo *cursor;
    //nodo *aux;
    int cantRS;
}rebSeparado;

Prest vacia = {-1,"-","-","-","-","-"};

int comparacionS(nodo *pos, Prest x){
    if(strcmpi(pos->dato.correo,x.correo) != 0){
        return 0;
    }if(strcmpi(pos->dato.domicilio,x.domicilio)!=0){
        return 0;
    }if(pos->dato.dni == x.dni){
        return 0;
    }if(strcmpi(pos->dato.nombreapellido,x.nombreapellido)!=0){
        return 0;
    }if(pos->dato.servicios != x.servicios){
        return 0;
    }if(strcmpi(pos->dato.telefono,x.telefono) != 0){
        return 0;
    }
    return 1; //si entra en algun if anterior es falso caso que todo este bien retorna 1
}

void inicializarRS(rebSeparado *r){
    int i;
    for(i = 0;i < 64; i++){
        r->T[i].dato = vacia;
        r->T[i].sig = NULL;
    }
    r->cantRS = 0;
}

void localizarRS(rebSeparado *x,int dni,nodo **pos,nodo **ant,int *posL,int *exito, float *cost){
    int pL = h(dni,64);
    *pos = &x->T[pL];
    *ant = NULL;
    while((*pos != NULL) && ((*pos)->dato.dni != dni)){
        *ant = *pos;
        *pos = (*pos)->sig;
        *cost = *cost + 1;
    }
    *exito = (*pos != NULL);
    if(*exito == 1){
        *cost = *cost + 1;
    }
    //*pos = act;
    *posL = pL;
}

void altaRS(rebSeparado *r,Prest x,int *exito){
    int exitoL,posL;
    float cL = 0;
    nodo *pos,*ant;
    localizarRS(r,x.dni,&pos,&ant,&posL,&exitoL,&cL);
    if(exitoL == 1){
        *exito = 0;
    }else{
        if(r->T[posL].dato.dni == -1){
            r->T[posL].dato = x;
            r->T[posL].sig = NULL;//no afecta por inicializacion
        }else{
            nodo *nuevo = (nodo*)malloc(sizeof(nodo));
            if(nuevo == NULL){
                *exito = -1;
                return;
            }else{
                nuevo->dato = x;
                nuevo->sig = r->T[posL].sig;
                r->T[posL].sig = nuevo;
            }
        }
        r->cantRS++;
        *exito = 1;
    }
}

void bajaRS(rebSeparado *r,Prest x,int *exito){
    int exitoL,posL;
    float cL = 0;
    nodo *pos,*ant;
    localizarRS(r,x.dni,&pos,&ant,&posL,&exitoL,&cL);
    if(exitoL == 0){
        *exito = 0;
    }else{
        if(comparacionS(pos,x) == 1){
            if(pos == &r->T[posL]){
                if(pos->sig == NULL){
                    r->T[posL].dato = vacia;
                    r->T[posL].sig = NULL;//no afecta por inicializacion
                }else{
                    r->T[posL].dato = pos->sig->dato;
                    nodo *temp = pos->sig;
                    r->T[posL].sig = pos->sig->sig;
                    free((void*)(temp));
                }
            }else{
                ant->sig = pos->sig;
                free((void*)(pos));
            }
            r->cantRS--;
            *exito = 1;
        }else
            *exito = -1;
    }
}

Prest evocarRS(rebSeparado *r,int dni,int *exito,float *cost){
    Prest nil;
    int exitoL,posL;
    nodo *pos,*ant;
    localizarRS(r,dni,&pos,&ant,&posL,&exitoL,cost);
    if(exitoL == 0){
        *exito = 0;
    }else{
        *exito = 1;
        return pos->dato;
    }
    return nil;
}

void muestraRS(rebSeparado *r){
    int i,j;
    for(i = 0; i < 64; i++){
        printf("\n------[Lista %d]-----\n",i + 1);
        nodo *act;
        act = &r->T[i];
        if(act->dato.dni == -1){
            printf("Vacia.\n");
            printf("-----------------------------\n\n");
        }else{
            j = 0;
            while(act != NULL){
                printf("----------[Prestador %d]-----\n",j + 1);
                printf("\tDNI: %d\n",act->dato.dni);
                printf("\tNombre: %s\n",act->dato.nombreapellido);
                printf("\tServicios: %s\n",act->dato.servicios);
                printf("\tDomicilio: %s\n",act->dato.domicilio);
                printf("\tCorreo: %s\n",act->dato.correo);
                printf("\tTelefono: %s\n",act->dato.telefono);
                printf("-----------------------------\n");
                j++;
                act = act->sig;
            }
            printf("\n");
        }
    }
}

void freeRS(rebSeparado *r){
    int i;
    nodo *act,*temp;
    for(i = 0;i < 64; i++){
        act = r->T[i].sig;
        while(act != NULL){
            temp = act;
            act = act->sig;
            free((void*)(temp));
        }
    }
}
#endif // RS_H_INCLUDED
