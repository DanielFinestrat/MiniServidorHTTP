#include "cabecera.h"
#include <string>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

//Metodo que lee una secuencia de carácteres para sacar el número total
int CharToInt(char cadena[16]){
    int num = 0;
    int potencia = 0;
    
    for(int i=15;i>=0;i--){
        if(cadena[i]>=48 && cadena[i]<=57){
            num = num + (cadena[i]-48) * pow(10, potencia);
            potencia++;
        }
    }
   
    return num;
}

//Metodo que se encarga de leer y guardar los valores del archivo de configuración del servidor
void leerDatos(string archivo, string* DocumentRoot, int* Maxclients, int* Puerto, string* Pagina){

    char cadena1[128];
    char cadena2[16];
    if(archivo!=""){
        ifstream fe(archivo.c_str());
        fe.getline(cadena1, 128);
        *DocumentRoot = cadena1;
        fe.getline(cadena2, 16);
        *Maxclients = CharToInt(cadena2);
        fe.getline(cadena2, 16);
        *Puerto = CharToInt(cadena2);
        fe.getline(cadena1, 128);
        *Pagina = cadena1;
	fe.close();
    }else{ *DocumentRoot = "./documentos/"; *Maxclients = 5; *Pagina = "index.html"; }
}

//Metodo que lee el método del mensaje HTTP recibido
int ver_metodo(char mensaje[]){
	int metodo;
	if(mensaje[0]=='G' || mensaje[0]=='g'){
		if((mensaje[1]=='E' || mensaje[1]=='e') && (mensaje[2]=='T' || mensaje[2]=='t')){
			metodo = 1;
		}
		else{
			metodo = 0;
		}
	}
	else if(mensaje[0]=='H' || mensaje[0]=='h'){
		if((mensaje[1]=='E' || mensaje[1]=='e') && (mensaje[2]=='A' || mensaje[2]=='a') && (mensaje[3]=='D' || mensaje[3]=='d')){
			metodo = 2;
		}
		else{
			metodo = 0;
		}
	}
	else if(mensaje[0]=='P' || mensaje[0]=='p'){
		if((mensaje[1]=='U' || mensaje[1]=='u') && (mensaje[2]=='T' || mensaje[2]=='t')){
			metodo = 3;
		}
		else{
			metodo = 0;
		}
	}
	else if(mensaje[0]=='D' || mensaje[0]=='d'){
		if((mensaje[1]=='E' || mensaje[1]=='e') && (mensaje[2]=='L' || mensaje[2]=='l') && (mensaje[3]=='E' || mensaje[3]=='e') && (mensaje[4]=='T' || mensaje[4]=='t') && (mensaje[5]=='E' || mensaje[5]=='e')){
			metodo = 4;	
		}
		else{
			metodo = 0;	
		}
	}
	else{
		metodo = 0;	
	}
	return metodo;
}

//Metodo que devuelve el uri que se pide en la peticion HTTP
string ver_uri(char mensaje[]){
	string uri = "";
	int contador = 0;
	bool guardar = false;

	// Modificado por Dani: Ahora guarda los "/" despues del primero, ya que
	// si queremos acceder a una subcarpeta necesitamos los "/"
	// (ejemplo: carpeta/subcarpeta/miPagina.html)
	bool primerSlash = true;

	for(int i=0; i<strlen(mensaje) && contador<2; i++){
		if(guardar && primerSlash && mensaje[i] == '/' && mensaje[i]!=' '){ //Este if te permite desechar el primer "/"
			primerSlash = !primerSlash;
		}
		else if(guardar && mensaje[i] != ' '){ //A partir del primer "/", te los guarda
			uri += mensaje[i];		
		}
		if(mensaje[i]==' ' && contador == 0){
			contador++;
			guardar = true;	
		}
		else if(mensaje[i]==' ' && contador == 1){
			contador++;
		}
	}

	return uri;
}

//Metodo que comprueba si el archivo existe en la carpeta del servidor
int existeArchivo (string filename, string directorio){
	
	//Modificado por Dani: si nos piden "/" quieren la pagina por defecto
	//ademas, busca el fichero en el documentRoot
	if (filename == "") filename = "index.html"; //Si nos piden "/", les damos el index
	filename = directorio + filename; //Indicamos el documentRoot antes de la uri nueva
	cout<<"SrvrMsg----> La ruta del fichero es: " <<filename <<endl;

	char* archivo = strdup(filename.c_str());
	FILE* f = NULL;
	f = fopen(archivo, "r");
	if( f == NULL && errno == ENOENT){
		return 0;
	}
	else{
		fclose(f);
		return 1;
	}
}

//Metodo que comprueba si la version HTTP es valida  
bool versionHTTP_valida(char mensaje[]){
	bool valida = false, leer = false;
	int contador_espacios = 0;
	for(int i=0; i<strlen(mensaje) && !leer ; i++){
		if(mensaje[i]==' ' && !leer){
			contador_espacios++;
		}
		if(contador_espacios == 2){
			leer = true;
			if(mensaje[i+1]=='H' && mensaje[i+2]=='T' && mensaje[i+3]=='T' && mensaje[i+4]=='P' && mensaje[i+5]=='/' &&  mensaje[i+7]=='.' && mensaje[i+9]==13){
				if(mensaje[i+6]=='1'){
					if(mensaje[i+8]=='0' || mensaje[i+8]=='1' || mensaje[i+8]=='2'){
						valida = true;
					}
				}
				else if(mensaje[i+6]=='2'){
					if(mensaje[i+8]=='0'){
						valida = true;
					}
				}	
			}
		}
	}
	return valida;
}
