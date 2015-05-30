#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdint.h>
#include <string.h>


void ejecutarScript(char *script,char *argumento);

int main (void){
	char script[20];
	char argumento[20];
	printf ("Ingrese el nombre del script: ");
	scanf ("%s",script);
	printf ("\n\nIngrese argumento para el script: ");
	scanf ("%s",argumento);
	ejecutarScript(script,argumento);
	return 0;
}

void ejecutarScript(char *script,char *argumento){
	int fd[2];
	FILE* archivo_resultado;
	archivo_resultado=fopen("/tmp/resultado","a");
	int childpid;
	pipe(fd);
	char result[100];
	char path[100];
	memset(result,'\0',100);
	memset(path,'\0',100);
	strcat(path,"/tmp/");
	strcat(path,script);
	if ( (childpid = fork() ) == -1){
	   fprintf(stderr, "FORK failed");

	} else if( childpid == 0) {
	   close(1);
	   dup2(fd[1], 1);
	   close(fd[0]);
	   execlp(path,script,argumento,NULL);
	}
	wait(NULL);
	read(fd[0], result, sizeof(result));
	fprintf(archivo_resultado,"%s",result);
	fclose(archivo_resultado);

}
