/*
Julia Fernandez Reyes - 70421020B
Miguel Perez de la Rubia - 53731992J
1ºE - Fundamentos de la Programación
Practica 4
*/
#include "indice.h"
#include "matrices.h"
#include <Windows.h>


using namespace std;

const string ARCHIVOINICIAL = "0raiz.txt";
void imprimirTabla(const tIndicePalabras &tabla);
string pedirPalabra();
int buscaIndice(const tListaCadenas &totales, string archivo);

int main() {
	tIndicePalabras tabla;
	tListaCadenas totales;
	tMatriz L;
	int pos;
	string pal, indices;
	tVector v;
	int indice = 0;

	tabla.cont = 0;
	L.dim = 0;
	
	
	cout << "Introduce el nombre del archivo con el que se empezaran a crear los indices: ";
		cin >> indices;
		cout << "Cargando archivos";
		for (int i = 0; i < 3; i++) {
			Sleep(500); 
			cout << ".";
		}
		Sleep(2000);
		cout << "[correcto]\n";
		Sleep(1000);
		cout << "Cargando tabla";
		for (int i = 0; i < 3; i++) {
		Sleep(500);
			cout << ".";
		}
		Sleep(2000);
		cout << " [correcto]\n";
		
	crearTabla(tabla, ARCHIVOINICIAL, totales, L, v);

	tListaCadenas aux;
	tVector vAux;
	int k = 0;
	pal = pedirPalabra();
	while (pal != "fin") {
		k = 0;
		if (buscBin(tabla, pal, pos)) {
			cout << endl;
			cout << "\nPalabra encontrada \n\n";
			for (int i = 0; i < (tabla.pal[pos].lista.contador); i++) {

				indice = buscaIndice(totales, tabla.pal[pos].lista.cadena[i]);
				aux.cadena[k] = tabla.pal[pos].lista.cadena[i];
				vAux.vector[k] = v.vector[indice];
				vAux.tam = v.tam;
				aux.contador = tabla.pal[pos].lista.contador;
				k++;
				

			}
			ordenar(vAux, aux);
			for (int j = 0; j < tabla.pal[pos].lista.contador; j++) {

				cout << "\tEncontrada en : " << aux.cadena[j] << " y relevancia (" << vAux.vector[j] << ")" << endl;
			}
			cout << endl;
		}
	else cout << "Palabra no encontrada.\n\n";
		pal = pedirPalabra();
	}
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
		if (totales.cadena[i] == archivo) {
			indice = i;
			encontrado = true;
		}
		i++;
	}
	
	return indice;
}