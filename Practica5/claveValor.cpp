#include "claveValor.h"
#include "checkML.h"
using namespace std;

void redimensiona(tIndicePalabras &indice);

int getTamanno(const tIndicePalabras & l) {
	return l.cont;
}

tRegistroIndicePalabras getRegistro( tIndicePalabras & l, int pos) {
	return l.puntList[pos];
}

bool esta(const tIndicePalabras & l, const string & s) {
	int pos;
	return buscBin(l, s, pos);
}

tListaCadenas buscar(const tIndicePalabras & l, const string & s) {
	int pos;
	buscBin(l, s, pos);
	return l.puntList[pos].lista;
}

void insertar(tIndicePalabras & idx, const string& palabra, const string& nombreArchivo) {
	int pos;
	if (buscBin(idx, palabra, pos)) {
		insertar(idx.puntList[pos].lista, nombreArchivo);
	}
	else{
		if (idx.dim == idx.cont) {
			redimensiona(idx);
		}
		for (int i = idx.cont - 1; i >= pos; i--) {
			idx.puntList[i + 1] = idx.puntList[i];
		}

		inicializaLista(idx.puntList[pos].lista);
		//cout << &idx.puntList[pos].lista << endl;
		idx.puntList[pos].registro = palabra;
		insertar(idx.puntList[pos].lista, nombreArchivo);
		idx.cont++;
	}

}

void imprimir(const tIndicePalabras & idx){
	for (int i = 0; i < idx.cont; i++) {
		cout << setw(20) << left << idx.puntList[i].registro<< "{\n";
		imprimir(idx.puntList[i].lista);
		cout <<"\n";
	}
}

bool resuelve(int ini, int fin, const string &pal, const tIndicePalabras &idx, int &pos1, int &pos2) {
	bool encontrado = false;
	int mitad = (ini + fin) / 2;
	if (ini <= fin) {
		if (pal == idx.puntList[mitad].registro) {
			encontrado = true;
			pos1 = mitad;
		}
		else if (pal < idx.puntList[mitad].registro) {
			encontrado = resuelve(ini, mitad - 1, pal, idx, pos1, pos2);
		}
		else {
			encontrado = resuelve(mitad + 1, fin, pal, idx, pos1, pos2);
		}
	}
	else pos2 = ini;
	return encontrado;
}

bool buscBin(const tIndicePalabras &l, const string &pal, int &pos){
	bool encontrado = false;
	int mitad, ini = 0, fin = l.cont - 1;
	int posIns = -1, posAct = 0;
	encontrado = resuelve(ini, fin, pal, l, posAct, posIns);
	if (encontrado) {
		pos = posAct;
	}
	else {
		pos = posIns;
	}
	return encontrado;
}

void destruirIndice(tIndicePalabras & l){
	for (int i = 0; i < l.cont; i++) {
		destruirLista(l.puntList[i].lista);
	}
	delete[]l.puntList;
}

void inicializaIndice(tIndicePalabras & l){
	l.puntList = new tRegistroIndicePalabras[TAMMIN];
	l.cont = 0;
	l.dim = TAMMIN;
}

void redimensiona(tIndicePalabras &indice) {
	int nuevaCap = (indice.dim * 3) / 2 + 1;
	tIndicePalabras nuevoIndice;

	indice.dim = nuevaCap;
	nuevoIndice.puntList = new tRegistroIndicePalabras[nuevaCap];

	for (int i = 0; i < indice.cont; i++) {
		nuevoIndice.puntList[i] = indice.puntList[i];
	}
	delete[] indice.puntList;
	indice.puntList = nuevoIndice.puntList;
}