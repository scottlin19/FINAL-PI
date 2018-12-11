
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
#define MAX_DENOM 70
#define MAX_TEXTO 250
#define DIAS_SEMANA 7
#define REGULAR 0
#define NO_REGULAR 1
#define VUELO_PRIVADO 2

typedef struct tMov{
	int cant_cabotaje;
	int cant_internacional;

}tMov;

typedef struct tDatosAP{
	char * oaci; 
	char * denom;
	char * prov;
}tDatosAP;

struct tAeropuerto {
	tDatosAP datos;	
	tMov cant_mov[DIAS_SEMANA][3]; //  0 = Regulares, 1 = Vuelos no regulares , 2= Vuelos privados;
	int mov_totales;
	struct tAeropuerto * cola;
	
};

typedef struct tAeropuerto * tAeropuertoP;

struct listaAeropuertoCDT {
	tAeropuertoP primero;
	
	tAeropuertoP proximo;
};



static comparaMov(tAeropuertoP a1,tAeropuertoP a2)
{
	return a1->mov_totales - a2->mov_totales;

}


static tAeropuertoP
insertarAPRec(tAeropuertoP primero,tDatosAP datos, int * ok)
{
	int c;
	if(primero == NULL || (c = strcmp(primero->datos.oaci,datos.oaci)) > 0){
		tAeropuertoP aux = calloc(1,sizeof(struct tAeropuerto));
		if(aux == NULL){
			printf("Error:No se pudo utilizar malloc\n");
		}else{
		aux->cola = primero;
		aux->datos = datos;
		printf("Nuevo OICI: %s\nNueva Denom: %s\nNueva Prov: %s\n",aux->datos.oaci,aux->datos.denom,aux->datos.prov);
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

static int
insertarAP( listaAeropuertoADT lista, tDatosAP datos)
{
	int ok =0 ;
	lista->primero = insertarAPRec(lista->primero, datos, &ok);

	return ok;
}



tAeropuertoP
agregarMovAPrec(tAeropuertoP primero,char * oaci,char * clase, char * clasif, int dia, int * agregado)
{
	
	int c;
	int claseIndex;
		if((c = strcmp(primero->datos.oaci,oaci)) == 0){
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
		}else if(c > 0){
			
			printf("Error: no existe un aeropuerto con OACI: %s \n",oaci);
			
		}else{
			primero->cola = agregarMovAPrec(primero->cola,oaci,clase,clasif,dia,agregado);
			if(*agregado == 1){
				int comp;
				if( (comp =comparaMov(primero,primero->cola)) < 0||
				   ((comp == 0) && 
				    strcmp(primero->datos.oaci,primero->cola->datos.oaci) > 0)){
						tAeropuertoP aux = primero->cola->cola;
						primero->cola->cola = primero;
						primero = primero->cola;
						primero->cola->cola = aux;
				}
			}
			*agregado = 2; //Agregado y ordenado
			
		}
	
	return primero;
}
int
agregarMovAP(listaAeropuertoADT lista,char * oaci,char * clase, char * clasif, int dia)
{
	int agregado = 0;
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
	tDatosAP  datos; 
	char  s[MAX_TEXTO];
	fgets(s,MAX_TEXTO,archA);
	while(fgets(s,MAX_TEXTO,archA) != NULL){
		
		token = strtok(s,";");
		cont = 0;
		valido = 1;
		
		while((token != NULL) && valido){
			
			if(cont == OACI){
				if(strcmp(token," ") == 0){
					valido = 0;
							
				}else{		
					datos.oaci = token;
				}
				
			}else if(valido && cont == DENOMINACION){	
					datos.denom = token;
				
			}else if(valido && cont == PROVINCIA){	
					datos.prov = token;
					
			}	
			cont++;
		
			token =  strtok(NULL, ";");
			
		}		
		if(valido){ //Si es valido el aeropuerto tiene OACI
			printf("OACI: %s\nDENOM: %s\nPROVINCIA: %s\n",datos.oaci,datos.denom,datos.prov);
			if(!insertarAP(lista,datos)){
				printf("Error al cargar datos \n");
				return 1;
			}
		}
	}
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
