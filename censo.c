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
	
	query1(listaAP, &ok);
	printf("ok vale %d\n", ok);
	query2(listaAP, &ok);
	printf("ok vale %d\n", ok);
	
	return ok;
	



}
