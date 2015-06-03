#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdint.h>
#include <string.h>

int main (int argc, char**argv){

	int fd[2];
	int childpid;
	pipe(fd);
	char result[1000];
	if (argc!=2){
		printf ("Cantidad de argumentos insuficientes\n");
		exit(-1);
	}
	memset(result,'\0',1000);
	if ( (childpid = fork() ) == -1){
		fprintf(stderr, "FORK failed");
	} else if( childpid == 0) {
		close(1);
		dup2(fd[1], 1);
		close(fd[0]);
		execlp("/usr/bin/md5sum","md5sum",argv[1],NULL);
	}
	wait(NULL);
	read(fd[0], result, sizeof(result));
	printf("%s",result);
	return 0;
}
