#include <stdlib.h>
#include <stdio.h>
#include "conjunto.h"

struct Noh {
    void (*imp)(void*);
	void* elemento;
    struct Noh* proximo;    // ponteiro para o seguinte na lista
    struct Noh* anterior;   // ponteiro para o anterior na lista
};
typedef struct Noh Noh;

struct Conjunto {
    
	Noh* cabeca;    // endereco do primeiro elemento do noh
};

Conjunto* inicializa(void) {
    
	Conjunto* l = (Conjunto*) malloc(sizeof(Conjunto));
    l->cabeca = NULL;
    return l;
}

void finaliza(Conjunto* l) {
    
	if (l == NULL) {
        return;
    }
    while (!vazio(l)) {
        remover_cabeca(l);
    }
    free(l);
}

bool vazio(const Conjunto* l) {
    
	return l == NULL || l->cabeca == NULL;
}

void imprime(const Conjunto* l) {
    
	if (vazio(l)) {
        printf("(Vazio)");
        return;
    }
    printf("\n{ CABECA, ");
    Noh* i = l->cabeca;
    while (i != NULL) {
        i->imp(i->elemento);
        i = i->proximo;
    }
    printf("CAUDA }");
    printf("\n{ CABECA, ");
    i = l->cabeca;
    while (i->proximo != NULL) {    // percorre a lista
        i = i->proximo;
    }
    do {
        i->imp(i->elemento);
        i = i->anterior;
    } while (i != NULL);
    printf("CAUDA }");
}

bool pertence(const Conjunto* l, void* x,bool (*compara)(void*, void*)) {
    
	if (vazio(l)) {
        return false;
    }
    Noh* i = l->cabeca;
    while (i != NULL) {  						// enquanto nao chega ao fim da lista...
        if(compara(i->elemento,x)==1) {
            return true;						// elemento pertence a lista 	
        }
        i = i->proximo;
    }
    return false;          		    // nao pertence
}

void adiciona(Conjunto* l,void* r, void (*imprime)(void*)) {
    
	if (l == NULL) {
        return;
    }
    Noh* n = (Noh*) malloc(sizeof(Noh));
    n->imp=imprime;
	n->elemento = r;
    n->proximo = NULL;
    if (l->cabeca == NULL) {    
        l->cabeca = n;
        n->anterior = NULL; 		// novo ultimo noh eh tambem o novo primeiro
        return;
    }
    Noh* i = l->cabeca;
    while (i->proximo != NULL) {    // percorre a lista 
        i = i->proximo;
    }
    								
    i->proximo = n;
    n->anterior = i;    			// o novo ultimo aponta para o antigo ultimo como anterior
}



void retirar(Conjunto* l, void* x,bool (*compara)(void*, void*)) {
	
    if (vazio(l)) {
        return ;
    } 
    Noh* n = l->cabeca;
    while(n!= NULL){
    if (compara(n->elemento,x)==1) {
    	if ((n->anterior == NULL)&&(n->proximo == NULL)) {  						//Tira o unico elemento do conjunto 
       		l->cabeca = NULL;   
		} 
		else if (n->anterior == NULL) {												//Tira o primeiro elemento do conjunto 
     		l->cabeca = n->proximo;   
      		n->proximo->anterior = NULL;
    	}
		else if(n->proximo == NULL){												//Tira o ultimo elemento do conjunto 
			n->anterior->proximo=NULL;
		} 
		else {																		//Tira o elemento do meio do conjunto 
      		n->anterior->proximo = n->proximo ;
       		n->proximo->anterior = n->anterior;
    	}	
	}
	n=n->proximo;
	}

	free(n);	
}
void retira_repetidos(Conjunto* C){
	int i, cont=1;
	Noh* n = (Noh*) malloc(sizeof(Noh));
	Noh* aux = (Noh*) malloc(sizeof(Noh));
    n=C->cabeca->proximo;
	while(n!=NULL){
		aux = C->cabeca;
		for(i=0; i<cont; i++){
			if(n->elemento == aux->elemento){
				if (aux->anterior == NULL) {												// se o primeiro elemento for o repetido  
     				C->cabeca = aux->proximo;   
      				aux->proximo->anterior = NULL;
    			}
				else if(aux->proximo == NULL){												// se o ultimo elemento for o repetido 
					aux->anterior->proximo=NULL;
				} 
				else {																		// se o elemento repetido estiver no meio da lista 
      			aux->anterior->proximo = aux->proximo ;
       			aux->proximo->anterior = aux->anterior;
				}
			cont-=2;
			}
			aux=aux->proximo;					
		}	
		++cont;
		n=n->proximo;
	}
	free(n);

}

Conjunto* uniao(const Conjunto* A,const Conjunto* B){

	Conjunto* aux = inicializa();
	if (vazio(A)&&vazio(B)){					// Se os dois conjuntos forem vazios, retorna uma lista vazia
		return aux;
	}
	else if(vazio(A)){							// Se o primeiro conjunto for vazio
		Noh* n = B->cabeca;
		while(n!= NULL){
			adiciona(aux,n->elemento,n->imp);	
			n=n->proximo;				
		}
		free(n);
		return aux;
	}
	else if(vazio(B)){							// Se o segundo conjunto for vazio
		Noh* n = A->cabeca;
		while(n!= NULL){
			adiciona(aux,n->elemento,n->imp);
			n=n->proximo;			
		}
		free(n);
		return aux;
	}else{
		Noh* n = B->cabeca;
		Noh* l = A->cabeca;
		while(l!= NULL){
			adiciona(aux,l->elemento,l->imp);
			l=l->proximo;					
		}
		while(n!= NULL){
			adiciona(aux,n->elemento,n->imp);
			n=n->proximo;					
		}
		free(n);
		free(l);
		
    	retira_repetidos(aux);
		return aux;
	}
}

Conjunto* interseccao(const Conjunto* A,const Conjunto* B){	// elementos repetido dos conjuntos

	Conjunto* C = inicializa();					
	Noh* a = (Noh*) malloc(sizeof(Noh));
	Noh* b = (Noh*) malloc(sizeof(Noh));
	a=A->cabeca;

	while(a!=NULL){
		b=B->cabeca;
		while(b!=NULL){
			if(a->elemento==b->elemento){
				adiciona(C,b->elemento,b->imp);
			}
			b=b->proximo;
		}
		a=a->proximo;		
	}
    free(a);
    free(b);
	
	return C;
}


Conjunto* diferenca(const Conjunto* A,const Conjunto* B){   // A-B
	
	Conjunto* C = inicializa();
	Noh* a = (Noh*) malloc(sizeof(Noh));
	Noh* b = (Noh*) malloc(sizeof(Noh));
	int c;
	a=A->cabeca;
	while(a!=NULL){
		b=B->cabeca;
		c=0;
		while(b!=NULL){
			if(a->elemento==b->elemento){
				c=1;
			}
			b=b->proximo;		
		}
		if((b==NULL)&&(c==0)){
				adiciona(C,a->elemento,a->imp);
			}
		a=a->proximo;
	}
    free(a);
    free(b);
	
	return C;
}


Conjunto* diferenca_simetrica(const Conjunto* A,const Conjunto* B){   //(A-B)+(B-A)
	
	Conjunto* AUX = diferenca(A,B);
	Conjunto* AUX2 = diferenca(B,A);
	Conjunto* C=uniao(AUX,AUX2);
	
	return C;
}

Conjunto* produto_cartesiano(const Conjunto* A, const Conjunto* B){
	Conjunto* C = inicializa();
	Noh* a = (Noh*) malloc(sizeof(Noh));
	Noh* b = (Noh*) malloc(sizeof(Noh));
	a=A->cabeca;
	while(a!=NULL){
		b=B->cabeca;
		while(b!=NULL){
				adiciona(C,a->elemento,a->imp);
				adiciona(C,b->elemento,b->imp);
			b=b->proximo;
		}
		a=a->proximo;		
	}
	free(a);
    free(b);
	
	return C;
}

bool igual(const Conjunto* A, const Conjunto* B){
	Noh* a = (Noh*) malloc(sizeof(Noh));
	Noh* b = (Noh*) malloc(sizeof(Noh));
/*	a=A->cabeca;
	b=B->cabeca;
	int igual=0;
	while(igual == 0 && a!=NULL && b!=NULL){
		if (a->elemento == b->elemento){
			igual = 0;
			a=a->proximo;
			b=b->proximo;
		}
		else{
			igual = 1;
		}		
	}
	if(a!=NULL || b!=NULL){
		igual=1;
	}
	if(igual==0){
		return true;
	}else{
		return false;
	}*/
	int i=0, cont=0;
	a=A->cabeca;
	while(a!=NULL){
		cont++;
		a=a->proximo;		
	}
	a=A->cabeca;
	while(a!=NULL){
		b=B->cabeca;
		while(b!=NULL){
			if (a->elemento == b->elemento){
					i++;
			}
			b=b->proximo;	
		}
		a=a->proximo;		
	}
	if(a==NULL || b==NULL){
		if(cont==i){
			return true;
		}else
			return false;
	}
	
}

bool contido(const Conjunto* A, const Conjunto* B){

	Noh* a = (Noh*) malloc(sizeof(Noh));
	Noh* b = (Noh*) malloc(sizeof(Noh));
	int i=0, cont=0;
	a=A->cabeca;
	while(a!=NULL){
		cont++;
		a=a->proximo;		
	}
	b=B->cabeca;
	while(b!=NULL){
		a=A->cabeca;
		while(a!=NULL){
			if (a->elemento == b->elemento){
					i++;
			}
			a=a->proximo;	
		}
		b=b->proximo;		
	}
	free(a);
    free(b);
	if(cont==i){
		return true;
	}else{
		return false;
	}
}

bool contem(const Conjunto* A, const Conjunto* B){

	Noh* a = (Noh*) malloc(sizeof(Noh));
	Noh* b = (Noh*) malloc(sizeof(Noh));
	int i=0, cont=0;
	b=B->cabeca;
	while(b!=NULL){
		cont++;
		b=b->proximo;		
	}
	a=A->cabeca;
	while(a!=NULL){
		b=B->cabeca;
		while(b!=NULL){
			if (a->elemento == b->elemento){
					i++;
			}
			b=b->proximo;	
		}
		a=a->proximo;		
	}
	free(a);
    free(b);
	if(cont==i){
		return true;
	}else{
		return false;
	}
}

bool proprio(const Conjunto* A, const Conjunto* B){			// A contem B mais nao eh igual a B

	Noh* a = (Noh*) malloc(sizeof(Noh));
	Noh* b = (Noh*) malloc(sizeof(Noh));
	int i=0, cont=0;
	a=A->cabeca;
	while(a!=NULL){
		cont++;
		a=a->proximo;		
	}
	a=A->cabeca;
	while(a!=NULL){
		b=B->cabeca;
		while(b!=NULL){
			if (a->elemento == b->elemento){
					i++;
			}
			b=b->proximo;	
		}
		a=a->proximo;		
	}
	free(a);
    free(b);
	if(cont==i){									
		if(igual(A,B)==1){
			return false;
		}else{
			return true;
		}
		
	}else{
		return false;
	}
}


int remover_cabeca(Conjunto* l) {
    
	if (vazio(l)) {
        int vazio = { 0 };
        return vazio;
    }
    Noh* x = l->cabeca;
    l->cabeca = x->proximo;
    if (l->cabeca != NULL) {    // existia um segundo que se tornou o primeiro?
        l->cabeca->anterior = NULL;
    }
    void *r = x->elemento;
    free(x);
    return 0;
}


