#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "listaAeropuertoADT.h"


#define DIAS_SEMANA 7



typedef struct tMov{
	int cant_cabotaje;
	int cant_internacional;
}tMov;



struct tAeropuerto {
	char   oaci[MAX_OACI];
	char * denom;
	char * prov;
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
		if(strcmp(aux->oaci,oaci) == 0){
			prov = aux->prov;
		}
	}
	return prov;
}


int 
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
	if(primero == NULL || (c = strcmp(primero->oaci,oaci)) > 0){
		tAeropuertoP aux = calloc(1,sizeof(struct tAeropuerto));
		if(aux == NULL){
			printf("Error: No hay lugar para otro nodo\n");
		}else{
			aux->cola = primero;
		  	strcpy(aux->oaci,oaci);
   	 		aux->denom = denom;
     			aux->prov = prov;
				
			*ok = 1;
		}
		return aux;
	}else if(c <0){
		primero->cola = insertarAPRec(primero->cola,oaci,denom,prov,ok);
	}else{
		printf("Error: aeropuerto repetido en el archivo. \n");
		
		
	}
	return primero;
	

}

int
insertarAP( listaAeropuertoADT lista, char * oaci, char * denom,char * prov)
{
	int ok =0 ;
	lista->primero = insertarAPRec(lista->primero, oaci,denom,prov, &ok);
	
	return ok;
}



static tAeropuertoP
agregarMovAPrec(tAeropuertoP primero,char * oaci,int clase, int clasif, int dia, int * agregado)
{	
	

		if(primero == NULL){
			
			return primero;
		}else if(strcmp(primero->oaci,oaci) == 0){
				

			if(clasif == CABOTAJE){
				
				(primero->cant_mov[dia][clase].cant_cabotaje)++;
				
			}else if(clasif == INTERNACIONAL){
				
				(primero->cant_mov[dia][clase].cant_internacional)++;
				
			}
			(primero->mov_totales)++;
			
			*agregado = 1;
			
			return primero;
		
		}else{
			
		
			primero->cola = agregarMovAPrec(primero->cola,oaci,clase,clasif,dia,agregado);
			
			int comp=0;
			if(primero->cola != NULL ){
				
				if( ((comp = (primero->mov_totales - primero->cola->mov_totales)) < 0) ||
				   ((comp == 0) &&  (strcmp(primero->oaci,primero->cola->oaci) > 0) )){
						
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
agregarMovAP(listaAeropuertoADT lista,char * oaci,int clase, int clasif, int dia)
{
	int agregado = 0;

	lista->primero = agregarMovAPrec(lista->primero,oaci,clase,clasif,dia,&agregado);
	
	return agregado;
}

listaAeropuertoADT
nuevaListaAP( void )
{
	return calloc(1, sizeof(struct listaAeropuertoCDT));
}

void freeAP(listaAeropuertoADT listaAP){
	tAeropuertoP actual = listaAP->primero, aux;
	while (actual != NULL){
		aux = actual->cola;
		free(actual->denom);
	
		free(actual->prov);
		free(actual);
		actual = aux;
	}
	free(listaAP);
}

void query1(listaAeropuertoADT listaAeropuerto, int *ok){
	FILE * archivoDest = fopen("movimientos_aeropuertos.csv", "w+t");
	if (archivoDest == NULL){
		printf("Error al crear/reemplazar archivo \"movimientos_aeropuertos.csv\"\n");
		*ok = 1;
	}
	else {
		tAeropuertoP aux = listaAeropuerto->primero;
		fprintf(archivoDest, "OACI;Denominación;Movimientos\n");
		while(aux != NULL){
			if (aux->mov_totales != 0){
				fprintf(archivoDest, "%s;%s;%d\n", aux->oaci, aux->denom, aux->mov_totales);
			}
			aux = aux->cola;
		}
	}
	fclose(archivoDest);
}	

void query2(listaAeropuertoADT listaAeropuerto, int *ok){
	FILE * archivoDest = fopen("dia_semana.csv", "w+t");
	if (archivoDest == NULL){
		printf("Error al crear/reemplazar archivo \"dia_semana.csv\"\n");
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
		printf("Error al crear/reemplazar archivo \"composicion.csv\"\n");
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
