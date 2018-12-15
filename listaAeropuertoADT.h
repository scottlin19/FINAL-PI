
/*
 * listADT.h
 * Contrato del TAD Lista Lineal
 * simplemente encadenada ordenada, sin repeticiones 
 */

#ifndef LISTAPADT_H_
#define LISTAPADT_H_


#define OACI 1
#define DENOMINACION 4
#define PROVINCIA 21

#define MAX_OACI 5


/* El siguiente tipo define el TAD Lista.
 * Se lo define como puntero a "cierta estructura"
 * para ocultar la real representacion de la misma
 */
typedef struct listaAeropuertoCDT * listaAeropuertoADT;

//Carga Datos del archivo aeropuertos.csv , devuelve 1 si hubo un error y 0 si no.
int sonDistintasProv(listaAeropuertoADT lista,char * origen, char * destino, char * provincias[]);
int agregarMovAP(listaAeropuertoADT lista,char * oaci,char * clase, char * clasif, int dia);
void query1(listaAeropuertoADT listaAeropuerto, int *ok);
void query2(listaAeropuertoADT listaAeropuerto, int *ok);
void query3(listaAeropuertoADT listaAP, int *ok);

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


/* Funcion:  		insertarAP
 * Uso:  	        res == 	insertAP(listAP, oaci, denom, prov);
 * -------------------------------------------------------------------
 * Descripción: 	Inserta un elemento en la lista ordenada,
 *  			usando la función de comparación Compare.
 * 			Si el elemento ya existía, lo ignora y retorna cero.
 * 		        Retorna 1 si lo pudo insertar	
 * -------------------------------------------------------------------
 * Precondicion:	Lista que sea valida, previamente creada
 * Postcondicion: 	Lista con el nuevo elemento,si no estaba repetido.
 */
int insertarAP( listaAeropuertoADT listaAP, char * oaci, char * denom, char * prov);

void freeAP(listaAeropuertoADT listaAP);


#endif
