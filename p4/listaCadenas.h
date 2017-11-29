#ifndef __listaCadenas_H
#define __listaCadenas_H
#include <iostream>
#include <string>
#include <iomanip>


using namespace std;
const int MAXT = 100;

typedef string tCadenas[MAXT];

typedef struct {
	tCadenas cadena;
	int contador;
}tListaCadenas;

int getTamano(const tListaCadenas & l);//Devuelve el tamaño de la lista
string getCadena(const tListaCadenas &l, int pos);//Devuelve una cadena en la posicion de pos
void insertar(tListaCadenas &l, const string &s);//Inserta un elemento al final de una lista
bool buscar(const tListaCadenas &l, const string &s);//Devuelve true si la cadena esta en la lista, false si no.
void eliminar(tListaCadenas &l, int pos);//Elimina el elemento en la posicion pos
void imprimir(const tListaCadenas &l);//Imprime los elementos de la lista



#endif