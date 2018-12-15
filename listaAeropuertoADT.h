
/*
 * listADT.h
 * Contrato del TAD Lista Lineal
 * simplemente encadenada ordenada, sin repeticiones 
 */

#ifndef LISTAPADT_H_
#define LISTAPADT_H_


#define OACI 1   //Número del campo donde se encuentra el OACI en el aeropuertos.csv
#define DENOMINACION 4 //Número del campo donde se encuentra la denominación en el aeropuertos.csv
#define PROVINCIA 21 //Número del campo donde se encuentra la provincia en el aeropuertos.csv
#define MAX_OACI 5 //Cantidad de letras de un OACI + el '\0'


/* El siguiente tipo define el TAD Lista.
 * Se lo define como puntero a "cierta estructura"
 * para ocultar la real representacion de la misma
 */
typedef struct listaAeropuertoCDT * listaAeropuertoADT;



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
 * Uso:  	        if( insertAP(listAP, oaci, denom, prov) ...
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




/* Funcion:  		agregarMovAP
 * Uso:  	       	if( agregarMovAP(listAP, oaci, clase, clasif,dia) ... 
 * -------------------------------------------------------------------
 * Descripción: 	Busca un aeropuerto con un OACI igual al que se
 			manda por parámetro. Si lo encuentra, le suma un 
			movimiento segun la clase, clasificación y dia del movimiento.
			Luego reordena si es necesario la lista de mayor a menor respecto
			a cantidad de movimientos,y si las cantidades son iguales,
			se los ordena alfabéticamente y retorna 1.
			Si no lo encuentra retorna 0.
 * -------------------------------------------------------------------
 * Precondicion:	Lista que sea valida, previamente creada y cargada con los datos de aeropuertos.csv.
 * Postcondicion: 	Lista con 1 movimiento más y reordenada, si encontró el aeropuerto, sino la lista no varía.
 */
int agregarMovAP(listaAeropuertoADT lista,char * oaci,char * clase, char * clasif, int dia);



/* Funcion:  		sonDistintasProv
 * Uso:  	       	if( sonDistintasProv(listAP, origen, destino, provincias) ...
 * -------------------------------------------------------------------
 * Descripción: 	Busca en la lista de aeropuertos los OACI origen y destino y guarda sus provincias
 			en orden alfabético en el vector provincias.
			Retorna 1 si son distintas provincias y 0 en caso contrario.
 * -------------------------------------------------------------------
 * Precondicion:	Lista de aeropuertos que sea valida, previamente creada, y cargada con los datos de aeropuertos.csv.
 			El vector provincias debe tener tamaño igual (o mayor) a 2.
 * Postcondicion: 	- (lista invariante).
 */
int sonDistintasProv(listaAeropuertoADT lista,char * origen, char * destino, char * provincias[]);



/* Funcion: 		freeAP
 * Uso: 		freeAP( listaAP );
 * -------------------------------------------------------------------
 * Descripción: 	Destruye la lista, liberando recursos alocados.
 * -------------------------------------------------------------------
 * Precondicion:	Lista que sea valida.
 * Postcondicion: 	-
 */
void freeAP(listaAeropuertoADT listaAP);


void query1(listaAeropuertoADT listaAeropuerto, int *ok);
void query2(listaAeropuertoADT listaAeropuerto, int *ok);
void query3(listaAeropuertoADT listaAP, int *ok);

#endif
