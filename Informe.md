## INFORME PROYECTO 1 - BASE DE DATOS 2

Integrantes:
-Choquehuanca, Said.
-Rodríguez, Mauricio.
-Tenazoa, Renzo

### INTRODUCCIÓN:
El presente año 2021 trajo consigo uno de los eventos deportivos más grandes del mundo. Nos referimos a **Los Juegos Olímpicos de Tokio 2020**. Dichos juegos tuvieron lugar del 23 de julio al 8 de agosto de 2021 en la cudad de Tokio, Japón. Los juegos tuvieron a muchos participantes de distintos países del mundo, y claro, cada participante acompañado de su respectivo coach. Es por ello, que en este proyecto implementaremos un simulador de gestor de base de datos con los datos obtenidos de los coaches de los participantes Los Juegos Olímpicos. Cada Coach cuenta con los campos de: Name, NOC, Discipline, Event. 

Con el objetivo de realizar nuestro gestor de base de datos se usaron dos técnicas de organización de archivos: Sequential File y Extendible Hashing. 

#### PROCEDIMIENTO

Primero se declaró la estructura del Registro a guardar, es decir, los datos del Coach:

struct Registro{
  char name [30];
  char NOC [26];
  char discipline [17];
  char event[8];
  long next;
  char file;
 }

 Luego se procedió a implementar cada una de las técnicas de organización en sus respectivos archivos: SequentialFile.h y ExtendibleHashing.h

 Finalmente, se realizó una interfaz gráfica para simular la ejecución de consultas en la base de datos para las técnicas usadas.

 Video sobre la explicación del proyecto: En el repositorio Github

