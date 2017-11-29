#include "listaCadenas.h"
#include "checkML.h"

using namespace std;

void redimensionar(tListaCadenas &lista);//cambia la dimension del array al que apunta el puntero

bool buscar(const tListaCadenas &l, const string & s) {
	bool encontrado = false;
	int i = 0, max = getTamano(l);
	while (i < max && !encontrado) {
		if (l.puntCadena[i] == s) {
			encontrado = true;
		}
		else i++;
	}
	return encontrado;
}

string getCadena(const tListaCadenas & l, int pos) {
	return l.puntCadena[pos];
}

void insertar(tListaCadenas & l, const string & s) {
	int max = getTamano(l);
	bool encontrado = buscar(l, s);
	if (l.dim == 0) {
		inicializaLista(l);
	}
	else if (l.contador == l.dim) {
		redimensionar(l);
	}

	if (l.contador < MAXCADENAS) {
		if (!encontrado) {
			l.puntCadena[max] = s;
			l.contador++;
		}
	}
	else {
		cout << "\n Lista llena \n";
	}
	
}

int getTamano(const tListaCadenas & l) {
	return l.contador;
}

void eliminar(tListaCadenas &l, int pos) {
		for (int i = pos; i < l.contador - 1; i++) {
			l.puntCadena[i] = l.puntCadena[i + 1];
		}
	l.contador--;
}

void imprimir(const tListaCadenas &l) {
	for (int i = 0; i < l.contador; i++){
		cout <<"\t" << right << l.puntCadena[i];
		cout << endl;

	}
}

void inicializaLista(tListaCadenas &lista) {
	if (lista.dim != 0) {
		ListaNula(lista);
	}
	lista.puntCadena = new string[TAMMIN];
	lista.dim = TAMMIN;
	lista.contador = 0;

}

void destruirLista(tListaCadenas &lista) {
	if (lista.puntCadena != NULL) {
		lista.contador = 0;
		lista.dim = 0;
		delete[] lista.puntCadena;
	}
}

void redimensionar(tListaCadenas &lista) {

	int nuevaDim = (lista.dim * 3) / 2 + 1;
	if (nuevaDim > MAXCADENAS) {
		nuevaDim = MAXCADENAS;
	}
	string *pAux = new string[nuevaDim];

	for (int i = 0; i < lista.contador; i++) {
		pAux[i] = lista.puntCadena[i];
	}
	delete[] lista.puntCadena;
	lista.puntCadena = pAux;
	pAux = NULL;
	lista.dim = nuevaDim;
}

void ListaNula(tListaCadenas & lista) {
	lista.puntCadena = NULL;
	lista.dim = 0;
	lista.contador = 0;
}