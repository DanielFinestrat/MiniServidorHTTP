#include <iostream>
#include <string>
using namespace std;

int manageArguments(int argc, char *argv[], string &rutaConf, int &puerto);
int inicializarSocket();
void leerDatos(string archivo, string* DocumentRoot, int* Maxclients, int* Puerto, string* Pagina);
int esperarConexiones(int maxClients, string documentRoot, string pagina, int s);
void finalizar(int senyal);
int ver_metodo(char mensaje[]);
string ver_uri(char mensaje[]);
