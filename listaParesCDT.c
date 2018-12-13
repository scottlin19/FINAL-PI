#include <stdio.h>


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

static int
coincidePar(nodeP nodo,char * origen, char * destino)
{
  return ((strcmp(nodo->origen.oaci,origen)== 0) && (strcmp(nodo->destino.oaci,destino) == 0 ));
  
}


static nodoP
insertarParesRec(nodoP primero, char * origen, char * destino, int * ok)
{
    if(primero == NULL){
      nodoP aux = calloc(1,sizeof(struct tNodo));
      if(aux == NULL){
        printf("Error: no se pudo crear el nodo. \n");
      }else {
        strcpy(aux->origen.oaci,origen);
        aux->cola = primero;
         *ok = 1;
        return aux;
      }
    }else if(coincidePar(primero,origen,destino)){
        (primero->mov_compartidos)++;
       *ok = 1;
    }else{
        primero->cola = insertarParesRec(primero->cola,origen,destino,ok);
        if((primero->cola != NULL )&& (primero->mov_compartidos - primero->cola->mov_compartidos) < 0){		
		tAeropuertoP aux = primero->cola->cola;
		primero->cola->cola = primero;
		primero = primero->cola;
		primero->cola->cola = aux;
	}
		
    }
  return primero;
    

}

int insertarPares(listaParesADT lista,char * origen, char * destino)
{
     int ok = 0;
    lista->primero = insertarParesRec(lista->primero,origen,destino,&ok);
  return ok;
}

