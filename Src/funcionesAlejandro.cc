#include "cabecera.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>

// recibe el metodo y la uri para responder acordemente
string tratarPeticion(string root,int metodo,string uri) {
	string doc = "HTTP/1.1 200 OK\nConnection: close\nContent-Type: text/html\nServer: MyHTTPServer/0.1\nContent-Lenght: ";
	switch (metodo) {
		case 1: { // get
			string fich = parsearFicheroGET(root + uri);
			string len = intToStr(fich.length());
			doc+=len;
			doc+="\n\n";			
			doc += fich;
			break;
		}
		case 2: // head
		{
			string fich = parsearFicheroGET(root + uri);
			string len = intToStr(fich.length());
			doc+=len;
			doc+="\n\n";
			break;
		}
		case 3: // put
		break;
		case 4: // delete
		break;
	}
	return doc;
}
// Devuelve un STRING que contiene un fichero
string parsearFicheroGET(string ruta) {

	string toRet = "";
	string temp = "";
	string modRuta = ruta;

    ifstream fe(modRuta.c_str());
	while(!fe.eof()){ getline(fe, temp); toRet += temp; }
	fe.close();

	return(toRet);
}

