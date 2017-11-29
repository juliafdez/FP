/*
PRACTICA 2 - GRÚAS Y EXCAVADORAS
Julia Fernández Reyes
Miguel Pérez de la Rubia
Fundamentos de la Programación 1ºE
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

const int CENTINELA = -1;
const int MAX_PROD = 25;
const int PROD_NULO = 0;
typedef int tArray[MAX_PROD];

//FUNCIONES VERSION 1
//MENU

//Muestra las opciones del menú
int menu();
//depende del valor introducido, ejecuta la funcion correspondiente
void ejecutarOpc(int opc, tArray fila, int &tam, bool &end, int &movimientos);
//Abre el archivo y llama a mostrar
void ejecutarGuardarFichero(const tArray fila, int tam);
//Guarda la fila final reenombrando el fichero
void ejecutarLeerFichero(tArray fila, int &tam);
//Pide las posiciones y donde soltarlas, si se realiza el movimiento, te dice el numero de movimientos que llevas y si está ordenada
void ejecutarGrua(tArray fila, int tam, int &movimientos);
//Hace lo mismo que la función anterior pero con la excavadora
void ejecutarExcavadora(tArray fila, int tam, int &movimientos);

// FILAS

//Funcion para mostrar la fila como pide en el enunciado
void mostrarFila(const tArray fila, int tam);
//Depende de la posicion que entre por parametro, y devuelve si es valida
bool esPosValida(int tam, int pos);
//Devueve si la casilla de la posicion que entra por parámetro está vacia
bool estaVacia(const tArray fila, int pos);

//FICHEROS

//Lee la fila del archivo
void LeerFilaFich(ifstream &fich, tArray fila, int &tam);
//Escribe la fila del archivo introducido por parámetro
void EscribirFilaFich(ofstream &fich, const tArray fila, int tam);

//GRUA

//Te devuelve si es posible hacer el movimiento de la grua
bool sonPosicionesPosiblesGrua(int tam, int posIni, int posFin, int posSoltar);
//Te dice si en todas lasposiciones introducidas son validas
bool esPosibleGrua(const tArray fila, int tam, int posIni, int posFin, int posSoltar);
//Si es posible realizar el movimiento, lo realiza guardando los valores en un array auxiliar y luego soltándolos en la posición elegida 
bool grua(tArray fila, int tam, int posIni, int posFin, int posSoltar);

//EXCAVADORA

//Mueve las posiciones de los valores dependiendo de los valores introducidos
bool excavadora(tArray fila, int tam, int posIni, int numDespla, int direccion);
//
int posHuecoLibreDir(const tArray fila, int tam, int posIni, int direccion);
//Realiza un movimiento de la excavadora
bool excavadora1dir(tArray fila, int tam, int posIni, int direccion);

//ORDENADO

//Te devuelve si la fila está ordenada
bool filaOrdenada(const tArray fila, int tam);

//AUXILIARES

//Dadas las posiciones inicial, final y soltar, te dice si es posible realizar el movimiento de la grua
bool posicionesVacias(const tArray fila, int posIni, int posFin, int posSoltar);
//Funcion para que al meter un valor incorrecto o una letra en vez de un numero, te vuelva a pedir uno correcto
int comp_int();


int main() {
	int tam = 0, opcion = 0, movimientos = 0;
	tArray fila;
	bool end = false;
	do {
		opcion = menu();
		ejecutarOpc(opcion, fila, tam, end, movimientos);
	} while (!end);

	system("pause");
	return 0;
}

//MENU

int menu(){
	int op;
	cout << "GRUAS Y EXCAVADORAS\n\n";
	do {
		cout << "***************************************\n\n";
		cout << "1. - Cargar fila de fichero" << endl;
		cout << "2. - Guardar fila en fichero" << endl;
		cout << "3. - Usar grua" << endl;
		cout << "4. - Usar escavadora" << endl;
		cout << "0. - Salir \n";
		cout << "Introduce una opcion: ";
		op = comp_int();
		cout << "\n";
	} while (op < 0 || op > 4);
	return op;
}

void ejecutarOpc(int opc, tArray fila, int &tam, bool &end, int &movimientos) {
	switch (opc) {
	case 1: ejecutarLeerFichero(fila, tam); break;
	case 2: ejecutarGuardarFichero(fila, tam); break;
	case 3: ejecutarGrua(fila, tam, movimientos); break;
	case 4: ejecutarExcavadora(fila, tam, movimientos); break;
	case 0: end = true; break;
	}
}

void ejecutarLeerFichero(tArray fila, int &tam) {
	string arch;
	ifstream lectura;

	cout << "Introduce un nombre para buscar el archivo: ";
	cin >> arch;
	arch = arch + ".txt";
	lectura.open(arch);
	if (lectura.is_open()) {
		LeerFilaFich(lectura, fila, tam);
		lectura.close();
		cout << "\nArchivo abierto correctamente \n\n";
		system("PAUSE");
		system("cls");
		cout << "GRUAS Y EXCAVADORAS\n\n";
		mostrarFila(fila, tam);
	}
	else cout << "No se ha podido abrir el archivo \n\n";
}

void ejecutarGuardarFichero(const tArray fila, int tam) {
	string arch;
	ofstream escritura;
	cout << "Introduce un nombre para guardar el archivo: ";
	cin >> arch;
	arch = arch + ".txt";
	escritura.open(arch);
	if (escritura.is_open()) {
		EscribirFilaFich(escritura, fila, tam);
		cout << "Archivo guardado correctamente \n\n";
	}
	else cout << "No se ha podido guardar el archivo \n\n";
}

void ejecutarGrua(tArray fila, int tam, int &movimientos) {
	int posIni, posFin, posSoltar;
	//system("PAUSE");
	system("cls");
	cout << "GRUAS Y EXCAVADORAS\n\n";
	cout << "GRUA\n\n";
	mostrarFila(fila, tam);
	do {
		cout << "Introduzca posicion inicial: ";
		posIni = comp_int();
	} while (posIni < 0 || posIni > tam - 1);
	do {
		cout << "Introduzca posicion final: ";
		posFin = comp_int();
	} while (posFin < 0 || posFin > tam - 1);
	do {
		cout << "Introduzca posicion soltar(entre 0 y " << tam - 1 << "): ";
		posSoltar = comp_int();
	} while (posSoltar < 0 || posSoltar > tam - 1);

	if (grua(fila, tam, posIni, posFin, posSoltar)) {
		cout << "\n";
		mostrarFila(fila, tam);
		cout << "Grua movida\n";
		movimientos++;
		if (!filaOrdenada(fila, tam)) {
			cout << "Fila no ordenada\n";
			cout << "Numero de movimientos realizados: " << movimientos << "\n\n";
		}
		else if (tam > 0) {
			cout << "ENHORABUENA, HAS ORDENADO LA FILA\n";
			cout << "Numero de movimientos realizados: " << movimientos << "\n\n";
		}
	}
	else {
		cout << "Grua no movida\n";
		if (!filaOrdenada(fila, tam)) {
			cout << "Fila no ordenada\n";
			cout << "Numero de movimientos realizados: " << movimientos << "\n\n";
		}
		else if (tam > 0) {
			cout << "ENHORABUENA, HAS ORDENADO LA FILA\n";
			cout << "Numero de movimientos realizados: " << movimientos << "\n\n";
		}
	}
}

void ejecutarExcavadora(tArray fila, int tam, int &movimientos) {
	int posIni = 0, numDespl = 0, direccion = 0;

	//system("PAUSE");
	system("cls");
	cout << "GRUAS Y EXCAVADORAS\n\n";
	cout << "EXCAVADORA\n\n";
	mostrarFila(fila, tam);
	do {
		cout << "Introduzca posicion inicial: ";
		posIni = comp_int();;
	} while (posIni < 0 || posIni > tam - 1);
	cout << "Introduzca numero de desplazamientos: ";
	numDespl = comp_int();;
	do {
		cout << "introduce la direccion(0 izquierda/ 1 derecha): ";
		direccion = comp_int();;
		if (direccion == 0) direccion = -1;
	} while (direccion != -1 && direccion != 1);

	if (excavadora(fila, tam, posIni, numDespl, direccion)) {
		cout << "\n";
		mostrarFila(fila, tam);
		cout << "Excavadora movida\n";
		movimientos++;
		if (!filaOrdenada(fila, tam)) {
			cout << "Fila no ordenada\n";
			cout << "Numero de movimientos realizados: " << movimientos << "\n\n";
		}
		else if (tam > 0) {
			cout << "ENHORABUENA, HAS ORDENADO LA FILA\n";
			cout << "Numero de movimientos realizados: " << movimientos << "\n\n";
		}
	}
	else {
		cout << "Excavadora no movida \n";
		if (!filaOrdenada(fila, tam)) {
			cout << "Fila no ordenada\n";
			cout << "Numero de movimientos realizados: " << movimientos << "\n\n";
		}
		else if (tam > 0) {
			cout << "ENHORABUENA, HAS ORDENADO LA FILA\n";
			cout << "Numero de movimientos realizados: " << movimientos << "\n\n";
		}
	}
}

//FILAS

void mostrarFila(const tArray fila, int tam) {
	for (int i = 0; i < tam; i++) {
		if (fila[i] != 0)
			cout << "|" << setw(3) << fila[i];
		else {
			cout << "|" << setw(3) << "";
		}
	}
	cout << "|\n-";
	for (int i = 0; i < tam; i++) {
		cout << "----";
	}cout << endl;
	for (int i = 0; i < tam; i++) {
		cout << "|" << setw(3) << i;
	}
	cout << "|" << endl;
	cout << "\n";
}

bool esPosValida(int tam, int pos) {
	bool valida = true;
	if (pos = 0 || pos >= tam) {
		valida = false;
	}
	return valida;
}

bool estaVacia(const tArray fila, int pos) {
	bool vacia = false;
	if (fila[pos] == PROD_NULO) {
		vacia = true;
	}
	return vacia;
}

//FICHERO

void LeerFilaFich(ifstream &fich, tArray fila, int &tam) {
	int num = 0;
	tam = 0;
	fich >> num;
	while (num != CENTINELA && tam < MAX_PROD) {
		fila[tam] = num;
		tam++;
		fich >> num;
	}
}

void EscribirFilaFich(ofstream &fich, const tArray fila, int tam) {
	int num = 0, i = 0;
	char espace = ' ';
	while (i < tam) {
		num = fila[i];
		fich << num;
		fich << espace;
		i++;
	}
	fich.close();
}


//GRUA

bool esPosibleGrua(const tArray fila, int tam, int posIni, int posFin, int posSoltar) {
	bool posibGrua = true;
	bool sonPosibles = sonPosicionesPosiblesGrua(tam, posIni, posFin, posSoltar);
	bool vacia = posicionesVacias(fila, posIni, posFin, posSoltar);

	if (!sonPosibles || !vacia)
		posibGrua = false;

	return posibGrua;
}

bool grua(tArray fila, int tam, int posIni, int posFin, int posSoltar) {
	bool GruaMovida = true;
	tArray aux;
	int posSoltarFin = posSoltar + (posFin - posIni);

	if (esPosibleGrua(fila, tam, posIni, posFin, posSoltar)) {
		int j = 0;
		for (int i = posIni; i <= posFin; i++) {
			aux[j] = fila[i];
			fila[i] = PROD_NULO;
			j++;
		}
		j = 0;
		for (int i = posSoltar; i <= posSoltarFin; i++) {
			if (!estaVacia(aux, j)) {
				fila[i] = aux[j];
				j++;
			}
			else j++;
		}
	}
	else {
		cout << "Movimiento no valido\n";
		GruaMovida = false;
	}
	return GruaMovida;
}

bool sonPosicionesPosiblesGrua(int tam, int posIni, int posFin, int posSoltar) {
	bool esPosible = false;
	int posSoltarFin = posSoltar + (posFin - posIni);

	if (posIni <= posFin) {
		if (posSoltarFin < tam){
			if (esPosValida(tam, posIni)) {
				if (esPosValida(tam, posFin)) {
					if (esPosValida(tam, posSoltar)) {
						if (esPosValida(tam, posSoltarFin))
							esPosible = true;
					}
				}
			}
		}
	}
	return esPosible;
}


//EXCAVADORA

int posHuecoLibreDir(const tArray fila, int tam, int posIni, int direccion) {
	int i = posIni, huecoLibre = 0;
	bool ocupado = true;

	do {
		if (!estaVacia(fila, i)) {
			if (direccion == 1)
				i++;
			else if (direccion == -1)
				i--;
		}
		else {
			huecoLibre = i;
			ocupado = false;
		}
	} while (ocupado && ((i < tam && direccion == 1) || (i > 0 && direccion == -1)));

	if (ocupado)
		huecoLibre = tam;

	return huecoLibre;
}

bool excavadora1dir(tArray fila, int tam, int posIni, int direccion) {
	bool excava = true;
	int libre = 0;

	libre = posHuecoLibreDir(fila, tam, posIni, direccion);
	if (libre != tam) {
		if (direccion == 1) {
			for (int i = libre; i >= posIni; i--) {
				if (i != posIni)
					fila[i] = fila[i - 1];
				else
					fila[posIni] = PROD_NULO;
			}
		}
		if (direccion == -1) {
			for (int i = libre; i <= posIni; i++) {
				if (i != posIni)
					fila[i] = fila[i + 1];
				else
					fila[posIni] = PROD_NULO;
			}
		}
	}
	else excava = false;

	return excava;
}

bool excavadora(tArray fila, int tam, int posIni, int numDespla, int direccion){
	bool excava = false;
	int libre = 0, despl = numDespla, posIniAux = posIni;
	if (posIni < tam) {
		for (int i = numDespla; i > 0; i--) {
			if (excavadora1dir(fila, tam, posIniAux, direccion)) {
				excava = true;
				if (direccion == 1)
					posIniAux++;
				else if (direccion == -1)
					posIniAux--;
			}
		}
	}
	else excava = false;

	return excava;
}

//ORDENADO

bool filaOrdenada(const tArray fila, int tam) {
	bool ordenado = true;
	int i = 0;

	while (i < tam && ordenado)  {
		if (estaVacia(fila, i))
			i++;
		if (fila[i - 1]>fila[i])
			ordenado = false;
		i++;
	}
	return ordenado;
}

//AUXILIARES

bool posicionesVacias(const tArray fila, int posIni, int posFin, int posSoltar) {
	bool vacia = false, mueve = false;
	int posSoltarFin = posSoltar + posFin - posIni;
	int soltar = posSoltar, inicio = posIni;

	if (soltar <= posFin && !estaVacia(fila, soltar) && inicio < soltar)
		vacia = true;
	else if (estaVacia(fila, soltar))
		vacia = true;

	while (soltar <= posSoltarFin && vacia && inicio <= posFin) {
		if (estaVacia(fila, soltar) || estaVacia(fila, inicio)) {
			mueve = true;
		}
		else if (soltar <= posFin && inicio < soltar) {
			mueve = true;
		}
		else
			mueve = false;
		soltar++;
		inicio++;
	}

	return mueve;
}

int comp_int() {
	int num;
	cin >> num;
	while (!cin) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "No es un caracter valido. Introduzca un numero entero: ";
		cin.sync();
		cin >> num;
	}
	cin.clear();
	cin.ignore(10000, '\n');
	return num;
}