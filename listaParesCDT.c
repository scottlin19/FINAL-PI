#include <stdio.h>
#include "listaAeropuertoADT.h";

struct tProvincia{
  char oaci[10];
  char nombre[25];
};

struct tNodo{
      tProvincia origen;
     tProvincia destino;
     int mov_compartidos;
     struct tNodo * cola;
};

typedef struct tNodo * nodoP;

struct listaParesCDT{
    nodoP primero;
    
};



static nodoP
insertarParesRec(nodoP primero, char * origen, char * destino)
{
    if(primero == NULL){
      nodoP aux = calloc(1,sizeof(struct tNodo));
        strcpy(aux->origen.oaci,origen);
    }

}

int insertarPares(char * origen, char * destino)
{
     
}

