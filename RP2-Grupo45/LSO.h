#ifndef LSO_H_INCLUDED
#define LSO_H_INCLUDED
#include <string.h>
#include "prestador.h"

Prest listaSO[111];
Prest ult = {99999999,"-","-","-","-","-"};
int cantLSO = 0;

//FUNCIONES AUXILIARES

/*void InicializarLSO(){// cambiar
    listaSO[0] = ult;
}*/ //cambios

//LOCALIZAR
void localizarLSO(int dni, int *pos, int *exito, float *cc){
    int i = 0;
    while(listaSO[i].dni < dni){
        *cc = *cc + 1;
        i++; //incrementa la posicion
    }
    *pos = i;
    *cc = *cc + 2; //Cuenta la comparacion al salir del while
    *exito = (listaSO[i].dni == dni);
}

//ALTA
void altaLSO(Prest x, int *exito, float *cc){
    int i = 0;
    int pos = 0;
    int exitoL = 0;
    float c;
    localizarLSO(x.dni, &pos, &exitoL, &c);
    if(exitoL){ //lo encontro, no se puede dar de alta
        *exito = 0;
    }else{// no lo encontro, por lo tanto se puede dar de alta
        for(i = cantLSO; i >= pos; i--){
            listaSO[i + 1] = listaSO[i];// cambio en la reasignacion
            *cc = *cc + 1;
        }
        listaSO[pos] = x; //cambio en la asignacion (antes lso[i]=x)
        *exito = 1; //se ingreso correctamente
        cantLSO++;
    }
}

//MUESTRA
void muestraLSO(){
    int pos = 0;
    while(pos < cantLSO){
        printf("---------------------------[%d]--------------------------\n",pos+1);
        printf(" \t Numero de documento: %d \n", listaSO[pos].dni);
        printf(" \t Nombre y Apellido: %s \n", listaSO[pos].nombreapellido);
        printf(" \t Domicilio : %s \n", listaSO[pos].domicilio);
        printf(" \t Correo electronico: %s \n", listaSO[pos].correo);
        printf(" \t Servicio: %s \n", listaSO[pos].servicios);
        printf(" \t Numero de telefono: %s \n", listaSO[pos].telefono);
        pos++;
        printf("-----------------------------------------------------\n");
        if(pos%5 == 0){
            printf("Presione enter para continuar...\n");
            getchar();
        }
    }
}
//BAJA
void bajaLSO(int dni, Prest pE, int *exito, float *cc){
    int i = 0;
    int pos = 0;
    int exitoL = 0;
    float c;
    Prest pr;
    *exito = 0;
    localizarLSO(dni, &pos, &exitoL, &c);
    if(exitoL){
        pr = listaSO[pos];
        if((pr.dni == pE.dni) && (strcmpi(pr.nombreapellido,pE.nombreapellido)==0)
           && (strcmpi(pr.servicios,pE.servicios)==0)
           && (strcmpi(pr.domicilio,pE.domicilio) == 0)
           && (strcmpi(pr.correo,pE.correo) == 0)
           && (strcmpi(pr.telefono,pE.telefono) == 0)){
            for(i = pos; i <= cantLSO - 1; i++){
                listaSO[i] = listaSO[i + 1]; //borra el elemento
                *cc = *cc + 1;
            }
            *exito = 1;
            cantLSO--;
        }else{
            *exito = 2; //Elemento no coincidente
        }
    }else
        *exito = 0; //Elemento no encontrado

    }

//MODIFICAR
/*void modificarLSO(int dniaux, int *exito){
    int pos, code, exitoL;
    *exito = 2;
    localizarLSO(dniaux, &pos, &exitoL);
    if(exitoL){
        do{
            printf("El elemento a modificar es: \n");
            printf(" \t DNI del prestador: %d \n", listaSO[pos].dni);
            printf(" \t Nombre y Apellido del prestador: %s \n", listaSO[pos].nombreapellido );
            printf(" \t Domicilio del prestador: %s \n", listaSO[pos].domicilio);
            printf(" \t Correo del prestador %s \n", listaSO[pos].correo);
            printf(" \t Servicio del prestador: %s \n", listaSO[pos].servicios);
            printf(" \t Numero de telefono del prestador %s \n ", listaSO[pos].telefono);
            printf("-------------------------------------------------------------------- \n");
            printf("¿Que desea modificar? \n");
            printf("-- [1] -- Nombre y Apellido del prestador --\n");
            printf("-- [2] -- Domicilio del prestador --\n");
            printf("-- [3] -- Correo del prestador --\n" );
            printf("-- [4] -- Servicio del prestador --\n");
            printf("-- [5] -- Numero de telefono del prestador --\n");
            printf("-- [6] -- Salir al menu principal --\n");
            printf("Ingrese opcion: \n ");
            fflush(stdin);
            scanf("%d", &code);
            switch(code){
                case 1:
                    printf("Ingrese el nuevo nombre y apellido del prestador.\n");
                    fflush(stdin);
                    scanf("%[^\n]s", listaSO[pos].nombreapellido);
                    *exito = 1;
                break;
                case 2:
                    printf("Ingrese el nuevo domicilio del prestador.\n");
                    fflush(stdin);
                    scanf("%s", listaSO[pos].domicilio);
                    *exito = 1;
                break;
                case 3:
                    printf("Ingrese el nuevo correo del prestador.\n");
                    fflush(stdin);
                    scanf("%[^\n]s", listaSO[pos].correo);
                    *exito = 1;
                break;
                case 4:
                    printf("Ingrese el nuevo servicio del prestador.\n");
                    fflush(stdin);
                    scanf("%[^\n]s", listaSO[pos].servicios);
                    *exito = 1;
                break;
                case 5:
                    printf("Ingrese el nuevo numero de telefono del prestador.\n");
                    fflush(stdin);
                    scanf("%s", listaSO[pos].telefono);
                    *exito = 1;
                break;
                case 6: printf("Volviendo al menu principal...\n");
                break;
                default: printf("Opcion equivocada.\n");
            }
        }while (code != 6);
    }else{//fallo el localizar
        *exito = 0;
    }
}
*/

//EVOCAR
Prest evocarLSO(int dni, int *exito, float *cc){
    int pos, exitoL;
    Prest nil;
    localizarLSO(dni, &pos, &exitoL, cc);
    if(exitoL){
        /*aux->DNI = lista[pos].DNI;
        strcpy(aux->correo,lista[pos].correo);
        strcpy(aux->domicilio,lista[pos].domicilio);
        strcpy(aux->nombreapellido,lista[pos].nombreapellido);
        strcpy(aux->servicios,lista[pos].servicios);
        strcpy(aux->telefono,lista[pos].telefono);*/
        *exito = 1;
        return listaSO[pos];
    }else{
        *exito = 0;
        return nil;
    }
}

//MEMORIZACION PREVIA - CARGA DE ARCHIVOS
/*int memorizacion_previa(){
    int exitoL;
    FILE *fp;
    fp = fopen("Prestadores.txt", "r");
    rewind(fp);
    if(fp == NULL){
        return 0; //no se encuentra el archivo
    }else {
        while(!feof(fp)){
            Prest aux;
            fscanf(fp, "%d\n %[^\n]\n %[^\n]\n %[^\n]\n %[^\n]\n %[^\n]\n",
                    &aux.dni,
                    aux.nombreapellido,
                    aux.servicios,
                    aux.domicilio,
                    aux.correo,
                    aux.telefono);
            if((cantLSO < 110) && (aux.dni < ult.dni)){//controla si se extrae un dni no valido del archivo
                altaLSO(aux, &exitoL);
            }
        }
        fclose(fp);
        return 1; //se cargo el archivo
    }
}*/
#endif // LSO_H_INCLUDED
