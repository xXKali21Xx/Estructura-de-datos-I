#ifndef RAC_H_INCLUDED
#define RAC_H_INCLUDED
#include "prestador.h"
#define maxRAC 131

typedef struct{
    int estado; //1 virgen, 2 libre, 3 ocupada
    Prest prestador;
}celdaRAC;

typedef struct{
    celdaRAC arreglo[131];
    int cantidad;
}rebACuadr;

//funciones auxiliares
/*int comparacionC(rebACuadr rac, Prest x, int pos){
    if(strcmpi(rac.arreglo[pos].prestador.correo,x.correo) != 0){
        return 0;
    }if(strcmpi(rac.arreglo[pos].prestador.domicilio,x.domicilio)!=0){
        return 0;
    }if(rac.arreglo[pos].prestador.dni == x.dni){
        return 0;
    }if(strcmpi(rac.arreglo[pos].prestador.nombreapellido,x.nombreapellido)!=0){
        return 0;
    }if(rac.arreglo[pos].prestador.servicios != x.servicios){
        return 0;
    }if(strcmpi(rac.arreglo[pos].prestador.telefono,x.telefono) != 0){
        return 0;
    }
    return 1; //si entra en algun if anterior es falso caso que todo este bien retorna 1
}
*/
void inicializarRAC(rebACuadr *rac){
    int i = 0;
    (*rac).cantidad = 0;
    while(i < 131){
        (*rac).arreglo[i].estado = 1; //inicializo el rebalse con todas las celdas virgenes
        i++;
    }
}

void localizarRAC(rebACuadr rac,int dni, int *pos, float *cost, int *exito){
    int i = h(dni, 131);
    int j = 0;
    int k = 1;
    int pLibre = -1;
    while(j < 131){
        if((rac.arreglo[i].estado == 2) && (pLibre == -1)){
            pLibre = i;
        }
        if(rac.arreglo[i].estado == 1){
            *cost = *cost + 1.0;
            if(pLibre == -1)
                *pos = i;
            else
                *pos = pLibre;
            *exito = 0;
            return;
        }
        if((rac.arreglo[i].estado == 3) && (rac.arreglo[i].prestador.dni == dni)){
            *cost = *cost + 1.0;
            *pos = i;
            *exito = 1; //exito (lo encuentra)
            return;
        }
        *cost = *cost + 1.0;
        i = (i+k) % 131;
        k++;
        j = j + 1;
    }
    *exito = -1; //caso que no se encuentre y se recorren los 131 baldes
}

void altaRAC(rebACuadr *rac, Prest aux, int *exito){
    int pos,exitoL;
    float a;
    localizarRAC(*rac,aux.dni,&pos,&a,&exitoL);
    if(exitoL == 1){
        *exito = 0; //encontro el elemento por lo tanto fracasa el alta
    }else{
        (*rac).arreglo[pos].prestador = aux;
        (*rac).arreglo[pos].estado = 3;
        (*rac).cantidad++;
        *exito = 1; // la alta se completo correctamente
        }
    }

void muestraRAC(rebACuadr rac){
    int i = 0;
    while (i < 131){
        if(rac.arreglo[i].estado == 3){
            printf("-----------------------------------------------------------\n");
            printf(" \t Numero de documento: %d \n", rac.arreglo[i].prestador.dni);
            printf(" \t Nombre y Apellido: %s \n", rac.arreglo[i].prestador.nombreapellido);
            printf(" \t Domicilio : %s \n", rac.arreglo[i].prestador.domicilio);
            printf(" \t Correo electronico: %s \n", rac.arreglo[i].prestador.correo);
            printf(" \t Servicio: %s \n", rac.arreglo[i].prestador.servicios);
            printf(" \t Numero de telefono: %s \n", rac.arreglo[i].prestador.telefono);
            printf("-----------------------------------------------------------\n");
        }
        if(rac.arreglo[i].estado == 1){
            printf("---------------------------- La celda en %d es virgen -------------------------\n", i);
        }if(rac.arreglo[i].estado == 2){
            printf("---------------------------- La celda en %d esta libre -------------------------\n", i);
        }
        i++;
        if(i%5 == 0){
            system("PAUSE");
        }
    }
}

void bajaRAC(rebACuadr *rac, Prest x,int *exito){
    int pos,exitoL;
    float a;
    localizarRAC(*rac, x.dni, &pos,&a,&exitoL);
    if(exitoL == 1 &&*exito == 1 && strcmpi((*rac).arreglo[pos].prestador.correo, x.correo)//correccion
                    && strcmpi((*rac).arreglo[pos].prestador.domicilio, x.domicilio)
                    && strcmpi((*rac).arreglo[pos].prestador.nombreapellido, x.nombreapellido)
                    && strcmpi((*rac).arreglo[pos].prestador.servicios, x.servicios)
                    && strcmpi((*rac).arreglo[pos].prestador.telefono, x.telefono)){
        (*rac).arreglo[pos].estado = 2;
        (*rac).cantidad--;
        *exito = 1; //lo elimina
    }else{
        *exito = 0;//no coincide o no lo encuentra
    }
}

Prest evocarRAC(rebACuadr rac,int dni, int *exito, float *cost){
    Prest nil;
    int pos,exitoL;
    localizarRAC(rac,dni,&pos,cost,&exitoL);
    if(exitoL == 1){
        *exito = 1;
        return rac.arreglo[pos].prestador;
    }else{
        *exito = 0;
        return nil;
    }
}

#endif // RAC_H_INCLUDED
