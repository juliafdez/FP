#ifndef indice_h
#define indice_h

#include "claveValor.h"
#include "matrices.h"

#include <cctype>
#include <algorithm>
//A partir de archivoInicial, rellena la tabla tabla, tras haberla inicializado(a vacía)
void crearTabla(tIndicePalabras & tabla, const std::string & archivoInicial, tListaCadenas & totales, tMatriz & L, tVector &v);
//Ordena el vector y la tabla de totales por el metodo de la burbuja
void ordenar(tVector &v, tListaCadenas &totales);

#endif