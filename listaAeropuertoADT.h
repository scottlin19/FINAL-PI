
/*
 * listADT.h
 * Contrato del TAD Lista Lineal
 * simplemente encadenada ordenada, sin repeticiones 
 */

#ifndef LISTAPADT_H_
#define LISTAPADT_H_

/* El siguiente tipo define el TAD Lista.
 * Se lo define como puntero a "cierta estructura"
 * para ocultar la real representacion de la misma
 */
typedef struct listaAeropuertoCDT * listaAeropuertoADT;

//Carga Datos del archivo aeropuertos.csv , devuelve 1 si hubo un error y 0 si no.
int insertarAP( listaAeropuertoADT lista, char * oaci, char * denom, char * prov);
int sonDistintasProv(listaAeropuertoADT lista,char * origen, char * destino, char * provincias[]);
int agregarMovAP(listaAeropuertoADT lista,char * oaci,char * clase, char * clasif, int dia);
void query1(listaAeropuertoADT listaAeropuerto, int *ok);
void query2(listaAeropuertoADT listaAeropuerto, int *ok);
void query3(listaAeropuertoADT listaAP, int *ok);

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
listaAeropuertoADT nuevaListaAP(void);


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




#endif
