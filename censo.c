#include <stdio.h>
#include <stdlib.h>
#include "listaAeropuertoCDT.c"
#include "listaAerolineaADT.h"

void query1(listaAeropuertoADT listaAeropuerto, int *ok);
void query2(listaAeropuertoADT listaAeropuerto, int *ok);

int main(int argc, char * argv[])
{
	int ok = 0;
	listaAeropuertoADT listaAP = nuevaListaAP();
	listaAerolineaADT listaAL = nuevaListaAL();
	if (cargarDatosAP(listaAP, "../aer.csv")){
		printf("funca\n");
	}
	//if (cargarDatosAL(listaAL, listaAP, "../mov.csv")){
	//	printf("funca\n");
	//}
	query1(listaAP, &ok);
	printf("ok vale %d\n", ok);
	query2(listaAP, &ok);
	printf("ok vale %d\n", ok);
	return ok;
	



}


void query1(listaAeropuertoADT listaAeropuerto, int *ok){
	alPrincipioAP(listaAeropuerto);
	FILE * archivoDest = fopen("movimientos_aeropuertos.csv", "w+t");
	if (archivoDest == NULL){
		printf("Error al crear/reemplazar archivo");
		*ok = 1;
	}
	else {
		fprintf(archivoDest, "OACI;Denominación;Movimientos\n");
		while(listaAeropuerto->proximo != NULL){
			printf("oaci vale %s\n", listaAeropuerto->proximo->datos.oaci);
			if (listaAeropuerto->proximo->mov_totales != 0){
				fprintf(archivoDest, "%s;%s;%d\n", listaAeropuerto->proximo->datos.oaci, listaAeropuerto->proximo->datos.denom, listaAeropuerto->proximo->mov_totales);
			}
			proximoAP(listaAeropuerto);
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
		char dias[7][11] = {"lunes", "martes", "miércoles", "jueves", "viernes", "sábado", "domingo"};
		int total[7][2];
		int dia = 0, clase;
		alPrincipioAP(listaAeropuerto);
		while (listaAeropuerto->proximo != NULL){
			for (dia = 0; dia < 7; dia++){	
				for (clase = 0; clase < 3;clase++){
					total[dia][0] += listaAeropuerto->proximo->cant_mov[dia][clase].cant_cabotaje;
					total[dia][1] += listaAeropuerto->proximo->cant_mov[dia][clase].cant_internacional;
				}
			}
			listaAeropuerto->proximo = listaAeropuerto->proximo->cola;
		}
		for (dia = 0; dia < 7; dia++){
			fprintf(archivoDest, "%s;%d;%d;%d\n", dias[dia], total[dia][0],total[dia][1],total[dia][0] + total[dia][1]);
		}
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
		int i,j;
		char *clasificacion[2][3] = {{"Cabotaje", "Regular", "No Regular", "Vuelo Privado"}, {"Internacional", "Regular", "No Regular", "Vuelo Privado"}}
		int total[2][3];
		alprincipioAP(listaAeropuerto);
*/
