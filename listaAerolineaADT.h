


#ifndef LISTALADT_H_
#define LISTALADT_H_
typedef struct listaAerolineaCDT* listaAerolineaADT;

listaAerolineaADT nuevaListaAL(void);

int
cargarDatosAL(listaAerolineaADT listaAL,listaAeropuertoADT listaAP,char * pathM);
#endif
