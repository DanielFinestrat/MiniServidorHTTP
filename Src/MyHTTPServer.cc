#include <sys/types.h>
#include <sys/socket.h>
#include <sys/mman.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <iostream>
#include <string>
#include "cabecera.h"
using namespace std;


static int *contHijos; //Contador de hijos disponibles, variable global
int miSocket; //Nuestro socket, variable global

void finalizar (int senyal){
    printf("SrvrMsg----> Recibida la señal de fin (cntr-C)\n\r");
    close(miSocket); //Cerrar para que accept termine con un error y salir del bucle principal
}

void enviarRespuesta(int socket, string respuesta, bool aumentarClientes){

	int enviados = 0;
	int longitud = 0;

	longitud = respuesta.length();
	cout<<"\n\r----------------------------\n\r";
	printf("Enviando respuesta [%d bytes]:\n\r%s", longitud, const_cast<char*>(respuesta.c_str()));
	enviados = write(socket, const_cast<char*>(respuesta.c_str()), longitud);
	cout<<"\n\r----------------------------\n\r\n\r";

	if (enviados == -1 || enviados < longitud){
		fprintf(stderr, "SrvrMsg----> Error enviando la respuesta (%d)\n\r", enviados);
		close(miSocket); close(socket); return;
	}

	printf("SrvrMsg----> Respuesta enviada correctamente\n\r");        
	close(socket); //Cierro el socket
	if(aumentarClientes){
		*contHijos = *contHijos + 1; //Aumentamos el contador de hijos disponibles
		cout << "SrvrMsg----> Clientes disponibles aumentado: " <<*contHijos <<endl;
	}
	exit(0); //El hijo ya no tiene que hacer nada

}

int main(int argc, char *argv[]){
    	char mensaje[1024];
    	int n, recibidos, s2, proceso;
	string documentRoot;    //Nos indica donde estan los archivos
	string rutaConf = "";	//Nos indica donde esta el fichero de configuracion
	string pagina;          //Pagina que por defecto que se envia si no se indica otra
	int maxclients;         //Es el número maximo de procesos que lanzará el servidor
	int puerto = 6000;      //Puerto en el que escuchará el servidor (Por defecto 6000)


	//Manejamos los argumentos, si no hay ruta del fichero establecida, devolvera un string vacio ("")
	if(manageArguments(argc, argv, rutaConf, puerto) == 1) return 1;
	
	leerDatos(rutaConf, &documentRoot, &maxclients, &puerto, &pagina);
	//Prueba de que funciona
	cout<< "SrvrMsg----> Datos configuracion -- DocRot: " << documentRoot <<" MaxClients: "<<maxclients<<" Puerto: "<<puerto<<" Pagina: "<<pagina<<endl;

	contHijos = (int*)mmap(NULL, sizeof *contHijos, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);	
	*contHijos = maxclients; //Inicializamos el contador de hijos disponibles al maximo
	cout << "SrvrMsg----> Clientes disponibles: " <<*contHijos <<endl;

	//Inicializamos el socket y comprobamos errores
	miSocket = inicializarSocket(); if(miSocket == -1) return 1;
	
	// Enlazamos una IP y un puerto al socket
    	unsigned int long_Cliente;
   	struct sockaddr_in Direccion, Cliente;
    	Direccion.sin_family = AF_INET;
    	Direccion.sin_port = htons(puerto);
    	Direccion.sin_addr.s_addr = INADDR_ANY;

	if(bind(miSocket, (struct sockaddr *)&Direccion, sizeof (Direccion)) == -1){
		cout << "SrvrMsg----> Error. No se puede asociar el puerto al socket\n\r" ;
		close(miSocket); return(1);
	}else cout <<"SrvrMsg----> Puerto de escucha establecido\n\r";


	// Preparamos el servidor para empezar a escuchar
	if(listen(miSocket, maxclients) == -1){
		cout << "SrvrMsg----> Error preparando el servidor\n\r";
		close(miSocket); return(1);
	}else cout << "SrvrMsg----> Servidor preparado correctamente\n\r";

    	signal(SIGINT, finalizar);

	cout<< "SrvrMsg----> Esperando conexión en el puerto " << puerto <<endl;
    	while (1){
        	long_Cliente = sizeof (Cliente);
		// s2 es el socket para comunicarse con el cliente, miSocket puede seguir siendo usado para comunicarse con otros clientes
        	s2 = accept (miSocket, (struct sockaddr *)&Cliente, &long_Cliente); 
        	
        	if (s2 == -1){ break; } // Salir del bucle
		if(*contHijos <= 0){
			int procHijoNoDisponible = fork();
			if (procHijoNoDisponible == -1) exit(1);
			if (procHijoNoDisponible == 0){
				string miRespuesta = construirRespuestaError(503, documentRoot, "");
				enviarRespuesta(s2, miRespuesta, false);
			}
			else close(s2);
		}else{
			*contHijos = *contHijos - 1; // Disminuimos los hijos disponibles
			cout << "SrvrMsg----> Clientes disponibles disminuido: " <<*contHijos <<endl;
			proceso = fork(); // Crear un nuevo proceso para que se pueda atender varias peticiones en paralelo

			if (proceso == -1) exit(1);
			if (proceso == 0){ // Soy el hijo
		    		close(miSocket); // El hijo no necesita el socket general
		    
		    		/**** Paso 5: Leer el mensaje ****/
			    	n = sizeof(mensaje);
			   	recibidos = read(s2, mensaje, n);
			    	cout<< "SrvrMsg----> Nuevo mensaje entrante" <<endl;
				if (recibidos == -1){ // No lee mensaje, error 500.
					cout<< "SrvrMsg----> Error leyendo el mensaje, enviando ERROR 500" <<endl;
					string miRespuesta = construirRespuestaError(500, documentRoot, "");
					enviarRespuesta(s2, miRespuesta, true);
				}
			    	
				mensaje[recibidos] = '\0'; // Pongo el final de cadena

				cout<<"\n\r----------------------------\n\r";
			    	cout<<"Mensaje recibido["<<recibidos<<"]: " <<endl << mensaje;
				cout<<"\n\r----------------------------\n\r\n\r";

				/**** Paso 5.1: Tratamos la peticion ****/

				//1.- Metodo compatible. Metodos validosGET - HEAD - PUT - DELETE)
			    	int metodo; // 0=Método Erroneo 1=GET 2=HEAD 3=PUT 4=DELETE
			    	metodo = ver_metodo(mensaje);
				if (metodo == 0){ //Metodo erroneo, error 405.
					cout<< "SrvrMsg----> Error de metodo erroneo, enviando ERROR 405" <<endl;
					string miRespuesta = construirRespuestaError(405, documentRoot, "");
					enviarRespuesta(s2, miRespuesta, true);
				}

				//2.- URI valida. (0 = No existe el fichero 1 = Si existe)
				string uri = ver_uri(mensaje);
				int existe = existeArchivo(uri, documentRoot);
				cout<< "SrvrMsg----> Uri: " << uri <<" Existe: "<<existe<<endl;
				if(!existe && metodo != 3){ //Doc pedido no existe y no estamos usando PUT, error 404.
					cout<< "SrvrMsg----> Error de fichero no encontrado, enviando ERROR 404" <<endl;
					string miRespuesta = construirRespuestaError(404, documentRoot, "");
					enviarRespuesta(s2, miRespuesta, true);
				}

				//3.- Version compatible. Versiones validas (1.0 - 1.1 - 1.2 - 2.0)
				bool valida = versionHTTP_valida(mensaje);
				cout<< "SrvrMsg----> Version validada (0/1): "<<valida<<endl; 
				if(!valida){ //Version no valida, error 505.
					cout<< "SrvrMsg----> Error de version no valida, enviando ERROR 505" <<endl;
					string miRespuesta = construirRespuestaError(505, documentRoot, "");
					enviarRespuesta(s2, miRespuesta, true);
				}

				//4.- Cabeceras y cuerpo
				string accept1 = "", accept2 = "", charset = "", user_agent = "", host="", cuerpo;
				bool error = false;  //Si hay alguna cabecera que no entendemos cambia a true
				leerCabeceras(mensaje, &accept1, &accept2, &charset, &user_agent, &host, &cuerpo, &error);
				cout<<endl<<endl;
				cout<< "SrvrMsg----> Accept (tipo1): "<<accept1<<endl;
				cout<< "SrvrMsg----> Accept (tipo2): "<<accept2<<endl;
				cout<< "SrvrMsg----> Accept-Charset: "<<charset<<endl;
				cout<< "SrvrMsg----> User-Agent: "<<user_agent<<endl;
				cout<< "SrvrMsg----> Host: "<<host<<endl;
				cout<< "SrvrMsg----> Cuerpo: "<<cuerpo<<endl;

				/*** Paso 6: Enviar respuesta y borrar hijo ****/
				string miRespuesta = tratarPeticion(documentRoot,metodo,uri, accept1, charset);
				enviarRespuesta(s2, miRespuesta, true);

			}else close(s2); //Soy el padre y no uso esta conexión
		}
	}

	/**** Paso 7: Cerrar socket****/
	close(miSocket);
	cout<< "SrvrMsg----> Socket cerrado" <<endl;
	munmap(contHijos, sizeof *contHijos); //Borramos la memoria compartida
	return 0;
}
