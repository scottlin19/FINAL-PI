#include <stdio.h>
#include <stdlib.h>

#include "listaAerolineaADT.h"

void query1(listaAeropuertoADT listaAeropuerto, int *ok);

int main(int argc, char * argv[])
{
	int ok = 0;
	listaAeropuertoADT lista = nuevaListaAP();
	listaAerolineaADT listaAL = nuevaListaAL();
	listaAL->primero->cant_mov_cabotages = 1;
	if (cargarDatosAP(lista, "../aer.csv")){
		printf("funca\n");
	}
	query1(lista, &ok);
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
			fprintf(archivoDest, "%s;%s;%d\n", listaAeropuerto->next->datos.OACI, listaAeropuerto->next->datos.denominacion, listaAeropuerto->next->mov_totales);
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
		char dias[7][10] = {"lunes", "martes", "miércoles", "jueves", "viernes", "sábado", "domingo"};
		int cantCab, cantInter, dia = 0, i;
		alPrincipioAP(listaAeropuerto);
		while (listaAeropuerto->proximo != NULL){
			cantCab = cantInter = 0;
			for (i = 0; i < 3;i++){
				cantCab += listaAeropuerto->proximo->cant_mov[dia][i].cant_cabotaje;
				cantInter += listaAeropuerto->proximo->cant_mov[dia][i].cant_internacional;
			}
			fprintf(archivoDest, "%s;%d;%d;%d", dias[dia], cantCab,cantInter,cantCab + cantInter);
			dia++;
		}
		fclose(archivoDest);
	}
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

*/
