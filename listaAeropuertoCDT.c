
/*
 * airportCDT.c
 *
 */
/* Version recursiva de listas implementadas dinamicamente */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "listaAeropuertoADT.h"


#define OACI 1
#define DENOMINACION 4
#define PROVINCIA 21
#define DIAS_SEMANA 7

#define MAX_DENOM 70
#define MAX_OACI 20
#define MAX_PROV  70
#define MAX_TEXTO 400

#define REGULAR 0
#define NO_REGULAR 1
#define VUELO_PRIVADO 2

typedef struct tMov{
	int cant_cabotaje;
	int cant_internacional;
}tMov;



struct tAeropuerto {
	char  oaci[MAX_OACI];
	char denom[MAX_DENOM];
	char prov[MAX_PROV];
	tMov cant_mov[DIAS_SEMANA][3]; //  0 = Regulares, 1 = Vuelos no regulares , 2= Vuelos privados;
	int mov_totales;
	struct tAeropuerto * cola;
	
};

typedef struct tAeropuerto * tAeropuertoP;

struct listaAeropuertoCDT {
	tAeropuertoP primero;
	
	tAeropuertoP proximo;
};

static char * 
obtenerProvincia(listaAeropuertoADT lista,char * oaci)
{
	char * prov = NULL;
	int listo = 0;
	for(tAeropuertoP aux = lista->primero; !listo && aux != NULL;aux = aux->cola){
		if(strcmp(aux->datos.oaci,oaci) == 0){
			prov = aux->datos.prov;
		}
	}
	return prov;
}


int //Devuelve 1 si no coinciden provincias, 0 si coinciden provincias
sonDistintasProv(listaAeropuertoADT lista,char * origen, char * destino, char * provincias[])
{
	char * prov1 = obtenerProvincia(lista,origen);
	if(prov1 != NULL){
		char * prov2 = obtenerProvincia(lista,destino);
		if((prov2 != NULL) && (strcmp(prov1,prov2) != 0)){
			provincias[0] = prov1;
			provincias[1] = prov2;
			return 1;
		}
	}
	return 0;
}


static tAeropuertoP
insertarAPRec(tAeropuertoP primero,char * oaci, char * denom,char * prov, int * ok)
{
	int c;
	if(primero == NULL || (c = strcmp(primero->datos.oaci,datos.oaci)) > 0){
		tAeropuertoP aux = calloc(1,sizeof(struct tAeropuerto));
		if(aux == NULL){
			printf("Error: No hay lugar para otro nodo\n");
		}else{
			aux->cola = primero;
		
			strcpy(aux->oaci,datos.oaci);
			strcpy(aux->denom,datos.denom);
			strcpy(aux->prov,datos.prov);
				
			*ok = 1;
		}
		return aux;
	}else if(c <0){
		primero->cola = insertarAPRec(primero->cola,datos,ok);
	}else{
		printf("Error: aeropuerto repetido en el archivo. \n");
		*ok = 1;
	}
	return primero;
	

}

void
printLista(listaAeropuertoADT lista)
{
	int i = 1;
	printf("Lista aeropuertos \n");
	for(tAeropuertoP aux = lista->primero; aux!= NULL;i++, aux = aux->cola){
			printf("%d : OACI: %s, DENOM: %s PROV: %s MOVS: %d\n",i,aux->datos.oaci,aux->datos.denom,aux->datos.prov,aux->mov_totales);
	}

}
int
insertarAP( listaAeropuertoADT lista, char * oaci, char * denom,char * prov)
{
	int ok =0 ;
	lista->primero = insertarAPRec(lista->primero, oaci,denom,prov, &ok);
	
	return ok;
}



static tAeropuertoP
agregarMovAPrec(tAeropuertoP primero,char * oaci,char * clase, char * clasif, int dia, int * agregado)
{	
	
	int c;
	int claseIndex;

		if(primero == NULL){
			printf("primero es NULL \n");
			return primero;
		}else if((c = strcmp(primero->datos.oaci,oaci)) == 0){
				

			if(strcmp(clase,"Regular") == 0){
				claseIndex = REGULAR;
			
			}else if(strcmp(clase,"No Regular") == 0){
				
				claseIndex = NO_REGULAR;	
			}else{
			
				claseIndex = VUELO_PRIVADO;
			}
			if(strcmp(clasif,"Cabotaje") == 0){
				
				(primero->cant_mov[dia][claseIndex].cant_cabotaje)++;
				
			}else{
				
				(primero->cant_mov[dia][claseIndex].cant_internacional)++;
				
			}
			
			(primero->mov_totales)++;
			*agregado = 1;
			
			return primero;
		
		}else{
			
		
			primero->cola = agregarMovAPrec(primero->cola,oaci,clase,clasif,dia,agregado);
			
			int comp=0;
			if(primero->cola != NULL ){
				
				if( ((comp = (primero->mov_totales - primero->cola->mov_totales)) < 0) ||
				   ((comp == 0) &&  (strcmp(primero->datos.oaci,primero->cola->datos.oaci) > 0) )){
						
						tAeropuertoP aux = primero->cola->cola;
						primero->cola->cola = primero;
						primero = primero->cola;
						primero->cola->cola = aux;
				}
		
			}
			
		}
	
	return primero;
}
int
agregarMovAP(listaAeropuertoADT lista,char * oaci,char * clase, char * clasif, int dia)
{
	int agregado = 0;
	//printf("entro a agregarMovap\n");
	lista->primero = agregarMovAPrec(lista->primero,oaci,clase,clasif,dia,&agregado);
	return agregado;
}

listaAeropuertoADT
nuevaListaAP( void )
{
	return calloc(1, sizeof(struct listaAeropuertoCDT));
}

void
alPrincipioAP(listaAeropuertoADT lista) {
	lista->proximo = lista->primero;
}

int
tieneProxAP(const listaAeropuertoADT lista) {
	return lista->proximo != NULL;
}

void
proximoAP(listaAeropuertoADT lista)
{
	lista->proximo = lista->proximo->cola;
}

void query1(listaAeropuertoADT listaAeropuerto, int *ok){
	FILE * archivoDest = fopen("movimientos_aeropuertos.csv", "w+t");
	if (archivoDest == NULL){
		printf("Error al crear/reemplazar archivo");
		*ok = 1;
	}
	else {
		tAeropuertoP aux = listaAeropuerto->primero;
		fprintf(archivoDest, "OACI;Denominación;Movimientos\n");
		while(aux != NULL){
			printf("oaci vale %s\n", aux->datos.oaci);
			if (aux->mov_totales != 0){
				fprintf(archivoDest, "%s;%s;%d\n", aux->datos.oaci, aux->datos.denom, aux->mov_totales);
			}
			aux = aux->cola;
		}
	}
	fclose(archivoDest);
}	

void query2(listaAeropuertoADT listaAeropuerto, int *ok){
	FILE * archivoDest = fopen("dia_semana.csv", "w+t");
	if (archivoDest == NULL){
		printf("Error al crear/reemplazar archivp");
		*ok = 1;
	}
	else {
		fprintf(archivoDest, "Día;Cabotaje;Internacional;Total\n");
		char dias[7][11] = {"domingo", "lunes", "martes", "miércoles", "jueves", "viernes", "sábado"};
		int total[7][2] = {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}; 
		int dia = 0, clase;
		tAeropuertoP aux = listaAeropuerto->primero;
		while (aux != NULL){
			for (dia = 0; dia < 7; dia++){	
				for (clase = 0; clase < 3;clase++){
					total[dia][0] += aux->cant_mov[dia][clase].cant_cabotaje;
					total[dia][1] += aux->cant_mov[dia][clase].cant_internacional;
				}
			}
			aux = aux->cola;
		}
		for (dia = 1; dia < 7; dia++){
			fprintf(archivoDest, "%s;%d;%d;%d\n", dias[dia], total[dia][0],total[dia][1],total[dia][0] + total[dia][1]);
		}
		fprintf(archivoDest, "%s;%d;%d;%d\n", dias[0], total[0][0],total[0][1],total[0][0] + total[0][1]);
	}
	fclose(archivoDest);
}


void query3(listaAeropuertoADT listaAeropuerto, int *ok){
	FILE * archivoDest = fopen("composicion.csv", "w+t");
	if (archivoDest == NULL){
		printf("Error al crear/reemplazar archivo");
		*ok = 1;
	}
	else {
		fprintf(archivoDest, "Clasificación de Vuelo;Clase de Vuelo;Movimientos\n");
		tAeropuertoP aux = listaAeropuerto->primero;
		int i,j, dia;
		char *clasificacion[2][4] = {{"Cabotaje", "Regular", "No Regular", "Vuelo Privado"}, {"Internacional", "Regular", "No Regular", "Vuelo Privado"}};
		int total[2][3] = {{0,0,0},{0,0,0}};
		while(aux != NULL){
			for (i = 0; i < 2;i++){
				for (j = 0; j < 3; j++){
					for (dia = 0; dia < 7; dia++){	
						if (i == 0){
							total[i][j] += aux->cant_mov[dia][j].cant_cabotaje;
						}
						else {
							total[i][j] += aux->cant_mov[dia][j].cant_internacional;
						}
					}
				}
			}
			aux = aux->cola;
		}
		for (i = 0; i < 2; i++){
			for (j = 1; j < 4; j++){
				fprintf(archivoDest, "%s;%s;%d\n", clasificacion[i][0],clasificacion[i][j], total[i][j-1]);
			}
		}
		fclose(archivoDest);
	}
}
