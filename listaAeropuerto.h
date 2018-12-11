
/*
 * listADT.h
 * Contrato del TAD Lista Lineal
 * simplemente encadenada ordenada, sin repeticiones 
 */

#ifndef LISTADT_H_
#define LISTADT_H_



/* El siguiente tipo define el TAD Lista.
 * Se lo define como puntero a "cierta estructura"
 * para ocultar la real representacion de la misma
 */
typedef struct listaAeropuertoCDT * listaAeropuertoADT;

//Carga Datos del archivo aeropuertos.csv , devuelve 1 si hubo un error y 0 si no.
int cargarDatos(listaAeropuertoADT lista,char * pathA);

/* Función de comparación para ordenar las componentes del TAD.
 * De no servir este código el usuario debe cambiarlo por el
 * que desea. La convención a seguir es que debe devolver
 * número negativo si el primer parámetro debe aparecer antes
 * que el segundo en la lista, devolver número positivo
 * si debe aparecer después, o bien 0 si son elementos equivalentes
 */
/*
static int compare(listElementT elem1, listElementT elem2 )
{
	return elem1 - elem2;		
}
*/
/* Funcion:  		newList
 * Uso:  		list = newList();
 * -------------------------------------------------------------------
 * Descripción: 	Inicializa la lista. No hay error posible.
 * -------------------------------------------------------------------
 * Precondicion:		-
 * Postcondicion: 	Lista creada
 */
listaAeropuertoADT nuevaLista(void);


/* Funcion:  		Insert
 * Uso:  	        res == 	Insert( list, 12.3);
 * -------------------------------------------------------------------
 * Descripción: 	Inserta un elemento en la lista ordenada,
 *  			usando la función de comparación Compare.
 * 			Si el elemento ya existía, lo ignora y retorna cero.
 * 		        Retorna 1 si lo pudo insertar	
 * -------------------------------------------------------------------
 * Precondicion:	Lista que sea valida, previamente creada
 * Postcondicion: 	Lista con el nuevo elemento,si no estaba repetido.
 */



/* Funcion:  		delete
 * Uso:  	        res = 	delete(list, 12.3 );
 * -------------------------------------------------------------------
 * Descripción: 	Elimina el elemento de la lista ordenada,
 *  			usando la función Compara. Si el elemento
 * 			no existía devuelve 0, caso contrario 1
 * -------------------------------------------------------------------
 * Precondicion:	Lista que sea valida, previamente creada
 * Postcondicion: 	Lista sin el elemento
 */
//int delete(listADT list, listElementT element);


/* Funcion:  		listIsEmpty
 * Uso:  		if ( listIsEmpty( list ) ...
 * -------------------------------------------------------------------
 * Descripción: 	Devuelve 1 si la lista está vacía o
 * 			0 en caso contrario
 * -------------------------------------------------------------------
 * Precondicion:	Lista que sea valida, previamente creada
 * Postcondicion: 	- (lista invariante).
 */
//int listIsEmpty(const listADT list);

/* Funcion:  		elementBelongs
 * Uso:  		if ( elementBelongs( list, 12.3 ))...
 * -------------------------------------------------------------------
 * Descripción: 	Devuelve 1 si el elemento pertenece a la lista
 * 					o 0 en caso contrario
 * -------------------------------------------------------------------
 * Precondicion:	Lista previamente creada
 * Postcondicion: 	- (lista invariante).
 */
//int elementBelongs(const listADT list, listElementT element);


/* Funcion: 		freeList
 * Uso: 		freeList( list );
 * -------------------------------------------------------------------
 * Descripción: 	Destruye la lista, liberando recursos alocados.
 * -------------------------------------------------------------------
 * Precondicion:	Lista que sea valida.
 * Postcondicion: 	-
 */
//void freeList(listADT list);

/** 
 * Retorna la cantidad de elementos en la lista
 */
//int listSize(const listADT list);


/**
 * Funciones para poder iterar sobre la lista
 */
void alPrincipio(listaAeropuertoADT listaAeropuerto);

//int tieneProximo(const listADT list);
int tieneProx(const listaAeropuertoADT lista);
//listElementT next(listADT list);

void proximo(listaAeropuertoADT listaAeropuerto);
/**
 * Ejemplo de implementación "funcional"
 * inject recibe una funcion y la aplica a cada elemento de la lista
 */
//void inject(listADT list, listElementT (*fn) (listElementT));

/**
 * Devuelve una nueva lista con los elementos de list, pero aplicandole la funcion fn
 * a cada elemento
 * */
//listADT map(const listADT list, listElementT (*fn) (listElementT));

#endif /* LISTADT_H_ */
