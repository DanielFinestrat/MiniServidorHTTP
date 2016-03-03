http_server: MyHTTPServer.o funcionesDaniel.o funcionesAlejandro.o funcionesAngel.o
    gcc -o http_server MyHTTPServer.o funcionesDaniel.o funcionesAlejandro.o funcionesAngel.o

MyHTTPServer.o: MyHTTPServer.c cabecera.h
    gcc -c MyHTTPServer.c

funcionesDaniel.o: funcionesDaniel.c cabecera.h
    gcc -c funcionesDaniel.c

funcionesAlejandro.o: funcionesAlejandro.c cabecera.h
    gcc -c funcionesAlejandro.c

funcionesAngel.o: funcionesAngel.c cabecera.h
    gcc -c funcionesAngel.c
