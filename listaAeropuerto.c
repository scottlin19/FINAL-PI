
/*
 * airportCDT.c
 *
 */
/* Version recursiva de listas implementadas dinamicamente */

#include <stdio.h>
#include <stdlib.h>
#include "listaAeropuertoADT.h"
#define MAX_DENOM 70
#define DIAS_SEMANA 7
#define OACI 1
#define DENOMINACION 4
#define PROVINCIA 21
#define FECHA 0
#define CLASE 2
#define CLASIFICACION 3
#define TIPO 4
#define ORIGEN 5
#define DESTINO 6
#define NOMBRE 7

typedef enum {LUNES = 0,MARTES,MIERCOLES,JUEVES,VIERNES,SABADO,DOMINGO} dias_semana;

typedef struct tMov{
	int cant_cabotaje;
	int cant_internacional;

}tMov;

struct tAerolinea {
	char * nombre;
	tMov cant_mov[DIAS_SEMANA]; // Si estan en una aerolinea significa que son vuelos REGULARES.
				
	int mov_totales; // = cantidad de vuelos regulares de la aerolinea
	
	struct tAerolinea * tail;

};

typedef struct tAerolinea * tAerolineaP;

struct datos{
	char * origen;
	char * destino;
	char * nombre;
	int tipo_vuelo;
	int clase_vuelo;
	char * 

}



struct tAeropuerto {
	char * OACI;
	char denominacion[MAX_DENOM];
	char * provincia;
	
	tMov cant_mov_no_regulares[DIAS_SEMANA][2]; //  0 = Vuelos no regulares , 1 = Vuelos privados;
	tAerolineaP first_Aerolinea;
	
	int mov_totales;
	struct tAeropuerto * tail;
	

};

typedef struct tAeropuerto * tAeropuertoP;

struct listaAeropuertoCDT {
	nodeP first;
	unsigned int size;
	nodeP next;
};

void
cargarDatos(char * pathA,char * pathM)
{
	FILE * archA = fopen(pathA,"rt");
	FILE * archM = fopen(pathM,"rt");
	int dia,mes,anio;
	char * 
	
	

}


static void
Error(const char* s)
{
	fprintf(stderr, "%s", s);
	exit(EXIT_FAILURE);
}


listaAeropuertoADT
newList( void )
{
	return calloc(1, sizeof(struct listaAeropuertoCDT ));
}


int
listIsEmpty( listaAeropuertoCDT list)
{
	return list->size == 0;
}




static int contains(nodeP first, listElementT elem) {
	int c;

	if(first == NULL || (c=compare(first->head, elem)) > 0)
		return 0;
	
	if ( c == 0 )
		return 1;

	return contains( first->tail, elem);
}

int
elementBelongs( listADT list, listElementT element)
{
	return contains(list->first, element);
}


static nodeP insertRec(nodeP first, , int * added) {
	int c;
	if( first == NULL || (c=compare(first->head, elem)) > 0 )
	{
		nodeP aux = malloc(sizeof( struct tAeropuerto ));
		if (aux == NULL)
			Error("No hay lugar para otro nodo\n");
		aux->tail = first;
		aux->head = elem;
		*added = 1;
		return aux;
	}

	if( c < 0 )
		first->tail = insertRec( first->tail, elem, added);
	return first;
}

int
insert( listaAeropuerto lista, listElementT element)
{
	/* Una mala solucion seria primero llamar a elementBelongs, y si retorna 1 no hacer nada porque ya pertenece
	 * a la lista. Y si retorna cero volver a recorrer para insertar */

	int added =0 ;
	list->first = insertRec(list->first, element, &added);
	if (added)
		list->size++;
	return added;
}





void
freeList( listADT list)
{
	nodeP curr=list->first, aux;

	while (curr != NULL) {
		aux = curr->tail;
		free(curr);
		curr = aux;
	}
	free(list);
}

int
listSize(const listADT list) {
	return list->size;
}

void
toBegin(listADT list) {
	list->next = list->first;
}

int
hasNext(const listADT list) {
	return list->next != NULL;
}

listElementT
next(listADT list) {
	if (list->next==NULL)
		Error("No hay mas elementos a recorrer");
	listElementT ans = list->next->head;
	list->next = list->next->tail;

	return ans;
}


