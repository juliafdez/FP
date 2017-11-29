/*
PRACTICA 1 - FUNDAMENTOS DE LA PROGRAMACION
Julia Fernandez Reyes 70421020-B
Miguel Perez de la Rubia 53731995-J
*/

/*La parte opcional está hecha, solo que tiene algunos errores.*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// FUNCIONES VERSION 1

int solicitaAnyo();//te pide el año y lo introduces por pantalla
int solicitaMes();//te pide introducir un mes, y lo introduces por pantalla
int solicitaDia(int anyo, int mes);//dado un año y un mes, te solicita el dia, para ver si existe
bool esBisiesto(int anyo);//comprueba cuando un año es bisiesto
long int diasTranscurridos(int dia, int mes, int anyo);//calcula el numero de dias transcurridos del 1 de enero de 1900 hasta la fecha dada
long int diasAnyosCompletos(int anyo);//calcula el numero de dias desde el año 1900 hasta el introducido por pantalla
int diasEsteAnyo(int dia, int mes, int anyo); //calcula el numero de dias del año introducido
int contarBisiestos(int anyoInicio, int anyo);//cuenta el numero de años bisiestos desde 1900 hasta la fecha
int diaSemana(long int numDias);//devuelve el numero del dia de la semana que es(0, 1, ..)
string nombreDia(int representacionDia);//pasa, el numero de la funcion anterior al nombre de dia de la semana(Lunes, Martes, ..)
int diasMes(int mes, int anyo);//calcula los dias del mes que has introducido

//FUNCIONES VERSION 2
int fechaDada(int dia, int mes, int anyo);//devuelve un int con el dia de la semana que es
int primerDomingo(int anyo, int numDias);//Te devuelve el primer domingo de un año (introducido por pantalla)
int menu();//Menu de opciones
int domingosAnyo(int anyo);//Te calcula todos los domingos de un año (introducido por pantalla)
string nombreMes(int mes);//Devuelve el nombre del mes
string diaDeLaSemana(int dia, int mes, int anyo);//Devuelve el nombre del dia de la semana que es
bool puentes();

//FUNCIONES VERSION OPCIONAL
bool puentesMejorado();//Te lee del archivo fiestas.txt y ve cuales son los puentes (si el lunes anterior o el viernes siguiente no son fiesta)
void puenteLM(string festivo, int dia, int mes, int anyo, ofstream& escritura, ifstream &lectura);//averigua los martes que son puente
void puenteJV(string festivo, int dia, int mes, int anyo, ofstream& escritura, ifstream &lectura);//averigua los jueves que son puente

const string Centinela = "XXX";

int main() {
	int anyo, mes, dia;
	bool salir = false;
	int op_menu;
	int numDias = 0;
	int diaAux = 0;

	do {
		op_menu = menu();
		switch (op_menu) {
		case 0: {
			salir = true;
			break;
		}
		case 1: {
			anyo = solicitaAnyo();
			mes = solicitaMes();
			dia = solicitaDia(anyo, mes);

			diaAux = fechaDada(dia, mes, anyo);

			cout << "El dia de la semana del " << dia << "/" << mes << "/" << anyo << " es: " << nombreDia(diaAux) << endl;

			break;
		}
		case 2: {
			int primerdomingo = 0;
			anyo = solicitaAnyo();
			primerdomingo = primerDomingo(anyo, numDias);
			cout << "El primer Domingo del anio " << anyo << " es el dia: " << primerdomingo << " de Enero \n";
			break;
		}
		case 3: {
			anyo = solicitaAnyo();
			cout << "Los Domingos del anio " << anyo << " son: " << endl;
			int i = domingosAnyo(anyo);
			cout << "Numero total de Domingos : " << i << endl;
			break;
		}
		case 4: {
			puentes();
			break; }

		case 5:{
			puentesMejorado();
			break;
		}
		default: {
			cout << "¡Opcion no valida!" << endl;
			break;
		}
		}
	} while (salir == false);

	system("pause");
	return 0;

}


int solicitaAnyo() {
	int a;

	do {
		cout << "introduce anyo(1900 o mas): ";
		cin >> a;
		if (a < 1900) {
			cout << "valor incorrecto \n";
		}
	} while (a < 1900);

	return a;
}

int solicitaMes() {
	int m;

	do {
		cout << "introduce numero de mes: ";
		cin >> m;
		if (m < 1 || m > 12) {
			cout << "valor incorrecto \n";
		}
	} while (m < 1 || m>12);

	return m;
}

int solicitaDia(int anyo, int mes) {
	int dia;
	int maxDia;

	maxDia = diasMes(mes, anyo);

	if (maxDia == 31) {
		do {
			cout << "introduce un dia ente 1 y 31: ";
			cin >> dia;
			if (dia < 1 || dia > 31) {
				cout << "Valor incorrecto.\n";
			}
		} while (dia < 1 || dia > 31);
	}
	else if (maxDia == 30) {
		do {
			cout << "introduce un dia ente 1 y 30: ";
			cin >> dia;
			if (dia < 1 || dia > 30) {
				cout << "Valor incorrecto.\n";
			}
		} while (dia < 1 || dia > 30);
	}
	else if (maxDia == 29) {
		do {
			cout << "introduce un dia ente 1 y 29: ";
			cin >> dia;
			if (dia < 1 || dia > 29) {
				cout << "Valor incorrecto.\n";
			}
		} while (dia < 1 || dia > 29);
	}
	else {
		do {
			cout << "introduce un dia ente 1 y 28: ";
			cin >> dia;
			if (dia < 1 || dia > 28) {
				cout << "Valor incorrecto.\n";
			}
		} while (dia < 1 || dia > 28);
	}
	return dia;
}

bool esBisiesto(int anyo) {
	bool bisiesto = false;
	int aux;
	aux = anyo % 4;
	if (aux == 0) {
		bisiesto = true;
		aux = anyo % 100;
		if (aux == 0) {
			bisiesto = false;
			aux = anyo % 400;
			if (aux == 0) {
				bisiesto = true;
			}
		}
	}
	return bisiesto;
}

long int diasTranscurridos(int dia, int mes, int anyo) {

	long int diastranscurridos;
	int añospasados = 0;
	int diasAnyo = 0;

	añospasados = diasAnyosCompletos(anyo);

	diasAnyo = diasEsteAnyo(dia, mes, anyo);

	diastranscurridos = añospasados + diasAnyo;


	return diastranscurridos;
}

long int diasAnyosCompletos(int anyo) {
	int anyoInicio = 1900;
	long int transcurridos;
	int añospasados;
	int añosbisiesto;

	añospasados = anyo - anyoInicio;

	añosbisiesto = contarBisiestos(anyoInicio, anyo);

	transcurridos = añospasados * 365 + añosbisiesto;

	return transcurridos;
}

int diasEsteAnyo(int dia, int mes, int anyo) {
	int sumaDias = 0;

	for (int i = 1; i < mes; i++) {
		sumaDias += diasMes(i, anyo);
	}
	sumaDias = sumaDias + dia - 1;

	return sumaDias;
}

int contarBisiestos(int anyoInicio, int anyoFinal) {
	int numBis = 0;

	for (int i = anyoInicio; i < anyoFinal; i++) {
		if (esBisiesto(i)) {
			numBis++;
		}
	}
	return numBis;
}

int diasMes(int mes, int anyo) {
	int dias;

	if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12) {
		dias = 31;
	}
	else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
		dias = 30;
	}
	else {
		if (esBisiesto(anyo)) {
			dias = 29;
		}
		else {
			dias = 28;
		}
	}
	return dias;
}

int diaSemana(long int numDias) {
	int diaDe = 0;

	diaDe = numDias % 7;

	return diaDe;
}

string nombreDia(int representacionDia) {
	string dia;

	switch (representacionDia)
	{
	case 0: dia = "Lunes"; break;
	case 1: dia = "Martes"; break;
	case 2: dia = "Miercoles"; break;
	case 3: dia = "Jueves"; break;
	case 4: dia = "Viernes"; break;
	case 5: dia = "Sabado"; break;
	case 6: dia = "Domingo"; break;
	default:
		break;
	}


	return dia;
}

int menu() {
	int num = 0;
	cout << "--------------------------------------------------" << endl;
	cout << "Selecciona una opcion:" << endl;
	cout << "1- Calcular el dia de la semana para una fecha dada" << endl;
	cout << "2- Obtener la fecha correspondiente al primer domingo de un anio" << endl;
	cout << "3- Obtener los domingos de un anio" << endl;
	cout << "4- Obtener los posibles puentes de un anio" << endl;
	cout << "5- Obtener los posibles puentes (mejorado)" << endl;
	cout << "0- Salir" << endl;
	cout << "Opcion: ";
	cin >> num;
	cout << endl;
	return num;
}

int fechaDada(int dia, int mes, int anyo) {
	int fecha = 0, numDias = 0;

	numDias = diasTranscurridos(dia, mes, anyo);
	fecha = diaSemana(numDias);

	return fecha;
}

int primerDomingo(int anyo, int numDias) {

	int domingo = 0, numDiasAux = 0, dias = 0;
	int dia = 1, mes = 1;
	numDias = diasTranscurridos(dia, mes, anyo);

	while (fechaDada(dia, mes, anyo) != 6) {
		dia++;
	}
	domingo = dia;

	return domingo;
}

string nombreMes(int mes) {
	string esMes;
	switch (mes) {
	case 1: esMes = "Enero"; break;
	case 2: esMes = "Febrero"; break;
	case 3: esMes = "Marzo"; break;
	case 4: esMes = "Abril"; break;
	case 5: esMes = "Mayo"; break;
	case 6: esMes = "Junio"; break;
	case 7: esMes = "Julio"; break;
	case 8: esMes = "Agosto"; break;
	case 9: esMes = "Septiembre"; break;
	case 10: esMes = "Octubre"; break;
	case 11: esMes = "Noviembre"; break;
	case 12: esMes = "Diciembre"; break;
	default: break;
	}


	return esMes;
}

int domingosAnyo(int anyo){
	int primerD = 0;
	int mes = 1;
	int numDomingos = 1;
	int numDias = diasMes(mes, anyo);
	primerD = primerDomingo(anyo, numDias);
	cout << primerD << " de " << nombreMes(mes) << endl;
	for (mes = 1; mes <= 12; mes++) {
		int numDias = diasMes(mes, anyo);
		while (primerD <= numDias && (primerD + 7 <= numDias)){
			primerD = primerD + 7;
			cout << primerD << " de " << nombreMes(mes) << endl;
			numDomingos = numDomingos + 1;
		}
		primerD = -(numDias - primerD);
	}

	return numDomingos;
}

string diaDeLaSemana(int dia, int mes, int anyo){
	string diaSemana;
	int fecha = fechaDada(dia, mes, anyo);

	diaSemana = nombreDia(fecha);

	return diaSemana;
}

bool puentes(){
	bool hayAlgunPosiblepuente = false;
	int anyo = 0, mes = 0, dia = 0;
	string festivo;
	ofstream escritura;
	ifstream lectura;
	escritura.open("puentes.txt");
	lectura.open("fiestas.txt");

	if (lectura.is_open() && escritura.is_open()){
		lectura >> anyo;
		escritura << anyo;
		lectura >> dia;
		lectura >> mes;
		while (dia != 0 && mes != 0){
			festivo = diaDeLaSemana(dia, mes, anyo);

			if (festivo == "Martes" || festivo == "Jueves"){
				escritura << endl;
				escritura << dia << " " << mes << " " << festivo;
				hayAlgunPosiblepuente = true;
			}
			lectura >> dia >> mes;
		}
		escritura << endl;
		escritura << 0 << " " << 0 << " " << Centinela;
		cout << "Archivo escrito\n";
		lectura.close();
		escritura.close();
	}
	else {
		cout << "error de apertura\n";
	}

	return hayAlgunPosiblepuente;
}

bool puentesMejorado(){
	bool hayAlgunPosiblepuente = false;
	int anyo = 0, mes = 0, dia = 0;
	ofstream escritura;
	ifstream lectura;
	escritura.open("puentes.txt");
	lectura.open("fiestas.txt");
	//se supone que el archivo ya contiene los dias
	//festivos que no caen en domingo
	// no creo que haga falta controlarlo
	//y si hace falta ya estaria controlado 
	//porque puente seria martes o jueves ningun otro
	//seria un posible puente
	if (lectura.is_open()){
		lectura >> anyo;
		lectura >> dia >> mes;
		escritura << anyo;
		while (dia != 0 && mes != 0){
			string festivo = diaDeLaSemana(dia, mes, anyo);
			puenteLM(festivo, dia, mes, anyo, escritura, lectura);
			puenteJV(festivo, dia, mes, anyo, escritura, lectura);

			//cout << endl;
			lectura >> dia >> mes;
		}
		escritura << endl;
		escritura << 0 << " " << 0 << " " << Centinela;
		lectura.close();
		escritura.close();
	}
	return hayAlgunPosiblepuente;
	//Es una funcion bool porque en la version 3 podras usar esta misma 
	//funcion para ver si hay algun posible puente
	//y luego comprobar si el dia siguiente o anterior es puente o no
}

void puenteLM(string festivo, int dia, int mes, int anyo, ofstream& escritura, ifstream &lectura){
	bool hayAlgunPosiblepuente = false;
	int diaAux = 0, mesAux = 0;
	diaAux = dia;
	mesAux = mes;
	if (festivo == "Lunes"){
		lectura >> dia >> mes;
		if (dia == diaAux + 1 && mesAux == mes){
			cout << "No es puente" << endl;
			
		}
		else {
			if (diaDeLaSemana(dia, mes, anyo) == "Martes")
			festivo = diaDeLaSemana(dia, mes, anyo);
			escritura << endl;
			escritura << dia << " " << mes << " " << festivo;

		}

	}
	else {
		dia = diaAux;
		mes = mesAux;
	}
}

void puenteJV(string festivo, int dia,int mes, int anyo, ofstream& escritura, ifstream &lectura){
	bool hayAlgunPosiblepuente = false;
	int diaAux = 0, mesAux = 0;
	
	diaAux = dia;
	mesAux = mes;
	if (festivo == "Jueves"){
		lectura >> dia >> mes;
		if (dia == diaAux + 1 && mesAux == mes){
			cout << "no es puente" << endl;
		} else{ 

		festivo = diaDeLaSemana(diaAux, mesAux, anyo);
		escritura << endl;
		escritura << diaAux << " " << mes << " " << festivo; }

	} 
	else {
		dia = diaAux;
		mes = mesAux;
	}

}