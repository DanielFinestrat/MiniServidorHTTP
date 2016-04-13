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
	string fich = ""; string len = "";
	switch (metodo) {
		case 1: { // get
			fich = parsearFicheroGET(root + uri);
			break;
		}
		case 2: // head
		{
			fich = parsearFicheroGET(root + uri);
			break;
		}
		case 3: // put
		{
			if (checkNombres(uri))
			{
				ofstream fs(root+"/publicdocs/"+uri);
				fs.close();
				fich = parsearFicheroGET(root+"PutCompleto.html");
			} else {
				doc = construirRespuestaError(403,root);
				return doc;
			}
			break;
		}
		case 4: // delete
		{
			if (checkNombres(uri)) {
				if (remove(root+uri)!=0) {
					doc = construirRespuestaError(500, root);
					return doc;
				} else {
					fich = parsearFicheroGET(root+"DeleteCompleto.html");
				}
			} else {
				doc = construirRespuestaError(403,root);
				return doc;
			}
			break;
		}
	}
	
	len = intToStr(fich.length());
	doc+=len;
	doc+="\n\n";	
	if (metodo!=2)
		doc += fich;
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

// comprueba que la ruta no sea PROOOHIIBIIIIDAAA
bool checkNombres(sring ruta) {
	if (ruta != "boo2.gif" &&
	ruta != "Boo.html" &&
	ruta != "Captura.PNG" &&
	ruta != "DeleteCompleto.html" &&
	ruta != "Err400.html" &&
	ruta != "Err403.html" &&
	ruta != "Err404.html" &&
	ruta != "Err405.html" &&
	ruta != "Err500.html" &&
	ruta != "Err503.html" &&
	ruta != "Err505.html" &&
	ruta != "favicon.ico" &&
	ruta != "index.html" &&
	ruta != "PutCompleto.html")
		return true;
	else
		return false;
}
