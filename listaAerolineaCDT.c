
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
	char  origen[10];
	char  destino[10];
	char  nombre[30];
	char  clase[40];
	char  clasificacion[40];
	int dia;
}tDatosAL;

struct listaAerolineaCDT{
	
	tAerolineaP primero;
	tAerolineaP proximo;

};

static tAerolineaP insertarALRec(tAerolineaP primero, tDatosAL datos, int * ok) {
	
	if( primero == NULL)
	{
		tAerolineaP aux = calloc(1,sizeof( struct tAerolinea ));
		if (aux == NULL){
			printf("Error: No hay lugar para otro nodo\n");
		}
		aux->cola = primero;
		//Cargo datos de aeropuerto y aerolinea
		
		*ok = 1;
		return aux;
	}else if(strcmp(primero->nombre,datos.nombre) == 0){
		(primero->cant_mov_cabotaje)++;
		*ok = 1;
		
	}else{	
		primero->cola = insertarALRec( primero->cola, datos, ok);
		if(primero->cant_mov_cabotaje - primero->cola->cant_mov_cabotaje < 0){
				tAerolineaP aux = primero->cola->cola;
				primero->cola->cola = primero;
				primero = primero->cola;
				primero->cola->cola = aux;
		}
	}
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

static int
esAerolinea(char * nombre)
{
	return ((strcmp(nombre," ") != 0 )&& (strcmp(nombre,"N/A") != 0));
}

int
cargarDatosAL(listaAerolineaADT listaAL,listaAeropuertoADT listaAP,char * pathM)
{
	FILE * archM = fopen(pathM,"rt"); //Abro archivo movimientos.csv
	
	printf("asd 1 \n");
	if(archM == NULL){
		printf("Error al abrir el archivo. \n");
	
	}
	
	int d,m,a;
	int cont = 0;	
	char * token;
	
	char  s[MAX_TEXTO];
	fgets(s,MAX_TEXTO,archM);
	
		printf("asd 2 \n");
	
	while(fgets(s,MAX_TEXTO,archM) != NULL){
		printf("s = %s\n",s);
		token = strtok(s,";");
		printf("token  = %s\n",token);
		cont = 0;
		tDatosAL  datos; 
		while(token != NULL){
			//printf("token = %s \n",token);
			//printf("cont = %d \n",cont);
			if(cont == 0){
				sscanf(token,"%02d/%02d/%04d",&d,&m,&a);
				printf("d = %d, m = %d, a = %d \n",d,m,a);
				datos.dia = diaDeLaSemana(d,m,a);
				//printf("dia = %d \n",datos->dia);
				
			}else if(cont != 1 && cont != 4 && cont != 8 && cont != 9){ //Si es un campo que me interesa extraigo la data;
			//	fscanf(archM,"%[^;]",s); //Extraigo la string hasta ;
			
				switch(cont){
					case CLASE:
						
						strcpy(datos.clase,token);
					break;
					case CLASIFICACION:
						
						strcpy(datos.clasificacion,token);
					break;
				
					case ORIGEN:
						
						strcpy(datos.origen,token);
						
					break;
					case DESTINO:
						
					
						strcpy(datos.destino,token);
						
					break;
					case NOMBRE:
						
						
						strcpy(datos.nombre,token);
						
					break;
				}
				//cont++;
			}
			cont++;
			token =  strtok(NULL, ";");
		}
		printf("nombre = %s\norigen = %s\ndestino = %s\nclase=%s\nclasificacion=%s\n",datos.nombre,datos.origen,datos.destino,datos.clase,datos.clasificacion);
		
		if(!agregarMovAP(listaAP,datos.origen,datos.clase,datos.clasificacion,datos.dia)){
			printf("Error al sumarle un movimiento al aeropuerto. \n");
			return 1;
		}
		if(esAerolinea(datos.nombre) && strcmp(datos.clasificacion,"Cabotaje") == 0){
			
			if( !insertarAL(listaAL,datos)){
				printf("Error al insertar los datos de la aerolinea.\n");
				return 1;
			}
		}
		
	}
	return 0;
}

listaAerolineaADT
nuevaListaAL(void)
{
	return calloc(1,sizeof(struct listaAerolineaCDT));
}

