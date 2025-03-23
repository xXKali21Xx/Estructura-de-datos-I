#ifndef COMPESTRS_H_INCLUDED
#define COMPESTRS_H_INCLUDED

typedef struct{
    float costoTotal;
    float costoMax;
    int cant;
}costo;

costo cLSO[4];
costo cLSOBT[4];
costo cABB[4];

void initC(costo *);
void initM(float *);
Prest dato;
Prest exitoE;
Prest exitoEv;
int exito = 0, opcion = 0;
int dniAux;
float mLSO[4],mLSOBT[4],mABB[4],c;

arbol arb;
int Comparacion(){
    initC(cLSO);
    initC(cLSOBT);
    initM(mLSO);
    initM(mLSOBT);
    initC(cABB);
    initM(mABB);
    FILE *fp;
    int codOp, exitoL;
    //if((fp=fopen("Operaciones-Prestadores.txt","r"))==NULL)
    if((fp=fopen("Operaciones-Prestadores.txt","r"))==NULL)
        return 0;
    else{
        cantLSO = 0;
        cantLSOBT = 0;
        freeABB(arb.raiz);
        listaSO[0] = ult;
        //InicializarLSO();
        inicializarABB(&arb);
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
                    if((cantLSO < 110) && (aux.dni < 99999999)){
                        c = 0;
                        altaLSO(aux,&exitoL,&c);
                        if(exitoL == 1){
                            cLSO[0].costoTotal = cLSO[0].costoTotal + c;
                            cLSO[0].cant++;
                            if(c > cLSO[0].costoMax)
                                cLSO[0].costoMax = c;
                        }
                    }
                    if(cantLSOBT < 110){
                        c = 0;
                        altaLSOBT(aux,&exitoL,&c);
                        if(exitoL == 1){
                            cLSOBT[0].costoTotal = cLSOBT[0].costoTotal + c;
                            cLSOBT[0].cant++;
                            if(c > cLSOBT[0].costoMax)
                                cLSOBT[0].costoMax = c;
                        }
                    }
                    nodo *n = (nodo*)malloc(sizeof(nodo));
                    if(n != NULL){
                        free(n);
                        c = 0;
                        altaABB(&arb,aux,&exitoL,&c);
                        if(exitoL == 1){
                            cABB[0].costoTotal = cABB[0].costoTotal + c;
                            cABB[0].cant++;
                            if(c > cABB[0].costoMax)
                                cABB[0].costoMax = c;
                        }
                    }
                }else{
                    if((cantLSO > 0) && (aux.dni < 99999999)){
                        c = 0;
                        bajaLSO(aux.dni,aux,&exitoL,&c);
                        if(exitoL == 1){
                            cLSO[1].costoTotal = cLSO[1].costoTotal + c;
                            cLSO[1].cant++;
                            if(c > cLSO[1].costoMax)
                                cLSO[1].costoMax = c;
                        }
                    }
                    if(cantLSOBT > 0){
                        c = 0;
                        bajaLSOBT(aux.dni,aux,&exitoL,&c);
                        if(exitoL == 1){
                            cLSOBT[1].costoTotal = cLSOBT[1].costoTotal + c;
                            cLSOBT[1].cant++;
                            if(c > cLSOBT[1].costoMax)
                                cLSOBT[1].costoMax = c;//revisar esto
                        }
                    }
                    if(arb.cantABB > 0){
                        c = 0;
                        bajaABB(&arb,aux,&c,&exitoL);
                        if(exitoL == 1){
                            cABB[1].costoTotal = cABB[1].costoTotal + c;
                            cABB[1].cant++;
                            if(c > cABB[1].costoMax)
                                cABB[1].costoMax = c;
                        }
                    }
                }
            }else{
                if(codOp == 3){
                    fscanf(fp, "%d\n",&aux.dni);
                    Prest aux2;
                    c = 0;
                        if(cantLSO == 0 && aux.dni < 99999999)
                            exitoL = 0;
                        else{
                            c = 0;
                            aux2 = evocarLSO(aux.dni,&exitoL,&c);
                        }
                        if(exitoL == 1){
                            cLSO[2].costoTotal = cLSO[2].costoTotal + c;
                            cLSO[2].cant++;
                            if(c > cLSO[2].costoMax)
                                cLSO[2].costoMax = c;
                        }else{//caso c = 0
                            cLSO[3].costoTotal = cLSO[3].costoTotal + c;
                            cLSO[3].cant++;
                            if(c > cLSO[3].costoMax)
                                cLSO[3].costoMax = c;
                        }
                        c = 0;
                        if(cantLSOBT == 0)
                            exitoL = 0;
                        else
                            aux2 = evocarLSOBT(aux.dni,&exitoL,&c);
                        if(exitoL == 1){
                            cLSOBT[2].costoTotal = cLSOBT[2].costoTotal + c;
                            cLSOBT[2].cant++;
                            if(c > cLSOBT[2].costoMax)
                                cLSOBT[2].costoMax = c;
                        }else{
                            cLSOBT[3].costoTotal = cLSOBT[3].costoTotal + c;
                            cLSOBT[3].cant++;
                            if(c > cLSOBT[3].costoMax)
                                cLSOBT[3].costoMax = c;
                        }
                        c = 0;
                        if(arb.cantABB == 0)
                            exitoL = 0;
                        else
                           aux2 =  evocarABB(&arb,&exitoL,&c,aux.dni);
                        if(exitoL == 1){
                            cABB[2].costoTotal = cABB[2].costoTotal + c;
                            cABB[2].cant++;
                            if(c > cABB[2].costoMax)
                                cABB[2].costoMax = c;
                        }else{
                            cABB[3].costoTotal = cABB[3].costoTotal + c;
                            cABB[3].cant++;
                            if(c > cABB[3].costoMax)
                                cABB[3].costoMax = c;
                        }
                }else
                    printf("Error: Codigo de operacion desconocido.\n");
            }
        }
        fclose(fp);
        //LSO
        if(cLSO[0].cant != 0)
            mLSO[0] = cLSO[0].costoTotal * (1.0/cLSO[0].cant);
        if(cLSO[1].cant != 0)
            mLSO[1] = cLSO[1].costoTotal * (1.0/cLSO[1].cant);
        if(cLSO[2].cant != 0)
            mLSO[2] = cLSO[2].costoTotal * (1.0/cLSO[2].cant);
        if(cLSO[3].cant != 0)
            mLSO[3] = cLSO[3].costoTotal * (1.0/cLSO[3].cant);

        //LSOBT
         if(cLSOBT[0].cant != 0)
            mLSOBT[0] = cLSOBT[0].costoTotal * (1.0/cLSOBT[0].cant);
        if(cLSOBT[1].cant != 0)
            mLSOBT[1] = cLSOBT[1].costoTotal * (1.0/cLSOBT[1].cant);
        if(cLSOBT[2].cant != 0)
            mLSOBT[2] = cLSOBT[2].costoTotal * (1.0/cLSOBT[2].cant);
        if(cLSOBT[3].cant != 0)
            mLSOBT[3] = cLSOBT[3].costoTotal * (1.0/cLSOBT[3].cant);

        //ABB
        if(cABB[0].cant != 0)
            mABB[0] = cABB[0].costoTotal * (1.0/cABB[0].cant);
        if(cABB[1].cant != 0)
            mABB[1] = cABB[1].costoTotal * (1.0/cABB[1].cant);
        if(cABB[2].cant != 0)
            mABB[2] = cABB[2].costoTotal * (1.0/cABB[2].cant);
        if(cABB[3].cant != 0)
            mABB[3] = cABB[3].costoTotal * (1.0/cABB[3].cant);
        return 1;
    }
}

void CompPantalla(){
     printf("\t COMPARACION DE ESTRUCTURAS\n\n");
    printf("CANTIDAD\tLSO\tLSOBT\tABB\n");
    printf("\t\t%d\t%d\t%d\t\n\n",cantLSO,cantLSOBT,arb.cantABB);
    printf("COSTOS\t\tLSO\t\tLSOBT\t\tABB\n");
    printf("____________________________________________________________________\n");
    printf("MAX.ALTA\t%.2f\t\t%.2f\t\t%.2f\t\t\n",cLSO[0].costoMax,cLSOBT[0].costoMax,cABB[0].costoMax);
    printf("MED.ALTA\t%.2f\t\t%.2f\t\t%.2f\t\t\n",mLSO[0],mLSOBT[0],mABB[0]);
    printf("____________________________________________________________________\n");
    printf("MAX.BAJA\t%.2f\t\t%.2f\t\t%.2f\t\t\n",cLSO[1].costoMax,cLSOBT[1].costoMax,cABB[1].costoMax);
    printf("MED.BAJA\t%.2f\t\t%.2f\t\t%.2f\t\t\n",mLSO[1],mLSOBT[1],mABB[1]);
    printf("____________________________________________________________________\n");
    printf("MAX.EVOEX\t%.2f\t\t%.2f\t\t%.2f\t\t\n",cLSO[2].costoMax,cLSOBT[2].costoMax,cABB[2].costoMax);
    printf("MED.EVOEX\t%.2f\t\t%.2f\t\t%.2f\t\t\n",mLSO[2],mLSOBT[2],mABB[2]);
    printf("____________________________________________________________________\n");
    printf("MAX.EVONOEX\t%.2f\t\t%.2f\t\t%.2f\t\t\n", cLSO[3].costoMax,cLSOBT[3].costoMax,cABB[3].costoMax);
    printf("MED.EVONOEX\t%.2f\t\t%.2f\t\t%.2f\t\t\n\n", mLSO[3],mLSOBT[3],mABB[3]);
    system("PAUSE");
}

void initC(costo *c){
    int i;
    for(i=0;i<4;i++){
        c[i].cant = 0;
        c[i].costoMax = 0;
        c[i].costoTotal = 0;
    }
}

void initM(float *m){
    int i;
    for(i=0;i<4;i++){
        m[i] = 0;
    }
}

#endif // COMPESTRS_H_INCLUDED
