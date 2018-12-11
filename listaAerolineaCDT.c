#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <listaAeropuertoADT.h>

typedef struct tAerolinea {
	char * nombre;
	tMov cant_mov[DIAS_SEMANA]; // Si estan en una aerolinea significa que son vuelos REGULARES.
				
	int mov_totales; // = cantidad de vuelos regulares de la aerolinea
	
	struct tAerolinea * tail;
}tAerolinea;
typedef struct tAerolinea * tAerolineaP;
*/
/*
typedef struct tDatosAL{
	char * origen;
	char * destino;
	char * nombre;
	int tipo_vuelo;
	int clase_vuelo;
	int clasificacion_vuelo;
	int dia;
}tDatosAL;
*/

/*
static tAeropuertoP insertRec(tAeropuertoP primero, tDatos datos,FILE * archA , int * added) {
	
	if( primero == NULL || (primero->mov_totales == 1) && strcmp(primero->OACI,datos->origen) > 0)
	{
		tAeropuertoP aux = malloc(sizeof( struct tAeropuerto ));
		if (aux == NULL){
			Error("No hay lugar para otro nodo\n");
		}
		aux->cola = primero;
		//Cargo datos de aeropuerto y aerolinea
		
			
		*added = 1;
		return aux;
	}else if((primero->mov_totales > 1) || strcmp(primero->OACI,datos->origen) < 0){
		
		primero->cola = insertRec( primero->cola, datos,archA, added);
	}
	return primero;
}
static int
diaDeLaSemana(int d, int m, int a)
{
	return   (d+=m<3?a--:a-2,23*m/9+d+4+a/4-a/100+a/400)%7  ; //Retorna el dia de la semana 0 es domingo, 1 es lunes, etc;
}
*/

/*
void
cargarDatos(listaAeropuertoADT lista,char * pathA)
{
	FILE * archA = fopen(pathA,"rt"); //Abro archivo aeropuerto.csv
	
	
	if(archA == NULL|| archM == NULL){
		printf("Error al abrir los archivos. \n");
	
	}
	
	int d,m,a;
	int cont = 0;	
	int index;
	char * token;
	tDatos * datos = malloc(sizeof(tDatos)); 
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
				
			}else if(cont != 1 && cont != 8 && cont != 9){ //Si es un campo que me interesa extraigo la data;
			//	fscanf(archM,"%[^;]",s); //Extraigo la string hasta ;
			
				switch(cont){
					case CLASE:
						if(strcmp(token, "Regular") == 0){
							
								index = REGULAR;
						}else if(strcmp(s, "No Regular") == 0){
								index = NO_REGULAR;
						}else if(strcmp(s,  "Vuelo Privado con Matrícula Extranjera") == 0 || strcmp(s, "Vuelo Privado con Matrícula Nacional") == 0){
								index = PRIVADO;
						}
						datos->clase_vuelo = index;
					break;
					case CLASIFICACION:
						if(strcmp(token, "Cabotaje") == 0){
							index = CABOTAJE;
							
						}else if (strcmp(token,  "Internacional")  == 0){	
							index = INTERNACIONAL;
							
						}else if (strcmp(token, "N/A") == 0){
							index = NA;
						}
						datos->clasificacion_vuelo = index;
					break;
					case TIPO:
						
							if(strcmp(token,"Aterrizaje") == 0){
								index = ATERRIZAJE;			
							}else if(strcmp(token,"Despegue") == 0){	
								index = DESPEGUE;
							}	
						datos->tipo_vuelo = index;
					break;
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
		printf("nombre = %s\norigen = %s\ndestino = %s\n,clase=%d\nclasificacion=%d\ntipo=%d\n",datos->nombre,datos->origen,datos->destino,datos->clase_vuelo,datos->clasificacion_vuelo,datos->tipo_vuelo);
	}
}
