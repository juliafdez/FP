#include "listaCadenas.h"

using namespace std;

bool buscar(const tListaCadenas &l, const string & s) {
	bool encontrado = false;
	int i = 0, max = getTamano(l);
	while (i < max && !encontrado) {
		if (l.cadena[i] == s) {
			encontrado = true;
		}
		else i++;
	}
	return encontrado;
}

string getCadena(const tListaCadenas & l, int pos) {
	return l.cadena[pos];
}

void insertar(tListaCadenas & l, const string & s) {
	int max = getTamano(l);
	bool encontrado = buscar(l, s);
	if (!encontrado) {
		l.cadena[max] = s;
		l.contador++;
	}
}

int getTamano(const tListaCadenas & l) {
	return l.contador;
}

void eliminar(tListaCadenas &l, int pos) {
		for (int i = pos; i < l.contador - 1; i++) {
			l.cadena[i] = l.cadena [i + 1];
		}
	l.contador--;
}

void imprimir(const tListaCadenas &l) {
	for (int i = 0; i < l.contador; i++){
		cout <<"\t" << right << l.cadena[i];
		cout << endl;

	}
}