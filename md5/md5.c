#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include </usr/src/linux-headers-3.13.0-45-generic/include/config/crypto/md5.h>
#define MD5_DIGEST_LENGTH 16

int main(int argc , char *argv[]){
  int i;
  char leer[500000];
  memset(leer,'\0',500000);
  FILE *archivo;
  unsigned char result[MD5_DIGEST_LENGTH];

  if ((archivo = fopen(argv[1],"r")) == NULL){
	  puts("");
	  puts("Error en Fopen");
	  puts("");
	  exit(1);
  }
  if (fread(&leer,sizeof(char),sizeof(leer), archivo) == 0){
	puts("");
	perror("Error en Fread");
	puts("");
	fclose(archivo);
  	exit(1);
  }

  MD5(leer, strlen(leer), result);

  for(i = 0; i < MD5_DIGEST_LENGTH; i++)
    printf("%02x", result[i]);
  printf("\n");

  return EXIT_SUCCESS;
}
