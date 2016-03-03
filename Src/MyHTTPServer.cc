#include <iostream>

using namespace std;


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


int main(int argc, char *argv[]){ 

	if(comprobarArgumentos(argc) == 1) return 1;
	return 0;

}




/*

// Leer el archivo de configuracion del servidor 

	 //DocumentRoot que nos indique donde estan los archivos 
	 //Maxclients que será el número maximo de procesos que lanzará el servidor 
	 //Puerto en el que escuchará el servidor 
	 //Página por defecto que se envia si no se indica otra 

// Declaramos las variables necesarias 
	
	int Socket;
	int Puerto = argv[1];
	struct Direccion;


// Abrimos el socket 
	
	Socket = socket(AF_INET, SOCK_STREAM, 0);
	if(Socket == -1){
		printf(stderr, "Error. El socket no se ha abierto correctamente\n\r");
	}
	else{
		printf("Socket abierto\n\r");
	}

// Enlazamos una IP y un puerto al socket 

	Direccion.sin_family = AF_INET;
	Direccion.sin_port = htons(Puerto);
	Direccion.sin_addr.s_addr = INADDR_ANY;

	if(bind(Socket, (struct sockaddr *)&Direccion, sizeof (Direccion)) == -1){
		fprintf(stderr, "Error. No se puede asociar el puerto al socket\n\r");
		close(Socket);
		return(1);	
	}
	else{
		fprintf("Puerto de escucha establecido\n\r");
	}

// Preparamos el servidor para empezar a escuchar 
	
	if(listen(Socket, Maxclients) == -1){
		fprintf(stderr, "Error preparando el servidor\n\r");
		close(Socket);
		return(1);
	}
	else{
		fprintf("Servidor preparado correctamente\n\r");
	}

// Esperar conexiones 

*/
