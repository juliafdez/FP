#include "indice.h"
#include "matrices.h"
#include <fstream>
#include <algorithm>
#include <cctype>


using namespace std;

int buscarPos(const tListaCadenas &totales, const string &vinc);


string eliminaPunct(string cadena) {
	int tam = cadena.length();
	int i = 0;

	while (i < tam) {
		if (ispunct(cadena.at(i)) || isspace(cadena.at(i))) {
			cadena.erase(i, 1);
			i--; tam--;
		}
		i++;
	}

	return cadena;
}

string limpiaVinc(string cadena) {
	int i, tam;
	cadena.erase(0, 1);
	i = cadena.find('>');
	cadena.erase(i, 1);
	i--;
	tam = cadena.length();

	if (i < tam) {
		cadena.erase(i + 1, tam - 1 - i);
	}
	return cadena;
}

bool encuentraVinc(string cadena) {
	bool encontrado = false;

	if (cadena.at(0) == '<') {
		encontrado = true;
	}
	return encontrado;
}

string separaPalabras(string &cadena) {
	int pos = 0, tam;
	bool ok = false;
	string pal;
	tam = cadena.length();
	while (pos < tam && !ok) {
		if (ispunct(cadena.at(pos))) {
			ok = true;
			pos--;
		}
		pos++;
	}

	if (ok) {
		pal = cadena.substr(0, pos);
		cadena.erase(0, pos + 1);
	}	
	else {
		pal = cadena;
		cadena.clear();
	}

	transform(pal.begin(), pal.end(), pal.begin(), tolower);
	return pal;
}

void crearTabla(tIndicePalabras & tabla, const string & archivoInicial, tListaCadenas &totales, tMatriz &L, tVector &v){
	tListaCadenas noVisitados;
	tListaCadenas visitados;
	ifstream escritura;
	tMatriz m;
	int i = 0;
	int x = 0, k = 0;
	string aux, aux2;
	int pos = 0;

	noVisitados.contador = 0;
	visitados.contador = 0;
	totales.contador = 0;

	insertar(noVisitados, archivoInicial);
	insertar(totales, archivoInicial);
	L.dim = 0;
	inicElems(L, 0);

	while (noVisitados.contador > 0) {
		insertar(visitados, noVisitados.cadena[0]);
		eliminar(noVisitados, 0);
		escritura.open(visitados.cadena[i]);
		if (escritura.is_open()) {
				do {
					aux.clear();
					aux2.clear();
					escritura >> aux;
					if (!aux.empty()) {
						if (encuentraVinc(aux)) {
							aux = limpiaVinc(aux);
							if (!buscar(visitados, aux) && !buscar(noVisitados, aux)) {
								insertar(noVisitados, aux);
								insertar(totales, aux);
								inicElems(L, 0);
							}

							pos = buscarPos(totales, aux);
							L.matriz[pos][k] = 1;

						}
						else {
							do {
								aux2 = separaPalabras(aux);
								if (!aux2.empty()) {
									insertar(tabla, aux2, visitados.cadena[i]);
								}
							} while (!aux.empty());
						}
					}
				} while (!escritura.eof());
			}
		k++;
		x = 0;
		escritura.close();
		i++;
	}
	m = desdeEnlacesAMatriz(L);
	v = vectorPropio(m);
}

int buscarPos(const tListaCadenas &totales, const string &vinc){
	int pos = 0;
	bool encontrado = false;
	int i = 0, max = getTamano(totales);
	while (i < max && !encontrado) {
		if (totales.cadena[i] == vinc) {
			encontrado = true;
			pos = i;
		}
		else i++;
	}

	return pos;
}


void ordenar( tVector &v, tListaCadenas &totales) {
	tVector vOrden;
	tListaCadenas totOrden;
	
	bool inter = true;
	int i = 0;
	while ((i < v.tam - 1) && inter) {
		inter = false;
		for (int j = v.tam - 1; j > i; j--) {
			if (v.vector[j] > v.vector[j - 1]) {
				double tmp;
				string aux;
				tmp = v.vector[j];
				aux = totales.cadena[j];
				v.vector[j] = v.vector[j - 1];
				totales.cadena[j] = totales.cadena[j - 1];
				v.vector[j - 1] = tmp;
				totales.cadena[j - 1] = aux;
				inter = true;
			}
		}
		if (inter) {
			i++;
		}
	}
}