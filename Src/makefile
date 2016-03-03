all: http_server clean

http_server: MyHTTPServer.o funcionesDaniel.o funcionesAlejandro.o funcionesAngel.o
	g++ -o http_server MyHTTPServer.o funcionesDaniel.o funcionesAlejandro.o funcionesAngel.o

MyHTTPServer.o: MyHTTPServer.cc cabecera.h
	g++ -c MyHTTPServer.cc

funcionesDaniel.o: funcionesDaniel.cc cabecera.h
	g++ -c funcionesDaniel.cc

funcionesAlejandro.o: funcionesAlejandro.cc cabecera.h
	g++ -c funcionesAlejandro.cc

funcionesAngel.o: funcionesAngel.cc cabecera.h
	g++ -c funcionesAngel.cc

clean:
	rm -rf *.o
	rm -rf *~
