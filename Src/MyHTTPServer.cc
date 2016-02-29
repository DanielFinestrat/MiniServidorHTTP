#include <iostream>

using namespace std;

int main(int argc, char *argv[]){ 
/* Hay que pasar por comando el puerto y el archivo con la orden */

/* Comprobamos los argumentos */
	if(argc != 3){ 
		fprintf(stderr, "Error. Debe indicar el puerto del servidor y el archivo de configuracion\n\r");
		fprintf(stderr, "Sintaxis: 3 <puerto> <-c archivo de configuracion>\n\r");
		return 1;
	}

/* Leer el archivo de configuracion del servidor */

	/* DocumentRoot que nos indique donde estan los archivos */
	/* Maxclients que será el número maximo de procesos que lanzará el servidor */
	/* Puerto en el que escuchará el servidor */
	/* Página por defecto que se envia si no se indica otra */

/* Declaramos las variables necesarias */
	
	int Socket;
	int Puerto = argv[1];
	struct Direccion;


/* Abrimos el socket */
	
	Socket = socket(AF_INET, SOCK_STREAM, 0);
	if(Socket == -1){
		printf(stderr, "Error. El socket no se ha abierto correctamente\n\r");
	}
	else{
		printf("Socket abierto\n\r");
	}

/* Enlazamos una IP y un puerto al socket */

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

/* Preparamos el servidor para empezar a escuchar */
	
	if(listen(Socket, Maxclients) == -1){
		fprintf(stderr, "Error preparando el servidor\n\r");
		close(Socket);
		return(1);
	}
	else{
		fprintf("Servidor preparado correctamente\n\r");
	}

/* Esperar conexiones */


	return 0;
}
