#include "matrices.h"

using namespace std;
tMatriz hacerPrima(const tMatriz &matrix);
void imprimirVector(const tVector &vector);
bool terminado(tVector &vector1, tVector &vector2);



tMatriz desdeEnlacesAMatriz(const tMatriz &L) {
	tMatriz M;
	double x = 1 /double(L.dim);
	M.dim = L.dim;

	tMatriz MPrima = hacerPrima(L);
	MPrima = MPrima * C;
	//imprimir(MPrima);

	tMatriz Cn = matrizConstante(x, L.dim);
	Cn = Cn * (1-C);
	//imprimir(Cn);

	M = Cn + MPrima;
	//imprimir(M);
	
	cout << endl;
	
	return M;
}

tVector normaliza(const tVector & v){
	tVector norm;
	for (int i = 0; i < v.tam; i++) {
		norm.vector[i] = v.vector[i] / v.vector[0];
	}
	return norm;
}

tVector vectorPropio(const tMatriz & M){
	tVector vector;
	int cont = 0;
	tVector vAux;
	vector.tam = M.dim;
	for (int i = 0; i < vector.tam; i++) {
		vector.vector[i] = 1;
	}
	vAux = M * vector;

	while(!terminado(vector, vAux)){
		vector = vAux;
		vAux = M * vector; 
		cont++;
	}
	
	vAux = normaliza(vAux);
	vAux.tam = M.dim;
	//imprimirVector(vAux);
	return vAux;
}

bool terminado(tVector &vector1, tVector &vector2) {
	bool termina = false;
	bool comp[MAX_TAM];
	for (int j = 0; j < vector1.tam; j++) {
		comp[j] = false;
	}
	for (int i = 0; i < vector1.tam; i++) {
		if (abs(1 - (vector2.vector[i] / vector1.vector[i])) < MIN) {
			comp[i] = true;
		}
	}
	int i = 0;
	while (i < vector1.tam && !termina) {
		if (comp[i] == false) {
			termina = true;
		}
		i++;
	}
	return !termina;
}

tMatriz hacerPrima(const tMatriz &matrix) {
	tMatriz MPrima;
	int suma[MAX_TAM];

	MPrima.dim = matrix.dim;

	for (int j = 0; j < matrix.dim; j++) {
		suma[j] = 0;
		for (int i = 0; i < matrix.dim; i++) {
			suma[j] += matrix.matriz[i][j];
		}
	}

	for (int j = 0; j < matrix.dim; j++) {
		for (int i = 0; i < matrix.dim; i++) {
			if (matrix.matriz[i][j] == 1)
				MPrima.matriz[i][j] = 1 / (double(suma[j]));
			else if (suma[j] != 0)
				MPrima.matriz[i][j] = 0;
			else
				MPrima.matriz[i][j] = 1 / (double(matrix.dim));
		}
	}
	//imprimir(MPrima);
	return MPrima;
}

void inicElems(tMatriz & matrix, int val) {
	for (int i = 0; i <= matrix.dim; i++){
		for (int j = 0; j <= matrix.dim; j++){
			if (matrix.matriz[i][j] != 1.0 && matrix.matriz[i][j] != 0.0){
				matrix.matriz[i][j] = 0;
			}
		}
	}
	matrix.dim++;
}

void imprimir(const tMatriz & matrix) {
	cout << endl << endl;
	for (int i = 0; i < matrix.dim; i++) {
		for (int j = 0; j < matrix.dim; j++) {
			cout << setw(25) << matrix.matriz[i][j];
		}
		cout << endl;
	}

}

void imprimirVector(const tVector &vector) {
	cout << endl << endl;
	for (int i = 0; i < vector.tam; i++) {
		cout << setw(25) << vector.vector[i];
		cout << endl;
	}

}

tMatriz matrizConstante(double x, int n) {
	tMatriz matrix;
	matrix.dim = n;
	for (int i = 0; i < matrix.dim; i++) {
		for (int j = 0; j < matrix.dim; j++) {
			matrix.matriz[i][j] = x;
		}
	}
	return matrix;
}

tVector operator*(const tMatriz & m, const tVector & v) {
	tVector mult;
	double suma = 0;
	mult.tam = v.tam;
	for (int i = 0; i < m.dim; i++) {
		for (int j = 0; j < m.dim; j++) {
			suma += m.matriz[i][j] * v.vector[j];
		}
		mult.vector[i] = suma;
		suma = 0;
	}
	return mult;
}

tMatriz operator*(const tMatriz & m, double x) {
	tMatriz matMul;
	matMul.dim = m.dim;
	for (int i = 0; i < m.dim; i++) {
		for (int j = 0; j < m.dim; j++) {
			matMul.matriz[i][j] = m.matriz[i][j] * x;
		}
	}
	return matMul;
}

tMatriz operator+(const tMatriz & m1, const tMatriz & m2) {
	tMatriz matSum;
	matSum.dim = m1.dim;
	for (int i = 0; i < m1.dim; i++) {
		for (int j = 0; j < m1.dim; j++) {
			matSum.matriz[i][j] = m1.matriz[i][j] + m2.matriz[i][j];
		}
	}
	return matSum;
}