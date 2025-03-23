#ifndef RAL_H_INCLUDED
#define RAL_H_INCLUDED
#include "prestador.h"
#define maxRAL 133
//STRUCTS

typedef struct{
    int estado; //1 virgen, 2 libre, 3 ocupada
    Prest prestador;
}celdaRAL;

typedef struct{
    celdaRAL arreglo[maxRAL];
    int cantidad;
}rebALineal;

//FUNCIONES AUXILIARES

void inicializarRAL(rebALineal *ral){
    int i = 0;
    (*ral).cantidad = 0;
    while(i < 132){
        (*ral).arreglo[i].estado = 1; //inicializo el rebalse con todas las celdas virgenes
        i++;
    }
}

int hashing(int dni, int M) {
    char x[10];
    int longitud, i;
    int contador = 0;
    sprintf(x, "%d",dni);
    longitud = strlen(x);
    for ( i =0; i< longitud; i++){
        contador +=((int) x[i]) * ( i + 1 ) ;
    }
    return (contador % M ) ;
}

/*int comparacion(rebALineal ral, Prest x, int pos){//no hace las bajas
    if(strcmpi(ral.arreglo[pos].prestador.correo,x.correo) != 0){
        return 0;
    }if(strcmpi(ral.arreglo[pos].prestador.domicilio,x.domicilio)!=0){
        return 0;
    }if(ral.arreglo[pos].prestador.dni == x.dni){//no deberia estar
        return 0;
    }if(strcmpi(ral.arreglo[pos].prestador.nombreapellido,x.nombreapellido)!=0){
        return 0;
    }if(ral.arreglo[pos].prestador.servicios != x.servicios){
        return 0;
    }if(strcmpi(ral.arreglo[pos].prestador.telefono,x.telefono) != 0){
        return 0;
    }
    return 1; //si entra en algun if anterior es falso caso que todo este bien retorna 1
}
*/
//FUNCIONES DE LA ESTRUCTURA

void localizarRAL(rebALineal ral,int dni, int *pos, float *cost, int *exito){
    int i = hashing(dni,132);
    int j=0;
    int pLibre = -1;
    while(j < maxRAL){
        if((ral.arreglo[i].estado == 2) && (pLibre == -1)){
            pLibre = i;
        }
        if(ral.arreglo[i].estado == 1){
            *cost = *cost + 1.0;
            if(pLibre == -1)
                *pos = i;
            else
                *pos = pLibre;
            *exito = 0;
            return;
        }
        if((ral.arreglo[i].estado == 3) && (ral.arreglo[i].prestador.dni == dni)){
            *cost = *cost + 1.0;
            *pos = i;
            *exito = 1;
            return;
        }
        *cost = *cost + 1.0;
        i = (i+1) % 132;
        j = j + 1;
    }
    *exito = -1;
}


void altaRAL(rebALineal *ral, Prest aux, int *exito){
    int pos,exitoL;
    float cL;
    localizarRAL(*ral,aux.dni,&pos,&cL,&exitoL);
    if(exitoL == 1){
        *exito = 0; //encontro el elemento por lo tanto fracasa el alta
    }else{
        (*ral).arreglo[pos].prestador = aux;
        (*ral).arreglo[pos].estado = 3;
        (*ral).cantidad++;
        *exito = 1; // la alta se completo correctamente
    }
}

void muestraRAL(rebALineal ral){
    int i = 0;
    while (i < 132){
        if(ral.arreglo[i].estado == 3){
            printf("-----------------------------------------------------------\n");
            printf(" \t Numero de documento: %d \n", ral.arreglo[i].prestador.dni);
            printf(" \t Nombre y Apellido: %s \n", ral.arreglo[i].prestador.nombreapellido);
            printf(" \t Domicilio : %s \n", ral.arreglo[i].prestador.domicilio);
            printf(" \t Correo electronico: %s \n", ral.arreglo[i].prestador.correo);
            printf(" \t Servicio: %s \n", ral.arreglo[i].prestador.servicios);
            printf(" \t Numero de telefono: %s \n", ral.arreglo[i].prestador.telefono);
            printf("-----------------------------------------------------------\n");
        }
        if(ral.arreglo[i].estado == 1){
            printf("---------------------------- La celda en %d es virgen -------------------------\n", i);
        }if(ral.arreglo[i].estado == 2){
            printf("---------------------------- La celda en %d esta libre -------------------------\n", i);
        }
        i++;
        if(i%5 == 0){
            system("PAUSE");
        }

    }
}

void bajaRAL(rebALineal *ral, Prest x,int *exito){
    int pos;
    float cL;
    localizarRAL(*ral, x.dni, &pos,&cL,exito);
    if(*exito == 1 && strcmpi((*ral).arreglo[pos].prestador.correo, x.correo)//correccion
                    && strcmpi((*ral).arreglo[pos].prestador.domicilio, x.domicilio)
                    && strcmpi((*ral).arreglo[pos].prestador.nombreapellido, x.nombreapellido)
                    && strcmpi((*ral).arreglo[pos].prestador.servicios, x.servicios)
                    && strcmpi((*ral).arreglo[pos].prestador.telefono, x.telefono)){//&& comparacion(ral,x, pos)
        (*ral).arreglo[pos].estado = 2;
        (*ral).cantidad--;
        *exito = 1; //lo elimina
    }else{
        *exito = 0;//no coincide o no lo encuentra
    }
}

Prest evocarRAL(rebALineal ral,int dni, int *exito, float *cost){
    Prest nil;
    int pos,exitoL;
    localizarRAL(ral,dni,&pos,cost,&exitoL);
    if(exitoL == 1){
        *exito = 1;
        return ral.arreglo[pos].prestador;
    }else{
        *exito = 0;
        return nil;
    }
}


#endif // RAL_H_INCLUDED
