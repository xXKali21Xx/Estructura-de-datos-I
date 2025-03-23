#ifndef PRESTADOR_H_INCLUDED
#define PRESTADOR_H_INCLUDED
#include <string.h>

typedef struct{
    int dni;
    char nombreapellido[80];
    char servicios[120];
    char domicilio[120];
    char correo[50];
    char telefono[30];
}Prest;

Prest Ingreso(){
    Prest x;
    do{
        printf("Ingrese el DNI: \n");
        scanf("%d",&x.dni);getchar();
        fflush(stdin);
        if(x.dni >= 99999999)
            printf("El DNI esta fuera del rango permitido.\n");
    }while (x.dni >= 99999999);
    printf("Ingrese Nombre y Apellido: \n");
    scanf("%[^\n]s", x.nombreapellido);getchar();
    fflush(stdin);
    printf("Ingrese el servicio: \n");
    scanf("%s", x.servicios);getchar();
    fflush(stdin);
    printf("Ingrese el correo electronico: \n");
    scanf("%s", x.correo);getchar();
    fflush(stdin);
    printf("Ingrese el domicilio: \n");
    scanf("%[^\n]s",x.domicilio);getchar();
    fflush(stdin);
    printf("Ingrese el Numero de telefono: \n");
    scanf("%s",x.telefono);getchar();
    fflush(stdin);
    return x;
}

#endif // PRESTADOR_H_INCLUDED
