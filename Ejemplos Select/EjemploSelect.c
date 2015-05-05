#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define STDIN 0

int main (void){

	struct timeval tv;
	fd_set readfds;
	tv.tv_sec = 2;
	tv.tv_usec = 500000;
	FD_ZERO (&readfds);
	FD_SET (STDIN, &readfds);
	select (STDIN+1, &readfds, NULL, NULL, &tv);
	if (FD_ISSET(STDIN, &readfds))
		printf ("Apretaron una tecla\n");
	else
		printf ("Timeout\n");
	return 0;
}
