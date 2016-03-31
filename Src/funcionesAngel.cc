#include "cabecera.h"
#include <string>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <string.h>


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
    }else{ *DocumentRoot = "./documentos/"; *Maxclients = 5; *Pagina = "index.html"; }
}

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

string ver_uri(char mensaje[]){
	char caracteres[40];
	int contador = 0, contador2 = 0;
	bool guardar = false;

	for(int i=0; i<strlen(mensaje) && contador<2; i++){
		if(guardar){
			caracteres[contador2] = mensaje[i];
			contador2++;		
		}
		if(mensaje[i]==' ' && contador == 0){
			contador++;
			guardar = true;	
		}
		else if(mensaje[i]==' ' && contador == 1){
			contador++;
		}
	}

	string uri = string(caracteres);
	return uri;
}
