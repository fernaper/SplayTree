#include <iostream>
#include <cstdlib>
#include <time.h>

#include <vector>
#include <map>

using namespace std;

int find( const vector<int>& where, int searchParameter ){
    int size = static_cast<int>(where.size());
    for( int i = 0; i < size; i++ ) {
       if( where[i] == searchParameter) {
           return i;
       }
    }
    return -1;
}

void generarBorrar (int repe, int max) {
	map <int, int> mapa;
	vector <int> claves;
	
	for (int i = 1; i <= repe; i++) {
		int valor = (int) (rand() % max);
		cout << valor << endl; 							// Inserto
		
		if (mapa.count(valor)) {						// Si existe
			mapa[valor] = mapa.find(valor)->second + 1; // Actualizo el numero de inserciones con ese valor
		} else {
			mapa[valor] = 1;							// Inserto 1
			claves.push_back(valor);
		}
		
		int valorBorrar = claves [(int) (rand() % claves.size())];
		
		// Toca borrar
		cout << "-1" << endl << valorBorrar << endl;
		
		int nuevo = mapa.find(valorBorrar)->second - 1;
		mapa[valorBorrar] = nuevo;							// Borro 1
		
		if (nuevo == 0) {									// Lo hago desaparecer de las estructuras si ya no queda nada
			//vector<int>::iterator it = find(claves.begin(),claves.end(),valorBorrar);
			claves.erase(claves.begin() + find(claves, valorBorrar));
			mapa.erase (valorBorrar);
		}
		
		// Inserto un nuevo valor para que aumente como realmente se esperaba
		valor = (int) (rand() % max);
		cout << valor << endl; 							// Inserto
		
		if (mapa.count(valor)) {						// Si existe
			mapa[valor] = mapa.find(valor)->second + 1; // Actualizo el numero de inserciones con ese valor
		} else {
			mapa[valor] = 1;							// Inserto 1
			claves.push_back(valor);
		}
	}
	cout << "-2" << endl; // Mando un terminar
}

void generarBuscar (int repe, int max) {
	for (int i = 1; i <= repe; i++) {
		cout << (int) (rand() % max)  << endl; 	// Inserto igual, pero no es lo que importa
		
		cout << "0" << endl;					// Busco
		cout << (int) (rand() % max)  << endl;
	}
	cout << "-2" << endl; // Mando un terminar
}

void generarInsertar (int repe, int max) {
	for (int i = 1; i <= repe; i++) {
		cout << (int) (rand() % max)  << endl;
	}
	cout << "-2" << endl; // Mando un terminar
}

int main () {
	int repe;
	int max = 1000;
	int modo;
	
	srand(time(NULL));
	
	cin >> modo; // -1, 0, 1
	cout << modo << endl;
	cin >> repe;
	
	for (int i = 0; i < 10; i++) {
		if (modo > 0) {
			generarInsertar (repe, max);
		} else if (modo == 0) {
			generarBuscar (repe, max);
		} else {
			generarBorrar(repe, max);
		}
	}
	
	return 0;
}