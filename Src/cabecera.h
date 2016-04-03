#include <iostream>
#include <string>
using namespace std;

int manageArguments(int argc, char *argv[], string &rutaConf, int &puerto);
int inicializarSocket();
void leerDatos(string archivo, string* DocumentRoot, int* Maxclients, int* Puerto, string* Pagina);
int ver_metodo(char mensaje[]);
string ver_uri(char mensaje[]);
string construirRespuestaError(int codErr, string ruta);
int existeArchivo (string filename);
bool versionHTTP_valida(char mensaje[]);
string intToStr(int n);
