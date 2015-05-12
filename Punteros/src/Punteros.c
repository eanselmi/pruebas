#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (void){
	int a=10; //Supongamos que es una variable cuya direccion es 0x1601
	int *puntero1; //El puntero tiene guardada la direccion de a,
	                  //pero este tiene como direccion 0x1890
	int **puntero2; //**puntero 2 guarda la direccion 0x1890
	puntero1=&a;
	puntero2=&puntero1;
	printf ("%d, %d",*puntero1,**puntero2);
	return 0;
}
