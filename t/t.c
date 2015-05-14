#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <commons/collections/list.h>

typedef struct estructura_copia {
	char *nodo;
	uint32_t bloqueNodo;
} t_copias;

typedef struct estructura_bloque {
	t_copias copias[3];
} t_bloque;

typedef struct estructura_filesystem {
	char *nombre;
	uint32_t padre;
	uint32_t tamanio;
	uint32_t estado;
	t_list *bloques;
} t_archivo;

static t_archivo *archivo_create(char *name, uint32_t padre, uint32_t tam, uint32_t est) {
    t_archivo *new = malloc(sizeof(t_archivo));
    new->nombre = strdup(name);
    new->padre = padre;
    new->tamanio = tam;
    new->estado = 0;
    return new;
}

static t_bloque *bloques_create(char *nodo1, char *nodo2, char *nodo3, uint32_t bloque1, uint32_t bloque2, uint32_t bloque3) {
    t_bloque *new = malloc(sizeof(t_bloque));
    new->copias[0].nodo = strdup(nodo1);
    new->copias[1].nodo = strdup(nodo2);
    new->copias[2].nodo = strdup(nodo3);
    new->copias[0].bloqueNodo = bloque1;
    new->copias[1].bloqueNodo = bloque2;
    new->copias[2].bloqueNodo = bloque3;
    return new;
}

int main (void){

	t_list *list;
	t_archivo *tmp;
	t_bloque *tmp2;
	int tam,i,j,tam2;
	list = list_create();
	list_add(list, archivo_create("Temperaturas.txt", 2, 40, 1));
	tmp = list_get(list,0);
	tmp->bloques = list_create();
	list_add(tmp->bloques,bloques_create("nodo1", "nodo2", "nodo3", 21, 43, 11));
	list_add(tmp->bloques,bloques_create("nodo5", "nodo3", "nodo2", 23, 46, 42));
	list_add(tmp->bloques,bloques_create("nodo9", "nodo1", "nodo5", 1, 64, 32));
	list_add(list, archivo_create("Notas.txt", 1, 40, 1));
	tmp = list_get(list,1);
	tmp->bloques = list_create();
	list_add(tmp->bloques,bloques_create("nodo4", "nodo5", "nodo1", 51, 42, 31));
	list_add(tmp->bloques,bloques_create("nodo5", "nodo3", "nodo2", 22, 43, 44));
	tam = list_size(list);
	printf ("Cantidad de archivos de la lista: %d\n",tam);
	i=0;
	while (i<tam){
		tmp = list_get(list,i);
		printf ("\n\n");
		printf ("Archivo: %s,Padre: %d, Tamanio: %d, Estado: %d\n",tmp->nombre,tmp->padre, tmp->tamanio, tmp->estado);
		printf ("El archivo %s esta dividido en %d partes, se listan a continuacion:\n",tmp->nombre,list_size(tmp->bloques));
		j=0;
		tam2 = list_size(tmp->bloques);
		while (j<tam2){
			tmp2 = list_get(tmp->bloques,j);
			printf ("Copia %d de la parte %d en el nodo %s, en el bloque %d\n",j+1,j+1,tmp2->copias[0].nodo,tmp2->copias[0].bloqueNodo);
			printf ("Copia %d de la parte %d en el nodo %s, en el bloque %d\n",j+2,j+1,tmp2->copias[1].nodo,tmp2->copias[1].bloqueNodo);
			printf ("Copia %d de la parte %d en el nodo %s, en el bloque %d\n",j+3,j+1,tmp2->copias[2].nodo,tmp2->copias[2].bloqueNodo);
			j++;
		}
		i++;
	}
    return 0;
}
