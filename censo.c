#include <stdio.h>
#include <stdlib.h>
#include "listaAeropuertoADT.h"
#include "listaParesADT.h"
#include "listaAerolineaADT.h"

int cargarMovimientos(listaAerolineaADT listaAL,listaAeropuertoADT listaAP,listaParesADT listaPares,char * pathM);


#define MAX_TEXTO 400
#define MAX_OACI 15
#define MAX_NOMBRE 30
#define MAX_CLASE 40
#define MAX_TIPO 10
#define MAX_CLASIF 40

#define FECHA 0
#define CLASE 2
#define CLASIFICACION 3
#define TIPO 4
#define ORIGEN 5
#define DESTINO  6
#define NOMBRE 7

typedef struct tDatosMov{
	char  origen[MAX_OACI];
	char  destino[MAX_OACI];
	char  nombre[MAX_NOMBRE];
	char  clase[MAX_CLASE];
	char  clasificacion[MAX_CLASIF];
	char tipo[MAX_TIPO];
	
	int dia;
}tDatosMov;

int main(int argc, char * argv[])
{
	int ok = 0;
	listaAeropuertoADT listaAP = nuevaListaAP();
	listaAerolineaADT listaAL = nuevaListaAL();
	listaParesADT listaPares = nuevaListaPares();
	if (cargarDatosAP(listaAP, "../aer.csv")){
		printf("funca\n");
	}
	if (cargarDatosAL(listaAL, listaAP,listaPares, "../mov.csv")){
		printf("funca\n");
	}
	query1(listaAP, &ok);
	printf("ok vale %d\n", ok);
	query2(listaAP, &ok);
	printf("ok vale %d\n", ok);
	query3(listaAP, &ok);
	printf("ok vale %d\n", ok);
	query4(listaPares, &ok);	
	printf("ok vale %d\n", ok);
	query5(listaAL,&ok);
	printf("ok vale %d\n", ok);
	return ok;
	



}

static int
diaDeLaSemana(int d, int m, int a)
{
	return   (d+=m<3?a--:a-2,23*m/9+d+4+a/4-a/100+a/400)%7  ; //Retorna el dia de la semana 0 es domingo, 1 es lunes, etc;
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
	while(fgets(s,MAX_TEXTO,archM) != NULL){

		token = strtok(s,";");	
		cont = 0;
		
		while(token != NULL){
			if(cont == 0){
				sscanf(token,"%02d/%02d/%04d",&d,&m,&a);
				datos.dia = diaDeLaSemana(d,m,a);		
			}else if(cont != 1 && cont != 8 && cont != 9){ //Si es un campo que me interesa extraigo la data;
		
			
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
						strcpy(datos.nombre,token);				
					break;
				}
				//cont++;
			}
			cont++;
			
			token =  strtok(NULL,";");
		}
		
		if(strcmp(datos.clasificacion,"Cabotaje") == 0){// Es cabotaje;
			char * provincias[2];
			
			if(sonDistintasProv(listaAP,datos.origen,datos.destino,provincias)){
			
				if(!insertarPares(listaPares,provincias)){
					printf("Error al insertar en la lista de pares.\n.");
					return 1;
				}
			}
			
		}
		
		char * aux;
		if(strcmp(datos.tipo,"Despegue") == 0){
			aux = datos.origen;
		}else{
			aux = datos.destino;
		}

		if(!agregarMovAP(listaAP,aux,datos.clase,datos.clasificacion,datos.dia)){
			printf("Error al sumarle un movimiento al aeropuerto.\n");
			return 1;
		}
		if(esAerolinea(datos.nombre) && strcmp(datos.clasificacion,"Cabotaje") == 0){
		
			if( !insertarAL(listaAL,datos.nombre)){
				printf("Error al insertar los datos de la aerolinea.\n");
				return 1;
			}
		}
	}
		return 0;

}
