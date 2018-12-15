#ifndef LISTAPARESADT_H_
#define LISTAPARESADT_H_

/* El siguiente tipo define el TAD Lista.
 * Se lo define como puntero a "cierta estructura"
 * para ocultar la real representacion de la misma
 */
typedef struct listaParesCDT * listaParesADT;


/* Funcion:                 nuevaListaPares
 * Uso:                     listaPares = nuevaListaPares();
 * ----------------------------------------------------
 * Descripcion:             Inicializa la lista. No hay error posible.
 * ----------------------------------------------------
 *  Precondicion:           -
 *  Postcondicion:          Lista creada.
 */
listaParesADT nuevaListaPares(void);

/* Funcion:                 insertarPares
 * Uso:                     insertarPares(listaPares, provincias);
 * ----------------------------------------------------
 * Descripcion:             Inserta un nuevo nodo con un par de provincias que comparten movimiento
 * 			    a la lista ordenada por movimientos compartidos entre provincias.
 * 			    Si el par ya existia, le suma un movimiento y retorna 1.
 * 			    Retorna 1 si lo pudo insertar y 0 en caso contrario.
 * ----------------------------------------------------
 *  Precondicion:           Lista que sea valida.
 *  Postcondicion:          Lista con un nuevo nodo si no estaban repetidos los pares de provincias.
 */
int insertarPares(listaParesADT lista,char * provincias[]);

void printListaPares(listaParesADT lista);

/* Funcion:                 freePares
 * Uso:                     freePares(listaPares);
 * ----------------------------------------------------
 * Descripcion:             Destruye la lista, liberando recursos alocados.
 * ----------------------------------------------------
 *  Precondicion:           Lista que sea valida.
 *  Postcondicion:          -
 */
void freePares(listaParesADT listaPares);

/* Funcion:                 query4
 * Uso:                     query4(listaPares, &ok);
 * ----------------------------------------------------
 * Descripcion:             Crea el archivo "pares_provincias.csv", donde cada línea de la salida contenga separados por ;
 * 			    el par de provincias distintas
			    (obteniendo los nombres de las mismas del archivo "aeropuertos.csv") y la cantidad de
			    movimientos de todo tipo que comparten ambas provincias. 
 * ----------------------------------------------------
 *  Precondicion:           Lista que sea valida y que los archivos "aeropuertos.csv", "movimientos.csv" hayan sido cargados correctamente.
 *  Postcondicion:          -
 */
void query4(listaParesADT listaPares, int *ok);
#endif
