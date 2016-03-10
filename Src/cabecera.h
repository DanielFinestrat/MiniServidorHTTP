#include <iostream>
#include <string>
using namespace std;

int manageArguments(int argc, char *argv[], string &rutaConf, int &puerto);
int inicializarSocket();
void leerDatos(string archivo, string* DocumentRoot, int* Maxclients, int* Puerto, string* Pagina);
void esperarConexiones(int maxClients, string documentRoot, string pagina, int s);
void finalizar(int senyal);
