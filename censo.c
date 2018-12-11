#include <stdio.h>
#include <stdlib.h>
#include "listaAeropuerto.h"

int main(int argc, char * argv[])
{
	listaAeropuertoADT listaAeropuerto = nuevaLista();
	cargarDatos(listaAeropuerto, "../aer.csv", "../mov.csv");
	return 0;
	



}

/*
void query1(listaAeropuertoADT listaAeropuerto){
	toBegin(listaAeropuerto);
	tAeropuertoP aux = listaAeropuerto->next;
	FILE * archivoDest = fopen("movimientos_aeropuertos.csv", "w+t");
	if (archivoDest == NULL){
		printf("Error al crear/reemplazar archivo");
	}
	else {
		while(aux != NULL){
			fprintf(archivoDest, "%s;%s;%d\n", aux->OACI, aux->denominacion, aux->mov_totales);
			aux = aux->tail;
		}
	}
	fclose(archivoDest);
}	

void query2(listaAeropuertoADT listaAeropuerto)
*/
