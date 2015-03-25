/*

*
*  Created on: 28/2/2015
*      Author: jonathan Candonga
*/



#ifndef CONJUNTOENLAZADO_H_
#define  CONJUNTOENLAZADO_H

#include "Exceptions.h"
//Declaracion de generico
template <class G>

//Declaramos la clase conjunto

class Conjunto {

private:
	//---------------------NODO-------------------
	/*
	Clase Nodo para la lista enlazada
	Almacena : El elemento de tipo T, dos punteros  (
	nodo anterior y al nodo siguiente ) y los
	constructores.
	*/
	class Nodo{
	
	public:
		//Puntero anterior y siguiente
		Nodo *siguienteN, *anteriorN;

		//Almacenamiento del elemento en el nodo
		G elemento;

		//Nodo pr defecto
		Nodo(){
			
			siguienteN = NULL;
			anteriorN = NULL;
		}

		//Cuando existe un solo nodo
		Nodo ( const G& elemento){

			this->elemento = elemento;

			//No habra mas nodos
			siguienteN = NULL;
			anteriorN = NULL;

		}

		/*Cuando existen mas nodos.
		Utilizaremos este siemper ya que utilizamos dos punteros 
		para situar el principio y el final
		 1.Almacenamos el elemento en el nodo
		 2. El nodo anterior cambia: 
		 3.El nodo siguiente cambia:
		*/
		Nodo ( const G& elemento, Nodo* izquierda, Nodo *derecha){

			this->elemento = elemento;
			
			/*
			Almancenamos el nodo siguiente al nodo creado
			para tener el apuntador, nodo de la  derecha  
			*/
			siguienteN = derecha;

			/*
			Almancenamos el nodo anterior al nodo creado
			para tener el apuntador, nodo de la izquierda
			*/
			anteriorN = izquierda;

		}


	};

//---------------------NODO-------------------
public:
//---------------------CONJUNTO-------------------
	//Constructo del conjunto
	Conjunto(){
	
		this->inicializa();
	}

	//Destructor del conjunto
	~Conjunto(){

		this->finaliza();
	}
	
	/*Mutador(set): Inserta un elemento en el conjunto
	si es necesario desplaza los nodos que hay en el de manera ordenada
	1.Restriccion :vector esta lleno, lo redimensiona (duplicamos)
	2.Restriccion: elemento repetido, mostramos error
	Utiliza el algoritmo de busqueda binaria para insertar el vector en la posicion correspondiente

	&elem = direccion del elemento que quiero insetar en el vector dinamico
	*/
	void insertar(const G& elem){

		

			bool repetido = false;

			/*
			Si el elemento es menor que el primero elemento que contiene
			el nodo primero o si no hay ningun nodo, inserto
			el nuevo elemento en nuevo nodo al principio
			*/
			if( this->ultimoC == NULL || elem < this->primeroC->elemento){
				 
				this->push_front(elem);
			}
			/*
			Si el elemento es mayor que el ultimo elemento que contiene
			el nodo ultimo de la lista inserto
			el nuevo elemento en nuevo nodo por el principio
			*/
			else if( this->ultimoC->elemento < elem){
				
				this->push_back(elem);
			}
			else{
			/*
				Si no puedo insertar por delante o por detras
				la inserccion debe ser entre dos nodos
			*/
				//Con el que ire recorriendo
				Nodo* actual= this->primeroC;
			
				//El anterior al actual es nulo
				Nodo* anterior = NULL;

				//Para saber cuando encuentro un elemento mayor a mi elemento
				bool encontrado = false;

				//Mientras no encuentre un elemento mayor
				//no paro

			     while(!encontrado && !repetido)
				{
					//Si mi elemento es mayor que el elemento en el nodo, avanzo le corresponde
					//una poscion siguiente
					if(elem > actual-> elemento){
					
						//El anterior sera el  actual
						anterior = actual;

						//El actual sera el siguiente
						actual = actual->siguienteN;
					}
					else if( elem < actual-> elemento){
					
						//Encontramos un elemento mayor al que quiero insertar
						//paro mi busqueda
						encontrado = true;

						//Inserto entre el anterior y el actual(que es mayor a mi elemento)
						insertaNodo(elem,anterior,actual);
					
					}
					else{

						repetido = true;
					}

			
				}

			}

		//Compruebo si el elemento existe
		if(repetido){
			cout << endl;
			cout <<"El elemento existe " << endl;
		}


	}

	/*
	Metodo que avisa si existe un elemento dentro del nodo
	Observadora 
	
	*/
	bool existe(const G& elem )const{

		bool existe = false;
		
		//Utilizo un nodo auxiliar para hacer el recorrido
		Nodo *actual= this->primeroC;

		/*
		Mientras no llegue al final con mi nodo actual
		y no haya encontrado el elemento dentro del nodo
		
		*/
		while( !existe && actual !=NULL){
		
			if(actual->elemento == elem){

				existe = true;
			}else if( elem > actual->elemento){
				//Si el elem a insetar es menor que el actual continuo 

				//Avanzo, el actual sera el siguiente
				actual = actual->siguienteN;

			}else if( elem < actual->elemento){
				//Si el elem a insetar es mayor que el actual
				//me he pasado ya no continuo
				return false;
			}
		}


		return existe;
	}


	/*
	Imprime todos los elementos existentes en el conjunto
	recorriendolos uno a uno utilizando un puntero auxiliar
	cuya referencia es el puntero primerN del conjunto 
	*/
	void imprime(){
		//Compruebo que conjunto tengan nodos
		if(this->primeroC == NULL){
			cout << "El conjunto esta vacio" << endl;
		}else
		{
			//Copio el puntero primero en auxiliar
			//Para avanzar con el auxiliar 
			Nodo *aux = this->primeroC;

			while( aux !=NULL){

				cout << aux->elemento << " ";

				//EL siguiente de aux sera el actual
				aux = aux->siguienteN;
			}


		}
	
	}


	/*

	MUTADOR(set)
	Busca el elemento a eliminar entre los nodos del conjunto
	Comprueba si el elemento a buscar es el primero o ultimo en el conjunto
	para no teneer que recorre.
	En caso de no serlo, recorre uno a uno hasta encontrar el nodo que contenga
	el elemento buscado
	*/
	void eliminar(const G& elem){

		//Compruebo si no esta vacio
		if(this->primeroC == NULL){

			cout << "Esta vacio" << endl;
		}
		else{
			//Compruebo si el nodo a borrar es el primero del conjunto
			if(this->primeroC->elemento == elem){
		
				//Guardo el puntero primero en auxiliar para borrarlo
				Nodo *borrar = this->primeroC;

				//Actualizo el nodo primero del conjunto (seria el siguiente al primero)
				this->primeroC = primeroC->siguienteN;

				this->eliminarNodo(borrar);

				//Si el primero es null, es porque habia un solo elemento
				if(primeroC == NULL){
					//El ultimo tambien sera null ya que no hay nodos en el conjunto
					ultimoC = NULL;
				}	
			}//Compruebo si el nodo a borrar es el ultimo del conjunto
			else if( this->ultimoC->elemento == elem)
			{
				//Guardo el puntero ultimo en auxiliar para borrarlo
				Nodo *borrar = this->ultimoC;

				//Actualizo el nodo ultimo del conjunto (seria el anterior al ultimo)
				this->ultimoC = ultimoC->anteriorN;
				this->eliminarNodo(borrar);

				//Si el ultimo es null, es porque habia un solo elemento
				if(ultimoC == NULL){
					//El primero tambien sera null ya que no hay nodos en el conjunto
					primeroC = NULL;
				}
			}
			else{//Si el nodo a borrar esta entre dos nodos
				
				//Auxiliar para recorrer uno a uno
				Nodo* actual = primeroC;

				//Para saber si lo encontrado
				bool encontrado = false;

				/*Mientras no encuentre el elemento o no haya llegado al final
				de los nodos del conjunto*/
				while(!encontrado && actual != NULL){
			
					if( actual->elemento == elem){
	
						encontrado = true;
					}else{
						//El siguiente sera el actual
						actual = actual->siguienteN;
					}
				}
				//Como lo encontre, borro el elemento actual
				if (encontrado)
					this->eliminarNodo(actual);
				else
					cout << "Elemento no existe " << endl;
			}
		}
	}

//========================FUNCIONES CONJUNTOS======================================
	/*
	*Mutador(set): Interseccion de un elementos que se encuentre en ambos
	*conjuntos en el conjunto que hace la llamada
	*Ej: c1.interseccionC(c2,c3) -> c1 contendra la interseccion
	*Se trata de un metodo void, ya que el cambio se hace sobre el conjunto
	que hace la llamada

	Es necesario Conjunto <G>&- > Le paso !!la direccion!!! de un conjunto especifico (del tipo G) 
	*/
	void interseccionC(const Conjunto& c1, const Conjunto& c2){
		/*
		Liberamos el conjunto sobre el cual se va hacer la interseccion
		(la que hizo la llamada)
		*/
		this->finaliza();
		this->inicializa();

		//Punteros primeros de c1 y c2
		Nodo *c1NodoPrimero = c1.primeroC ;
		Nodo *c2NodoPrimero = c2.primeroC ;

		/*
		Si algun puntero primero llega a null
		quiere decir que ya alguno esta ya vacio
		y no puede habe interseccion
		*/
		while(c1NodoPrimero != NULL && c2NodoPrimero !=NULL){
			
			//Si ambos elementos de los nodos de c1 y c2 son iguales
			if(c1NodoPrimero->elemento == c2NodoPrimero->elemento)
			{
				/*Insertamos el elemento por el final de los nodos
				del conjunto que hace la llamada*/
				this->push_back(c1NodoPrimero->elemento);

				//Actualiazamos punteros
				c1NodoPrimero = c1NodoPrimero->siguienteN;
				c2NodoPrimero = c2NodoPrimero->siguienteN;
			}
			else if( c1NodoPrimero->elemento < c2NodoPrimero->elemento)
			{
				//Pasamos al siguiente nodo del c1
				c1NodoPrimero = c1NodoPrimero->siguienteN;
			}
			else if ( c2NodoPrimero->elemento < c1NodoPrimero->elemento)
			{
				//Pasamos al siguiente nodo del c1
				c2NodoPrimero = c2NodoPrimero->siguienteN;
					
			}	
		}
}

	/*
	Mutador (set ): Union de los elementos que se encuentre en ambos
	*conjuntos que se pasan por parametros en el conjunto que hace la llamada.
	*Ej: c1.unionC(c2,c3) -> c1 contendra la union de ambos conjuntos 
	*Se trata de un metodo void, ya que el cambio se hace sobre el conjunto
	que hace la llamada

	*/
	void unionC(const Conjunto& c1, const Conjunto& c2){

		/*
		Liberamos el conjunto sobre el cual se va hacer la interseccion
		(la que hizo la llamada)
		*/
		this->finaliza();
		this->inicializa();

		//Punteros primeros de c1 y c2
		Nodo *c1NodoPrimero = c1.primeroC ;
		Nodo *c2NodoPrimero = c2.primeroC ;

		while (c1NodoPrimero != NULL && c2NodoPrimero != NULL)
		{
			/*
			* Si el elemento C1 es menor que el de C2
			* insertamos el elemento C1
			*/
			if (c1NodoPrimero->elemento < c2NodoPrimero->elemento)
			{
				/*Insertamos el elemento por el final de los nodos
				del conjunto que hace la llamada*/
				this->push_back(c1NodoPrimero->elemento);
				//Apuntamos al siguiente nodo
				c1NodoPrimero = c1NodoPrimero->siguienteN;
			}
			/*
			* Si el elemento C2 es menor que el de C1
			* insertamos el elemento C1
			*/
			else if (c2NodoPrimero->elemento < c1NodoPrimero->elemento)
			{
				/*Insertamos el elemento por el final de los nodos
				del conjunto que hace la llamada*/
				this->push_back(c2NodoPrimero->elemento);
				c2NodoPrimero = c2NodoPrimero->siguienteN;
			}
			else{//Si los elementos son iguales, insertamos uno
				
				/*Insertamos el elemento por el final de los nodos
				del conjunto que hace la llamada*/
				this->push_back(c1NodoPrimero->elemento);
				//Apuntamos al siguiente nodo
				c1NodoPrimero = c1NodoPrimero->siguienteN;
				c2NodoPrimero = c2NodoPrimero->siguienteN;
			}
		}

		/*
		Si quedan elementos por insertar en el c1
		insertarmos
		*/
		while (c1NodoPrimero != NULL){

			/*Insertamos el elemento por el final de los nodos
			del conjunto que hace la llamada*/
			this->push_back(c1NodoPrimero->elemento);
			//Apuntamos al siguiente nodo
			c1NodoPrimero = c1NodoPrimero->siguienteN;

		}

		/*
		Si quedan elementos por insertar en el c2
		insertarmos
		*/
		while (c2NodoPrimero != NULL){

			/*Insertamos el elemento por el final de los nodos
			del conjunto que hace la llamada*/
			this->push_back(c2NodoPrimero->elemento);
			//Apuntamos al siguiente nodo
			c2NodoPrimero = c2NodoPrimero->siguienteN;

		}
	}

	/*
	Mutador (set ): La diferencia de los elementos de un c1 que no
	estan en conjunto 2. Recorro todo el c1, si hay elementos iguales
	en el c2 no inserto en caso contrario y si el elemento c1 es menor
	inserto ya que dicho elemento no existira en c2 al ser menor.
	*/

	void diferenciaC(const Conjunto& c1, const Conjunto& c2)
	{
		
		/*
		Liberamos el conjunto sobre el cual se va hacer la interseccion
		(la que hizo la llamada)
		*/
		finaliza();
		inicializa();

		//Punteros primeros de c1 y c2
		Nodo *c1NodoPrimero = c1.primeroC;
		Nodo *c2NodoPrimero = c2.primeroC;
	
		/*
		* Recorro los elementos de c1  y uno a uno busco
		* si se encuentra en c2.Si no se encuentra guardo, almaceno
		*/

		while( c1NodoPrimero !=NULL && c2NodoPrimero !=NULL)
		{
			if(c1NodoPrimero->elemento == c2NodoPrimero->elemento)
			{
				//Avanzo los punteros a los siguientes
				c1NodoPrimero = c1NodoPrimero->siguienteN;
				c2NodoPrimero = c2NodoPrimero->siguienteN;
			}
			/*
			Si el elemento c1 es menor que c2, quiere decir que en c2
			no existe c1, por lo que este elemento no es "diferencia"
			*/
			else if( c1NodoPrimero->elemento < c2NodoPrimero->elemento)
			{
				/*Insertamos el elemento por el final de los nodos
				del conjunto que hace la llamada*/
				this->push_back(c1NodoPrimero->elemento);
				//Apuntamos al siguiente nodo
				c1NodoPrimero = c1NodoPrimero->siguienteN;

			}
			else if (c1NodoPrimero->elemento > c2NodoPrimero->elemento)
			{
			/*
			Si el elemento c1 es mayor que c1, quiere decir que en c2
			puede existir c1, por lo que avanzamos al siguiente nodo de c2
			*/
				c2NodoPrimero = c2NodoPrimero->siguienteN;
				
			}			
		}
	
		while(c1NodoPrimero !=NULL){
			/*Insertamos el elemento por el final de los nodos
			del conjunto que hace la llamada*/
			this->push_back(c1NodoPrimero->elemento);
			//Apuntamos al siguiente nodo
			c1NodoPrimero = c1NodoPrimero->siguienteN;

		}
	}


	/*
	MUTADOR (SET): Los elementos que no pertenecen a la interseccion de C1 y C2 y
	pertenecen a C1 o C2.
	
	*/
	void diferenciaSimetricaC(const Conjunto& c1,const Conjunto& c2)
	{
		/*
		Liberamos el conjunto sobre el cual se va hacer la interseccion
		(la que hizo la llamada)
		*/
		finaliza();
		inicializa();

		//Punteros primeros de c1 y c2
		Nodo *c1NodoPrimero = c1.primeroC;
		Nodo *c2NodoPrimero = c2.primeroC;


		while (c1NodoPrimero != NULL &&  c2NodoPrimero != NULL)
		{
			//Si los elementos de los 2 son iguales (interseccion)
			//apunto a los siguiente nodos
			if (c1NodoPrimero->elemento == c2NodoPrimero->elemento)
			{
				c1NodoPrimero = c1NodoPrimero->siguienteN;
				c2NodoPrimero = c2NodoPrimero->siguienteN;

			}
			else if (c1NodoPrimero->elemento < c2NodoPrimero->elemento)
			{

				/*Insertamos el elemento por el final de los nodos
				del conjunto que hace la llamada*/
				this->push_back(c1NodoPrimero->elemento);
				//Apuntamos al siguiente nodo
				c1NodoPrimero = c1NodoPrimero->siguienteN;

			}
			else if (c2NodoPrimero->elemento < c1NodoPrimero->elemento)
			{
				/*
				El elemento de c2 es menor por lo que no existira
				este elemento en c1 y puedo insertarlo
				*/

				/*Insertamos el elemento por el final de los nodos
				del conjunto que hace la llamada*/
				this->push_back(c2NodoPrimero->elemento);
				//Apuntamos al siguiente nodo
				c2NodoPrimero = c2NodoPrimero->siguienteN;
			}

		}


		/*
		Si quedan elementos por insertar en el c1
		insertarmos
		*/
		while (c1NodoPrimero != NULL){

			/*Insertamos el elemento por el final de los nodos
			del conjunto que hace la llamada*/
			this->push_back(c1NodoPrimero->elemento);
			//Apuntamos al siguiente nodo
			c1NodoPrimero = c1NodoPrimero->siguienteN;

		}

		/*
		Si quedan elementos por insertar en el c2
		insertarmos
		*/
		while (c2NodoPrimero != NULL){

			/*Insertamos el elemento por el final de los nodos
			del conjunto que hace la llamada*/
			this->push_back(c2NodoPrimero->elemento);
			//Apuntamos al siguiente nodo
			c2NodoPrimero = c2NodoPrimero->siguienteN;

		}
			
}

	/*
	Comprueba si el conjunto que hace la llamada y el conjunto
	pasado por parametro tiene algun elemento en comun
	Si tiene un elemento en comun: No disjuntos (false)
	Si no tiene elementos en comun: disjuntos (true)
	
	
	*/
	bool disjuntosC( const Conjunto& c1)
	{
	
		//Compruebo si es el mismo conjunto 
		if( this == &c1)
		{
			return false;
		}else
		{
			/*
			Auxiliares para recorrer los dos conjuntos,
			de los punteros que apuntan al principio
			de los nodos de los conjuntos 
			*/
			//El que hace la llamada 
			Nodo*  actualPropio = this->primeroC;
			//El conjunto pasado por parametro
			Nodo* actualC1 = c1.primeroC;

			while(actualPropio != NULL && actualC1 !=NULL){

				if( actualC1->elemento < actualPropio->elemento)
				{
					
					/*
					Si el elemento de c1 es menor que el elemento
					que hace la llamada 
					*/
					//Apuntamos al siguiente
					actualC1 = actualC1->siguienteN;
				}
				else if(actualC1->elemento > actualPropio->elemento)
				{
					/*
					Si el elemento de c1 es mayor que el elemento
					que hace la llamada 
					*/
					//Apuntamos al siguiente
					actualPropio = actualPropio->siguienteN;
				}
				else if(actualC1->elemento == actualPropio->elemento){
				
					//Hay un elemento comun, no son disjuntos
					return false;
				}
			}

		}

		return true;
	}
		
//========================FUNCIONES CONJUNTOS======================================


//========================OPERACIONES CONJUNTOS======================================
	bool operator==(const Conjunto& rhs) const{
	
		//SI no tiene los mismos elementos ambos conjuntos
		if( this->nElementos != rhs.nElementos)
		{
			return false;
		}

		//Comparo uno a uno los elementos
		Nodo *actualC1 = this->primeroC;
		Nodo *actualC2 = rhs.primeroC;

		while(actualC1 != NULL)
		{
			/*
			Existen los mismo elementos, si termina uno
			termina el otro
			*/
			if( actualC1-> elemento !=  actualC2-> elemento)
			{
				return false;
			}


			actualC1 = actualC1->siguienteN;
			actualC2 = actualC2->siguienteN;
		}
	

	return true;

	}

	bool operator!=(const Conjunto& rhs) const{

		return !(*this == rhs);
	}

	Conjunto<G>& operator=(const Conjunto& c1){

		if (this != &c1){

			finaliza();
			copia();
		}

		return *this;
	}
//========================OPERACIONES CONJUNTOS======================================

//---------------------CONJUNTO-------------------
protected:
//---------------------CONJUNTO-------------------


	void copia(const Conjunto& c1){

		nElementos = 0;

		Nodo *actual = c1.primeroC;
		/*
		Mientras no llego al ultimo nodo del c1 a copiar
		Copio el nodo ac
		*/
		while (actual != NULL){

			push_back(actual->elemento);

			actual = actual->siguienteN;
		}

	}
	/*
	Metodo que inicializa un objeto de conjunto
	*/
	void inicializa(){
		this->nElementos = 0;

		//Inicializo los punteros
		//Al principio y al final no se apunta a nada 
		this->primeroC = NULL;
		this->ultimoC = NULL;
	}

	void finaliza(){

		/*
		Liberamos los nodos de la lista empezando
		desde el principio de los nodos con el puntero que apunta
		al primer nodo
		*/
		liberaNodos(this->primeroC);

		//AL quedarse vacio el conjunto apunto a null
		this->primeroC = NULL;
		this->ultimoC = NULL;
	}


//---------------------CONJUNTO-------------------

private:

//---------------------CONJUNTO-------------------
	unsigned int nElementos;

	//Apunta al primer elemento y al ultimo
	Nodo *primeroC, * ultimoC;


//-------------------CONJUNTO-----------------------



//---------------------NODO-------------------


	/**
	 Elimina todos los nodos de la lista enlazada cuyo
	 primer nodo se pasa como parámetro.
	 Se admite que el nodo sea NULL (no habrá nada que
	 liberar). En caso de pasarse un nodo válido,
	 su puntero al nodo anterior debe ser NULL (si no,
	 no sería el primero de la lista!).
	 */
	static void liberaNodos( Nodo *principio){
		/*
		Recorro todos los nodos hasta llegar al final
		liberando uno a uno, almaceno en un auxiliar el principioo
		para poderlo borrar 
		*/
		while(principio !=NULL){

			//Nodo a borrar
			Nodo *anterior = principio;
			//Actualizo( paso al siguiente)
			principio = principio->siguienteN;
			//Borro anterior
			delete anterior;
		}
	
	}
	
	/*
	 Añade un nuevo elemento en la cabeza de la lista.
	 Operación generadora.

	 -elem Elemento que se añade en la cabecera de
	 la lista.
	*/
	void push_front(const G& elem){
		
		//El puntero al primer elemento del conjunto sera el que acaba de ser
		//insertado a la cabecera
		this->primeroC = this->insertaNodo(elem, NULL, this->primeroC);

		//Si la lista esta vacia, el ultimo sera el primero que acabo de meter
		if(this->ultimoC == NULL){
		
			this->ultimoC = primeroC;
		}
	
	
	}
	
	
	/*
	 Añade un nuevo elemento al final de la lista (a la 
	 "derecha"). Operación modificadora.
	 */
	void push_back(const G& elem){
		
		//El puntero al ultimo elemento del conjunto sera el que acaba de ser
		//insertado a la cabecera
		this->ultimoC = this->insertaNodo(elem, this->ultimoC, NULL);


		//Si la lista esta vacia, el primero sera el ultimo que acabo de meter
		if(this->primeroC == NULL){
		
			this->primeroC = ultimoC;
		}
	}

	/**
	 Inserta un elemento entre el nodo1 y el nodo2.
	 Devuelve el puntero al nodo creado. Operación modificadora.
	 Casos especiales: alguno de los nodos no existe
	    nodo1 == NULL y/o nodo2 == NULL
	*/

	Nodo* insertaNodo (const G& elem, Nodo *izquierda,  Nodo *derecha){

		//Creamos el nuevo nodo a insertar que contiene el elemeneto
		Nodo *nuevo = new Nodo(elem,izquierda,derecha);

		//Si no esta vacio el nodo de la izquierda 
		//su siguiente sera el nuevo
		if(izquierda !=NULL){

			//El nodo de la izquierda su siguiente apuntara al nodo creado
			izquierda->siguienteN = nuevo;

		}
		//Si no esta vacio el nodo de la derehca 
		//su anterior sera el nuevo
		if( derecha !=NULL){
			
			//El nodo de la derecha su anterior apuntara al nodo creado
			derecha->anteriorN= nuevo;
		}


		 
		//Incremetamos numeroo de nodos en el conjunto
		nElementos++;

		return nuevo;
	}

	/*

	Elimina el nodo actual, si este nodo tiene nodos a la izquierda o a la derecha
	se actualizo los punteros de los nodos de ambos lados para que se apunten
	ambos.
	Caso general: hay nodos a la izquierda y derecha(anteriorN y siguienteN)
	Caso limite: alguno de los dos es nullo y no existen


	*/
	void eliminarNodo(Nodo *actual){
	
		//Compruebo que el nodo no es nullo
		if(actual == NULL){
		
			cout << "No se puede eliminar nodo" << endl;
		}
		else{
			//Almaceno el nodo de la izquierda al actual
			Nodo *izquierda = actual->anteriorN;

			//Almaceno el nodo de la derecha al actual
			Nodo *derecha = actual->siguienteN;

			//Si el nodo de la izquierda no es null, actualizo el puntero
			if( izquierda != NULL){
			
				//El nodo de la izquierda apuntara al nodo de la derecha del actual
				izquierda-> siguienteN = derecha;
			}

			if( derecha != NULL){
			
				//El nodo de la derecha apuntara al nodo de la izquierda del actual
				derecha-> anteriorN = izquierda;
			}

			//Al eliminar decremente elementos
			this->nElementos--;

			//borramos el nodo

			delete actual;
		}
	
	}

//---------------------NODO-------------------------

	

};

#endif

