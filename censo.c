#include <stdio.h>
#include <stdlib.h>
#include "listaAeropuerto.h"

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
		/*while(listaAeropuerto->next != NULL){
			fprintf(archivoDest, "%s;%s;%d\n", listaAeropuerto->next->datos.OACI, listaAeropuerto->next->datos.denominacion, listaAeropuerto->next->mov_totales);
			listaAeropuerto->next = listaAeropuerto->next->siguiente;
		}*/
	}
	fprintf(archivoDest, "%s;%s;%d\n", listaAeropuerto->proximo->datos.oaci, listaAeropuerto->proximo->datos.denom, listaAeropuerto->proximo->mov_totales);
	proximoAP(listaAeropuerto);
	fclose(archivoDest);
}	

/*
void query2(listaAeropuertoADT listaAeropuerto){
	FILE * archivoDest = fopen("dia_semana.csv", "w+t");
	char dias[7][10] = {"lunes", "martes", "miércoles", "jueves", "viernes", "sábado", "domingo"};
	int cantCab, cantInter, dia = 0, i;
	toBegin(listaAeropuerto);
	tAeropuertoP auxAerop = listaAeropuerto->proximo;
	while (auxAerop != NULL){
		cantCab = cantInter = 0;
		for (i = 0; i < 3;i++){
			cantCab += cant_mov_no_regulares[dia][i].cant_cabotaje;
			cantInter += cant_mov_no_regulares[dia][i].cant_internacional;
		}
		fprintf(archivo, "%s;%d;%d;%d", dias[dia], cantCab;cantInter;cantCab + cantInter);
		auxAerop = auxAerop->tail;
		dia++;
	}
	fclose(archivoDest);
}

void query3(listaAeropuertoADT listaAeropuerto){
	FILE * archivoDest = fopen("composicion.csv", "w+t");
	int i,j;
	char *clasificacion[2][3] = {{"Cabotaje", "Regular", "No Regular", "Vuelo Privado"}, {"Internacional", "Regular", "No Regular", "Vuelo Privado"}}
	d
*/
