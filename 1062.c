/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Luiz Felipe Gonzaga
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1062
Data        : 30/09/2026
Objetivo    : Verificar se uma sequência pode ser escrita através de pop/push de uma pilha 
Dificuldade : <<<Qual foi o principal desafio neste problema?>>> Distinguir dois valores que pareciam a mesma coisa: o N (quantidade
              de vagões do bloco) e o primeiro valor de cada permutação (usado só para testar se a linha é 0, indicando fim do bloco).
              Isso exigiu o padrão de "ler antes para decidir, e repassar esse valor já lido" em vez de simplesmente descartá-lo. 
Uso de IA   : <<<Se usou, descreva brevemente o uso de IA na solução>>> Me ajudou a interpretar o enunciado, a fazer os testes de mesa
                e debugar, através de perguntas e sem me mostrar o código pronto.
-------------------------------------------------------------------------- */
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct no{
    int conteudo;
    struct no *prox;
} Tno;

void empilhar(int y, Tno *head);
int desempilhar(Tno *head);
void limpar(Tno *head);
int topo(Tno *head);
int verificar (Tno *head, int n, int primeiro);

int main (){
    int N, primeiroValor, i;
    Tno *head;
    head = malloc(sizeof(Tno));
    head->prox = NULL;
    while(scanf("%d",&N) != EOF){
        if(N == 0) break; // problema fala que deve parar de ler caso seja N = 0;
        scanf("%d",&primeiroValor); // le o primeiro valor da permutação
        while(primeiroValor!=0){ // processa permutações enquanto primeiroValor não for 0
            if(verificar(head,N,primeiroValor)){
                printf("Yes\n"); // a sequência pode ser obtida usando a pilha
            }else{
                printf("No\n"); // a sequência não pode ser obtida usando a pilha, topo foi diferente do que o esperado para imprimir
            } 
            limpar(head);
            scanf("%d",&primeiroValor); // lê o primeiro valor da próxima permutação
        }
        printf("\n");
        
    }
    return 0;
}

void empilhar(int y, Tno *head){
    Tno *novo;
    novo = malloc(sizeof(Tno));
    novo->conteudo = y;
    novo->prox = head->prox;
    head->prox = novo;
}

int desempilhar(Tno *head){
    if (head->prox == NULL) return 0; //pilha vazia
    else{
        Tno *lixo;
        int x;
        lixo = head->prox;
        x = lixo->conteudo;
        head->prox = lixo->prox;
        free(lixo);
        return x;
    }       
}

void limpar (Tno *head){
    Tno *p; //novo ponto
    Tno *aux;
    p = head->prox; // novo ponto recebe nó que a cabeça aponta
    while (p != NULL){
        aux = p->prox; // auxiliar salva o nó que p aponta
        free(p); // apago o ponto
        p = aux; // ponto recebe quem aux tinha salvado 
    }
    head->prox = NULL;
}

int topo(Tno *head){
    if(head->prox == NULL) return 0;
    else{
        return head->prox->conteudo;
    }
}

int verificar (Tno *head, int n, int primeiro){
    int proximo, possivel, i, desejado;
    proximo = possivel = 1;
    for(i=0; i<n; i++){
        if(i == 0) desejado = primeiro;
        else scanf("%d",&desejado); // le o próximo valor da permutação desejada
        if(possivel){ // só continua rodando o for se possivel for verdadeiro 
            while (topo(head)!=desejado && proximo<=n){ //enquanto o topo não for o número desejado ou esgotar os vagoes, eu empilho próximo vagão 
            empilhar(proximo, head);
            proximo++;

            }
            if(topo(head) == desejado) desempilhar(head); //se o topo da pilha for o desejado, eu tiro ele da pilha
            else possivel = 0; // se não der para tirar ele da pilha, impossível
        }
    }
    return possivel;
}