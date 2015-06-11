#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

int main (int argc, char**argv){
	int count,bak0,bak1;
	char *cadena="Hola";
	printf ("La cadena %s mide %d\n\n",cadena,strlen(cadena));
	int fd[2];
	int md[2];
	int childpid;
	pipe(fd);
	pipe(md);
	char result[50];
	memset(result,'\0',50);
	if ( (childpid = fork() ) == -1){
		fprintf(stderr, "FORK failed");
	} else if( childpid == 0) {
		bak0=dup(0);
		bak1=dup(1);
		dup2(fd[0],0);
		dup2(md[1],1);
		close(fd[1]);
		close(fd[0]);
		close(md[1]);
		close(md[0]);
		execlp("/usr/bin/md5sum","md5sum",NULL);
	}
	write(fd[1],cadena,strlen(cadena));
    close(fd[1]);
	close(fd[0]);
	close(md[1]);
	count=read(md[0],result,36);
	close(md[0]);
	dup2(bak0,0);
	dup2(bak1,1);
	if (count>0){
		result[32]=0;
		printf("%s",result);
	}else{
		printf ("ERROR READ RESULT\n");
		exit(-1);
	}
	return 0;
}



