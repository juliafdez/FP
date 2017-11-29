/*
Práctica 3 - Sokoban
Julia Fernández Reyes
Miguel Pérez de la Rubia
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <Windows.h>
#include <sstream>
#include <conio.h>

using namespace std;

const int MAXC = 50;
const int MAXH = 10;
const int MAXP = 100;

typedef enum tCasilla { Libre, Muro, DestinoL, DestinoC, DestinoJ, Jugador, Caja };
typedef tCasilla tTablero[MAXC][MAXC];

typedef struct {
	tTablero tablero;
	int nFilas;
	int nColumnas;
	int fila_jug;
	int col_jug;
	int num_cajas;
	int num_cajas_correct;
}tSokoban;

typedef  tSokoban tArraySokoban[MAXH];

typedef struct {
	tArraySokoban vectorSoko;
	int cont;
}tHistoria;

typedef struct {
	tSokoban sokoban;
	int nivel;
	int movs;
	string filename;
	tHistoria historia;
}tJuego;

typedef enum tTecla { ARRIBA, ABAJO, IZQUIERDA, DERECHA, SALIR, NADA, DESHACER };

typedef struct {
	string fichero;//juego.filemane
	int nivel;//juego.nivel
	int movimientos;//juego.movs
}tPartida;

typedef tPartida tExitos[MAXP];

typedef struct {
	string nombreJugador;
	tExitos partidasFin;
	int contPart = 0;
}tInfo;

int menu();//Muestra las opciones del menu
bool cargarJuego(tJuego &juego);//Carga el archivo de levels
bool cargarNivel(tSokoban &sokoban, ifstream &lectura, int nivel);//Carga el nivel introducido por el usuario
bool cargarTablero(tSokoban &sokoban, ifstream &lectura);//Carga el tablero del nivel elegido
void dibujar(const tJuego &juego);//Dibujamos el tablero del nivel elegido
void dibujarCasilla(tCasilla casilla);//Dibujamos las casillas
void colorFondo(int color);
tCasilla char2casilla(char char_aux);
void inicializa(tJuego &juego);
void hacerMovimiento(tJuego &juego, tTecla tecla, int &ind);
tTecla leerTecla();
void liberaPosicion(tJuego &juego, int filaFin, int colFin);
bool cajasCorrectas(tJuego &juego);
bool bloqueado(const tJuego &juego);
bool deshacerMovimiento(tJuego &juego);
void guardarAnterior(tJuego &juego);
int comp_int();
bool pideJugador(tInfo &info);
bool guardaInfo(tInfo &info, tJuego &juego);
void cargarInfo(tInfo &info, ifstream &lectura);
bool operator==(tPartida partida1, tPartida partida2);
bool operator<(tPartida partida1, tPartida partida2);
void insertar(tInfo &info, tPartida partida, int pos);
bool buscarBinaria(const tInfo &info, tPartida buscada, int &pos);
void mostrarDatos(const tInfo &info);



int main() {
	tJuego juego;
	tCasilla casilla = Libre;
	tTecla tecla = NADA;
	tInfo infoJugador;
	string aux;
	char auxi = ' ';
	bool end = false;
	int op = -1, maxMovDes = 0, ind = 0;

	pideJugador(infoJugador);
	//op = menu();
	while (op != 0) {
		system("pause");
		system("cls");
		op = menu();
		end = false;
		switch (op) {
		case 1:
			inicializa(juego);
			while (!end)
				if (cargarJuego(juego)) {
					dibujar(juego);
					while (!end) {
						tecla = leerTecla();
						if (tecla != SALIR) {
							if (tecla == DESHACER && maxMovDes != 0) {
								deshacerMovimiento(juego);
								maxMovDes--;//para que no pueda deshacer más de 10 veces

								dibujar(juego);
								cout << "puedes deshacer: " << maxMovDes << endl;
							}
							else {
								hacerMovimiento(juego, tecla, maxMovDes);
								dibujar(juego);
								if (maxMovDes > 10) maxMovDes = 10;
								cout << "puedes deshacer: " << maxMovDes << endl;
								if (bloqueado(juego))
									cout << "Estas bloquado.\n";
								if (cajasCorrectas(juego)) {
									cout << "****** HAS GANADO!!******\n";
									guardaInfo(infoJugador, juego);

									end = true;
								}
							}
						}
						else end = true;
					}
				}
			break;
		case 2: mostrarDatos(infoJugador);
		case 0: cout << "nos vemos pronto\n"; break;
		}
	}
	system("PAUSE");
	return 0;
}


int menu() {
	int opcion;
	do {
		cout << " 1.- Jugar partida \n 2.- Mostrar datos del jugador\n 0.- Salir\n Introduce la opcion: ";
		opcion = comp_int();
	} while (opcion < 0 || opcion > 2);
	return opcion;
}

void inicializa(tJuego &juego) {//Inicializamos el tablero
	juego.movs = 0;
	for (int i = 0; i < MAXC; i++) {
		for (int j = 0; j < MAXC; j++) {
			juego.sokoban.tablero[i][j] = Libre;
		}
	}
	juego.sokoban.nColumnas = 0;
	juego.sokoban.nFilas = 0;
	juego.sokoban.num_cajas_correct = 0;
	juego.sokoban.num_cajas = 0;
	juego.historia.cont = 0;
}

bool cargarJuego(tJuego &juego) {//Introducimos el nombre del fichero que queremos cargar y el nivel y llamamos a cargar nivel
	bool ok = false;
	ifstream lectura;
	ofstream escritura;

	cout << "Introduce el nombre del fichero que quieres jugar: ";
	cin >> juego.filename;

	juego.filename += ".txt";

	lectura.open(juego.filename);
	if (lectura.is_open()) {
		cout << "Introduce el nivel que quieres jugar: ";
		juego.nivel = comp_int();

		ok = cargarNivel(juego.sokoban, lectura, juego.nivel);

		lectura.close();
	}
	else { cout << "Error al cargar\n"; }

	return ok;
}

bool cargarNivel(tSokoban &sokoban, ifstream &lectura, int nivel) {//Decimos a que nivel queremos acceder y llamamos a cargar tablero
	bool ok = false;
	string nivel_cad = "Level ";
	string aux_nivel;
	ostringstream convert;

	convert << nivel;
	nivel_cad = nivel_cad + convert.str();

	do {
		getline(lectura, aux_nivel);
		if (aux_nivel == nivel_cad) {
			ok = cargarTablero(sokoban, lectura);
		}
	} while (aux_nivel != nivel_cad && !lectura.eof() && !ok);

	return ok;
}

bool cargarTablero(tSokoban &sokoban, ifstream &lectura) {//Cargamos el tablero del nivel que introducimos
	char char_aux;
	bool carga = false, fin = false;
	int i, j;


	i = 0; j = 0;
	char_aux = lectura.get();
	do {
		do {
			if (!lectura.eof()) {
				if (char_aux != '\n') {
					if (char_aux != ' ') {
						sokoban.tablero[i][j] = char2casilla(char_aux);
						if (sokoban.tablero[i][j] == Caja) {
							sokoban.num_cajas++;
						}
						else if (sokoban.tablero[i][j] == Jugador) {
							sokoban.col_jug = j;
							sokoban.fila_jug = i;
						}
					}j++;
				}
			}
			char_aux = lectura.get();
		} while (j < MAXC && char_aux != '\n' && !lectura.eof());
		if (j > sokoban.nColumnas) sokoban.nColumnas = j;
		j = 0;
		i++;
		char_aux = lectura.get();
		if (char_aux == '\n' || lectura.eof()) {
			fin = true;
			carga = true;
		}
	} while (i < MAXC && !lectura.eof() && !fin);
	sokoban.nFilas = i;
	if (carga) {
		cout << "nivel encontrado \n";
	}
	return carga;
}

tCasilla char2casilla(char char_aux) {//Decimos a que equivale cada simbolo
	tCasilla casilla = Libre;
	switch (char_aux) {
	case ' ':
		casilla = Libre; break;
	case '#':
		casilla = Muro; break;
	case '.':
		casilla = DestinoL; break;
	case '*':
		casilla = DestinoC; break;
	case '+':
		casilla = DestinoJ; break;
	case '$':
		casilla = Caja; break;
	case '@':
		casilla = Jugador; break;
	}
	return casilla;
}

void dibujar(const tJuego &juego) {//se dibuja el tablero
	tCasilla casilla;
	int var = 0;

	system("CLS");
	cout << "Nombre del fichero: " << juego.filename << "  Nivel: " << juego.nivel << endl;
	for (int i = 0; i < juego.sokoban.nFilas; i++) {
		for (int j = 0; j < juego.sokoban.nColumnas; j++) {
			casilla = juego.sokoban.tablero[i][j];
			dibujarCasilla(casilla);//Vamos dibujando casilla a casilla
		}
		cout << endl;
	}
	cout << "Numero de movimientos realizados: " << juego.movs << endl;
}

void dibujarCasilla(tCasilla casilla) {//Dibujamos cada simbolo
	switch (casilla) {
	case Libre:
		colorFondo(1);
		cout << "  "; break;
	case Muro:
		colorFondo(2);
		cout << "  "; break;
	case DestinoL:
		colorFondo(12);
		cout << ".."; break;
	case DestinoC:
		colorFondo(13);
		cout << "{}"; break;
	case DestinoJ:
		colorFondo(6);
		cout << "00"; break;
	case Jugador:
		colorFondo(5);
		cout << "00"; break;
	case Caja:
		colorFondo(8);
		cout << "()"; break;
	}
	colorFondo(0);
}

void colorFondo(int color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (color << 4));
}

tTecla leerTecla() {//Decimos que tecla equivale a cada movimiento
	int dir = 0;
	tTecla tecla = NADA;

	cin.sync();
	dir = _getch();
	if (dir == 0xe0) {
		dir = _getch();
	}
	switch (dir) {
	case 27: tecla = SALIR; break;
	case 72: tecla = ARRIBA; break;
	case 80: tecla = ABAJO; break;
	case 77: tecla = DERECHA; break;
	case 75: tecla = IZQUIERDA; break;
	case 100: tecla = DESHACER; break;
	case 68: tecla = DESHACER; break;
	default: tecla = NADA; break;
	}
	return tecla;
}

void hacerMovimiento(tJuego &juego, tTecla tecla, int &ind) {
	int fDestino = 0, cDestino = 0, filaCaja = 0, colCaja = 0;
	bool mover = true;

	switch (tecla) {//movemos en la direccion que introducimos
	case ARRIBA:
		fDestino = juego.sokoban.fila_jug - 1;
		cDestino = juego.sokoban.col_jug;
		filaCaja = juego.sokoban.fila_jug - 2;
		colCaja = juego.sokoban.col_jug;
		break;
	case ABAJO:
		fDestino = juego.sokoban.fila_jug + 1;
		cDestino = juego.sokoban.col_jug;
		filaCaja = juego.sokoban.fila_jug + 2;
		colCaja = juego.sokoban.col_jug;
		break;
	case DERECHA:
		fDestino = juego.sokoban.fila_jug;
		cDestino = juego.sokoban.col_jug + 1;
		filaCaja = juego.sokoban.fila_jug;
		colCaja = juego.sokoban.col_jug + 2;
		break;
	case IZQUIERDA:
		fDestino = juego.sokoban.fila_jug;
		cDestino = juego.sokoban.col_jug - 1;
		filaCaja = juego.sokoban.fila_jug;
		colCaja = juego.sokoban.col_jug - 2;
		break;
	case DESHACER:
		mover = false;
		break;
	case SALIR: mover = false;
		break;
	}

	if (mover == true) {
		switch (juego.sokoban.tablero[fDestino][cDestino]) {
		case Muro: mover = false; break;//si donde queremos mover hay muero, mover = false

		case Libre:
			guardarAnterior(juego);//Se guardan los movimientos en el array
			juego.sokoban.tablero[fDestino][cDestino] = Jugador;
			liberaPosicion(juego, fDestino, cDestino);//libera la posicion donde estaba antes el jugador
			ind++;
			juego.movs++;
			break;

		case DestinoL:
			guardarAnterior(juego);
			juego.sokoban.tablero[fDestino][cDestino] = DestinoJ;
			liberaPosicion(juego, fDestino, cDestino);
			ind++;
			juego.movs++;
			break;

		case Caja:

			if (juego.sokoban.tablero[filaCaja][colCaja] != Muro && juego.sokoban.tablero[filaCaja][colCaja] != DestinoC && juego.sokoban.tablero[filaCaja][colCaja] != Caja) {
				guardarAnterior(juego);
				if (juego.sokoban.tablero[filaCaja][colCaja] == Libre) {
					juego.sokoban.tablero[filaCaja][colCaja] = Caja;
					juego.sokoban.tablero[fDestino][cDestino] = Jugador;
				}
				else if (juego.sokoban.tablero[filaCaja][colCaja] == DestinoL) {
					juego.sokoban.tablero[filaCaja][colCaja] = DestinoC;
					juego.sokoban.tablero[fDestino][cDestino] = Jugador;
				}
				liberaPosicion(juego, fDestino, cDestino);
				ind++;
				juego.movs++;
			}

			break;

		case DestinoC:

			if (juego.sokoban.tablero[filaCaja][colCaja] != Muro && juego.sokoban.tablero[filaCaja][colCaja] != DestinoC && juego.sokoban.tablero[filaCaja][colCaja] != Caja) {
				guardarAnterior(juego);
				if (juego.sokoban.tablero[filaCaja][colCaja] == Libre) {
					juego.sokoban.tablero[filaCaja][colCaja] = Caja;
					juego.sokoban.tablero[fDestino][cDestino] = DestinoJ;
				}
				else if (juego.sokoban.tablero[filaCaja][colCaja] == DestinoL) {
					juego.sokoban.tablero[filaCaja][colCaja] = DestinoC;
					juego.sokoban.tablero[fDestino][cDestino] = DestinoJ;
				}
				liberaPosicion(juego, fDestino, cDestino);
				ind++;
				juego.movs++;
			}
			break;
		}
	}
	//dibujar(juego);
}

void liberaPosicion(tJuego &juego, int filaFin, int colFin) {//Se libera la posicion de tablero donde estaba el jugador
	if (juego.sokoban.tablero[juego.sokoban.fila_jug][juego.sokoban.col_jug] == Jugador) {
		juego.sokoban.tablero[juego.sokoban.fila_jug][juego.sokoban.col_jug] = Libre;
	}
	else if (juego.sokoban.tablero[juego.sokoban.fila_jug][juego.sokoban.col_jug] == DestinoJ) {
		juego.sokoban.tablero[juego.sokoban.fila_jug][juego.sokoban.col_jug] = DestinoL;
	}
	juego.sokoban.fila_jug = filaFin;
	juego.sokoban.col_jug = colFin;
}

bool cajasCorrectas(tJuego &juego) {//Dice cuando estan las cajas en su posicion final
	bool correct = false;
	int i = 0, j = 0;
	juego.sokoban.num_cajas_correct = 0;
	for (i = 0; i < juego.sokoban.nFilas; i++) {
		for (j = 0; j < juego.sokoban.nColumnas; j++) {
			if (juego.sokoban.tablero[i][j] == DestinoC)
				juego.sokoban.num_cajas_correct++;//Sumamos uno a cajas correctas
		}
	}
	if (juego.sokoban.num_cajas_correct == juego.sokoban.num_cajas)
		correct = true;

	return correct;
}

bool bloqueado(const tJuego &juego) {//lo usamos para bloquear el juego
	bool bloq = false;
	int i = 0, j = 0;

	while (i < juego.sokoban.nFilas && !bloq) {
		while (j < juego.sokoban.nColumnas && !bloq) {
			if (juego.sokoban.tablero[i][j] == Caja) {//encuentro la caja
				if ((juego.sokoban.tablero[i - 1][j] == Muro || juego.sokoban.tablero[i + 1][j] == Muro)) {// si arriba o abajo hay muro 
					if (juego.sokoban.tablero[i][j + 1] == Caja) {// y a la derecha hay una caja
						if (juego.sokoban.tablero[i - 1][j + 1] == Muro || juego.sokoban.tablero[i + 1][j + 1] == Muro) {//y esa caja tiene muro arriba o abajo
							bloq = true;//esta bloqueado
						}
					}
					else if ((juego.sokoban.tablero[i][j + 1] == Muro) || (juego.sokoban.tablero[i][j - 1] == Muro)) {//si no tiene una caja, pero si muro a la derecha o izquierda
						bloq = true;//esta bloqueado
					}
				}
				else if ((juego.sokoban.tablero[i][j + 1] == Muro || juego.sokoban.tablero[i][j - 1] == Muro)) {// si el muro esta a la derecha o la izquierda
					if (juego.sokoban.tablero[i + 1][j] == Caja) {//y abajo hay una caja
						if (juego.sokoban.tablero[i + 1][j - 1] == Muro || juego.sokoban.tablero[i + 1][j + 1] == Muro) {//y esa caja tiene muros a la izquierda o la derecha
							bloq = true;//esta bloqueado
						}
					}
					else if ((juego.sokoban.tablero[i + 1][j] == Muro) || (juego.sokoban.tablero[i - 1][j] == Muro)) {//si no tiene una caja, pero si muro abajo o arriba
						bloq = true;//esta bloqueado
					}
				}
				else if ((juego.sokoban.tablero[i][j + 1] == Caja) && (juego.sokoban.tablero[i - 1][j + 1] == Caja) && (juego.sokoban.tablero[i - 1][j] == Caja)) {//si las cajas estan en cuadrado
					bloq = true;//esta bloqueado
				}
			}
			j++;
		}
		i++; j = 0;
	}
	return bloq;
}

void guardarAnterior(tJuego &juego) {

	//si haces juego.historia.cont%10 lo que hace es coger el resto de la division entre 10
	//que va de 0 a 9, y asi te aseguras de no salirte del vector
	//P.E  juego.historia.cont = 12.  juego.historia.cont % 10 = 2 
	// 0 1  2  3  4   5  6  7  8  9
	//10 11 12 13 14 15 16 17 18 19
	juego.historia.vectorSoko[juego.historia.cont % 10].col_jug = juego.sokoban.col_jug;
	juego.historia.vectorSoko[juego.historia.cont % 10].fila_jug = juego.sokoban.fila_jug;
	juego.historia.vectorSoko[juego.historia.cont % 10].nFilas = juego.sokoban.nFilas;
	juego.historia.vectorSoko[juego.historia.cont % 10].nColumnas = juego.sokoban.nColumnas;
	juego.historia.vectorSoko[juego.historia.cont % 10].num_cajas = juego.sokoban.num_cajas;
	juego.historia.vectorSoko[juego.historia.cont % 10].num_cajas_correct = juego.sokoban.num_cajas_correct;

	for (int i = 0; i < juego.sokoban.nFilas; i++) {
		for (int j = 0; j < juego.sokoban.nColumnas; j++) {
			juego.historia.vectorSoko[juego.historia.cont % 10].tablero[i][j] = juego.sokoban.tablero[i][j];
		}
	}
	juego.historia.cont++;
}

bool deshacerMovimiento(tJuego &juego) {
	bool deshacer = false;
	int ind = 0;
	if (juego.historia.cont > 0)
		deshacer = true;
	if (deshacer) {
		ind = (juego.historia.cont - 1) % 10;

		for (int i = 0; i < juego.historia.vectorSoko[ind].nFilas; i++) {
			for (int j = 0; j < juego.historia.vectorSoko[ind].nColumnas; j++) {
				juego.sokoban.tablero[i][j] = juego.historia.vectorSoko[ind].tablero[i][j];//deshacemos movimiento volviendo al mov anterior
			}
		}
		//ponemos todos los datos como el movimiento anterior
		juego.sokoban.fila_jug = juego.historia.vectorSoko[ind].fila_jug;
		juego.sokoban.nFilas = juego.historia.vectorSoko[ind].nFilas;
		juego.sokoban.nColumnas = juego.historia.vectorSoko[ind].nColumnas;
		juego.sokoban.col_jug = juego.historia.vectorSoko[ind].col_jug;
		juego.movs--;
		juego.historia.cont--;

	}

	return deshacer;
}

int comp_int() {//Funcion para que si metes una letra, no te deje sontinuar y te pida un numero entero
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

bool pideJugador(tInfo &info) {//Pedimos el nombre del jugador para acceder a su archivo con sus partidas
	bool correct = false;
	ifstream lectura;
	ofstream escritura;
	string nombre_aux, cadena_aux;
	info.contPart = 0;

	cout << "Introduce tu nombre: ";
	cin >> info.nombreJugador;

	nombre_aux = info.nombreJugador + ".txt";
	lectura.open(nombre_aux);
	if (lectura.is_open()) {
		cout << "Bienvenido de nuevo. \n";//Si ya tiene archivo creado anteriormente
		cargarInfo(info, lectura);
		correct = true;
	}
	else {
		escritura.open(nombre_aux);
		if (escritura.is_open()) {
			cout << "Te damos la bienvenida \n";//Si es nueva la persona
			correct = true;
		}
	}

	return correct;
}

bool guardaInfo(tInfo &info, tJuego &juego) {//guarda la informacion de las partidas del jugador en la posicion adecuada
	bool guardado = false;
	ifstream lectura;
	ofstream escritura;
	string nombre_aux;
	int pos = 0;
	tPartida partida;

	partida.fichero = juego.filename;
	partida.movimientos = juego.movs;
	partida.nivel = juego.nivel;

	nombre_aux = info.nombreJugador + ".txt";
	escritura.open(nombre_aux);
	if (escritura.is_open()) {
		buscarBinaria(info, partida, pos);
		insertar(info, partida, pos);
		for (int i = 0; i < info.contPart; i++) {
			escritura << info.partidasFin[i].fichero << " " << info.partidasFin[i].nivel << " " << info.partidasFin[i].movimientos << endl;
		}
		guardado = true;
	}
	return guardado;
}

void cargarInfo(tInfo &info, ifstream &lectura) {//carga la informacion del archivo del usuario que metes
	string cadena_aux;
	lectura >> cadena_aux;
	while (!lectura.eof() && info.contPart < MAXP) {
		info.partidasFin[info.contPart].fichero = cadena_aux;
		lectura >> info.partidasFin[info.contPart].nivel;
		lectura >> info.partidasFin[info.contPart].movimientos;
		info.contPart++;
		lectura >> cadena_aux;
	}
}

bool buscarBinaria(const tInfo &info, tPartida buscada, int &pos) {//busqueda binaria mejorada
																   //Te devuelve la posicion donde deberian ir los datos a insertar en orden
	int ini = 0, fin = info.contPart - 1, mitad = 0;
	bool encontrado = false;
	while (ini <= fin && !encontrado) {
		mitad = (ini + fin) / 2;
		if (buscada < info.partidasFin[mitad]) {
			fin = mitad - 1;
		}
		else if (info.partidasFin[mitad] < buscada) {
			ini = mitad + 1;
		}
		else encontrado = true;
	}
	if (encontrado) pos = mitad;
	else pos = ini;

	return encontrado;
}

bool operator==(tPartida partida1, tPartida partida2) {
	bool igual = false;
	if (partida1.fichero == partida2.fichero && partida1.nivel == partida2.nivel) {
		igual = true;
	}
	return igual;
}

bool operator<(tPartida partida1, tPartida partida2) {
	bool menor = false;
	if (partida1.fichero < partida2.fichero)
		menor = true;
	else if (partida1.fichero == partida2.fichero) {
		if (partida1.nivel < partida2.nivel) {
			menor = true;
		}
	}
	return menor;
}

void insertar(tInfo &info, tPartida partida, int pos) {//Insertamos la partida en el archivo
	if (info.partidasFin[pos] == partida) {
		if (info.partidasFin[pos].movimientos > partida.movimientos) {
			info.partidasFin[pos].movimientos = partida.movimientos;
		}
	}
	else {
		for (int i = info.contPart; i > pos; i--) {
			info.partidasFin[i] = info.partidasFin[i - 1];
		}
		info.partidasFin[pos] = partida;
		info.contPart++;
	}
}

void mostrarDatos(const tInfo &info) {//Se muestran los datos recibiendo la informacion
	for (int i = 0; i < info.contPart; i++) {
		cout << setw(15) << left << info.partidasFin[i].fichero << setw(4) << right << info.partidasFin[i].nivel << setw(6) << right << info.partidasFin[i].movimientos << endl;
	}
}