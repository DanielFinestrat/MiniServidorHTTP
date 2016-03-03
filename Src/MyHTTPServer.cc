#include <iostream>
#include "cabecera.h"
using namespace std;

int main(int argc, char *argv[]){

	if(comprobarArgumentos(argc) == 1) return 1;
	
	// Leer el archivo de configuracion del servidor
    
    string DocumentRoot;    //Nos indica donde estan los archivos
    int Maxclients;         //Es el número maximo de procesos que lanzará el servidor
    int Puerto;             //Puerto en el que escuchará el servidor
    string Pagina;          //Pagina que por defecto que se envia si no se indica otra
    
    
    //Paso a String el argumento de la página
    
    
    string archivo(argv[3]);
    leerDatos(archivo, &DocumentRoot, &Maxclients, &Puerto, &Pagina);
    
    
    //Prueba de que funciona
    cout<< DocumentRoot <<" "<<Maxclients<<" "<<Puerto<<" "<<Pagina;

	



// Declaramos las variables necesarias

	/*int Socket;
	int Puerto = argv[1];
	struct Direccion;*/


// Abrimos el socket

	/*Socket = socket(AF_INET, SOCK_STREAM, 0);
	if(Socket == -1){
		printf(stderr, "Error. El socket no se ha abierto correctamente\n\r");
	}
	else{
		printf("Socket abierto\n\r");
	}*/

// Enlazamos una IP y un puerto al socket

	/*Direccion.sin_family = AF_INET;
	Direccion.sin_port = htons(Puerto);
	Direccion.sin_addr.s_addr = INADDR_ANY;

	if(bind(Socket, (struct sockaddr *)&Direccion, sizeof (Direccion)) == -1){
		fprintf(stderr, "Error. No se puede asociar el puerto al socket\n\r");
		close(Socket);
		return(1);
	}
	else{
		fprintf("Puerto de escucha establecido\n\r");
	}*/

// Preparamos el servidor para empezar a escuchar

	/*if(listen(Socket, Maxclients) == -1){
		fprintf(stderr, "Error preparando el servidor\n\r");
		close(Socket);
		return(1);
	}
	else{
		fprintf("Servidor preparado correctamente\n\r");
	}*/

// Esperar conexiones

	return 0;

}
