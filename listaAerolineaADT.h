#ifndef LISTAALADT_H_
#define LISTAALADT_H_
typedef struct listaAerolineaCDT* listaAerolineaADT;

/* Funcion:                nuevaListaAL
 * Uso:                    listaAL = nuevaListaAL();
 * ---------------------------------------------
 * Descripcion:            Inicializa la lista, no hay errores posibles.
 * ---------------------------------------------
 * Precondicion:           -
 * Postcondicion:          Lista creada.
 */
listaAerolineaADT nuevaListaAL(void);

/* Funcion:                freeAL
 * Uso:                    freeAL(listaAL);
 * ---------------------------------------------
 * Descripcion:            Destruye la lista, liberandorecursos alocados.
 * ---------------------------------------------
 * Precondicion:           Lista que sea valida. 
 * Postcondicion:          -
 */
void freeAL(listaAerolineaADT listaAL);

int insertarAL( listaAerolineaADT lista, char * nombre);
int esAerolinea(char * nombre);
void query5(listaAerolineaADT listaAL, int *ok);

#endif
