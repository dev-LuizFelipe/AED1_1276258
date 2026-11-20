/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Luiz Felipe Gonzaga
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1191
Data        : 20/11/2026
Objetivo    : Receber textos no formato infixo e prefixo e devolver o texto no formato posfixo.
Dificuldade : <<<Qual foi o principal desafio neste problema?>>> Reconstruir a árvore a partir dos percursos prefixo e infixo.
Uso de IA   : <<<Se usou, descreva brevemente o uso de IA na solução>>> IA usada para identificar erros nos índices da reconstrução da árvore
por recursão. Não forneceu código pronto, apenas apontou erros e me questionou sobre eles
-------------------------------------------------------------------------- */
#include <stdio.h>
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
        aux = reconstruir(prefixa, infixa, 0, strlen(infixa) - 1 , 0); //inicio = 0, fim = tam da string-1, posição da prefixa=0
        posfixa(aux); //printar
        printf("\n");
        limpar(aux);// da free nessa árvore para reconstruir a próxima   
    }

    return 0;
}

Tno *reconstruir(char prefixa[], char infixa[], int inicio, int fim, int posiPrefixa){
    if(inicio > fim) return NULL;
    int i, qtd_esquerda;
    char val_raiz;
    Tno *novo;
    val_raiz = prefixa[posiPrefixa]; //valor da raiz obtido pela posicao 0 da prefixa (na prefixa a raiz é prefixa[0])

    for(i=inicio; i<=fim && infixa[i] != val_raiz; i++); //acha onde o valor da raiz está na prefixa
    qtd_esquerda = i-inicio; // conta quantos "nós" tem a esquerda da raiz

    novo = criar_no(val_raiz); 

    //i-1 como fim, pois queremos só os valores da esquerda(todos antes de i). posiPrefixa + 1, pois o próximo dele já a "subraiz esquerda"
    novo->esq = reconstruir(prefixa, infixa, inicio, i-1, posiPrefixa + 1); 

    //i+1, pois após o val_raiz (i) são os valores da direita. para achar a posiPrefixa da direita temos que pular todos da esquerda (qtd + 1)
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

void limpar(Tno *r){
    if(r == NULL) return;
    Tno *aux;
    limpar(r->esq);
    limpar(r->dir);
    free(r);
}
