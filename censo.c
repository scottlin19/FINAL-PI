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
void query1(listaAeropuertoADT lsitaAeropuerto){
	FILE * archivoDest = fopen("movimientos_aeropuertos.csv", "w+t");
	if (archivoDest == NULL){
		printf("Error al crear/reemplazar archivo");
	}
	else {
		
*/
