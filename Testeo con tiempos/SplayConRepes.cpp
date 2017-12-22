/**
	Versión definitiva para la medición de los tiempos.
	Por Fernando Pérez Gutiérrez
	
	El crédito por lo referente a la medición de tiempos, así cómo el metodo
	performancecounter_diff	pertenece integramente a la página:
		https://davidcapello.com/blog/cpp/medir-el-tiempo-de-una-rutina/
*/

/*
	Este documento .cpp lo he utilizado para obtener los ficheros de texto para
	gráficas generadas con gnuplot.
	
	La manera en que lo he hecho ha sido ejecutando por consola de comandos
	manualmente (con el fichero preparar.bat) de esta forma (usando el compilador GNU):
		SplayConTiempos.exe < sample.in > salida.out
	
	Para cada sample.in he ejecutado este programa en tres versiones diferentes,
	cada una con un "cin >> caso" diferente, para el valor necesario para
	cada gráfica (insertar, buscar o borrar)
	
	La forma en que lo he hecho no es la más "ortodoxa" pero cómo era únicamente para 
	generar las gráficas.
	
	Por otro lado, las entradas: sample.in las he generado pseudo-aleatoriamente
	con el documento generador.cpp (también realizado integramente por mi)
*/
#include "SplayTree.h"

#include <vector>
#include <windows.h>
#include <stdio.h>

using namespace std;

const int NUM_REPES = 10;

/* retorna "a - b" en segundos */
double performancecounter_diff(LARGE_INTEGER *a, LARGE_INTEGER *b) {
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	return (double)(a->QuadPart - b->QuadPart) / (double)freq.QuadPart;
}

// No lo uso, pero puede ser más útil que splay.mostrarArbol();
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
	// Lo usaré para saber si quiero los datos de insertar, de buscar o de borrar
	int caso; 										// Insertar = 1; Buscar = 0; Borrar = -1
	cin >> caso;
	
	vector <vector<double> > costes;

	for (int i = 0; i < NUM_REPES; i++) {			// Esto me va a permitir hacer NUM_REPES ejecuciones del programa para poder extraer la media
		SplayTree splay = SplayTree ();				// para cada tamaño del SplayTree. (para hacer unas gráficas más precisas)
		
		vector <double> coste;
		
		LARGE_INTEGER t_ini, t_fin;
		double secs;
		
		while(true) {
			int t;
			cin >> t;
			
			if(t==0){
				cin >> t;
				
				QueryPerformanceCounter(&t_ini); 	// Cogemos el tiempo justo antes y justo después
				Nodo *buscado = splay.buscar(t);
				QueryPerformanceCounter(&t_fin);
				
				secs = performancecounter_diff(&t_fin, &t_ini);
				
				if (caso == 0) {
					coste.push_back(secs*1000.0);
				}
			} else if (t == -1) {
				cin >> t;

				QueryPerformanceCounter(&t_ini);	// Cogemos el tiempo justo antes y justo después
				// En este caso se que siempre borrará porque mi generador de casos de prueba se asegura de ello,
				// esto me sirve para asegurarme que el tamaño de mi splay tree es el que espero.
				if(splay.borrar(t)) {
					QueryPerformanceCounter(&t_fin);
					
					secs = performancecounter_diff(&t_fin, &t_ini);
					
					if (caso == -1) {
						coste.push_back(secs*1000.0);
					}
				}
			} else if (t == -2) {
				costes.push_back(coste);			// Insertamos toda la lista
				break;
			} else {
				QueryPerformanceCounter(&t_ini);	// Cogemos el tiempo justo antes y justo después
				splay.insertar(t);
				QueryPerformanceCounter(&t_fin);
				
				secs = performancecounter_diff(&t_fin, &t_ini);
				
				if (caso == 1) {
					coste.push_back(secs*1000.0);
				}
			}
		}
	}
	
	int recorrido = costes[0].size();
	
	for (int j = 0; j < recorrido; j++) {
		double suma = 0.0;
		for (int i = 0; i < NUM_REPES; i++) {
			suma += costes[i][j];
		}
		// Mostramos toda la lista.
		// Como el compilador me permite redirigir lo que muestro de pantalla a un fichero, esto se guardará en el fichero.
		cout << j << ' ' << suma/NUM_REPES << endl;
	}
}
