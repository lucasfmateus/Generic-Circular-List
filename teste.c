#include <stdlib.h>
#include <stdio.h>
#include "tad_conjunto_void.h"
#include "impl_conjunto_void.c"


void imp_int(void*c){
	printf("%d, ", *(int*) c);
}
void imp_char(void*c){
	printf("%c, ", *(char*) c);
}
void imp_float(void*c){
	printf("%.1f, ", *(float*) c);
}
void imp_string(void*c){
	printf("%s, ",(char*) c);
}
bool compara(void* a, void*b){
	if(a==b){
		return true;
	}else
		return false;
}



int main(void) {
    
	Conjunto* A = inicializa();
    Conjunto* B = inicializa();

	
	int a= 1;
	char b='a';
	float c=1.1;
	
	void* r;
	void* l;
	
	r=&b;
	l=&a;
	adiciona(A,r,imp_char);	
	adiciona(A,l,imp_int);
	r=&a;
	l=&b;
	adiciona(B,r,imp_int);	
	adiciona(B,l,imp_char);	
	
	r=&c;
	adiciona(B,r,imp_float);
	
	printf("Conjunto: A "); imprime(A); puts("\n"); 
	printf("Conjunto: B "); imprime(B); puts("\n"); 
	
		printf("A eh igual C:");
	if(igual(A,B)==1){
   		printf("\t\tIgual\n");
    }else{
   		printf("\t\tNao eh Igual\n");
    }
}
