#include <iostream>
#include <string>
#include <sys/socket.h>
#include "cabecera.h"
using namespace std;

int miSocket; //Nuestro socket, variable global

int main(int argc, char *argv[]){

	string documentRoot;    //Nos indica donde estan los archivos
	string rutaConf = "";	//Nos indica donde esta el fichero de configuracion
	string pagina;          //Pagina que por defecto que se envia si no se indica otra
	int maxclients;         //Es el número maximo de procesos que lanzará el servidor
	int puerto = 6000;      //Puerto en el que escuchará el servidor (Por defecto 6000)

	//Manejamos los argumentos, si no hay ruta del fichero establecida, devolvera un string vacio ("")
	if(manageArguments(argc, argv, rutaConf, puerto) == 1) return 1;
	
	leerDatos(rutaConf, &documentRoot, &maxclients, &puerto, &pagina);
	//Prueba de que funciona
	//cout<< documentRoot <<" "<<maxclients<<" "<<puerto<<" "<<pagina<<endl;

	//Inicializamos el socket y comprobamos errores
	miSocket = inicializarSocket(); if(miSocket == -1) return 1;
	
	return 0;

	// Enlazamos una IP y un puerto al socket
	/*
	struct Direccion;
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
	*/


	// Preparamos el servidor para empezar a escuchar
	/*
	if(listen(Socket, Maxclients) == -1){
		fprintf(stderr, "Error preparando el servidor\n\r");
		close(Socket);
		return(1);
	}
	else{
		fprintf("Servidor preparado correctamente\n\r");
	}
	*/

}
