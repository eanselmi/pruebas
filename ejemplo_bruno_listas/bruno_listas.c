#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <commons/log.h>
#include <commons/config.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <commons/collections/list.h>
#include "ejemplo_bruno.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define BUF_SIZE 50
#define BLOCK_SIZE 20971520
#define MENSAJE_SIZE 4096

fd_set master; // conjunto maestro de descriptores de fichero
fd_set read_fds; // conjunto temporal de descriptores de fichero para select()
t_log* logger;
t_list *nodos; //lista de nodos conectados al fs
t_list* archivos; //lista de archivos del FS
t_config * configurador;
int fdmax; // número máximo de descriptores de fichero
int listener; // descriptor de socket a la escucha
int marta_sock; //Socket exclusivo para marta
struct sockaddr_in filesystem; // dirección del servidor
struct sockaddr_in remote_client; // dirección del cliente
char identificacion[BUF_SIZE]; // buffer para datos del cliente
char mensaje[MENSAJE_SIZE];
int cantidad_nodos=0;
int cantidad_nodos_historico=0;
int read_size;


int main (){

	/*Desarrollo de un ejemplo para la estructura del fs*/
	t_archivo* archivoDeEjemplo;
	archivoDeEjemplo=malloc(sizeof(t_archivo));
	strcpy(archivoDeEjemplo->nombre,"ArchEjemplo14032015.txt");
	archivoDeEjemplo->padre=0; //sería un archivo en la raíz ("/")
	archivoDeEjemplo->tamanio=41943040; //40 MB --> 2 Bloques
	archivoDeEjemplo->bloques=list_create();
	archivoDeEjemplo->estado=1; //asumiendo que estado 1 sería disponible
	//Creo el bloqueUno y asigno el nodo y bloque del nodo de cada copia
	t_bloque* bloqueUno;
	bloqueUno=malloc(sizeof(t_bloque));
	strcpy(bloqueUno->copias[0].nodo,"NodoA");
	bloqueUno->copias[0].bloqueNodo=30;
	strcpy(bloqueUno->copias[1].nodo,"NodoF");
	bloqueUno->copias[1].bloqueNodo=12;
	strcpy(bloqueUno->copias[2].nodo,"NodoU");
	bloqueUno->copias[2].bloqueNodo=20;
	//Creo el bloqueDos y asigno el nodo y bloque del nodo de cada copia
	t_bloque* bloqueDos;
	bloqueDos=malloc(sizeof(t_bloque));
	strcpy(bloqueDos->copias[0].nodo,"NodoC");
	bloqueDos->copias[0].bloqueNodo=3;
	strcpy(bloqueDos->copias[1].nodo,"NodoD");
	bloqueDos->copias[1].bloqueNodo=34;
	strcpy(bloqueDos->copias[2].nodo,"NodoA");
	bloqueDos->copias[2].bloqueNodo=50;

	list_add(archivoDeEjemplo->bloques,bloqueUno); //Mediante las commons, agrego el bloqueUno a la lista de bloques
	list_add(archivoDeEjemplo->bloques,bloqueDos); //Mediante las commons, agrego el bloqueUno a la lista de bloques
	list_add(archivos,archivoDeEjemplo); //Mediante las commons agrego a la lista de archivos del FS el archivoDeEjemplo

	printf("En la lista de archivos hay: %d archivos\n",list_size(archivos));
	t_archivo* primerArchivoDeLaListaDeArchivos	= list_get(archivos,0);
	printf("El nombre del primer archivo es: %s\n",primerArchivoDeLaListaDeArchivos->nombre);
	printf("En el %s hay: %d bloques\n",primerArchivoDeLaListaDeArchivos->nombre,list_size(primerArchivoDeLaListaDeArchivos->bloques));
	t_bloque* bloqueUnoDeArchivoUno=list_get(primerArchivoDeLaListaDeArchivos->bloques,0);
	printf("El primer bloque del %s, tiene su copia numero 2 en el %s bloque %d\n",primerArchivoDeLaListaDeArchivos->nombre,bloqueUnoDeArchivoUno->copias[1].nodo,bloqueUnoDeArchivoUno->copias[1].bloqueNodo);
	/*Fin del ejemplo de la estructura del FS*/
	return 0;
}
