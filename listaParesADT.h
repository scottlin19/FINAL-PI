#ifndef LISTAPARESADT_H_
#define LISTAPARESADT_H_

typedef struct listaParesCDT * listaParesADT;

int insertarPares(listaParesADT lista,char * provincias[]);

/* Funcion:                 nuevaListaPares
 * Uso:                     listaPares = nuevaListaPares();
 * ----------------------------------------------------
 * Descripcion:             Inicializa la lista. No hay error posible.
 * ----------------------------------------------------
 *  Precondicion:           
 *  Postcondicion:          Lista creada.
 */
listaParesADT nuevaListaPares(void);

void printListaPares(listaParesADT lista);

/* Funcion:                 freePares
 * Uso:                     freePares(listaPares)
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
			    (obteniendo los nombres de las mismas del archivo aeropuertos.csv) y la cantidad de
			    movimientos de todo tipo que comparten ambas provincias. 
 * ----------------------------------------------------
 *  Precondicion:           Lista que sea valida y que los archivos "aeropuertos.csv", "movimientos.csv" hayan sido cargados correctamente.
 *  Postcondicion:          -
 */
void query4(listaParesADT listaPares, int *ok);
#endif
