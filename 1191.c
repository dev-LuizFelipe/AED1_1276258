#include <stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct no{
    char conteudo;
    struct no *esq;
    struct no *dir;
} Tno;

void limpar(Tno *r);
Tno *criar_no(int x);
Tno *reconstruir(char prefixa[], char infixa[], int inicio, int fim, int posiPrefixa);
void posfixa(Tno *r);

int main(){ 
    char prefixa[27]; // 27 pq são 26 letras do alfabeto + '\0'
    char infixa[27];
    Tno *aux;

    while(scanf("%s %s", prefixa, infixa) != EOF){
        aux = reconstruir(prefixa, infixa, 0, strlen(infixa) - 1 , 0);    
    }

    return 0;
}

Tno *reconstruir(char prefixa[], char infixa[], int inicio, int fim, int posiPrefixa){
    if(inicio > fim) return NULL;
    int i, qtd_esquerda;
    char val_raiz;
    Tno *novo;
    val_raiz = prefixa[posiPrefixa];

    for(i=inicio; i<=fim && infixa[i] != val_raiz; i++);
    qtd_esquerda = i-inicio;

    novo = criar_no(val_raiz);
    novo->esq = reconstruir(prefixa, infixa, inicio, i-1, posiPrefixa + 1);
    novo->dir = reconstruir(prefixa, infixa, i + 1, fim, posiPrefixa + qtd_esquerda + 1);
    return novo;
}

Tno *criar_no (int x){
    Tno *novo = malloc(sizeof(Tno));
    if(novo == NULL) return NULL;
    novo->conteudo = x;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

void posfixa(Tno *r){
    if (r == NULL) return;
    posfixa(r->esq);
    posfixa(r->dir);
    printf("%c", r->conteudo);
}