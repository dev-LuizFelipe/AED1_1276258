/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Luiz Felipe Gonzaga
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1195
Data        : 24/10/2026
Objetivo    : Mostrar a formatção de uma árvore binária infixa, prefixa e posfixamente em diferentes casos teste.
Dificuldade : <<<Qual foi o principal desafio neste problema?>>> A dificuldade foi formatar a saída corretamente e um else mal ligado em 
inserir que causou um segmentation fault. 
Uso de IA   : <<<Se usou, descreva brevemente o uso de IA na solução>>> IA usada para corrigir a formatação e achar o segmentation fault.
Somente via perguntas, sem mostrar a resposta.
-------------------------------------------------------------------------- */
#include <stdio.h>
#include<stdlib.h>
typedef struct no{
    int conteudo;
    struct no *esq;
    struct no *dir;
} Tno;

void posfixa(Tno *r);
void prefixa(Tno *r);
void infixa(Tno *r);
void inserir(Tno *raiz, int x);
Tno *criar_no(int x);
void limpar(Tno *r);

int main(){
    int c,casos, n;
    c=0;
    Tno *raiz;
    scanf("%d",&casos);
    while(c != casos){
        scanf("%d",&n);
        int v[n];

        for(int i=0; i<n; i++){
            scanf("%d",&v[i]);
        }
        raiz = criar_no(v[0]);

        for (int j=1; j<n; j++){
            inserir(raiz,v[j]);
        }
        printf("Case %d:", c+1);
        printf("\n");
        printf("Pre.:");
        prefixa(raiz);
        printf("\n"); 
        printf("In..:");
        infixa(raiz);
        printf("\n");
        printf("Post:");
        posfixa(raiz);
        printf("\n\n");
        limpar(raiz);
        c++;
    }

    return 0;
}

void posfixa(Tno *r){
    if(r!=NULL){
        posfixa (r->esq);
        posfixa(r->dir);
        printf(" %d", r->conteudo);
    }
}

void prefixa(Tno *r){
    if(r!=NULL){
        printf(" %d", r->conteudo);
        prefixa (r->esq);
        prefixa(r->dir);
    }
}

void infixa(Tno *r){
    if(r!=NULL){
        infixa (r->esq);
        printf(" %d", r->conteudo);
        infixa(r->dir);
    }
}

void inserir(Tno *raiz, int x){
    if(x < raiz->conteudo && raiz->esq == NULL){ //lembrete: a esquerda do nó é sempre menor que ele, já a direita é sempre maior
        raiz->esq = criar_no(x);
    }
    else if(x > raiz->conteudo && raiz->dir == NULL){
        raiz->dir = criar_no(x);
    } else{
        if(x < raiz->conteudo) inserir(raiz->esq, x);//aqui que ele vai pulando caso já tenha nós na esquerda ex: 5-3-2, pulou o 3 e colocou o 2 a esquerda dele
        else inserir(raiz->dir, x); //mesma coisa que na esquerda só que com valores maiores indo para a direita.
    }
}

Tno *criar_no(int x){
    Tno *novo = malloc(sizeof(Tno));
    if(novo != NULL){
        novo->conteudo = x;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }
    return NULL;
}

void limpar(Tno *r) {
    if (r != NULL) {
        limpar(r->esq);
        limpar(r->dir);
        free(r);
    }
}
