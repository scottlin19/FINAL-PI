


#ifndef LISTAALADT_H_
#define LISTAALADT_H_
typedef struct listaAerolineaCDT* listaAerolineaADT;

listaAerolineaADT nuevaListaAL(void);

int insertarAL( listaAerolineaADT lista, char * nombre);
int esAerolinea(char * nombre);
void query5(listaAerolineaADT listaAL, int *ok);

#endif
