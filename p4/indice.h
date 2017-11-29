#ifndef indice_h
#define indice_h

#include "claveValor.h"
#include "matrices.h"

#include <cctype>
#include <algorithm>

void crearTabla(tIndicePalabras & tabla, const std::string & archivoInicial, tListaCadenas & totales, tMatriz & L, tVector &v);//.A partir de archivoInicial, rellena la tabla tabla, tras haberla inicializado(a vacía)
void ordenar(tVector &v, tListaCadenas &totales);

#endif