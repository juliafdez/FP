#include "claveValor.h"

using namespace std;


int getTamanno(const tIndicePalabras & l) {
	return l.cont;
}

tRegistroIndicePalabras getRegistro(const tIndicePalabras & l, int pos) {
	return 	 l.pal[pos];
}

bool esta(const tIndicePalabras & l, const string & s) {
	int pos;
	return buscBin(l, s, pos);
}

tListaCadenas buscar(const tIndicePalabras & l, const string & s) {
	int pos;
	buscBin(l, s, pos);
	return l.pal[pos].lista;
}

void insertar(tIndicePalabras & idx, const string& palabra, const string& nombreArchivo) {
	int pos;
	if (buscBin(idx, palabra, pos)) {
		insertar(idx.pal[pos].lista, nombreArchivo);
	}
	else{
		for (int i = idx.cont; i > pos; i--){
			idx.pal[i] = idx.pal[i - 1];
		}
		idx.pal[pos].lista.contador = 0;
		idx.pal[pos].registro = palabra;
		insertar(idx.pal[pos].lista, nombreArchivo);
		idx.cont++;
	}

}

void imprimir(const tIndicePalabras & idx){
	for (int i = 0; i < idx.cont; i++) {
		cout << setw(20) << left << idx.pal[i].registro<< "{\n";
		imprimir(idx.pal[i].lista);
		cout <<"\n";
	}
}

bool buscBin(const tIndicePalabras &l, const string &pal, int &pos){
	bool encontrado = false;
	int mitad, ini = 0, fin = l.cont - 1;
	pos = -1;
	while (ini <= fin && !encontrado) {
		mitad = (fin + ini) / 2;
		if (pal == l.pal[mitad].registro) {
			encontrado = true;
		}
		else if (pal < l.pal[mitad].registro) {
			fin = mitad - 1;
		}
		else {
			ini = mitad + 1;
		}
	}
	if (encontrado) {
		pos = mitad;
	}
	else pos = ini;

	return encontrado;
}

