
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
#define CANT_CLASES 3
typedef enum {REGULAR = 0,NO_REGULAR, PRIVADO} clases_mov;
typedef enum {LUNES = 0,MARTES,MIERCOLES,JUEVES,VIERNES,SABADO,DOMINGO} dias_semana;
typedef enum {OACI = 1,DENOMINACION = 4,PROVINCIA = 21};
struct tAerolinea {
	int mov_cabojate[DIAS_SEMANA][CANT_CLASES];
	struct tAerolinea * tail;

};

struct listaAerolinea {

	

};
typedef struct tAerolinea * tAerolinieaP;

struct tAeropuerto {
	char * OACI;
	char denominacion[MAX_DENOM];
	char * provincia;
	
	
	struct tAeropuerto * tail;

};

typedef struct tAeropuerto * tAeropuertoP;

struct listaAeropuertoCDT {
	nodeP first;
	unsigned int size;
	nodeP next;
};


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


static nodeP insertRec(nodeP first, listElementT elem, int * added) {
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
insert( airportListADT list, listElementT element)
{
	/* Una mala solucion seria primero llamar a elementBelongs, y si retorna 1 no hacer nada porque ya pertenece
	 * a la lista. Y si retorna cero volver a recorrer para insertar */

	int added =0 ;
	list->first = insertRec(list->first, element, &added);
	if (added)
		list->size++;
	return added;
}


static nodeP delRec(nodeP first, listElementT elem, int * res) {

	int c;
	if( first==NULL || (c=compare(first->head, elem)) > 0 )
		return first;

	if( c == 0 )
	{
		nodeP aux = first->tail;
		free(first);
		*res = 1;
		return aux;
	}
	first->tail = delRec(first->tail, elem, res);
	return first;

}

int
delete( listADT list, listElementT element)
{
	int del=0;
	list->first = delRec(list->first, element, &del);
	if ( del )
		list->size--;
	return del;
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


