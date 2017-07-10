# MiniServidorHTTP

Servidor HTTP básico desarrollado en C++

# Instrucciones de Compilación:

1.- Si no lo tenemos, instalar el g++:

  - ```sudo apt-get install g++```

2.- Navegar a la ruta del archivo y ejecutar:

  - ```make```

# Instrucciones de Uso:

1.- Ejecutar con:

  - ```./http_server [puerto] [-c ficheroConfiguración]```

2.- Alimentarle con una peticion completa:

  - ```cat ficheroPeticion | telnet dirIP puerto```

3.- Sintaxis del fichero de Configuración:

    Primera línea: Document Root.

    Segunda línea: Clientes Máximos.

    Tercera línea: Puerto.

    Cuarta línea: Página de inicio.

    Quinta linea: IP.

Por ejemplo:

    ./Documentos.
    
    5
    
    8080
    
    Index.html
    
    127.0.0.1

___
2016
