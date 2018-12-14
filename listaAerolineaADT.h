


#ifndef LISTAALADT_H_
#define LISTAALADT_H_
typedef struct listaAerolineaCDT* listaAerolineaADT;

listaAerolineaADT nuevaListaAL(void);

int
cargarDatosAL(listaAerolineaADT listaAL,listaAeropuertoADT listaAP,listaParesADT listaPares,char * pathM);

void freeAL(listaAerolineaADT listaAL);

void query5(listaAerolineaADT listaAL, int *ok);

#endif
