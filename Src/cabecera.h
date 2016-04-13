#include <iostream>
#include <string>
using namespace std;

int manageArguments(int argc, char *argv[], string &rutaConf, int &puerto);
int inicializarSocket();
void leerDatos(string archivo, string* DocumentRoot, int* Maxclients, int* Puerto, string* Pagina);
int ver_metodo(char mensaje[]);
string ver_uri(char mensaje[]);
int existeArchivo (string filename, string directorio);
bool versionHTTP_valida(char mensaje[]);
string intToStr(int n);
void leerCabeceras(char mensaje[], string* accept1, string* accept2, string* charset, string* user_agent, string* host, bool* error);
void guardarCabeceras(string cabecera, string* accept1, string* accept2, string* charset, string* user_agent, string* host, bool* error);
void leerAccept(string accept, string* accept1, string* accept2);
string parsearFicheroGET(string ruta);
string tratarPeticion(string root,int metodo,string uri);
string construirRespuestaError(int codErr, string ruta, string charset);
