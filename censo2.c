#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#include "listaAeropuertoADT.h"
#include "listaParesADT.h"
#include "listaAerolineaADT.h"

/* Funcion:  		cargarAeropuertos
 * Uso:  		if( cargarAeropuertos(lista,pathA) ...
 * -------------------------------------------------------------------
 * Descripción: 	Abre el archívo que contiene la data de los aeropuertos, extrae el OACI de cada aeropuerto, y si este no es " ", 
 			extrae la denominación, la provincia y llama a insertarAP para agregar el aeropuerto a la lista.
 			Retorna 0 si se pudo abrir el archivo y agregar todos los aeropuertos válidos a la lista,
			retorna 1 en el caso contrario o si habían aeropuertos repetidos en el archívo.
 * -------------------------------------------------------------------
 * Precondicion:	Lista válida, previamente creada.
 * Postcondicion: 	Lista cargada con la data de aeropuertos.
 */
int cargarAeropuertos(listaAeropuertoADT listaAP, char * pathA);


/* Funcion:  		cargarMovimientos
 * Uso:  		if( cargarMovimientos(listaAL,listaAP,listaPares,pathM) ...
 * -------------------------------------------------------------------
 * Descripción: 	Abre el archívo que contiene la data de los movimientos. Extraigo la fecha,clase,clasificación,tipo,origen
 			destino y nombre de aerolíena en cada movimiento.
			Si la clasificacion es cabotaje y  el nombre pertenece a una aerolínea, lo mando como parametro en insertarLA, 
			para agregarlo a la lista de aerolíneas.
			Luego si el tipo es despegue/aterrizaje mando el origen/destino a la funcion agregarMovAP, para que le sume un
			movimiento a dicho aeropuerto en la lista de aeropuertos.
			Si el aeropuerto se encontró en la lista y el mov. era cabotaje, llamo a sonDistintasProv, para obtener las
			provincias de los OACI origen y destino y mandarlas como parametró en la función insertarPares, la cual
			agrega  y/o suma un movimiento a los pares de provincias que comparten movimientos.
			
			Retorna 0 si se pudo abrir el archívo y no ocurrió ningún error en las funciones utilizadas.
			Retorna 1 en caso contrario.
			
 * -------------------------------------------------------------------
 * Precondicion:	Listas válidas, previamente creadas.La listaAP debe estar cargada con la data de aeropuertos.	
 * Postcondicion: 	Listas ordenadas de aeropuertos, aerolineas y pares de provincias con datos cargados.
 */
int cargarMovimientos(listaAerolineaADT listaAL,listaAeropuertoADT listaAP,listaParesADT listaPares,char * pathM);



#define MAX_TEXTO 400 //Máxima cantidad de letras para cada oración de los archívos. Si esta se supera los resultados de las querys serán erróneos.
#define MAX_CLASIF 15 //Máxima cantidad de letras para las clasificaciones de los movimientos.
#define MAX_CLASE 40 //Máxima cantidad de letras para las clases de los movimientos.
#define MAX_TIPO 12 //Máxima cantidad de letras para los tipos de los movimientos.

#define FECHA 0
#define CLASE 2
#define CLASIFICACION 3
#define TIPO 4
#define ORIGEN 5
#define DESTINO  6
#define NOMBRE 7

typedef struct tDatosAP{
  char  oaci[MAX_OACI];
  char  * denom;
  char * prov;
}tDatosAP;

typedef struct tDatosMov{
	char  origen[MAX_OACI];
	char   destino[MAX_OACI];
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
		
	
		query2(listaAP, &ok);
	
		
		query3(listaAP, &ok);
		
	
		query4(listaPares, &ok);	

	
		query5(listaAL,&ok);
		
	}
	freeAP(listaAP);
	freeAL(listaAL);
	freePares(listaPares);

	
	return ok;
	



}


//Retorna el dia de la semana segun el dia, mes y año :0 es domingo, 1 es lunes, etc;
static int
diaDeLaSemana(int d, int m, int a)
{
	return   (d+=m<3?a--:a-2,23*m/9+d+4+a/4-a/100+a/400)%7  ; 
}


int
cargarAeropuertos(listaAeropuertoADT listaAP, char * pathA)
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
					
					
					//printf("aux = %s \n",aux);
					
					if(cont == OACI){
						if(strcmp(token," ") == 0){
							valido = 0;
							

						}else{		
          
         						strcpy(datos.oaci,token);
							
						}

					}else if(valido){
								
						aux = malloc(strlen(token) +1);
						if(aux == NULL){
							printf("Error: no se pudo usar malloc. \n");
							return 0;
						}
						strcpy(aux,token);
						
						if(cont == DENOMINACION){
							datos.denom = aux;
						}else{
							datos.prov = aux;
						}
						
					}

				
				
				}
				cont++;

				token =  strtok(NULL, ";");	

			}	
			
			if(valido){ //Si es valido el aeropuerto tiene OACI
					if(!insertarAP(listaAP,datos.oaci,datos.denom,datos.prov)){
						printf("Error al cargar datos \n");
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
	char * oaciAux;
	int esCabotaje = 0;
	char * provincias[2];
	while(fgets(s,MAX_TEXTO,archM) != NULL){

		token = strtok(s,";");	
		cont = 0;
		esCabotaje = 0;
		while(token != NULL){
			if(cont == 0){
				sscanf(token,"%02d/%02d/%04d",&d,&m,&a);
				datos.dia = diaDeLaSemana(d,m,a);		
			}else{
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
					case ORIGEN:	
					
            					strcpy(datos.origen,token);
							
					
					break;
						
					case DESTINO:
						
            					strcpy(datos.destino,token);
									
					break;
						
					case NOMBRE:
						if(strcmp(datos.clasificacion,"Cabotaje") == 0){
							esCabotaje = 1;
							datos.nombre = malloc(strlen(token) +1);
							if(datos.nombre == NULL){
								printf("Error: no se pudo usar malloc. \n");
								return 0;
							}
							strcpy(datos.nombre,token);
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
					break;
				}
			} 			
		
			cont++;
			
			token =  strtok(NULL,";");
		}
		
		if(strcmp(datos.tipo,"Despegue") == 0){
			oaciAux = datos.origen;
		}else {
			oaciAux =datos.destino;
		}
		
		if(agregarMovAP(listaAP,oaciAux,datos.clase,datos.clasificacion,datos.dia)){
			
				if(esCabotaje && sonDistintasProv(listaAP,datos.origen,datos.destino,provincias)){
			
					if(!insertarPares(listaPares,provincias)){
						printf("Error al insertar en la lista de pares.\n.");
						free(datos.nombre);
						return 0;
					}
				}
		}
	
		

		
	}
		fclose(archM);
		return 1;

}

