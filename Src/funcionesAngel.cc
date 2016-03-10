#include "cabecera.h"
#include <string>
#include <fstream>
#include <math.h>


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
    
    ifstream fe(archivo.c_str());
    fe.getline(cadena1, 128);
    *DocumentRoot = cadena1;
    fe.getline(cadena2, 16);
    *Maxclients = CharToInt(cadena2);
    fe.getline(cadena2, 16);
    *Puerto = CharToInt(cadena2);
    fe.getline(cadena1, 128);
    *Pagina = cadena1;
    
}



