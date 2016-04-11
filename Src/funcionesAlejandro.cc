#include "cabecera.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
int s;
void finalizar1(int senyal)
{
	printf("Recibida la señal de fin (cntr-C)\n\r");
	close(s); /* cerrar para que accept termine con un error y salir del bucle principal */
}

int esperarConexiones(int maxClients, string documentRoot, string pagina, int socket) {
/**** Paso 4: Esperar conexiones ****/
	s=socket;
	char *servidor_puerto;
	unsigned int long_dir_cliente;
	int s2;
	struct sockaddr_in dir_cliente;
	char mensaje[1024], respuesta[]="Gracias por tu mensaje";
	int n, enviados, recibidos;
	int proceso;
	
	signal(SIGINT, finalizar1);
	
	while (1)
	{
		fprintf(stderr, "Esperando conexión en el puerto %s...\n\r", servidor_puerto);
		long_dir_cliente = sizeof (dir_cliente);
		s2 = accept (s, (struct sockaddr *)&dir_cliente, &long_dir_cliente);
		/* s2 es el socket para comunicarse con el cliente */
		/* s puede seguir siendo usado para comunicarse con otros clientes */
		if (s2 == -1)
		{
			break; /* salir del bucle */
		}
		/* crear un nuevo proceso para que se pueda atender varias peticiones en paralelo */
		proceso = fork();
		if (proceso == -1) exit(1);
		if (proceso == 0) /* soy el hijo */
		{
			close(s); /* el hijo no necesita el socket general */

			/**** Paso 5: Leer el mensaje ****/

			n = sizeof(mensaje);
			recibidos = read(s2, mensaje, n);
			if (recibidos == -1)
			{
				fprintf(stderr, "Error leyendo el mensaje\n\r");
				exit(1);
			}
			mensaje[recibidos] = '\0'; /* pongo el final de cadena */
			printf("Mensaje [%d]: %s\n\r", recibidos, mensaje);


			/**** Paso 6: Enviar respuesta ****/

			n = strlen(respuesta);
			printf("Enviar respuesta [%d bytes]: %s\n\r", n, respuesta);
			enviados = write(s2, respuesta, n);
			if (enviados == -1 || enviados < n)
			{
				fprintf(stderr, "Error enviando la respuesta (%d)\n\r",enviados);
				close(s);
				return 1;
			}

			printf("Respuesta enviada\n\r");

			close(s2);
			exit(0); /* el hijo ya no tiene que hacer nada */
		}
		else /* soy el padre */
		{
			close(s2); /* el padre no usa esta conexión */
		}

	}
}
