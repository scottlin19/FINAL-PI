#ifndef LISTAPARESADT_H_
#define LISTAPARESADT_H_

typedef struct listaParesCDT * listaParesADT;

int insertarPares(nodoP primero,char * provincias[], int * ok);

void query5(listaParesADT lista, int *ok);
#endif
