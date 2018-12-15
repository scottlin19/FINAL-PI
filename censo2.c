#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#include "listaAeropuertoADT.h"
#include "listaParesADT.h"
#include "listaAerolineaADT.h"

int cargarMovimientos(listaAerolineaADT listaAL,listaAeropuertoADT listaAP,listaParesADT listaPares,char * pathM);
int cargarAeropuertos(listaAeropuertoADT lista, char * pathA);

#define MAX_TEXTO 400
#define MAX_CLASIF 15
#define MAX_CLASE 40
#define MAX_TIPO 12

#define OACI 1
#define DENOMINACION 4
#define PROVINCIA 21
#define DIAS_SEMANA 7

#define FECHA 0
#define CLASE 2
#define CLASIFICACION 3
#define TIPO 4
#define ORIGEN 5
#define DESTINO  6
#define NOMBRE 7

typedef struct tDatosAP{
  char * oaci;
  char * denom;
  char * prov;
}tDatosAP;

typedef struct tDatosMov{
	char * origen;
	char  * destino;
	char  * nombre;
	char  clase[MAX_CLASE];
	char   clasificacion[MAX_CLASIF];
	char  tipo[MAX_TIPO];
	
	int dia;
}tDatosMov;



int main(int argc, char * argv[])
{
	int ok = 0;
	listaAeropuertoADT listaAP = nuevaListaAP();
	listaAerolineaADT listaAL = nuevaListaAL();
	listaParesADT listaPares = nuevaListaPares();
	if (!cargarAeropuertos(listaAP, argv[1])){
		ok = 1;
	}
	if (!cargarMovimientos(listaAL, listaAP,listaPares, argv[2])){
		
		ok = 1;
	
	}
	if(!ok){	
		query1(listaAP, &ok);
		printf("se hizo la query 1, ok vale %d\n", ok);
	
		query2(listaAP, &ok);
		printf("se hizo la query 2, ok vale %d\n", ok);
		
		query3(listaAP, &ok);
		printf("se hizo la query 3, ok vale %d\n", ok);
	
		query4(listaPares, &ok);	
		printf("se hizo la query 4, ok vale %d\n", ok);
	
		query5(listaAL,&ok);
		printf("se hizo la query 5, ok vale %d\n", ok);
	}
	freeAP(listaAP);
	freeAL(listaAL);
	freePares(listaPares);

	
	return ok;
	



}

static int
diaDeLaSemana(int d, int m, int a)
{
	return   (d+=m<3?a--:a-2,23*m/9+d+4+a/4-a/100+a/400)%7  ; //Retorna el dia de la semana 0 es domingo, 1 es lunes, etc;
}


int
cargarAeropuertos(listaAeropuertoADT lista, char * pathA)
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
	tDatosAP  datos;
	char * aux;
  	
	fgets(s,MAX_TEXTO,archA); //Me salto la primera linea del archivo que contiene los nombres  de los campos.
	
	
	while(fgets(s,MAX_TEXTO,archA )!= NULL){
		
			token = strtok(s,";");
			cont = 0;
			valido =1;
			
			while((token != NULL) && valido){
				if(cont == OACI || cont == DENOMINACION || cont == PROVINCIA){
					
					aux = malloc(strlen(token) +1);
					if(aux == NULL){
						printf("Error: no se pudo usar malloc. \n");
						return 0;
					}
					strcpy(aux,token);
					
					//printf("aux = %s \n",aux);
					
				
					if(cont == OACI){
						if(strcmp(token," ") == 0){
							valido = 0;
							free(aux);

						}else{		
          
         						datos.oaci = aux;
							
						}

					}else if(valido && cont == DENOMINACION){	
        					datos.denom = aux;

					}else if(valido && cont == PROVINCIA){	
          					datos.prov =	aux;
					
					}

				
				
				}
				cont++;

				token =  strtok(NULL, ";");	

			}	
			
			if(valido){ //Si es valido el aeropuerto tiene OACI
					if(!insertarAP(lista,datos.oaci,datos.denom,datos.prov)){
						printf("Error al cargar datos \n");
						free(datos.oaci);
						free(datos.denom);
						free(datos.prov);
						return 0;
					}

			}
	
	
	}
	fclose(archA);
	return 1;
}

int
cargarMovimientos(listaAerolineaADT listaAL,listaAeropuertoADT listaAP,listaParesADT listaPares,char * pathM)
{
FILE * archM = fopen(pathM,"rt"); //Abro archivo movimientos.csv
		
	if(archM == NULL){
		printf("Error al abrir el archivo. \n");
	}
	
	int d,m,a;
	int cont = 0;	
	char * token;	
	char  s[MAX_TEXTO];	
	fgets(s,MAX_TEXTO,archM);
	
	tDatosMov  datos; 
	char * aux;
	
	
	while(fgets(s,MAX_TEXTO,archM) != NULL){

		token = strtok(s,";");	
		cont = 0;
		
		while(token != NULL){
			if(cont == 0){
				sscanf(token,"%02d/%02d/%04d",&d,&m,&a);
				datos.dia = diaDeLaSemana(d,m,a);		
			}else if( cont == NOMBRE){ //Si es un campo que me interesa extraigo la data;
				//cont == ORIGEN || cont == DESTINO  || 
				aux = malloc(strlen(token) +1);
				strcpy(aux,token);
				printf("aux = %s \n",aux);
				if(aux == NULL){
					printf("Error: no se pudo usar malloc. \n");
					return 0;
				}
				datos.nombre = aux;	
				/*switch(cont){
					/*	
					case ORIGEN:		
            					datos.origen  = aux;
					break;
						
					case DESTINO:
             					datos.destino = aux;	
					break;
						
					case NOMBRE:
            					datos.nombre = aux;		
					break;
				}
			*/
				//cont++;
			}else if(cont == CLASE || cont == CLASIFICACION || cont == TIPO){
				switch(cont){
						
					case CLASE:		
            					strcpy(datos.clase,token);
					break;
						
					case CLASIFICACION:
             					strcpy(datos.clasificacion,token);	
					break;
						
					case TIPO:
            					strcpy(datos.tipo,token);		
					break;
				}
			}
			cont++;
			
			token =  strtok(NULL,";");
		}
		
	
		
	/*	char * oaciAux;
		if(strcmp(datos.tipo,"Despegue") == 0){
			oaciAux = datos.origen;
		}else{
			oaciAux = datos.destino;
		}
*/
		/*if(!agregarMovAP(listaAP,oaciAux,datos.clase,datos.clasificacion,datos.dia)){
			printf("Error al sumarle un movimiento al aeropuerto.\n");
			free(datos.origen);
			free(datos.destino);
			free(datos.nombre);
			return 0;
		}*/
		if(strcmp(datos.clasificacion,"Cabotaje") == 0){// Es cabotaje;
		/*	char * provincias[2];
			
			if(sonDistintasProv(listaAP,datos.origen,datos.destino,provincias)){
			
				if(!insertarPares(listaPares,provincias)){
					printf("Error al insertar en la lista de pares.\n.");
					free(datos.origen);
					free(datos.destino);
					free(datos.nombre);
					return 0;
				}
			}*/
			if(esAerolinea(datos.nombre)){
		
				if( !insertarAL(listaAL,datos.nombre)){
					printf("Error al insertar los datos de la aerolinea.\n");
					free(datos.nombre);
					return 0;
				}
			}else{
				free(datos.nombre);
			}
			
		}
		
		free(datos.origen);
		free(datos.destino);
		
	}
		fclose(archM);
		return 1;

}

