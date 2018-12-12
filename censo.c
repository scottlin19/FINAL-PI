#include <stdio.h>
#include <stdlib.h>
#include "listaAeropuertoADT.h"
#include "listaAerolineaADT.h"

void query1(listaAeropuertoADT listaAeropuerto);

int main(int argc, char * argv[])
{
	listaAeropuertoADT listaAeropuerto = nuevaListaAP();
	if (cargarDatosAP(listaAeropuerto, "../aer.csv")){
		printf("funca\n");
	}
	query1(listaAeropuerto);
	return 0;
	



}


void query1(listaAeropuertoADT listaAeropuerto){
	alPrincipioAP(listaAeropuerto);
	FILE * archivoDest = fopen("movimientos_aeropuertos.csv", "w+t");
	if (archivoDest == NULL){
		printf("Error al crear/reemplazar archivo");
	}
	else {
		while(listaAeropuerto->proximo != NULL){
			fprintf(archivoDest, "%s;%s;%d\n", listaAeropuerto->next->datos.OACI, listaAeropuerto->next->datos.denominacion, listaAeropuerto->next->mov_totales);
			proximoAP(listaAeropuerto);
		}
	}
	fclose(archivoDest);
}	


void query2(listaAeropuertoADT listaAeropuerto){
	FILE * archivoDest = fopen("dia_semana.csv", "w+t");
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
/*
void query3(listaAeropuertoADT listaAeropuerto){
	FILE * archivoDest = fopen("composicion.csv", "w+t");
	int i,j;
	char *clasificacion[2][3] = {{"Cabotaje", "Regular", "No Regular", "Vuelo Privado"}, {"Internacional", "Regular", "No Regular", "Vuelo Privado"}}
	int total[2][3];
*/
