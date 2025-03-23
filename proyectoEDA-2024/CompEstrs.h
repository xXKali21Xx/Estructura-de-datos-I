#ifndef COMPESTRS_H_INCLUDED
#define COMPESTRS_H_INCLUDED
typedef struct{
    float costoTotal;
    float costoMax;
    int cant;
}costo;

costo cRAL[2];
costo cRAC[2];
costo cRS[2];

void initC(costo *);
void initM(float *);
Prest dato;
Prest exitoE;
Prest exitoEv;
int exito = 0, opcion = 0;
int dniAux,v;
float mRAL[2],mRAC[2],mRS[2],c;

rebALineal rebAL;
rebACuadr rebAC;
rebSeparado rebSe;
int Comparacion(){
    initC(cRAL);
    initC(cRAC);
    initM(mRAL);
    initM(mRAC);
    initC(cRS);
    initM(mRS);
    FILE *fp;
    int codOp, exitoL;
    //if((fp=fopen("Operaciones-Prestadores.txt","r"))==NULL)
    if((fp=fopen("Operaciones-Prestadores.txt","r"))==NULL)
        return 0;
    else{
        inicializarRAL(&rebAL);
        inicializarRAC(&rebAC);
        freeRS(&rebSe);
        inicializarRS(&rebSe);
        rewind(fp);
        while(!(feof(fp))){
            Prest aux;
            fscanf(fp,"%d\n",&codOp);
            if((codOp==1) || (codOp==2)){
                fscanf(fp, "%d\n %[^\n]\n %[^\n]\n %[^\n]\n %[^\n]\n %[^\n]\n",
                    &aux.dni,
                    aux.nombreapellido,
                    aux.servicios,
                    aux.domicilio,
                    aux.correo,
                    aux.telefono);
                if(codOp == 1){
                    if(rebAL.cantidad < 132)// cambiar a M
                        altaRAL(&rebAL,aux,&exitoL);
                    if(rebAC.cantidad < 131)
                        altaRAC(&rebAC,aux,&exitoL);

                    altaRS(&rebSe,aux,&exitoL);//correccion

                }else{
                    if(rebAL.cantidad > 0)
                        bajaRAL(&rebAL,aux,&exitoL);
                    if(rebAC.cantidad > 0)
                        bajaRAC(&rebAC,aux,&exitoL);
                    if(rebSe.cantRS > 0)
                        bajaRS(&rebSe,aux,&exitoL);
                }
            }else{
                if(codOp == 3){
                    fscanf(fp, "%d\n",&aux.dni);
                    Prest aux2;
                    c = 0;
                    if(rebAL.cantidad == 0)
                        exitoL = 0;
                    else{//correcion
                        aux2 = evocarRAL(rebAL,aux.dni,&exitoL,&c);

                    if(exitoL){
                        cRAL[0].costoTotal = cRAL[0].costoTotal + c;
                        cRAL[0].cant++;
                        if(c > cRAL[0].costoMax)
                            cRAL[0].costoMax = c;
                    }else{
                        cRAL[1].costoTotal = cRAL[1].costoTotal + c;
                        cRAL[1].cant++;
                        if(c > cRAL[1].costoMax)
                            cRAL[1].costoMax = c;
                    }
                    }
                    c = 0;
                    if(rebAC.cantidad == 0)
                        exitoL = 0;
                    else{//correccion
                        aux2 = evocarRAC(rebAC,aux.dni,&exitoL,&c);
                        if(exitoL){
                        cRAC[0].costoTotal = cRAC[0].costoTotal + c;
                        cRAC[0].cant++;
                            if(c > cRAC[0].costoMax)
                            cRAC[0].costoMax = c;
                        }else{
                            cRAC[1].costoTotal = cRAC[1].costoTotal + c;
                            cRAC[1].cant++;
                        if(c > cRAC[1].costoMax)
                            cRAC[1].costoMax = c;
                        }
                    }

                    c = 0;
                    if(rebSe.cantRS == 0){
                        exitoL = 0;
                    }else{//corecion
                        aux2 =  evocarRS(&rebSe,aux.dni,&exitoL,&c);
                        if(exitoL){
                        cRS[0].costoTotal = cRS[0].costoTotal + c;
                        cRS[0].cant++;
                        if(c > cRS[0].costoMax){
                            cRS[0].costoMax = c;
                        }
                    }else{
                        cRS[1].costoTotal = cRS[1].costoTotal + c;
                        cRS[1].cant++;
                        if(c > cRS[1].costoMax){
                            cRS[1].costoMax = c;
                        }
                    }
                    }

                }else
                    printf("Error: Codigo de operacion desconocido.\n");
            }
        }
        fclose(fp);
        //RAL
        if(cRAL[0].cant != 0)
            mRAL[0] = cRAL[0].costoTotal * (1.0/cRAL[0].cant);
        if(cRAL[1].cant != 0)
            mRAL[1] = cRAL[1].costoTotal * (1.0/cRAL[1].cant);

        //RAC
         if(cRAC[0].cant != 0)
            mRAC[0] = cRAC[0].costoTotal * (1.0/cRAC[0].cant);
        if(cRAC[1].cant != 0)
            mRAC[1] = cRAC[1].costoTotal * (1.0/cRAC[1].cant);
        //RS
        if(cRS[0].cant != 0)
            mRS[0] = cRS[0].costoTotal * (1.0/cRS[0].cant);
        if(cRS[1].cant != 0)
            mRS[1] = cRS[1].costoTotal * (1.0/cRS[1].cant);
        return 1;
    }
}

void CompPantalla(){
     printf("\t COMPARACION DE ESTRUCTURAS\n\n");
    printf("CANTIDAD\tRAL\tRAC\tRS\n");
    printf("\t\t%d\t%d\t%d\t\n\n",rebAL.cantidad,rebAC.cantidad,rebSe.cantRS);
    printf("COSTOS\t\tRAL\t\tRAC\t\tRS\n");
    printf("____________________________________________________________________\n");
    printf("MAX.EVOEX\t%.2f\t\t%.2f\t\t%.2f\t\t\n",cRAL[0].costoMax,cRAC[0].costoMax,cRS[0].costoMax);
    printf("MED.EVOEX\t%.2f\t\t%.2f\t\t%.2f\t\t\n",mRAL[0],mRAC[0],mRS[0]);
    printf("____________________________________________________________________\n");
    printf("MAX.EVONOEX\t%.2f\t\t%.2f\t\t%.2f\t\t\n",cRAL[1].costoMax,cRAC[1].costoMax,cRS[1].costoMax);
    printf("MED.EVONOEX\t%.2f\t\t%.2f\t\t%.2f\t\t\n\n",mRAL[1],mRAC[1],mRS[1]);
    system("PAUSE");
}

void initC(costo *c){
    int i;
    for(i=0;i<2;i++){
        c[i].cant = 0;
        c[i].costoMax = 0;
        c[i].costoTotal = 0;
    }
}

void initM(float *m){
    int i;
    for(i=0;i<2;i++){
        m[i] = 0;
    }
}


#endif // COMPESTRS_H_INCLUDED
