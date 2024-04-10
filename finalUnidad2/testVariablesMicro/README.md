#Documentación

Esta documentación hace referencia al testVariablesMicro.ino de la carpeta actual

##Definición de las variables

Empezamos definiendo las 3 variables que vamos a implementar en el microcontrolador, establecimos las siguientes:

- Volumen: es un valor numerico que vaya desde 0 a 10, donde 0 es silencio y 10 es el max volumen
- Pista actual: representa la pista actual del reproductor con un numero entero dentro de la lista de reproduccion
- Duracion de la cancion: un valor en segundos que refleje la duracion de la pista actual

El micro debe encender el LED a 1 hz cada 500 milisegundos (0.5 segundos) para visualizar fisicamente que no se bloquee

Desde Unity debe haber comunicacion con el controlador para cambiar los parametros iniciales y en tiempo real de las variables mediante elementos interactivos en la interfaz grafica

La estructura para el codigo del microcontrolador estructurada de la siguiente manera

```c

```
