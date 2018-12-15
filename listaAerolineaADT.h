#ifndef LISTAALADT_H_
#define LISTAALADT_H_
typedef struct listaAerolineaCDT* listaAerolineaADT;


/* Funcion:                 nuevaListaAL
 * Uso:                     listaAL = nuevaListaPares();
 * ----------------------------------------------------
 * Descripcion:             Inicializa la lista de aerolíneas. No hay error posible.
 * ----------------------------------------------------
 *  Precondicion:           
 *  Postcondicion:          Lista creada.
 */
listaAerolineaADT nuevaListaAL(void);



/* Funcion:                 insertarAL
 * Uso:                     insertarAL(listaAL, nombre);
 * ----------------------------------------------------
 * Descripcion:             Inserta un nuevo nodo con el nombre de la aerolínea, y le suma 1 movimiento.
 * 			                    Si la aerolínea ya existia, le suma un movimiento.
 * 			                    Retorna 1 si lo pudo insertar y 0 en caso contrario.
 * ----------------------------------------------------
 *  Precondicion:           Lista que sea válida, previamente creada.
 *  Postcondicion:          Lista con un nuevo nodo si no existía dicha aerolinea ya en ella.
 */
int insertarAL( listaAerolineaADT lista, char * nombre);

int esAerolinea(char * nombre);

/* Funcion:                freeAL
 * Uso:                    freeAL(listaAL);
 * ---------------------------------------------
 * Descripcion:            Destruye la lista, liberandorecursos alocados.
 * ---------------------------------------------
 * Precondicion:           Lista que sea valida. 
 * Postcondicion:          -
 */
void freeAL(listaAerolineaADT listaAL);

void query5(listaAerolineaADT listaAL, int *ok);

#endif
