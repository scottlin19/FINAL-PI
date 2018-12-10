
/*
 * airportCDT.c
 *
 */
/* Version recursiva de listas implementadas dinamicamente */

#include <stdio.h>
#include <stdlib.h>
#include "listaAeropuerto.h"
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
	nodeP first;
	unsigned int size;
	nodeP next;
};

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
	struct tDatos datos; 
	while((c = fgetc(archM)) != '\n');
	printf("c vale %c \n",c);
	while((c = fgetc(archM)) != EOF){
	
		if(c == ';'){
			cont++;
			if(cont > CANT_CAMPOS_MOV){ //Si llego al final de los campos tengo que agregar el movimiento;
				cont = 0;	
				printf("nombre = %s\norigen = %s\ndestino = %d\nclase = %d\nclasificacion = %d\ntipo = %d\ndia = %d\n");		
			}
		}
		if(cont == 0){
			fscanf(archM,"%02d/%02d/%04d;",&d,&m,&a);
			datos.dia = diaDeLaSemana(d,m,a);
			cont++;
		}
		if(cont != 1 && cont != 8 && cont != 9){ //Si es un campo que me interesa extraigo la data;
				
			fscanf(archM,"%[^;]",s); //Extraigo la string hasta ;
			
			
			switch(cont){
				case CLASE:
					switch(s){
					
						case "Regular":
							index = REGULAR;			
						break;
							
						case "No Regular":
							index = NO_REGULAR;
						break;
							
						case "Vuelo Privado con Matrícula Extranjera":
						case "Vuelo Privado con Matrícula Nacional":
							index = PRIVADO;
						break;
					}
					datos.clase_vuelo = index;
				break;
					
				case CLASIFICACION:
					switch(s){
					
						case "Cabotaje":
							index = CABOTAJE;			
						break;
							
						case "Internacional":
							index = INTERNACIONAL;
						break;
							
						case "N/A":
							index = NA;
						break;
					}
					datos.clasificacion_vuelo = index;
				break;
					
				case TIPO:
					switch(s){
					
						case "Aterrizaje":
							index = ATERRIZAJE;			
						break;
							
						case "Despegue":
							index = DESPEGUE;
						break;
							
			
					}
					datos.tipo_vuelo = index;
				break;
					
				case ORIGEN:
					datos.origen = s;
				break;
					
				case DESTINO:
					datos.destino = s;
				break;
					
				case NOMBRE:
					datos.nombre = s;
				break;
			
			
			}
			cont++;
		}
		
	
	}
	
	

}
static int
diaDeLaSemana(int d, int m, int a)
{
	return (d+=m<3?y--:y-2,23*m/9+d+4+y/4-y/100+y/400)%7; //Retorna el dia de la semana 0 es domingo, 1 es lunes, etc;

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
/*
int
elementBelongs( listADT list, listElementT element)
{
	return contains(list->first, element);
}
*/
/*
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
*/
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
