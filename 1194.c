/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Luiz Felipe Gonzaga
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1194
Data        : 22/10/2026
Objetivo    : Receber textos no formato infixo e prefixo e devolver o texto no formato posfixo.
Dificuldade : <<<Qual foi o principal desafio neste problema?>>> A dificuldade maior foi sobre organizar os parâmetros recebidos para 
fazer a função reconstruir funcionar corretamente. Obs: eu fiz esse antes do 1195 que é base para este, descobri depois. 
Uso de IA   : <<<Se usou, descreva brevemente o uso de IA na solução>>> IA usada para orientar a reconstrução da árvore binária 
usando os recursos de prefixo e infixo, identificando erros e compreender os índices utilizados a partir de perguntas direcionadas para me fazer
revisar meu próprio código. Não forneceu a solução
-------------------------------------------------------------------------- */
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct no{
    char conteudo;
    struct no *esq;
    struct no *dir;
} Tno;

Tno *reconstruir(char prefixa[], char infixa[],int inicio, int fim, int posPrefixa);
void edr(Tno *r);
void limpar(Tno *r);

int main(){
    char prefixa[53]; char infixa[53];
    int c, casos, n;
    c=0;
    Tno *aux;
    scanf("%d", &casos);
    while(c != casos){
        scanf("%d %s %s", &n, prefixa, infixa);
        aux = reconstruir(prefixa, infixa, 0, n-1, 0);
        edr(aux);
        printf("\n");
        limpar(aux);
        c++;
    }
    return 0;
}

void edr(Tno *r){
    if(r!=NULL){
        edr (r->esq);
        edr(r->dir);
        printf("%c", r->conteudo); //ordem de print : esquerda, direita, raiz
    }
}


Tno *reconstruir(char prefixa[], char infixa[],int inicio, int fim, int posPrefixa){
    if (inicio > fim) return NULL;
    
    int i, qtd_esq;
    char raiz = prefixa[posPrefixa]; // raiz para a nova formatação recebe a raiz original (prefixa na posição da prefixa)
    
    for (i = inicio; i<= fim && infixa[i] != raiz; i++); // acha qual letra é a raiz
    
    qtd_esq = i - inicio; // quantidade de nós na sub esquerda
    Tno *novo = malloc(sizeof(Tno));
    
    if(novo == NULL) return NULL;
    novo->conteudo = raiz;
    novo->esq = reconstruir(prefixa, infixa, inicio, i-1, posPrefixa +1); //preenche na esquerda
    novo->dir = reconstruir(prefixa, infixa, i+1, fim, posPrefixa + qtd_esq + 1); //preenche na direita  
    return novo;
}
void limpar(Tno *r) {
    if (r != NULL) {
        limpar(r->esq);
        limpar(r->dir);
        free(r);
    }
}
