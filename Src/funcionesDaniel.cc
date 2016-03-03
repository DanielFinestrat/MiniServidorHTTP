#include <iostream>
#include <string>
#include "cabecera.h"
using namespace std;

// Maneja los argumentos y saca del programa si la sintaxis es erronea
int comprobarArgumentos(int argc, char *argv[], string &rutaConf, int &puerto){
	int toRet = 0;

	if (argc != 4){
		cout << "Error. Se debe indicar el puerto del servidor y la ruta al archivo de configuracion\n\r";
		cout << "Sintaxis: http_server [puerto] [-c fichero_configuraci�n]\n\r";
		toRet = 1;
	}

	return toRet;
}
