#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaAerolineaADT.h"




struct tAerolinea {
	char * nombre;
	int cant_mov_cabotaje;

	struct tAerolinea * cola;
};
typedef struct tAerolinea * tAerolineaP;



struct listaAerolineaCDT{
	
	tAerolineaP primero;
	tAerolineaP proximo;
	int cabotaje_total;

};



static tAerolineaP insertarALRec(tAerolineaP primero, char * nombre, int * ok) {
	
	if( primero == NULL)
	{
		
		tAerolineaP aux = calloc(1,sizeof( struct tAerolinea ));
		if (aux == NULL){
			printf("Error: No hay lugar para otro nodo\n");
		
		}else{
			
			aux->cola = primero;
      			aux->nombre = nombre;
		
			aux->cant_mov_cabotaje= 1;
			
			*ok = 1;
		}
		return aux;
	}else if(strcmp(primero->nombre,nombre) == 0){
		
		(primero->cant_mov_cabotaje)++;
		//printf(" libero aux = %s \n",nombre);
		free(nombre);
		*ok = 1;
		
	}else{	

		primero->cola = insertarALRec( primero->cola, nombre, ok);
		if((primero->cola != NULL) && (primero->cant_mov_cabotaje - primero->cola->cant_mov_cabotaje) < 0){
				tAerolineaP aux = primero->cola->cola;
				primero->cola->cola = primero;
				primero = primero->cola;
				primero->cola->cola = aux;
		}
	}
	return primero;
}
int 
insertarAL( listaAerolineaADT lista, char * nombre)
{
	int ok =0 ;
	lista->primero = insertarALRec(lista->primero, nombre, &ok);
	if(ok){
		(lista->cabotaje_total)++;
	}
	//printListaAL(lista);
	return ok;
}


int
esAerolinea(char * nombre)
{
	return ((strcmp(nombre," ") != 0 )&& (strcmp(nombre,"N/A") != 0));
}



listaAerolineaADT
nuevaListaAL(void)
{
	return calloc(1,sizeof(struct listaAerolineaCDT));
}

void freeAL(listaAerolineaADT listaAL){
	tAerolineaP actual = listaAL->primero, aux;
	while (actual != NULL){
		aux = actual->cola;
		//printf(" libero aux = %s \n",actual->nombre);
		free(actual->nombre);
		free(actual);
		actual = aux;
	}
	free(listaAL);
}

void query5(listaAerolineaADT listaAL, int *ok){
	FILE * archivoDest = fopen("porcentaje_cabotaje.csv", "w+t");
	if (archivoDest == NULL){
		printf("Error al crear/reemplazar archivo \"porcentaje_cabotaje.csv\"\n");
		*ok = 1;
	}
	else {
		fprintf(archivoDest,"Aerolínea;Porcentaje\n");
		tAerolineaP aux = listaAL->primero;
		int porcentaje;
		while (aux != NULL){
			porcentaje = ((float)aux->cant_mov_cabotaje / listaAL->cabotaje_total) * 100;
			if (porcentaje > 0){
				fprintf(archivoDest, "%s;%d%%\n", aux->nombre, porcentaje);
			}
			aux = aux->cola;
		}
		fclose(archivoDest);
	}
}
