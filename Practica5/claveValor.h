#ifndef _claveValor_h
#define _claveValor_h
#include "listaCadenas.h"

using namespace std;

const int MAX = 200;

typedef struct {
	string registro;
	tListaCadenas lista;
}tRegistroIndicePalabras;

typedef tRegistroIndicePalabras *tPalabras;


typedef struct{
	tPalabras puntList;
	int cont;
	int dim;
}tIndicePalabras;

int getTamanno(const tIndicePalabras & l);//.Devuelve el tama�o de la tabla
tRegistroIndicePalabras getRegistro(const tIndicePalabras & l, int pos);//.Devuelve el registro en la posici�n pos.
bool esta(const tIndicePalabras & l, const string & s);//.Devuelve true si la palabra es una clave en la tabla, y false en caso contrario.
tListaCadenas buscar(const tIndicePalabras & l, const string & s);// :dada una clave que est� en la tabla devuelve la lista de cadenas asociada a esa clave.
void insertar(tIndicePalabras & idx, const string & palabra, const string &nombreArchivo);//.Si palabra es ya una clave de la tabla, a�ade nombreArchivo a la lista de archivos correspondiente.Si no, crea un registro nuevo con esa informaci�n.
void imprimir(const tIndicePalabras & idx);//.Imprime la tabla.
bool buscBin(const tIndicePalabras &l, const string &pal, int &pos);//busqueda binaria mejorada
void destruirIndice(tIndicePalabras & l);
void inicializaIndice(tIndicePalabras & l);

#endif
 