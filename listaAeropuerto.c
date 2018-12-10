
/*
 * airportCDT.c
 *
 */
/* Version recursiva de listas implementadas dinamicamente */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "listaAeropuerto.h"
#include <string.h>
#define MAX_DENOM 70
#define DIAS_SEMANA 7
#define FECHA 0
#define CLASE 2
#define CLASIFICACION 3
#define TIPO 4
#define ORIGEN 5
#define DESTINO 6
#define NOMBRE 7
#define CABOTAJE 0
#define INTERNACIONAL 1
#define NA 2
#define ATERRIZAJE 0
#define DESPEGUE 1
#define REGULAR 0
#define NO_REGULAR 1
#define PRIVADO 2
#define CANT_CAMPOS_MOV 10
#define MAX_TEXTO 145

typedef enum {DOMINGO = 0,LUNES ,MARTES,MIERCOLES,JUEVES,VIERNES,SABADO} dias_semana;

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

typedef struct tDatos{
	char * origen;
	char * destino;
	char * nombre;
	int tipo_vuelo;
	int clase_vuelo;
	int clasificacion_vuelo;
	int dia;
}tDatos;



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
	tAeropuertoP first;
	unsigned int size;
	tAeropuertoP next;
};

static int
diaDeLaSemana(int d, int m, int a)
{
	return   (d+=m<3?a--:a-2,23*m/9+d+4+a/4-a/100+a/400)%7  ; //Retorna el dia de la semana 0 es domingo, 1 es lunes, etc;

}

void
cargarDatos(listaAeropuertoADT lista,char * pathA,char * pathM)
{
	FILE * archA = fopen(pathA,"rt"); //Abro archivo aeropuerto.csv
	FILE * archM = fopen(pathM,"rt");//Abro archivo movimientos.csv
	
	if(archA == NULL|| archM == NULL){
		printf("Error al abrir los archivos. \n");
	
	}
	
	int d,m,a;
	int cont = 0;
	char c;
	char s[MAX_TEXTO];
	int index;
	tDatos * datos = malloc(sizeof(tDatos)); 
	while((c = fgetc(archM)) != '\n');
	printf("c vale %c \n",c);
	while((c = fgetc(archM)) != EOF){
	
		if(c == ';'){
			cont++;
			if(cont > CANT_CAMPOS_MOV){ //Si llego al final de los campos tengo que agregar el movimiento;
				cont = 0;	
				printf("nombre = %s\norigen = %s\ndestino = %s\nclase = %d\nclasificacion = %d\ntipo = %d\ndia = %d\n",datos->nombre,datos->origen,datos->destino,datos->clase_vuelo,datos->clasificacion_vuelo,datos->tipo_vuelo,datos->dia);		
			}
		}
		if(cont == 0){
			fscanf(archM,"%02d/%02d/%04d;",&d,&m,&a);
			datos->dia = diaDeLaSemana(d,m,a);
			printf("dia = %d \n",datos->dia);
			   
			cont++;
		}
		if(cont != 1 && cont != 8 && cont != 9){ //Si es un campo que me interesa extraigo la data;
				
			fscanf(archM,"%[^;]",s); //Extraigo la string hasta ;
			printf("s = %s \n",s);
			
			switch(cont){
				case CLASE:
					printf("cont = %d \n",cont);
					if(strcmp(s, "Regular") == 0){
					
							index = REGULAR;
					}else if(strcmp(s, "No Regular") == 0){
							index = NO_REGULAR;
					}else if(strcmp(s,  "Vuelo Privado con Matrícula Extranjera") == 0 || strcmp(s, "Vuelo Privado con Matrícula Nacional") == 0){
						
							index = PRIVADO;
					
					}
					datos->clase_vuelo = index;
				break;
					
				case CLASIFICACION:
										printf("cont = %d \n",cont);

					if(strcmp(s, "Cabotaje") == 0){
						
						index = CABOTAJE;
						printf("index = internacional\n");
					}else if (strcmp(s,  "Internacional")  == 0){	
							
						index = INTERNACIONAL;
						printf("index = internacional\n");

					}else if (strcmp(s, "N/A") == 0){
						
						index = NA;
						
					}
					datos->clasificacion_vuelo = index;
				break;
					
				case TIPO:
					printf("cont = %d \n",cont);

					
						if(strcmp(s,"Aterrizaje") == 0){
							index = ATERRIZAJE;			
						}else if(strcmp(s,"Despegue") == 0){	
						 
							index = DESPEGUE;
						}	
			
					
					datos->tipo_vuelo = index;
				break;
					
				case ORIGEN:
					printf("cont = %d \n",cont);

					datos->origen = s;
				break;
					
				case DESTINO:
					printf("cont = %d \n",cont);

					datos->destino = s;
				break;
					
				case NOMBRE:
					printf("cont = %d \n",cont);
					
					datos->nombre = s;
				break;
			
			
			}
			cont++;
		}
		
	
	}
	
	

}


static void
Error(const char* s)
{
	fprintf(stderr, "%s", s);
	exit(EXIT_FAILURE);
}


listaAeropuertoADT
nuevaLista( void )
{
	return calloc(1, sizeof(struct listaAeropuertoCDT ));
}


int
listIsEmpty( listaAeropuertoADT list)
{
	return list->size == 0;
}



/*
static int contains(nodeP first, listElementT elem) {
	int c;

	if(first == NULL || (c=compare(first->head, elem)) > 0)
		return 0;
	
	if ( c == 0 )
		return 1;

	return contains( first->tail, elem);
}*/
/*
int
elementBelongs( listADT list, listElementT element)
{
	return contains(list->first, element);
}
*/
/*
static tAeropuertoP insertRec(tAeropuertoP first, int elem , int * added) {
	int c;
	if( first == NULL || (c=compare(first->head, elem)) > 0 )
	{
		tAeropuertoP aux = malloc(sizeof( struct tAeropuerto ));
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
}*/
/*
int
insert( listaAeropuertoADT lista, listElementT element)
{
	int added =0 ;
	list->first = insertRec(list->first, element, &added);
	if (added)
		list->size++;
	return added;
}

*/

/*

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

*/
