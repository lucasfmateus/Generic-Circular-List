#ifndef TAD_CONJUNTO_VOID_H
#define TAD_CONJUNTO_VOID_H

#include <stdbool.h>




struct Conjunto;
typedef struct Conjunto Conjunto;

Conjunto* inicializa(void);
void finaliza(Conjunto* l);
void adiciona(Conjunto* l,void* r,void (*imprime)(void*));
void retirar(Conjunto* l, void* x,bool (*compara)(void*, void*));
void retira_repetidos(Conjunto* C);
void imprime(const Conjunto* l);
bool pertence(const Conjunto* l, void* x,bool (*compara)(void*, void*));
bool vazio(const Conjunto* l);
bool contido(const Conjunto* A, const Conjunto* B);
bool contem(const Conjunto* A, const Conjunto* B);
bool proprio(const Conjunto* A, const Conjunto* B);
bool igual(const Conjunto* A, const Conjunto* B); 
Conjunto* uniao(const Conjunto* A,const Conjunto* B);
Conjunto* interseccao(const Conjunto* A,const Conjunto* B);
Conjunto* diferenca(const Conjunto* A,const Conjunto* B);
Conjunto* diferenca_simetrica(const Conjunto* A,const Conjunto* B);
Conjunto* produto_cartesiano(const Conjunto* A, const Conjunto* B);






int remover_cabeca(Conjunto* l);
#endif
