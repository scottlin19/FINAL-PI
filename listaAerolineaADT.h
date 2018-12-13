


#ifndef LISTAALADT_H_
#define LISTAALADT_H_
typedef struct listaAerolineaCDT* listaAerolineaADT;

listaAerolineaADT nuevaListaAL(void);

int
cargarDatosAL(listaAerolineaADT listaAL,listaAeropuertoADT listaAP,char * pathM);

void query5(listaAerolineaADT listaAL, int *ok);

#endif
