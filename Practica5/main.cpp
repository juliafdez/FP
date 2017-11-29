/*
Julia Fernandez Reyes - 70421020B
Miguel Perez de la Rubia - 53731992J
1ºE - Fundamentos de la Programación
Practica 5
*/
#include "checkML.h"
#include "indice.h"
#include "matrices.h"
#include <Windows.h>


using namespace std;

const string ARCHIVOINICIAL = "0raiz.txt";
void imprimirTabla(const tIndicePalabras &tabla);
string pedirPalabra();
int buscaIndice(const tListaCadenas &totales, string archivo);

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	tIndicePalabras tabla;
	tListaCadenas totales;
	tMatriz L;
	int pos;
	string pal, indices;
	tVector v;
	int indice = 0;

	L.dim = 0;
	inicializaIndice(tabla);

		cout << "Introduce el nombre del archivo con el que se empezaran a crear los indices: ";
		cin >> indices;
		cout << "Cargando archivos";
		for (int i = 0; i < 3; i++) {
			Sleep(250); 
			cout << ".";
		}
		Sleep(750);
		cout << "[correcto]\n";
		Sleep(800);
		cout << "Cargando tabla";
		for (int i = 0; i < 3; i++) {
		Sleep(250);
			cout << ".";
		}
		Sleep(750);
		cout << " [correcto]\n";
		
	crearTabla(tabla, indices, totales, L, v);
	
	tListaCadenas aux;
	tVector vAux;
	int k = 0;

	inicializaLista(aux);
	pal = pedirPalabra();
	while (pal != "fin") {
		k = 0;
		ListaNula(aux);
		if (buscBin(tabla, pal, pos)) {
			cout << "\nPalabra encontrada \n";
			for (int i = 0; i < getTamano(tabla.puntList[pos].lista); i++) {
				indice = buscaIndice(totales, getCadena(tabla.puntList[pos].lista, i));
				insertar(aux, tabla.puntList[pos].lista.puntCadena[i]);
				vAux.vector[k] = v.vector[indice];
				vAux.tam = aux.contador;
				k++;
				

			}
			ordenar(vAux, aux);
			
			for (int j = 0; j < getTamano(tabla.puntList[pos].lista);j++) {
				cout << "\t en : " << getCadena(aux, j) << " y relevancia ("<< vAux.vector[j] << ")\n";
			}
			cout << endl;
		}
	else cout << "Palabra no encontrada.\n\n";
	
	pal.clear();
	pal = pedirPalabra();
	}
	destruirLista(totales);
	destruirLista(aux);
	destruirIndice(tabla);

	system("Pause");
	return 0;
}

void imprimirTabla(const tIndicePalabras &tabla) {
	imprimir(tabla);
}

string pedirPalabra() {
	string pal;
	cout << "Introduce la palabra a buscar (\"fin\" para terminar): ";
	cin >> pal;
	return pal;
}

int buscaIndice(const tListaCadenas &totales, string archivo) {
	int indice = 0;
	int i = 0;
	bool encontrado = false;

	while( i < totales.contador&&!encontrado) {
		if (getCadena(totales, i) == archivo) {
			indice = i;
			encontrado = true;
		}
		i++;
	}
	
	return indice;
}