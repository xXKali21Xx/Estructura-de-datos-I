#ifndef LSOBT_H_INCLUDED
#define LSOBT_H_INCLUDED
#include <math.h>
#include <string.h>
#include "prestador.h"


//triseccion (lim inf inc, lim sup exc, segmento mas grande izq)
Prest listaSOBT[110];
int cantLSOBT = 0;

void localizarLSOBT(int dni, int *pos, int *exito, float *cc){
    int li = 0, ls = cantLSOBT,m;
    m = floor((li+ls)/2);
    while((li < ls) && (listaSOBT[m].dni != dni)){
        if(listaSOBT[m].dni < dni)
            li = m + 1;
        else
            ls = m;
        *cc = *cc + 2;
        m = floor((li+ls)/2);
    }
    if(li<ls){
        *pos = m;
        *cc = *cc + 1;
    }
    else
        *pos = li;
    *exito = li < ls;
}

void altaLSOBT(Prest x, int *exito, float *cc){
    int i = 0;
    int pos = 0;
    int exitoL = 0;
    float c;
    localizarLSOBT(x.dni, &pos, &exitoL, &c);
    if(exitoL){ //lo encontro, no se puede dar de alta
        *exito = 0;
    }else{// no lo encontro, por lo tanto se puede dar de alta
        for(i = cantLSOBT - 1; i >= pos; i--){
            listaSOBT[i + 1] = listaSOBT[i];// cambio en la reasignacion
            *cc = *cc + 1;
        }
        listaSOBT[pos] = x; //cambio en la asignacion (antes lso[i]=x)
        *exito = 1; //se ingreso correctamente
        cantLSOBT++;
    }
}

void bajaLSOBT(int dni, Prest pE, int *exito, float *cc){
    int i = 0;
    int pos = 0;
    int exitoL = 0;
    float c;
    Prest pr;
    *exito = 0;
    localizarLSOBT(dni, &pos, &exitoL, &c);
    if(exitoL){
        pr = listaSOBT[pos];
        if((pr.dni == pE.dni) && (strcmpi(pr.nombreapellido,pE.nombreapellido)==0)
           && (strcmpi(pr.servicios,pE.servicios)==0)
           && (strcmpi(pr.domicilio,pE.domicilio) == 0)
           && (strcmpi(pr.correo,pE.correo) == 0)
           && (strcmpi(pr.telefono,pE.telefono) == 0)){
               for(i = pos; i < cantLSOBT - 1; i++){
                   listaSOBT[i] = listaSOBT[i + 1]; //borra el elemento
                   *cc = *cc + 1;
               }
            *exito = 1;
            cantLSOBT--;
        }else{
            *exito = 2; //Elemento no coincidente
        }
    }else
        *exito = 0; //Elemento no encontrado
}

Prest evocarLSOBT(int dni, int *exito, float *cc){
    int pos, exitoL;
    Prest nil;
    localizarLSOBT(dni, &pos, &exitoL, cc);
    if(exitoL){
        *exito = 1;
        return listaSOBT[pos];
    }else{
        *exito = 0;
        return nil;
    }
}

void muestraLSOBT(){
    int pos = 0;
    while(pos < cantLSOBT){
        printf("---------------------------[%d]--------------------------\n",pos+1);
        printf(" \t Numero de documento: %d \n", listaSOBT[pos].dni);
        printf(" \t Nombre y Apellido: %s \n", listaSOBT[pos].nombreapellido);
        printf(" \t Domicilio : %s \n", listaSOBT[pos].domicilio);
        printf(" \t Correo electronico: %s \n", listaSOBT[pos].correo);
        printf(" \t Servicio: %s \n", listaSOBT[pos].servicios);
        printf(" \t Numero de telefono: %s \n", listaSOBT[pos].telefono);
        pos++;
        printf("-----------------------------------------------------\n");
        if(pos%5 == 0){
            printf("Presione enter para continuar...\n");
            getchar();
        }
    }
}
#endif // LSOBT_H_INCLUDED
