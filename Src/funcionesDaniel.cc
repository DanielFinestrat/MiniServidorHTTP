#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h> 
#include <sys/socket.h>
#include "cabecera.h"
using namespace std;

// Maneja los argumentos y saca del programa si la sintaxis es erronea
int manageArguments(int argc, char *argv[], string &rutaConf, int &puerto){
	int toRet = 0;
	string err = "Error. Se debe indicar el puerto del servidor y la ruta al archivo de configuracion\n\rSintaxis: http_server [puerto] [-c fichero_configuracion]\n\r";

	if(argc == 2) puerto = atoi(argv[1]);
	
	if(argc == 3){
		if(strcmp(argv[1],"-c") == 0){ rutaConf = argv[2]; }
		else toRet = 1;
	}

	if(argc == 4){
		if(strcmp(argv[1],"-c") == 0){
			rutaConf = argv[2];
			puerto = atoi(argv[3]);
		}
		else if(strcmp(argv[2],"-c") == 0){
			rutaConf = argv[3];
			puerto = atoi(argv[1]);
		}
		else toRet = 1;
	}

	if(toRet == 1 || argc > 4){ toRet = 1; cout << err; }

	return toRet;
}

// Crea el socket y lo devuelve, si hay error lo muestra
int inicializarSocket(){

	string err = "Error. No se puede abrir el socket\n\r";

	int nuevoSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (nuevoSocket == -1) cout << err; 
	else cout << "Socket creado sin errores\n\r";

	return nuevoSocket;

}
