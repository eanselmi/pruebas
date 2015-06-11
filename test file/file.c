#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <commons/collections/list.h>
#include <commons/log.h>
#include <commons/config.h>
#include <commons/string.h>
#include <commons/bitarray.h>

int main(){
	printf("Eligió Copiar un archivo local al MDFS\n");
    FILE * archivoLocal;
	char* path;
	path = string_new();
	char car;
	int i=0;
	int j=0;
	int k=0;
	int n=0;
	int pos;
	char cadena[100];
	memset(cadena,'\0',100);

	printf("Ingrese el path del archivo local \n");
    scanf("%s", path);
    //Validacion de si existe el archivo en el filesystem local
    if((archivoLocal = fopen(path,"r"))==NULL){
    	perror("fopen");
    	exit(1);
    }
    while ((car = fgetc(archivoLocal)) != EOF)
    {
    	i++;
    	k++;
    	cadena[i-1]=car;
    	if(car == '\n'){
    		pos=i-1;
    		n=k;
    	}
    	if(strlen(cadena) == 20){
    		if(car == '\n'){ //Caso Feliz

    			//Ordenar los bloques del archivo según el espacio disponible
    			//Copiar el contenido del Buffer en los bloques mas vacios por triplicado
    			//Vaciar el Buffer
    			printf ("Cadena FULL: %s\n",cadena);
    			pos = 0;
    			i=0;
    			memset(cadena,'\0',100);
    		}else{ //Caso en que el bloque no termina en "\n"
    			for(j=pos+1;j<100;j++) cadena[j]='\0';
    			printf ("Cadena Con Fragmentacion: %s\n",cadena);
    			pos = 0;
    			i=0;
    			fseek(archivoLocal,n,SEEK_SET);
    			k=n;
    			memset(cadena,'\0',100);
    			//Ordenar los bloques del archivo según el espacio disponible
    			//Copiar el contenido del Buffer en los bloques mas vacios por triplicado
    			//Vaciar el Buffer

    		}
    	}
    }
    /*for(j=pos+1;j<100;j++){
    	cadena[j]='\0';
    }*/


    fclose(archivoLocal);
    return 0;
}
