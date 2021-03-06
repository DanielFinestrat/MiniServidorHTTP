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

// comprueba que la ruta no sea prohibida
bool checkNombres(string ruta) {
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
	ruta != "PutCompleto.html"){ cout << "SrvrMsg----> La ruta esta prohibida"<<endl; return true;}
	else
		return false;
}

// recibe el metodo y la uri para responder acordemente
string tratarPeticion(string root,int metodo,string uri,string contentType, string charset) {
	string fich = ""; string len = ""; string doc = "";
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
				string rutCompuesta = root+uri;
				ofstream fs(const_cast<char*>(rutCompuesta.c_str()));
				fs.close();
				if (existeArchivo (uri,root) == 0){ doc = construirRespuestaError(500,root,""); return doc;}
				fich = parsearFicheroGET(root+"PutCompleto.html");
				cout << "SrvrMsg----> Hemos creado el fichero correctamente"<<endl;
			} else {
				doc = construirRespuestaError(403,root,"");
				return doc;
			}
			break;
		}
		case 4: // delete
		{
			if (checkNombres(uri)) {
				string aux = root+uri;
				if (remove(const_cast<char*>(aux.c_str()))!=0) {
					doc = construirRespuestaError(500, root,"");
					return doc;
				} else {
					fich = parsearFicheroGET(root+"DeleteCompleto.html");
					cout << "SrvrMsg----> Hemos borrado el fichero correctamente"<<endl;
				}
			} else {
				doc = construirRespuestaError(403,root,"");
				return doc;
			}
			break;
		}
	}
	
	doc = "HTTP/1.1 ";
	if(metodo != 3) doc += "200 OK"; else doc += "201 Created";
	doc += "\nConnection: close\nContent-Type: ";
	if(contentType == "" || contentType == "*/*" ) doc += "text/html"; else doc += contentType;
	doc += "; charset=";
	if(charset == "") doc += "utf-8"; else doc += charset;
	doc += "\nServer: MyHTTPServer/0.1\nContent-Lenght: ";
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
