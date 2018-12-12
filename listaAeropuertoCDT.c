
/*
 * airportCDT.c
 *
 */
/* Version recursiva de listas implementadas dinamicamente */
#include "listaAeropuertoADT.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <string.h>

#define OACI 1
#define DENOMINACION 4
#define PROVINCIA 21
#define DIAS_SEMANA 7
#define MAX_DENOM 70
#define MAX_TEXTO 250
#define REGULAR 0
#define NO_REGULAR 1
#define VUELO_PRIVADO 2

typedef struct tMov{
	int cant_cabotaje;
	int cant_internacional;
}tMov;

typedef struct tDatosAP{
	char  oaci[20]; 
	char  denom[70];
	char  prov[30];
}tDatosAP;

struct tAeropuerto {
	tDatosAP  * datos;	
	tMov cant_mov[DIAS_SEMANA][3]; //  0 = Regulares, 1 = Vuelos no regulares , 2= Vuelos privados;
	int mov_totales;
	struct tAeropuerto * cola;
	
};

typedef struct tAeropuerto * tAeropuertoP;

struct listaAeropuertoCDT {
	tAeropuertoP primero;
	
	tAeropuertoP proximo;
};



static int 
comparaMov(tAeropuertoP a1,tAeropuertoP a2)
{
	return a1->mov_totales - a2->mov_totales;

}


static tAeropuertoP
insertarAPRec(tAeropuertoP primero,tDatosAP * datos, int * ok)
{
	int c;
	if(primero == NULL || (c = strcmp(primero->datos->oaci,datos->oaci)) > 0){
		tAeropuertoP aux = calloc(1,sizeof(struct tAeropuerto));
		if(aux == NULL){
			printf("Error:No se pudo utilizar malloc\n");
		}else{
			aux->cola = primero;
		
			aux->datos = datos;
		
			*ok = 1;
		}
		return aux;
	}else if(c <0){
		primero->cola = insertarAPRec(primero->cola,datos,ok);
	}else{
		printf("Aeropuerto repetido \n");
	}
	return primero;
	

}

void
printLista(listaAeropuertoADT lista)
{
	int i = 1;
	for(tAeropuertoP aux = lista->primero; aux!= NULL; aux = aux->cola,i++){
			printf("%d : OACI: %s, DENOM: %s PROV: %s \n",i,aux->datos->oaci,aux->datos->denom,aux->datos->prov);
	}

}
static int
insertarAP( listaAeropuertoADT lista, tDatosAP * datos)
{
	int ok =0 ;
	lista->primero = insertarAPRec(lista->primero, datos, &ok);
	printLista(lista);
	return ok;
}



static tAeropuertoP
agregarMovAPrec(tAeropuertoP primero,char * oaci,char * clase, char * clasif, int dia, int * agregado)
{	
		printf("entro a AGREGAR REC \n");
	printf("origen = %s\nclase=%s\nclasificacion=%s\n",oaci,clase,clasif);
	printf("oaci primero2 : %s \n",primero->datos->oaci);
	int c;
	int claseIndex;

		if(primero == NULL){
			return primero;
		}else if((c = strcmp(primero->datos->oaci,oaci)) == 0){
				

			if(strcmp(clase,"Regular") == 0){
				claseIndex = REGULAR;
				printf("2 IF \n");
			}else if(strcmp(clase,"No Regular") == 0){
				printf("3 IF \n");
				claseIndex = NO_REGULAR;	
			}else{
				printf("4 IF \n");
				claseIndex = VUELO_PRIVADO;
			}
			if(strcmp(clasif,"Cabotaje") == 0){
				printf("5 IF \n");
				(primero->cant_mov[dia][claseIndex].cant_cabotaje)++;
				
			}else{
				printf("6 IF \n");
				(primero->cant_mov[dia][claseIndex].cant_internacional)++;
				
			}
			
			(primero->mov_totales)++;
			 printf("ELSE \n");
			*agregado = 1;
			return primero;
		}else if(c > 0){
			printf("7 IF \n");
			printf("Error: no existe un aeropuerto con OACI: %s \n",oaci);
			
		}else{
			printf("ELSE 2 \n");
			printf("origen: %s oaci data: %s \n",primero->datos->oaci,oaci);
			primero->cola = agregarMovAPrec(primero->cola,oaci,clase,clasif,dia,agregado);
			if(*agregado == 1){
				printf("8 IF \n");
				int comp;
				if(primero->cola != NULL &&( (comp =(primero->mov_totales - primero->cola->mov_totales)) < 0 || ((comp == 0) &&  (strcmp(primero->datos->oaci,primero->cola->datos->oaci) > 0) ))){
					printf("9 IF \n");
						tAeropuertoP aux = primero->cola->cola;
						primero->cola->cola = primero;
						primero = primero->cola;
						primero->cola->cola = aux;
				}
		
			*agregado = 2; //Agregado y ordenado
			}
		}
	
	return primero;
}
int
agregarMovAP(listaAeropuertoADT lista,char * oaci,char * clase, char * clasif, int dia)
{
	int agregado = 0;
	printf("entro a agregarMovap\n");
	lista->primero = agregarMovAPrec(lista->primero,oaci,clase,clasif,dia,&agregado);
	
	return agregado;
}
int
cargarDatosAP(listaAeropuertoADT lista, char * pathA)
{

	FILE * archA = fopen(pathA,"rt"); //Abro archivo aeropuerto.csv
		
	if(archA == NULL){
		printf("Error al abrir los archivos. \n");
		return 1;
	
	}
		
	int cont;	
	int valido;
	char * token;
	
	char  s[MAX_TEXTO];
	fgets(s,MAX_TEXTO,archA);
	while(fgets(s,MAX_TEXTO,archA) != NULL){
		
		token = strtok(s,";");
		cont = 0;
		valido = 1;
		tDatosAP *  datos = malloc(sizeof(tDatosAP)); 
		while((token != NULL) && valido){
			
			if(cont == OACI){
				if(strcmp(token," ") == 0){
					valido = 0;
							
				}else{		
					
					strcpy(datos->oaci,token);
				}
				
			}else if(valido && cont == DENOMINACION){	
					strcpy(datos->denom,token);
				
			}else if(valido && cont == PROVINCIA){	
					strcpy(datos->prov,token);
					
			}	
			cont++;
		
			token =  strtok(NULL, ";");
			
		}		
		if(valido){ //Si es valido el aeropuerto tiene OACI
			printf("OACI: %s\nDENOM: %s\nPROVINCIA: %s\n",datos->oaci,datos->denom,datos->prov);
			if(!insertarAP(lista,datos)){
				printf("Error al cargar datos \n");
				return 1;
			}
			printf("se inserto bien \n");
		}
	}
	printLista(lista);
	printf("oaci p: %s denom p %s, prov p :%s \n",lista->primero->datos->oaci,lista->primero->datos->denom,lista->primero->datos->prov);
	return 0;
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
			printf("oaci vale %s\n", aux->datos->oaci);
			if (aux->mov_totales != 0){
				fprintf(archivoDest, "%s;%s;%d\n", aux->datos->oaci, aux->datos->denom, aux->mov_totales);
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

/*
void query3(listaAeropuertoADT listaAeropuerto, int *ok){
	FILE * archivoDest = fopen("composicion.csv", "w+t");
	if (archivo == NULL){
		printf("Error al crear/reemplazar archivo");
		*ok = 1;
	}
	else {
		fprintf(archivoDest, "Clasificación de Vuelo;Clase de Vuelo;Movimientos");
		tAeropuertoP aux = listaAeropuerto->primero;
		int i,j;
		char *clasificacion[2][3] = {{"Cabotaje", "Regular", "No Regular", "Vuelo Privado"}, {"Internacional", "Regular", "No Regular", "Vuelo Privado"}}
		int total[2][3];
*/
