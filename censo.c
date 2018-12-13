#include <stdio.h>
#include <stdlib.h>
#include "listaAeropuertoADT.h"
#include "listaParesADT.h"
#include "listaAerolineaADT.h"

int main(int argc, char * argv[])
{
	int ok = 0;
	listaAeropuertoADT listaAP = nuevaListaAP();
	listaAerolineaADT listaAL = nuevaListaAL();
	listaParesADT listaPares = nuevaListaPares();
	if (cargarDatosAP(listaAP, argv[1])){
		printf("funca\n");
	}
	if (cargarDatosAL(listaAL, listaAP,listaPares, argv[2])){
		printf("funca\n");
	}
	query1(listaAP, &ok);
	printf("ok vale %d\n", ok);
	query2(listaAP, &ok);
	printf("ok vale %d\n", ok);
	query3(listaAP, &ok);
	printf("ok vale %d\n", ok);
	//query4(listaPares, &ok);	
	//printf("ok vale %d\n", ok);
	query5(listaAL,&ok);
	printf("ok vale %d\n", ok);
	return ok;
	



}
