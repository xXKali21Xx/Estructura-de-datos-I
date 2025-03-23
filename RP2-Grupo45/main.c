//Grupo 45
//Alume Alberto
//P Scardapane Bruno
/*
Sobre los siguientes datos obtenidos

         COMPARACION DE ESTRUCTURAS

CANTIDAD        LSO     LSOBT   ABB
                69      69      79

COSTOS          LSO             LSOBT           ABB
____________________________________________________________________
MAX.ALTA        108.00          107.00          0.50
MED.ALTA        27.71           26.71           0.50
____________________________________________________________________
MAX.BAJA        97.00           96.00           1.50
MED.BAJA        30.59           29.59           0.80
____________________________________________________________________
MAX.EVOEX       99.00           13.00           28.00
MED.EVOEX       37.79           9.64            12.43
____________________________________________________________________
MAX.EVONOEX     84.00           14.00           24.00
MED.EVONOEX     44.18           11.30           42.99



Costos luego de RPM:

         COMPARACION DE ESTRUCTURAS

CANTIDAD        LSO     LSOBT   ABB
                69      69      79

COSTOS          LSO             LSOBT           ABB
____________________________________________________________________
MAX.ALTA        108.00          107.00          0.50
MED.ALTA        27.71           26.71           0.50
____________________________________________________________________
MAX.BAJA        97.00           96.00           1.50
MED.BAJA        30.59           29.59           0.80
____________________________________________________________________
MAX.EVOEX       99.00           13.00           28.00
MED.EVOEX       37.79           9.64            12.43
____________________________________________________________________
MAX.EVONOEX     84.00           14.00           24.00
MED.EVONOEX     32.92           11.51           12.97

Se concluye, para esta disposicion, que:
- La mejor estructura para realizar inserciones es el Arbol Binario de Busqueda (ABB) porque medido en actualizaciones de punteros
  (funcion que no infiere con la cantidad de elementos) es la que menos costo produce frente a las estructuras secuenciales, las
  cuales requieren corrimientos.
- La mejor estructura para realizar eliminaciones es el ABB ya que, nuevamente, la funcion de costo no infiere en la cantidad de
  elementos y como costo maximo solo se debe realizar una copia de datos y una actualizacion de punteros, lo cual es mucho menor
  al costo de realizar corrimientos en base al numero de elementos.
- La mejor estructura para realizar tanto evocaciones exitosas como intentos de evocacion resulto ser la lista secuencial ordenada
  con busqueda binaria por triseccion (LSOBT) ya que medido en comparaciones por X es la que menor costo produjo con gran diferencia
  frente a la lista secuencial ordenada con terminacion dada por contenido (LSO) y con un margen notable frente al ABB en ambas
  categorias.

- Si se tuviese que decidir por una estructura sabiendo que se espera agregar y eliminar datos con moderacion en un futuro (es decir,
  se espera que la estructura sufra modificaciones), el ABB seria la opcion indicada.

- Si se tuviese que decidir por una estructura esperando que se realicen consultas sobre sus elementos con moderacion, la LSOBT seria
  la opcion mas efectiva para dichas operaciones.

- Pero en general, suponiendo que un usuario puede tolerar el costo que requiere consultar en un ABB (un maximo de aproximadamente el
  doble que en una LSOBT para esta disposicion de los datos) con la ventaja que esta supone durante las inserciones y eliminaciones,
  podria inclinarse por dicha estructura dinamica.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prestador.h"
#include "LSO.h"
#include "LSOBT.h"
#include "ABB.h"
#include "CompEstrs.h"

int main()
{
    //Prestadores *prestLSO = (Prestadores*)malloc(sizeof(Prestadores)*110);
    int opcion1, opcion2/*, opcion3*/;
    //float cost;
    //int dni;
    //Prest a;
    int exito; //cantidad total y 1 para exito 0 para fracaso
    exito = 0;
    listaSO[0] = ult;
    //InicializarLSO();
    inicializarABB(&arb);
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
                    printf("------ [1] Lista secuencial ordenada con terminacion dada por contenido ------\n");
                    printf("------ [2] Lista secuencia ordenada (Busqueda binaria)                  ------\n");
                    printf("------ [3] Arbol binario de busqueda                                    ------\n");
                    printf("------ [4] Salir                                                        ------\n");
                    printf("------------------------------------------------------------------------------\n");
                    printf("Ingrese una opcion...\n");
                    fflush(stdin);
                    scanf("%d", &opcion2);
                    switch(opcion2){
                        case 1:
                            if(cantLSO == 0)
                                printf("La lista no tiene elementos.\n");
                            else
                                muestraLSO();
                        break;
                        case 2:
                            if(cantLSOBT == 0)
                                printf("La lista no tiene elementos.\n");
                            else
                                muestraLSOBT();
                        break;
                        case 3:
                            if(arb.cantABB == 0)
                                printf("El arbol no tiene elementos.\n");
                            else
                                muestraABB1(&arb);
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
