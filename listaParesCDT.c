#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "listaParesADT.h"
#define MAX_TEXTO_PROV 25

struct tNodo{
    char * provincias[2];
     int mov_compartidos;
     struct tNodo * cola;
};

typedef struct tNodo * nodoP;

struct listaParesCDT{
    nodoP primero;
    
};

static int
coincidenProv(char * provs1[], char * provs2[])
{
	return ((provs1[0] == provs2[0]) && (provs1[1] == provs2[1])) || ((provs1[0] == provs2[1]) && (provs1[1] == provs2[0]));
}

static nodoP
insertarParesRec(nodoP primero,char * provincias[], int * ok)
{
    if(primero == NULL){
      nodoP aux = calloc(1,sizeof(struct tNodo));
      if(aux == NULL){
        printf("Error: no se pudo crear el nodo. \n");
      }else {
      	if(strcmp(provincias[0],provincias[1]) < 0){
		aux->provincias[0] =provincias[0];
		aux->provincias[1]= provincias[1];
	}else{
		aux->provincias[0] =provincias[1];
		aux->provincias[1]= provincias[0];
	}
        aux->cola = primero;
         *ok = 1;
        return aux;
      }
    }else if(coincidenProv(primero->provincias,provincias)){
	(primero->mov_compartidos)++;
        *ok = 1;
    }else{
        primero->cola = insertarParesRec(primero->cola,provincias,ok);
        if((primero->cola != NULL )&& (primero->mov_compartidos - primero->cola->mov_compartidos) < 0){		
		nodoP aux = primero->cola->cola;
		primero->cola->cola = primero;
		primero = primero->cola;
		primero->cola->cola = aux;
	}
		
    }
  return primero;
    

}

int insertarPares(listaParesADT lista,char * provincias[])
{
    int ok = 0;
    lista->primero = insertarParesRec(lista->primero,provincias,&ok);
    return ok;
}

listaParesADT nuevaListaPares(void)
{
	return calloc(1,sizeof(struct listaParesCDT));
}

void query4(listaParesADT lista, int *ok){
	FILE * archivoDest = fopen("pares_provincias.csv", "w+t");
	if (archivoDest == NULL){
		printf("Error al crear/reemplazar archivo\n");
		*ok = 1;
	}
	else {
		nodoP aux = lista->primero;
		fprintf(archivoDest, "Provincia A;Provincia B;Movimientos\n");
		while (aux != NULL){
			fprintf(archivoDest, "%s;%s;%d\n", aux->provincias[0], aux->provincias[1], aux->mov_compartidos);
			aux = aux->cola;
		}
		fclose(archivoDest);
	}
}


