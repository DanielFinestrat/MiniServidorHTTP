#include "cabecera.h"
// Maneja los argumentos y saca del programa si la sintaxis es erronea
int comprobarArgumentos(int argc){
	int toRet = 0;

	if (argc != 4){
		cout << "Error. Se debe indicar el puerto del servidor y la ruta al archivo de configuracion\n\r";
		cout << "Sintaxis: http_server [puerto] [-c fichero_configuración]\n\r";
		toRet = 1;
	}

	return toRet;
}
