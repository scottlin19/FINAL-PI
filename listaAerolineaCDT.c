
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaAeropuertoADT.h"
#include "listaAerolineaADT.h"

#define FECHA 0
#define CLASE 2
#define CLASIFICACION 3
#define TIPO 4
#define ORIGEN 5
#define DESTINO  6
#define NOMBRE 7
#define DIAS_SEMANA 7
#define MAX_TEXTO 250
#define REGULAR 0
#define NO_REGULAR 1
#define VUELO_PRIVADO 2


struct tAerolinea {
	char * nombre;
	int cant_mov_cabotaje;

	struct tAerolinea * cola;
};
typedef struct tAerolinea * tAerolineaP;

typedef struct tDatosAL{
	char * origen;
	char * nombre;
	int clase_vuelo;
	int clasificacion_vuelo;
	int dia;
}tDatosAL;

struct listaAerolineaCDT{
	
	tAerolineaP primero;
	tAerolineaP proximo;

};

static tAerolineaP insertarALRec(tAerolineaP primero, tDatosAL datos, int * ok) {
	/*
	if( primero == NULL || (primero->mov_totales == 1) && strcmp(primero->OACI,datos->origen) > 0)
	{
		tAerolineaP aux = malloc(sizeof( struct tAerolinea ));
		if (aux == NULL){
			Error("No hay lugar para otro nodo\n");
		}
		aux->cola = primero;
		//Cargo datos de aeropuerto y aerolinea
		
			
		*added = 1;
		return aux;
	}else if((primero->mov_totales > 1) || strcmp(primero->OACI,datos->origen) < 0){
		
		primero->cola = insertRec( primero->cola, datos,archA, added);
	}*/
	return primero;
}

static int
insertarAL( listaAerolineaADT lista, tDatosAL datos)
{
	int ok =0 ;
	lista->primero = insertarALRec(lista->primero, datos, &ok);

	return ok;
}

static int
diaDeLaSemana(int d, int m, int a)
{
	return   (d+=m<3?a--:a-2,23*m/9+d+4+a/4-a/100+a/400)%7  ; //Retorna el dia de la semana 0 es domingo, 1 es lunes, etc;
}

int
cargarDatosAL(listaAerolineaADT lista,char * pathM)
{
	FILE * archM = fopen(pathM,"rt"); //Abro archivo movimientos.csv
	
	
	if(archM == NULL){
		printf("Error al abrir el archivo. \n");
	
	}
	
	int d,m,a;
	int cont = 0;	
	int index;
	char * token;
	tDatosAL * datos = malloc(sizeof(tDatosAL)); 
	char  s[MAX_TEXTO];
	fgets(s,MAX_TEXTO,archM);
	
	
	
	while(fgets(s,MAX_TEXTO,archM) != NULL){
		printf("s = %s\n",s);
		token = strtok(s,";");
		
		cont = 0;
		
		while(token != NULL){
			printf("token = %s \n",token);
			printf("cont = %d \n",cont);
			if(cont == 0){
				sscanf(token,"%02d/%02d/%04d",&d,&m,&a);
				printf("d = %d, m = %d, a = %d \n",d,m,a);
				datos->dia = diaDeLaSemana(d,m,a);
				printf("dia = %d \n",datos->dia);
				
			}else if(cont != 1 && cont != 4 && cont != 8 && cont != 9){ //Si es un campo que me interesa extraigo la data;
			//	fscanf(archM,"%[^;]",s); //Extraigo la string hasta ;
			
				switch(cont){
					case CLASE:
						if(strcmp(token, "Regular") == 0){
							
								index = REGULAR;
						}else if(strcmp(s, "No Regular") == 0){
								index = NO_REGULAR;
						}else{
								index = VUELO_PRIVADO;
						}
						datos->clase_vuelo = index;
					break;
					case CLASIFICACION:
						if(strcmp(token, "Cabotaje") == 0){
							index = 0;
							
						}
						datos->clasificacion_vuelo = index;
					break;
					/*case TIPO:
						
							if(strcmp(token,"Aterrizaje") == 0){
								index = ATERRIZAJE;			
							}else if(strcmp(token,"Despegue") == 0){	
								index = DESPEGUE;
							}	
						datos->tipo_vuelo = index;
					break;
					*/
					case ORIGEN:
						
						datos->origen = token;
						
					break;
					case DESTINO:
						
					
						datos->destino = token;
						
					break;
					case NOMBRE:
						
						
						datos->nombre = token;
						
					break;
				}
				//cont++;
			}
			cont++;
			token =  strtok(NULL, ";");
		}
		printf("nombre = %s\norigen = %s\ndestino = %s\n,clase=%d\nclasificacion=%d\n",datos->nombre,datos->origen,datos->destino,datos->clase_vuelo,datos->clasificacion_vuelo);
	}
}

listaAerolineaADT
nuevaListaAL(void)
{
	return calloc(1,sizeof(struct listaAreolineaCDT));
}
