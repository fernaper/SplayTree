/**
	Versión definitiva del Testeo para el usuario
	Por Fernando Pérez Gutiérrez
	
	Este código es integramente mio y sirve para un
	testeo manual de la estructura de datos SplayTree.
*/
#include "SplayTree.h"

using namespace std;

// En la versión final no lo uso, pero puede ser más útil que splay.mostrarArbol();
void mostrarInorden (SplayTree &splay) {
	if(splay.getRoot() != NULL)
		cout << "root: " << splay.getRoot()->valor << endl;
	list<int> in = splay.inorden(splay.getRoot());
	cout << "[ ";
	for (std::list<int>::iterator it = in.begin(); it != in.end(); ++it) {
		cout << *it << ' ';
	}
	cout << "]\n";
}

int main () {
	SplayTree splay = SplayTree ();

	while(true) {
		int t;
		cout << "** Comandos: 0 = buscar, -1 = borrar, -2 = salir, otro = insertar (otro)" << endl;
		cout << "-? Inserte un valor: ";
		cin >> t;
		
		if(t==0){
			cout << "Inserte valor a buscar: ";
			cin >> t;

			Nodo *buscado = splay.buscar(t);
			
			cout << "Encontrado " << buscado->valor << endl;
		} else if (t == -1) {
			cout << "Inserte valor a borrar: ";
			cin >> t;

			if(splay.borrar(t)) {
				cout << "Borrado " << t << endl;
			} else {
				cout << "No se puede borrar de un SplayTree vacio" << endl;
			}
		} else if (t == -2) {
			break;
		} else {
			splay.insertar(t);
			
			cout << "Insertado " << t << endl;
		}
		
		splay.mostrarArbol(splay.getRoot());
	}
	
	mostrarInorden(splay);
}
