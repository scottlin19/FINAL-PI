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

//Numero del campo dentro de cada oración de movimientos
#define FECHA 0      
#define CLASE 2
#define CLASIFICACION 3
#define TIPO 4
#define ORIGEN 5
#define DESTINO  6
#define NOMBRE 7        

int main(int argc, char * argv[])
{
	int ok = 0;
	//Creo lista de aeropuertos, de aerolineas y de pares de provincias que comparten movimientos.
	
	listaAeropuertoADT listaAP = nuevaListaAP();
	listaAerolineaADT listaAL = nuevaListaAL();
	listaParesADT listaPares = nuevaListaPares();
	
	//Cargo data de aeropuertos a la lista y si hubo error, ok = 1
	if (!cargarAeropuertos(listaAP, argv[1])){
		ok = 1;
	}
	//Cargo data de movimientos a las lista y si hubo error, ok = 1
	if (!cargarMovimientos(listaAL, listaAP,listaPares, argv[2])){
		
		ok = 1;
	
	}
	//Si no hubo errores, hago las querys
	if(!ok){	
		query1(listaAP, &ok);
		
	
		query2(listaAP, &ok);
	
		
		query3(listaAP, &ok);
		
	
		query4(listaPares, &ok);	

	
		query5(listaAL,&ok);
		
	}
	//Destruyo las listas y libero espacio reservado.
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

	FILE * archA = fopen(pathA,"rt"); //Abro archivo de aeropuertos.
		
	if(archA == NULL){  //Si el archivo no se pudo abrir retorno 1.
		printf("Error al abrir los archivos. \n");
		return 1;
	
	}
	
	//Variables que necesito para guardar los datos del archivo de aeropuertos.
	char  oaci[MAX_OACI];
 	char  * denom;
	char * prov;
	
	//Variales auxiliares
	int cont;	
	int valido;
	char * token;
	char  s[MAX_TEXTO];
	char * aux;
  	
	fgets(s,MAX_TEXTO,archA); //Salteo la primera línea del archívo de aeropuertos.
	
	
	while(fgets(s,MAX_TEXTO,archA )!= NULL){ //Mientras haya aeropuertos que leer, que lea.
		
			token = strtok(s,";"); //Divido cada oracion de aeropuertos en strings, usando como delimitador el ;
		
			cont = 0;
			valido = 1;
			
			while((token != NULL) && valido){
				if(cont == OACI || cont == DENOMINACION || cont == PROVINCIA){
					
					
					//printf("aux = %s \n",aux);
					
					if(cont == OACI){
						if(strcmp(token," ") == 0){
							valido = 0;
							

						}else{		
          
         						strcpy(oaci,token);
							
						}

					}else if(valido){
								
						aux = malloc(strlen(token) +1);
						if(aux == NULL){
							printf("Error: no se pudo usar malloc. \n");
							return 0;
						}
						strcpy(aux,token);
						
						if(cont == DENOMINACION){
							denom = aux;
						}else{
							prov = aux;
						}
						
					}

				
				
				}
				cont++;

				token =  strtok(NULL, ";");	

			}	
			
			if(valido){ //Si es valido el aeropuerto tiene OACI
					if(!insertarAP(listaAP,oaci,denom,prov)){
						printf("Error al cargar datos \n");
						free(denom);
						free(prov);
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
	FILE * archM = fopen(pathM,"rt"); //Abro archivo de movimientos.
		
	if(archM == NULL){   //Si el archivo no se pudo abrir retorno 1.
		printf("Error al abrir el archivo. \n");
		return 1;
	}
	
	//Variables donde guardo la informacion que necesito de los movimientos
	int dia;
	int  clase; // 0 = Regular, 1= No Regular, 2 = Vuelo Privado 
	int   clasificacion; //0 = Cabotaje, 1 = Internacional , 2 = N/A
	int  tipo; // 0 = Despegue , 1 = Aterrizaje
	char  origen[MAX_OACI];
	char   destino[MAX_OACI];
	char  * nombre;
	
	//Variables auxiliares
	char  s[MAX_TEXTO];
	char * provincias[2];
	char * token;		
	char * oaciAux;
	int d,m,a;
	int cont;	
	
	
	fgets(s,MAX_TEXTO,archM); //Salteo la primera línea del archívo de movimientos.
	

	
	while(fgets(s,MAX_TEXTO,archM) != NULL){ //Mientras haya movimientos que leer, que lea.

		token = strtok(s,";");	//Divido cada oracion de movimientos en strings, usando como delimitador el ;
		cont = 0;
		esCabotaje = 0;
		
		while(token != NULL){ //Mientras haya campos que leer, que los lea.
			if(cont == 0){
				sscanf(token,"%02d/%02d/%04d",&d,&m,&a);
				dia = diaDeLaSemana(d,m,a);		
			}else{
				switch(cont){
						
					case CLASE:		
						if(strcmp(token,"Regular") == 0){
							clase = REGULAR;
						}else if(strcmp(token,"No Regular") == 0){
							clase = NO_REGULAR;
						}else{
							clase = VUELO_PRIVADO;
						}
					break;
						
					case CLASIFICACION:
             					if(strcmp(token,"Cabotaje") == 0){
							clasificacion = CABOTAJE;
						}else if(strcmp(token,"Internacional") == 0){
							clasificacion = INTERNACIONAL;
						}else{
							clasificacion = NA;
						}		
					break;
						
					case TIPO:
						
            					if(strcmp(token,"Despegue") == 0){
							tipo = 0;
						}else{
							tipo = 1;
						}		
					break;
					case ORIGEN:	
						if(!((clase == VUELO_PRIVADO) &&(tipo == ATERRIZAJE)) ){
            						strcpy(origen,token);
						}
					
					break;
						
					case DESTINO:
						if(!( (clase == VUELO_PRIVADO) && (tipo == DESPEGUE) ){
            						strcpy(destino,token);
						}
									
					break;
						
					case NOMBRE:
						if(clasificacion == CABOTAJE){
						
							nombre = malloc(strlen(token) +1);
							if(nombre == NULL){
								printf("Error: no se pudo usar malloc. \n");
								return 0;
							}
							strcpy(nombre,token);
							if(esAerolinea(nombre)){
		
								if( !insertarAL(listaAL,nombre)){
									printf("Error al insertar los datos de la aerolinea.\n");
									free(nombre);
									return 0;
								}
							}else{
				
								free(nombre);
							}
						}	
					break;
				}
			} 			
		
			cont++;
			
			token =  strtok(NULL,";");
		}
		
		if(tipo == DESPEGUE){
			oaciAux = origen;
		}else {
			oaciAux =destino;
		}
		
		if(agregarMovAP(listaAP,oaciAux,clase,clasificacion,dia)){
			
				if((clasificacion == CABOTAJE) && sonDistintasProv(listaAP,origen,destino,provincias)){
			
					if(!insertarPares(listaPares,provincias)){
						printf("Error al insertar en la lista de pares.\n.");
						free(nombre);
						return 0;
					}
				}
		}
	
		

		
	}
		fclose(archM);
		return 1;

}

