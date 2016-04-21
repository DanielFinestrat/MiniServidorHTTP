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


# Instrucciones de configuración del repositorio en Ubuntu:

1.- Descargar Git: 

  - ```sudo apt-get install git```

2.- Configurar nombre y correo:

  - ```sudo git config --global user.name "miNombre"```

  - ```sudo git config --global user.email "miEmail@miDominio.com"```

3.- Navegar a la carpeta y clonar nuestro repositorio:

  - ```git clone https://github.com/DanielFinestrat/MiniServidorHTTP```

4.- Editar, y al terminar usar:

- Para añadir los cambios (Todos los archivos):

  - ```git add -A```

- Para añadir los cambios (Solo algunos archivos específicos):

  - ```git add nombreArchivo```

- Para ponerle un mensaje a la actualziación:

  - ```git commit -m "Mensaje de Actualziación"```

- Para subirlo a la rama (te pedira tus datos de usuario de GitHub, introdúcelos):

  - ```git push```

5.- Si regresamos después de un tiempo, para actualizar nuestro clon usar:

  - ```git pull```

6.- Si queremos descartar cambios sin subirlos:

  - ```git reset --hard HEAD```
  - ```git pull```


___
2016
