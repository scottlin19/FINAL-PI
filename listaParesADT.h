#ifndef LISTAPARESADT_H_
#define LISTAPARESADT_H_

typedef struct listaParesCDT * listaParesADT;

int insertarPares(listaParesADT lista,char * origen, char * destino);

void query5(listaParesADT lista, int *ok);
#endif
