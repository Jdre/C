/*
* Conjunto.h
*
*  Created on: 28/2/2015
*      Author: jonathan Candonga 
*/

#ifndef CONJUNTO_H_
#define CONJUNTO_H_





//Definicion de generico
template < class G >


class Conjunto {


public:


	//Tamañao por defecto
	const static int TAM_INI = 10;

	//Constructor contruye el vector
	Conjunto(){
		//Inicializamos el objetos
		inicia();
	}
	//Destructor  destruye el vector
	~Conjunto(){
		//Liberamos
		finaliza();
	}

	/*M.Mutador(set): Inserta un elemento en el vector de manera ordenada
	1.Restriccion :vector esta lleno, lo redimensiona (duplicamos)
	2.Restriccion: elemento repetido, mostramos error
	Utiliza el algoritmo de busqueda binaria para insertar el vector en la posicion correspondiente

	&g = direccion del elemento que quiero insetar en el vector dinamico
	*/
	void insertaC(const G &g){

		int ini = 0, fin = this->nElementos - 1, pos = 0;

		//Comprobamos si llegamos al limite
		if (this->nElementos == this->tam){

			amplia();
		}

		//Buscamos el elemento, si no esta insertamos
		if (!busqueda(g, ini, fin, pos)){

			//Desplazamos los elementos desde el final
			//Hasta la posicion (desplazamos a la derecha )
			for (int i = this->nElementos; i > pos; i--){

				this->v[i] = this->v[i - 1];
			}
			//Insertamos el elemento en la posicion que le corresponde
			this->v[pos] = g;
			this->nElementos++;
		}
		else
		{
			cout << endl;
			cout << " Elemento repetido." << endl;
		}
	}


	/*MUTADOR(set)Eliminiamos un elemento del vector, pasandole la dir del elemento.
	Se buscar en el vector y si lo encontramos desplazamos desde la posicion a la derecha*/
	void eliminaC(const G &g){

		if (this->nElementos == 0){

			 cout << endl;
			 cout << " Conjunto Vacio, no se puede eleminar ." << endl;
		 }
		else{
			
			//Inicializamos datos para la busqueda 
			 int ini = 0, fin = this->nElementos - 1, pos = 0;
		
			//Si encontramos el elemento lo borramos
			if (busqueda(g, ini, fin, pos)){

				//Desplazo desde la posicion donde esta el elemento
				for(int i = pos; i< this->nElementos; i++){

					this->v[i] = this->v[i+1];
				}

				//Decrementamos elementos
				this->nElementos--;
			}
		}
		
	}


	/*OBSERVADOR(get): Si existe el elemento en el vector
	const G &g = direcccion del elementos que buscamos
	return : true existe
	*/
	bool existe( const G &g)const{

		//Inicializamos datos para la busqueda 

		int ini = 0, fin = this->nElementos - 1, pos = 0;

		return busqueda(g, ini, fin, pos);
	}


	/* OBSERVADOR(get): Permite visualizar el contenido
	del conjunto.
	*
	*/
	void imprime()const{

		if (this->nElementos == 0){
			cout << "El conjunto es vacio" << endl;;

		}
		else{

			for (int i = 0; i < this->nElementos; i++)
				
				cout << v[i] << " ";
		}

	}


	
	/*
	*Mutador(set): Interseccion de un elementos que se encuentre en ambos
	*conjuntos en el conjunto que hace la llamada
	*Ej: c1.interseccionC(c2,c3) -> c1 contendra la interseccion
	*Se trata de un metodo void, ya que el cambio se hace sobre el conjunto
	que hace la llamada

	Es necesario Conjunto <G>&- > Le paso !!la direccion!!! de un conjunto especifico (del tipo G) 
	*/
	void interseccionC(const Conjunto <G>& c1, const Conjunto <G>& c2){

		/*
		Liberamos el conjunto sobre el cual se va hacer la interseccion
		(la que hizo la llamada)
		*/
		finaliza();
		inicia();

		int iteC1 = 0, iteC2 = 0;

		/*
		* Si llegamos con alguno de los iteradores a los elementos totales
		* se terimna la interseccion
		* Ya que si en un conjunto se acaban los elementos ya no puede
		* existir interseccion
		*/
		while (iteC1 < c1.nElementos && iteC2 < c2.nElementos){

			//Si los elementos de los 2 son iguales->inserto en el conjunto que llama
			if (c1.v[iteC1] == c2.v[iteC2]){
				//Insertarmos uno y aumentamos iteradores
				insertaLineal(c1.v[iteC1]);
				iteC1++;
				iteC2++;
			}
			else if (c1.v[iteC1] < c2.v[iteC2]){

				iteC1++;
			}
			else
				iteC2++;
		}


	}



	/*
	Mutador (set ): Union de los elementos que se encuentre en ambos
	*conjuntos que se pasan por parametros en el conjunto que hace la llamada.
	*Ej: c1.unionC(c2,c3) -> c1 contendra la union de ambos conjuntos 
	*Se trata de un metodo void, ya que el cambio se hace sobre el conjunto
	que hace la llamada

	*/
	void unionC(const Conjunto <G>& C1, const Conjunto <G>& C2){

		/*
		Liberamos el conjunto sobre el cual se va hacer la interseccion
		(la que hizo la llamada)
		*/
		finaliza();
		inicia();

		//Iteradores para ambos vectores
		int iteC1 = 0, iteC2 = 0;


		while (iteC2 < C2.nElementos && iteC1 < C1.nElementos)
		{
			/*
			* Si el elemento Con1 es menor que el de Con2
			* insertamor el elemento Con1
			*/

			if (C1.v[iteC1] < C2.v[iteC2]){


				insertaLineal(C1.v[iteC1]);
				//Desplazamos el iterador de este conjunto
				iteC1++;

				/*
				* Si el elemento Con2 es menor que el de Con1
				* insertamor el elemento Con2
				*/

			}
			else if (C2.v[iteC2] < C1.v[iteC1]){

				insertaLineal(C2.v[iteC2]);
				//Desplazamos el iterador de este conjunto
				iteC2++;
			}
			else{
				//Si los elementos son iguales, insertamos uno
				//Y avanzamos los dos iteradores
				insertaLineal(C2.v[iteC2]);
				iteC2++;
				iteC1++;
			}
		}


		/*
		Si quedan elementos por insertar en el c1
		insertarmos
		*/
		while (iteC1 < C1.nElementos){
			
			insertaLineal(C1.v[iteC1]);
			iteC1++;
		}

		/*
		Si quedan elementos por insertar en el c2
		insertarmos
		*/
		while (iteC2 < C2.nElementos){

			insertaLineal(C2.v[iteC2]);
			iteC2++;
		}
	}


	/*
	
	Mutador (set ): La diferencia de los elementos de un conjunto1 que no estan en
	conjunto 2.
	*/
	void diferenciaC(const Conjunto <G>& C1, const Conjunto <G>& C2){

		/*
		Liberamos el conjunto sobre el cual se va hacer la interseccion
		(la que hizo la llamada)
		*/
		finaliza();
		inicia();



		//Iteradores para ambos vectores
		int iteC1 = 0, iteC2 = 0;
		
		while (C2.nElementos > iteC2 && C1.nElementos > iteC1){

			/*
			Si el elemento c1 es menor que c2, quiere decir que en c2
			no exisitara el elemento c1 por lo que puedo insertar
			O c2 ya ha sido recorrido entero por lo que insertor
			los que falten de c1
			*/
			if (C1.v[iteC1] < C2.v[iteC2])
			{
				//Insertamos y aumentamos el iterador
				insertaLineal(C1.v[iteC1]);
				iteC1++;
			}else if (C2.v[iteC2] < C1.v[iteC1]){
				/*
				Si el elemento c1 es mayor que c1, quiere decir que en c2
				puede existir c1, por lo que avanzamos al de c2
				*/
				iteC2++;
			}
			else if (C2.v[iteC2] == C1.v[iteC1]){
				//Avanzo los punteros a los siguientes
				iteC2++;
				iteC1++;
			}



		}


		while (C1.nElementos < iteC1)
		{
			//Insertamos y aumentamos el iterador
			insertaLineal(C1.v[iteC1]);
			iteC1++;
		}



	}

	/*
	MUTADOR (SET): Los elementos que no pertenecen a la interseccion de C1 y C2 y
	pertenecen a C1 o C2.
	
	*/
	void diferenciaSimetricaC(const Conjunto <G>& C1, const Conjunto <G>& C2){

		/*
		Liberamos el conjunto sobre el cual se va hacer la interseccion
		(la que hizo la llamada)
		*/
		finaliza();
		inicia();

		bool fin = false;

		//Iteradores para ambos vectores
		int iteC1 = 0, iteC2 = 0;

		//Si los iteradores no llegan alcanzar a todos los elementos en vector
		while (iteC1 < C1.nElementos && iteC2 < C2.nElementos){

			//Si los elementos de los 2 son iguales (interseccion)
			//aumento los iteradores
			if (C1.v[iteC1] == C2.v[iteC2]){

				iteC1++;
				iteC2++;
			}
			else if (C1.v[iteC1] < C2.v[iteC2]){
				//Al ser menor el elemento del C1, son distintos por lo
				//que podemos insertar 
				insertaLineal(C1.v[iteC1]);
				iteC1++;
			}
			else if (C2.v[iteC2] < C1.v[iteC1]){
				/*
				El elemento de c2 es menor por lo que no existira
				este elemento en c1 y puedo insertarlo
				*/ 
				insertaLineal(C2.v[iteC2]);
				iteC2++;
			}



		}

		/*
		Si quedan elementos por insertar en el c1
		insertarmos
		*/
		while (iteC1 < C1.nElementos){

			insertaLineal(C1.v[iteC1]);
			iteC1++;
		}

		/*
		Si quedan elementos por insertar en el c2
		insertarmos
		*/
		while (iteC2 < C2.nElementos){

			insertaLineal(C2.v[iteC2]);
			iteC2++;
		}
}

	/*
	Comprueba si el conjunto que hace la llamada y el conjunto
	pasado por parametro tiene algun elemento en comun
	Si tiene un elemento en comun: No disjuntos (false)
	Si no tiene elementos en comun: disjuntos (true)
	
	
	*/
	bool disyuncionC( const Conjunto <G>& C1)
	{
	
		bool iguales = true;

		//Compruebo si es el mismo conjunto 
		if( this == &C1)
		{
			return false;
		}
		else{
			//Iteradores para ambos vectores
			int miIterador = 0, iteC1 = 0;
			
			//Compruebo uno a uno a ver si son iguales
			//y si hay alguno
			while(iguales && (iteC1 < C1.nElementos &&
				miIterador < this->nElementos)){

				/*
				Si el elemento de c1 es menor que el elemento
				que hace la llamada 
				*/
				if( C1.v[iteC1] < this->v[miIterador])
				{
				/*
				Si el elemento de c1 es mayor que el elemento
				que hace la llamada.Comprobamos el siguiente elemento de c1
				*/
					iteC1++;
				}
				
				else if( C1.v[iteC1] > this->v[miIterador])
				{
					/*
					Si el elemento de c1 es menor que el elemento
					que hace la llamada.
					Comprobamos el siguiente elemento de mi conjunto
					*/
					miIterador++;
				}
				else if ( C1.v[iteC1] == this->v[miIterador])
				{
					//Hay un elemento comun, no son disjuntos
					iguales = false;

				}
			}
		
		
		}


	return iguales;
	}
	
	void complemento(const Conjunto<G>& C1){



	}
	//----------METODOS UTILES---------------------
	/*
	Operador de igualdad entre dos conjuntos
	*/
	bool operator==(const Conjunto<G>& c1){

		//Si tienen distinto numero de elementos no son iguales
		if (this->nElementos != c1.nElementos){
			return false;
		}
		//Comparo uno a uno
		for (int i = 0; i < this->nElementos; i++){

			if (this->v[i] != c1.v[i]){
				return false;
			}
		}

		return true;
	}

	/*
	Operador de asignacion entre dos conjuntos
	*/
	Conjunto<G>& operator=(const Conjunto<G>& c1){

		//Compruebo si no  es el mismo
		if (this != &c1){

			finaliza();
			copia();
		}

		/*
		ESTOY DEVOLVIENDO &
		PORQUE VOY A DEVOLVER * SEGUN
		LA PILA*/
		return this;
	}

	/*
	Operador de no igualdad entre dos conjuntos
	*/
	bool operator!=(const Conjunto<G>& c1){

		return !(*this == c1)
	}


	//----------METODOS UTILES---------------------


protected:

	/*
	Inicializa los valores del objeto
	*/
	void inicia(){
		/*
		Creo un vector dinamico del tamaño inicial
		al puntero le asigno la direccion donde empieza
		el primen indice del vector
		*/
		v = new G[TAM_INI];
		//Tamaño por defecto
		this->tam = TAM_INI;

		//No hay elementos
		this->nElementos = 0;
	}


	/*
	Libera recursos del objeto
	*/
	void finaliza(){
		//Liberamos memoria
		delete[] v;

		//Apuntamos hacia un valor nulo, por si acaso
		v = nullptr;
	}



	/*Amplia el tamaño del vector original, utilizando un puntero auziliar
	para no perder la referencia al vector original */
	void amplia(){

		/*
		Puntero auxiliar para tener referencia a la direccion
		del vector viejo que contiene los datos
		*/
		G *viejo = v;

		//Ampliamos el tamaño que usara el nuevo vector
		tam = tam * 2;

		//Creamos el nuevo vector con nuevo tamaño
		v = new G[tam];

		/*Copiamos el contenido del array que esta apuntando
		atras ves del puntero viejo al nuevo vector (ampliado) que
		apunta v. Elemento a elemento
		*/
		for (int i = 0; i< this->nElementos; i++){
			v[i] = viejo[i];
		}

		//Liberamos el vector que esta apuntado por viejo, ya no sirve
		delete[] viejo;

	}



	/* Observador(get) Busqueda binaria , busca en el vector un elemento
	const T *v = vector que contiene los elementos (puntero) constante
	const T &elemento = direccion del elemento que buscamos
	-> accederemos a su contenido sin * y sin &
	int inicio = del vector
	int fin = fin del vector
	bool& existe = para saber si existe el elemento en el vector  E/S
	int& pos = E/S : para almacenar la posicion que le corresponde en el vector
	al ser ordenador*/
	bool busqueda(const G&elemento, int ini, int fin, int &pos)
	{

		int mitad = 0;
		bool existe = false;

		if ((ini <= fin) && !existe){

			mitad = (ini + fin) / 2;

			if (elemento == this->v[mitad]){
				/*
				Si encontramos el elemento, la mitad
				tendra su posicion y paramos de buscar
				*/
				existe = true;
				pos = mitad;
			}
			else if (elemento < this->v[mitad]){
				/*
				Si el elemento es menor que el elemento en el
				vector quiere decir que puede que se encuentre en la izquierda
				del vector para insertar
				*/
				pos = mitad;
				busqueda(elemento, ini, mitad - 1, pos);
			}
			else{
				/*
				Si el elemento es mayor que el elemento en el
				vector quiere decir que puede que se encuentre en la derecha
				del vector para insertar
				*/
				pos = mitad + 1;
				busqueda(elemento, mitad + 1, fin, pos);
			}
		}
		return existe;
	}

	/*
	Mutador(set)
	Inserto el elemento en la posicion que corresponda segun el nElementos
	que hay en el vector, inserccion lineal
	
	*/
	void insertaLineal(const G &elemento){

		//Compruebo que hay espacio en el vector
		if (this->nElementos == this->tam){

			amplia();
		}

		//Inserto el elemento en el indice que le corresponde
		this->v[this->nElementos] = elemento;

		//aumento el numero de elementos en el vector del conjunto que llama 
		this->nElementos++;
	
	}

	/*
	Copia los elementos de un conjunto pasado por parametro
	a otro conjunto que hace la llamada uno a uno
	*/
	void copia(const Conjunto<G>& c1){

		this->nElementos = c1.nElementos;
		this->tam = c1.tam;

		//Creamos un vector con el nuevo tamaño
		this->v = new G[tam];

		//Copiamos uno a uno
		for (unsigned int i = 0; i < this->nElementos; i++){

			this->v[i] = c1.v[i];
		}
	}

private:

	//Privado que utiliza el tad

	//Puntero al vector(Contiene direccion de memoria, donde estan los datos)
	G *v;

	//Tamaño del vector
	long long int tam;

	//Numero de elementos en el vector
	long long int nElementos;




};

#endif /* CONJUNTO_H_ */
