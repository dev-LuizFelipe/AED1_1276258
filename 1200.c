/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Luiz Felipe Gonzaga
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1200
Data        : 28/10/2026
Objetivo    : Mostrar a formatção de uma árvore binária infixa, prefixa e posfixamente em diferentes casos teste 
e verificar se um elemento está presente
Dificuldade : <<<Qual foi o principal desafio neste problema?>>>Formatar a saída corretamente e mudar as funções para char
(mudar as funções de inteiros para caracetres).
Uso de IA   : <<<Se usou, descreva brevemente o uso de IA na solução>>> IA usada para corrigir a formatação 
e arrumar eventuais bugs de caracteres. Somente via perguntas, sem mostrar a resposta.
-------------------------------------------------------------------------- */
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct no{
    char conteudo;
    struct no *esq;
    struct no *dir;
}Tno;

Tno *criar_no(char x);
void inserir(Tno *raiz, char x);
void limpar(Tno *r);
int buscar(Tno *r, char x);
void posfixa(Tno *r);
void prefixa(Tno *r);
void infixa(Tno *r);

int main(){
    char entrada[1000];
    char letra;
    Tno *raiz;
    raiz = NULL;
    while(scanf("%s",entrada) != EOF){
        if(strcmp(entrada,"I") == 0){ //comando de inserir letra
            if(raiz == NULL){
                scanf(" %c",&letra);
                raiz = criar_no(letra);
            } else{
                scanf(" %c",&letra);    
                inserir(raiz,letra);
            }
        }else if (strcmp(entrada,"P") == 0){ //comando de pesquisar se a letra está presente
            scanf(" %c",&letra);
            if(buscar(raiz, letra)){
                printf("%c existe\n", letra);
            }else{
                printf("%c nao existe\n", letra);
            }
        }else if (strcmp(entrada, "INFIXA") == 0) { //printar formatação
            infixa(raiz);
            printf("\n");
        } else if (strcmp(entrada, "PREFIXA") == 0) {
            prefixa(raiz);
            printf("\n");
        } else if (strcmp(entrada, "POSFIXA") == 0) {
            posfixa(raiz);
            printf("\n");
        }
    }
    limpar(raiz);
    return 0;
}


Tno *criar_no(char x){
    Tno *novo = malloc(sizeof(Tno));
    if(novo != NULL){
        novo->conteudo = x;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }
    return NULL;
}

void inserir(Tno *raiz, char x){
    if(x < raiz->conteudo && raiz->esq == NULL){
        raiz->esq = criar_no(x);
    }else if (x > raiz->conteudo && raiz->dir == NULL){
        raiz->dir = criar_no(x);
    }else{
        if(x < raiz->conteudo)inserir(raiz->esq, x);
        else inserir(raiz->dir, x);
    }
}

void limpar(Tno *r) {
    if (r != NULL) {
        limpar(r->esq);
        limpar(r->dir);
        free(r);
    }
}

int buscar(Tno *r, char x){ //busca binária em árvore
    if(r == NULL) return 0;
    if(r->conteudo == x) return 1;
    else if(r->conteudo > x) return buscar(r->esq, x);
    else  return buscar(r->dir, x);
}

void posfixa(Tno *r){
    if(r!=NULL){
        posfixa (r->esq);
        posfixa(r->dir);
        printf(" %c", r->conteudo);
    }
}

void prefixa(Tno *r){
    if(r!=NULL){
        printf(" %c", r->conteudo);
        prefixa (r->esq);
        prefixa(r->dir);
    }
}

void infixa(Tno *r){
    if(r!=NULL){
        infixa (r->esq);
        printf(" %c", r->conteudo);
        infixa(r->dir);
    }
}