/**
	Versión definitiva del Splay Tree
	Por Fernando Pérez Gutiérrez
	
	Parte de la estructura estába basada en la librería Arbin.h usada
	en la asignatura EDA.
	
	También se ha buscado información por internet para solucionar
	algunos problemas, en general sobre el uso de punteros y sobre las
	rotaciones RR y LR.
	
	En el método Splay(), no hago uso de una rotación RR y LR tal y cómo
	la vimos en clase, esto es porque tras empezarlo, se me comenzó a
	complicar su uso y buscando en internet observé una forma un poco
	más sencilla (a mi parecer), esta consiste en realizar dos rotaciones
	sencillas, una sobre el padre y otra sobre el abuelo (que equivale
	a realizar la rotación correspondiente RR o LR).
	
	Las páginas visitadas para la creación de este código han sido:
		
		- Corrección de errores y datos no tan concretos.
			http://stackoverflow.com/
			http://cplusplus.com/
		
		- Entendimiento con más profundidad sobre SplayTrees así cómo la idea
		  de usar dos veces la rotacion sencilla.
			Los apuntes de clase.
			https://en.wikipedia.org/wiki/Tree_rotation#/media/File:Tree_Rotations.gif
*/

#ifndef __SPLAY_H
#define __SPLAY_H

#include <iostream>
#include <cstdlib>
#include <list>

/*
	El SplayTree estará compuesto de estos nodos, que contienen un hijo izquierdo,
	un hijo derecho y un padre.
	
	Durante el comienzo consideré que no era necesario un puntero al nodo padre, pero
	con el tiempo me di cuenta de lo útil que era a la hora de realizar las rotaciones.
*/
struct Nodo  {
	Nodo *izq;
	Nodo *der;
	Nodo *padre;
	
	int valor;
};

class SplayTree {
	private:
	// Este es el nodo por donde comenzará nuestra estructura.
	Nodo* root;

	// Right Rotate
	void RR(Nodo *nodo){
		Nodo *hijoIzq = nodo->izq;
		Nodo *hijoIzqDer = hijoIzq->der;
		Nodo *padre = nodo->padre;
		
		if(padre != NULL) { // Si tiene padre
			if(padre->der == nodo) { // Si el hijo derecho del padre es nuestro nodo
				padre->der = hijoIzq;
			} else {
				padre->izq = hijoIzq;
			}
		}
		
		if(hijoIzqDer != NULL) // Si exise el hijo derecho del hijo izquierdo de nuestro nodo
			hijoIzqDer->padre = nodo;
		
		hijoIzq->padre = padre; // Consolido el movimiento (mantiene la consistencia)
		hijoIzq->der = nodo;
		
		nodo->padre = hijoIzq; // De nuevo para mantener la consistencia
		nodo->izq = hijoIzqDer;
	}

	// Left Rotate
	void LR(Nodo *nodo){
		Nodo *hijoDer = nodo->der;
		Nodo *hijoDerIzq = hijoDer->izq;
		Nodo *padre = nodo->padre;
		
		if(padre != NULL) { // Si tiene padre
			if(padre->der == nodo) { // Si el hijo derecho del padre es nuestro nodo
				padre->der = hijoDer;
			} else {
				padre->izq = hijoDer;
			}
		}
		
		if(hijoDerIzq != NULL) // Si exise el hijo izquierdo del hijo derecho de nuestro nodo
			hijoDerIzq->padre = nodo;
		
		hijoDer->padre = padre;
		hijoDer->izq = nodo;
		
		nodo->padre = hijoDer;
		nodo->der = hijoDerIzq;
	}

	// Algoritmo de reequilibrado (el splay o flotacion)
	void Splay (Nodo *nodo) {
		
		// Saldremos de este bucle con los break;
		while (true) {
			Nodo *padre = nodo->padre;				// El padre del que estamos tratando
			
			if (padre == NULL)						// Si no tiene padre, significa que ya hemos terminado las rotaciones
				break;
			
			Nodo *padreDePadre = padre->padre;
			
			// Si no tiene abuelo
			if (padreDePadre == NULL) {
				if (padre->izq == nodo) {			// Si el hijo izquierdo del padre es nuestro nodo
					RR(padre);						// Rotación a la derecha del padre
				} else {							// Si el hijo derecho del padre es nuestro nodo
					LR(padre);
				}
				
				break;
			}
			
			// Si el padre de nuestro nodo es el hijo izquierdo del abuelo de nuestro nodo (para saber si es el izquierdo o el derecho)
			if (padreDePadre->izq == padre) {
				// Volvemos a hacer cómo en el caso anterior, con la diferencia
				// de que ahora si habrá que rotar tambien al padreDePadre (porque este no es NULL)
				if (padre->izq == nodo) {			// Si el hijo izquierdo del padre es nuestro nodo
					RR(padreDePadre);
					RR(padre);
				} else { 							// Si el hijo derecho del padre es nuestro nodo
					LR(padre);
					RR(padreDePadre);
				}
			} else {
				if (padre->izq == nodo) {
					RR(padre);
					LR(padreDePadre);
				} else {
					LR(padreDePadre);
					LR(padre);
				}
			}
		}
		
		// Al terminar el splay sólo nos queda cambiar la variable root por la nueva (nuestro nodo)
		root = nodo;
	}
	
	
	/*
		Tres métodos para recorrer nuestro SplayTree.
		inordenAux, preodenAux y postordenAux.
		Estos tres métodos son auxiliares y privados porque serán
		llamados desde los métodos publicos que directamente
		devuelven la lista.
		Está hecho así paraque no sea el que importe esta
		libreria el que tenga que crear una lista vacía y pasarla
		por parámetro.
	*/
	void inordenAux (Nodo *nodo, std::list <int> &res) {
		if (nodo == NULL)
			return;
		
		if (nodo->izq != NULL)
			inordenAux(nodo->izq, res);
		
		res.push_back (nodo->valor);
		
		if (nodo->der != NULL)
			inordenAux (nodo->der, res);
	}
	
	void preordenAux (Nodo *nodo, std::list <int> &res) {
		if (nodo == NULL)
			return;
		
		res.push_back(nodo->valor);
		
		if (nodo->izq != NULL)
			preordenAux(nodo->izq, res);
		
		if (nodo->der != NULL)
			preordenAux(nodo->der, res);
	}
	
	void postordenAux (Nodo *nodo, std::list <int> &res) {
		if (nodo == NULL)
			return;
		
		if (nodo->izq != NULL)
			postordenAux(nodo->izq, res);
		
		if (nodo->der != NULL)
			postordenAux(nodo->der, res);
		
		res.push_back(nodo->valor);
	}
	
	/*
		Método auxiliar que borra uno a uno todos los nodos del SplayTree
	*/
	void destruir (Nodo *nodo) {
		if (nodo == NULL)
			return;
		
		if (nodo->izq != NULL)
			destruir(nodo->izq);
		
		if (nodo->der != NULL)
			destruir(nodo->der);
			
		free(nodo);
	}
	
	public:
	
	// Constructora
	SplayTree () {
		root = NULL;			// SplayTree vacío
	}
	
	// Destructora
	~SplayTree() {
		destruir(root);			// Libero todo el espacio de cada uno de los nodos
		root = NULL;			// Pongo root a NULL porque el árbol ya es vacío
	}
	
	/*
		Permite acceder al nodo Root.
		Lo uso porque cree un método mostrarArbol que no era necesario que muestra
		todo el sub arbol a partir de un nodo.
	*/
	Nodo* getRoot(){
		return root;
	}
	
	// Insertar valor en el SplayTree
	void insertar (int valor) {
		if (root == NULL) {						// Si nuestro SplayTree está vacío
			root = (Nodo *)malloc(sizeof(Nodo));// Reservamos un espacio en memoria dinámica del tamaño exacto de un nodo (para nuestro root).
			
			// Inicializamos todos los punteros de nuestra estructura Nodo
			root->izq = NULL;
			root->der = NULL;
			root->padre = NULL;
			
			// Insertamos en root el valor
			root->valor = valor;
			
			// Ya hemos insertado el valor, y cómo esta sólo no necesito realizar el splay.
			return;
		}
		
		Nodo* aux = root;						// Necesitaré este puntero auxiliar (que será donde insertemos más adelante)
		
		// Saldremos del bucle usando breaks.
		while (true) {
			if (valor <= (aux->valor)) {		// Si debemos insertar a la izquierda
				if (aux->izq != NULL) {			// Si tiene hijo izquierdo
					aux = aux->izq;
				} else {						// Si no tiene hijo izquierdo lo creamos e insertamos
					/* 
						Reservamos el espacio.
						Lo hago con malloc y no con new porque me resulta más comodo hacerlo así
						siempre que son tipos simples y porque lo usamos mucho en Sistemas Operativos.
					*/
					aux->izq=(Nodo *)malloc(sizeof(Nodo));
					aux->izq->padre = aux;		// Marcamos quién es su padre
					
					aux = aux->izq;				// Actualizo el valor de aux (nos servirá para cuando llame a Splay(aux))
					
					// Inicializamos todos los valores (teniendo en cuenta que ya actualicé aux)
					aux->der = NULL;
					aux->izq = NULL;
					aux->valor = valor;
					break;
				}
			} else {							// Si debemos insertar a la derecha (exatamente igual pero donde pone izq poner der)
				if (aux->der != NULL) {
					aux = aux->der;
				} else {
					aux->der=(Nodo *)malloc(sizeof(Nodo));
					aux->der->padre = aux;
					
					aux = aux->der;
					
					aux->der = NULL;
					aux->izq = NULL;
					aux->valor = valor;
					break;
				}
			}
		}
		
		Splay(aux);
	}

	// Buscar un valor en el SplayTree, si no lo encuentra borrará el último nodo por el que pasó.
	Nodo* buscar (int valor) {
		if (root == NULL) {
			return NULL; 		// Si el splay tree está vacío, devuelvo NULL
		}
		
		Nodo *aux = root;
		
		while (aux != NULL) { 	// Mientras pueda seguir mirando
			if (valor == aux->valor) {
				// Lo hemos encontrado, aux ahora es el nodo que nos interesa
				// Pero antes de devolverlo debemos hacer otras cosas (solamente salimos del bucle)
				break;
			}
			if (valor < (aux->valor)) { 	// Si el buscado está a la izquierda
				// Nos preparamos para la siguiente vuelta del bucle
				
				// Si entra significa que no lo hemos encontrado (estamos en una hoja),
				// asi que el nodo que hemos decidido devolver es aux (el último visitado)
				if (aux->izq == NULL)
					break;
					
				aux = aux->izq;
			} else { 						// Si el buscado está a la derecha
				// Si entra significa que no lo hemos encontrado (estamos en una hoja),
				// asi que el nodo que hemos decidido devolver es aux (el último visitado)
				if (aux->der == NULL)
					break;
			
				aux = aux->der;
			}
		}
		
		// Ahora realizamos el reequilibrado sobre el nodo que hemos seleccionado
		// Este puede ser el buscado o en su defecto, el último nodo por el que hemos pasado.
		Splay(aux);
		
		// Finalmente lo devolvemos
		return aux;
	}

	/*
		Borrar un valor en el SplayTree, si ese valor no existe, flotará el último nodo por el que pasó
		al buscar dicho valor y devolverá false.
		
		Por otro lado, si el SplayTree está vacío, devolverá false (es decir, que no ha podido borrar),
		en otro caso devolverá true.
	*/
	bool borrar (int &valor) {
		if (root == NULL)				// El SplayTree esta vacío
			return false;
	
		Nodo *buscado = buscar(valor);	// Buscamos el valor en el SplayTree, si no lo encuentra, devolverá el último por el que pasó.
		
		if (buscado->valor != valor) 	// Me aseguro de si el valor buscado es el que queriamos
			return false;
		
		Nodo *aux = buscado->izq;
		
		if (aux == NULL) {				// Si no tiene hijo izquierdo
			root = buscado->der;		// Colocamos en root el hijo derecho del buscado
			// Sin olvidarnos de actualizar que root no tiene padre
			// Ya nadie apunta a buscado
			if (root != NULL)			// Aquí nos aseguramos si es que borramos el último nodo
				root->padre = NULL;		// Si no lo hicieramos, daría error al borrar el último nodo de nuestro SplayTree.
			
			free(buscado);				// Liberamos el nodo buscado
			return true;				// Hemos conseguido borrarlo
		}
		
		while (aux->der != NULL) {
			// Recorremos todos los hijos derechos desde el hijo izq del nodo
			// Y nos quedamos con el que sea semi-hoja (que no tenga hijo derecho)
			aux = aux->der;
		}
		
		if (buscado->der != NULL) {
			aux->der = buscado->der; 	// El hijo derecho del nodo a borrar lo guardamos en el hijo derecho de la hoja
			buscado->der->padre = aux;	// Mantenemos la consistencia haciendo que el padre del hijo derecho del buscado sea ahora la hoja
		}
		
		// Sin olvidarnos de actualizar que root no tiene padre
		// Ya nadie apunta a buscado
		root = buscado->izq;
		root->padre = NULL;
		
		free(buscado);					// Liberamos el nodo buscado
		return true;					// Hemos conseguido borrarlo
	}
	
	/*
		Métodos públicos de recorridos del SplayTree.
		Nos dan una lista con el recorrido del árbol en:
		Inorden, preorden y postorden.
	*/
	std::list <int> inorden(Nodo *nodo) {	
		std::list <int> resultado;
		
		inordenAux(nodo, resultado);
		
		return resultado;
	}

	std::list <int> preorden (Nodo *nodo) {
		std::list <int> resultado;
		
		preordenAux(nodo, resultado);
		
		return resultado;
	}

	std::list <int> postorden(Nodo *nodo) {
		std::list <int> resultado;
		
		postordenAux(nodo, resultado);
		
		return resultado;
	}
	
	/*
		Este método se parece mucho a un recorrido preorden,
		lo he creado para poder observar perfectamente si mi
		splay tree está bien creado.
	*/
	void mostrarArbol (Nodo *nodo) {
		if (root == NULL) {
			std::cout << "SplayTree vacio" << std::endl;
			return;
		}
		if (nodo == NULL)
			return;
		
		if (nodo == root)
			std::cout << "Root: " << nodo->valor << std::endl;
		
		if (nodo->izq != NULL) {
			std::cout << "Hijo izquierdo de " << nodo->valor << " => " << nodo->izq->valor << std::endl;
			mostrarArbol(nodo->izq);
		}
		if (nodo->der != NULL) {
			std::cout << "Hijo derecho de " << nodo->valor << " => " << nodo->der->valor << std::endl;
			mostrarArbol(nodo->der);
		}
	}
};

#endif // __SPLAY_H