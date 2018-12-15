#ifndef LISTAALADT_H_
#define LISTAALADT_H_

/* El siguiente tipo define el TAD Lista.
 * Se lo define como puntero a "cierta estructura"
 * para ocultar la real representacion de la misma
 */
typedef struct listaAerolineaCDT* listaAerolineaADT;


/* Funcion:                 nuevaListaAL
 * Uso:                     listaAL = nuevaListaPares();
 * ----------------------------------------------------
 * Descripcion:             Inicializa la lista de aerolíneas. No hay error posible.
 * ----------------------------------------------------
 *  Precondicion:           -
 *  Postcondicion:          Lista creada.
 */
listaAerolineaADT nuevaListaAL(void);



/* Funcion:                 insertarAL
 * Uso:                     if (insertarAL(listaAL, "Aerolineas Argentinas")) ...;
 * ----------------------------------------------------
 * Descripcion:             Inserta un nuevo nodo con el nombre de la aerolínea, y le suma 1 movimiento.
 * 			    Si la aerolínea ya existia, le suma un movimiento.
                            En ambos casos reordena la lista segun cantidad de movimientos.
 * 			    Retorna 1 si lo pudo insertar y 0 en caso contrario.
 * ----------------------------------------------------
 *  Precondicion:           Lista que sea válida, previamente creada.
 *  Postcondicion:          Lista con un nuevo nodo si no existía dicha aerolinea ya en ella.
 */
int insertarAL( listaAerolineaADT lista, char * nombre);

/* Funcion:                 esAerolinea
 * Uso:                     if (esAerolinea("Aerolineas Argentinas")) ...;
 * ----------------------------------------------------
 * Descripcion:             Retorna 1 si el string que se pasa es diferente del espacio o del N/A, 0 en caso contrario..
 * ----------------------------------------------------
 * Precondicion:            - 
 * Postcondicion:           -
 */
int esAerolinea(char * nombre);

/* Funcion:                 freeAL
 * Uso:                     freeAL(listaAL);
 * ----------------------------------------------------
 * Descripcion:             Destruye la lista, liberando recursos alocados.
 * ----------------------------------------------------
 * Precondicion:            Lista que sea valida. 
 * Postcondicion:           -
 */
void freeAL(listaAerolineaADT listaAL);

/* Funcion:                 query5
 * Uso:                     query5(listaAL, &ok);
 * ----------------------------------------------------
 * Descripcion:             Crea o reemplaza si ya existe el archivo "porcentaje_cabotaje.csv", donde cada línea de la salida 
 * 			    contenga separados por ‘;’ el nombre de la aerolínea y el porcentaje de movimientos 
 * 		            donde Clasificación de Vuelo es Cabotaje de esa aerolínea respecto del total de movimientos
 * 	                    de cabotaje de todas las aerolíneas.
 * 	                    Aquellos movimientos de cabotaje que no tengan asociados una aerolinea o sea N/A son descartados.
 * ----------------------------------------------------
 * Precondicion:            Lista y archivos "aerpuertos.csv", "movimientos.csv", validos. 
 * Postcondicion:           Lista invariante y nuevo archívo creado/reemplazado.
 */
void query5(listaAerolineaADT listaAL, int *ok);

#endif
