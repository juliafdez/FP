#ifndef matrices_h
#define matrices_h
#include "listaCadenas.h"
const int MAX_TAM = 50;
const double C = 0.85;
const double MIN = 0.00001;

typedef struct {
	double matriz[MAX_TAM][MAX_TAM];
	int dim;
}tMatriz;

typedef struct {
	double vector[MAX_TAM];
	int tam;
}tVector;

tMatriz matrizConstante(double x, int n);
//Crea una matriz de 𝑛∙𝑛, en la que todos los valores iniciales son x.
tVector operator*(const tMatriz & m, const tVector & v);
//Multiplica una matriz por un vector.
tMatriz operator*(const tMatriz & m, double x);
//Obtiene la matriz que se obtiene multiplicando cada elemento de m por x.
tMatriz operator+(const tMatriz & m1, const tMatriz & m2);
//Suma dos matrices.
tMatriz desdeEnlacesAMatriz(const tMatriz & L);
//Devuelve la matriz M obtenida de L como en la introducción de la sección 4.
tVector normaliza(const tVector & v);
//Devuelve un vector proporcional a v con la primera componente igual a 1.0.
tVector vectorPropio(const tMatriz & M);
//M es una matriz tal que todas sus columnas suman 1, devuelve un vector v con la primera 
//componente igual a 1 tal que 𝑀∙𝑣≃𝑣.
void inicElems(tMatriz & matrix, int val);
//inicializa la nueva fila y columna a 0
void imprimir(const tMatriz & matrix);

#endif