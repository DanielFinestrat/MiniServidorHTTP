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

void finalizar (int senyal){
    printf("Recibida la señal de fin (cntr-C)\n\r");
    close(miSocket); //Cerrar para que accept termine con un error y salir del bucle principal
}

int main(int argc, char *argv[]){

    	char mensaje[1024];
    	int n, enviados, recibidos, s2, proceso;
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
    	unsigned int long_Cliente;
   	struct sockaddr_in Direccion, Cliente;
    	Direccion.sin_family = AF_INET;
    	Direccion.sin_port = htons(puerto);
    	Direccion.sin_addr.s_addr = INADDR_ANY;

	if(bind(miSocket, (struct sockaddr *)&Direccion, sizeof (Direccion)) == -1){
		cout << "Error. No se puede asociar el puerto al socket\n\r" ;
		close(miSocket); return(1);
	}else cout <<"Puerto de escucha establecido\n\r";


	// Preparamos el servidor para empezar a escuchar
	if(listen(miSocket, maxclients) == -1){
		cout << "Error preparando el servidor\n\r";
		close(miSocket); return(1);
	}
	else cout << "Servidor preparado correctamente\n\r";

    	signal(SIGINT, finalizar);
    
    	while (1){
        	cout<< "Esperando conexión en el puerto " << puerto <<endl;
        	long_Cliente = sizeof (Cliente);
        	s2 = accept (miSocket, (struct sockaddr *)&Cliente, &long_Cliente);
        	
		/* s2 es el socket para comunicarse con el cliente
        	   s puede seguir siendo usado para comunicarse con otros clientes */

        	if (s2 == -1){ break; } //Salir del bucle
       		proceso = fork(); //crear un nuevo proceso para que se pueda atender varias peticiones en paralelo
        	if (proceso == -1) exit(1);
        	if (proceso == 0){ //Soy el hijo
            		close(miSocket); //El hijo no necesita el socket general
            
            		/**** Paso 5: Leer el mensaje ****/
		    	n = sizeof(mensaje);
		   	recibidos = read(s2, mensaje, n);
		    	if (recibidos == -1){ cout<< "Error leyendo el mensaje" <<endl; exit(1); }
		    	mensaje[recibidos] = '\0'; // pongo el final de cadena
            
            
			//EMPEZAMOS A TRATAR EL MENSAJE QUE RECIBIMOS
		    	cout<<"Mensaje ["<<recibidos<<"] : "<< mensaje <<endl;
		  
		    	int metodo; /* 0=Método Erroneo 1=GET 2=HEAD 3=PUT 4=DELETE */
		    	metodo = ver_metodo(mensaje);

	
		    	if(metodo == 0){ /*Error 405*/ }
		    	else{ string uri = ver_uri(mensaje); cout<< uri <<endl; } //No se comprueba si la uri es valida
		

            
            		/**** Paso 6: Enviar respuesta ****/

			//STRING A CHAR			
			string miRespuesta = construirRespuestaError(500, documentRoot);
			char respuesta[miRespuesta.size()+1];
			strncpy(respuesta, miRespuesta.c_str(), sizeof(respuesta));
			respuesta[sizeof(respuesta) - 1] = 0;
			//STRING A CHAR

			n = strlen(respuesta);
			printf("Enviar respuesta [%d bytes]: %s\n\r", n, respuesta);
			enviados = write(s2, respuesta, n);
			if (enviados == -1 || enviados < n){
				fprintf(stderr, "Error enviando la respuesta (%d)\n\r",enviados);
				close(miSocket); return 1;
			}
            		printf("Respuesta enviada\n\r");
            
            		close(s2);
           		exit(0); //El hijo ya no tiene que hacer nada
        }
        else{ close(s2); } //Soy el padre y no uso esta conexión
    }
	close(miSocket);
	cout<< "Socket cerrado" <<endl;
	return 0;
}
