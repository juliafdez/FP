#ifndef __listaCadenas_H
#define __listaCadenas_H
#include <iostream>
#include <string>
#include <iomanip>


using namespace std;
const int MAXCADENAS = 100;
const int TAMMIN = 3;

typedef string *tCadenas;// [MAXCADENAS];

typedef struct {
	tCadenas puntCadena;
	int contador;
	int dim;
}tListaCadenas;

int getTamano(const tListaCadenas & l);//Devuelve el tamaño de la lista
string getCadena(const tListaCadenas &l, int pos);//Devuelve una cadena en la posicion de pos
void insertar(tListaCadenas &l, const string &s);//Inserta un elemento al final de una lista
bool buscar(const tListaCadenas &l, const string &s);//Devuelve true si la cadena esta en la lista, false si no.
void eliminar(tListaCadenas &l, int pos);//Elimina el elemento en la posicion pos
void imprimir(const tListaCadenas &l);//Imprime los elementos de la lista
void inicializaLista(tListaCadenas &lista);//Inicializa el puntero, el contador y la dimension
void destruirLista(tListaCadenas &lista);//Elimina la lista de memoria, con a 0 y dim a 0
void ListaNula(tListaCadenas  &lista);//crea una lista a NULL con dim y cont a 0;
#endif