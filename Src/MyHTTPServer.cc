#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
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
	cout<< "Datos configuracion -- DocRot: " << documentRoot <<" MaxClients: "<<maxclients<<" Puerto: "<<puerto<<" Pagina: "<<pagina<<endl;

	//Inicializamos el socket y comprobamos errores
	miSocket = inicializarSocket(); if(miSocket == -1) return 1;
	
	// Enlazamos una IP y un puerto al socket
	struct sockaddr_in Direccion;
	Direccion.sin_family = AF_INET;
	Direccion.sin_port = htons(puerto);
	Direccion.sin_addr.s_addr = INADDR_ANY;

	if(bind(miSocket, (struct sockaddr *)&Direccion, sizeof (Direccion)) == -1){
		cout << "Error. No se puede asociar el puerto al socket\n\r" ;
		close(miSocket);
		return(1);
	}else cout <<"Puerto de escucha establecido\n\r";


	// Preparamos el servidor para empezar a escuchar
	if(listen(miSocket, maxclients) == -1){
		cout << "Error preparando el servidor\n\r";
		close(miSocket);
		return(1);
	}
	else cout << "Servidor preparado correctamente\n\r";

	close(miSocket);
	return 0;
}

