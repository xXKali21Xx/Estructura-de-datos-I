//Grupo 45
//Alume Alberto
//P Scardapane Bruno

/*
         COMPARACION DE ESTRUCTURAS

CANTIDAD        RAL     RAC     RS
                120     120     120

COSTOS          RAL             RAC             RS
____________________________________________________________________
MAX.EVOEX       55.00           26.00           7.00
MED.EVOEX       3.90            2.61            1.88
____________________________________________________________________
MAX.EVONOEX     12.00           15.00           4.00
MED.EVONOEX     3.54            3.68            1.62

como podemos observar en la comparacion de estructuras, podemos notar que
el Revalse Separado es la estructura para evocar mas eficiente entre las otras
tanto en la evocacion exitosa como la que fracasa diferenciandose en gran medida
de las otras estructuras
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prestador.h"
#include "ral.h"
#include "rac.h"
#include "rs.h"
#include "CompEstrs.h"

int main()
{
    int opcion1, opcion2;
    int exito;
    exito = 0;
    //freeRS(&rebSe);
    inicializarRAL(&rebAL);
    inicializarRS(&rebSe);
    do{
        printf("-------------------------- Menu --------------------------\n");
        printf("------------------------------------------------------------------\n");
        printf("------ [1] Comparacion de estructuras            ------\n");
        printf("------ [2] Mostrar estructuras                   ------\n");
        printf("------ [3] Salir                                 ------\n");
        printf("------------------------------------------------------------------\n");
        printf("Ingrese una opcion...\n");
        scanf("%d", &opcion1);
        fflush(stdin);
        switch(opcion1){
            case 1:
                printf("Cargando...\n");
                exito = Comparacion();
                if(exito){
                    printf("Lectura de operaciones exitosa.\n");
                    CompPantalla();
                }else
                    printf("Error en la lectura de operaciones.\n");
            break;
            case 2:
                do{
                    printf("------------------------------------------------------------------------------\n");
                    printf("------ [1] Rebalse Abierto Lineal ----------\n");
                    printf("------ [2] Rebalse Abierto Cuadratico ------\n");
                    printf("------ [3] Rebalse Separado ----------------\n");
                    printf("------ [4] Salir                                                        ------\n");
                    printf("------------------------------------------------------------------------------\n");
                    printf("Ingrese una opcion...\n");
                    fflush(stdin);
                    scanf("%d", &opcion2);
                    switch(opcion2){
                        case 1:
                            if(rebAL.cantidad == 0)
                                printf("La lista no tiene elementos.\n");
                            else
                                muestraRAL(rebAL);
                        break;
                        case 2:
                            if(rebAC.cantidad == 0)
                                printf("La lista no tiene elementos.\n");
                            else
                                muestraRAC(rebAC);
                        break;
                        case 3:
                            if(rebSe.cantRS == 0)
                                printf("La lista no tiene elementos.\n");
                            else
                                muestraRS(&rebSe);
                            /*do{
                            printf("------------------------------------------------------------------------------\n");
                            printf("------ [1] Alta ABB                                                     ------\n");
                            printf("------ [2] Baja ABB                                                     ------\n");
                            printf("------ [3] evocar ABB                                                   ------\n");
                            printf("------ [4] Muestra ABB                                                  ------\n");
                            printf("------ [5] Salir                                                        ------\n");
                            printf("------------------------------------------------------------------------------\n");
                            printf("Ingrese una opcion...\n");
                            scanf("%d", &opcion3);
                            switch(opcion3){
                                case 1:altaABB(&arb, Ingreso(), &exito, &cost);break;
                                case 2:
                                case 3:

                                    printf("ingrese el dni a buscar \n");
                                    scanf("%d", &dni);
                                    evocarABB(&arb,&exito, &cost,dni,a);
                                    printf("DNI: %d",a.dni);
                                    printf("Nombre: %s",a.nombreapellido);
                                    printf("Correo: %s",a.correo);
                                    break;
                                case 4: muestraABB1(&arb);break;
                            }
                            //muestraABB1(&arb);
                        }while(opcion3 != 5);
                            exit(0);*/
                        break;
                        case 4:
                            printf("Saliendo del menu Muestra de estructuras...\n");
                        default:
                            printf("Ingreso una opcion incorrecta.\n");break;
                    }
                }while(opcion2 != 4);
            break;
            case 3:
                printf("Cerrando el programa...\n");
            break;
            default: printf("Ingreso una opcion incorrecta.\n");break;
        }
    }while(opcion1 != 3);
    return 0;
}
