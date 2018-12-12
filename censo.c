#include <stdio.h>
#include <stdlib.h>
#include "listaAeropuertoCDT.c"
#include "listaAerolineaADT.h"

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
	/*
	query1(listaAP, &ok);
	printf("ok vale %d\n", ok);
	query2(listaAP, &ok);
	printf("ok vale %d\n", ok);
	*/
	return ok;
	



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
