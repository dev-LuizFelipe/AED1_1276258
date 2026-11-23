/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Luiz Felipe Gonzaga
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1076
Data        : 23/11/2026
Objetivo    : Calcular a quantidade mínima de movimentos de caneta para desenhar um labirinto (grafo sem ciclos) começando e
terminando no mesmo nó, sem levantar a caneta.
Dificuldade : <<<Qual foi o principal desafio neste problema?>>> Entender que sem o ciclo, cada aresta precisa ser percorrida duas vezes
(ida e volta) e que a resposta disso é a soma dos graus dos vértices.
Uso de IA   : <<<Se usou, descreva brevemente o uso de IA na solução>>> IA usada para entender melhor o objetivo do problema e 
o conceito de graus 
Não forneceu código pronto, correção feita via perguntas.
-------------------------------------------------------------------------- */
#include <stdio.h>
#define MAX 49

void zerar(int m[][MAX]);
void inserir(int m[][MAX], int u, int v);
int grau(int m[][MAX], int u, int n);
//int existe(int m[][MAX], int u, int v);
//void remover(int m[][MAX], int u, int v);

int main(){
    int T, t, n, v, a, i, x, w;
    int m[MAX][MAX];
    int soma;
    t=0;
    scanf("%d",&T);

    while(t != T){
        zerar(m);
        soma=0;
        scanf("%d",&n);
        scanf("%d %d",&v, &a); //le quantos vertices e quantas arestas
        for(int l =0; l<a; l++){
            scanf("%d %d", &x, &w);
            inserir(m, x, w);//insere os dois extremos de uma aresta na matriz
        }

        for(i=0; i<v; i++){
           soma+= grau(m, i, v); //soma da quantidade de movimentos (quantidade de arestar * 2, neste exercicio)
        }
        printf("%d\n",soma);
        t++;
    }

    return 0;
}

void zerar(int m[][MAX]){
    int i;
    for(i=0; i<MAX; i++){
        for(int j=0; j<MAX; j++){
            m[i][j] = 0;
        }
    }
}

void inserir(int m[][MAX], int u, int v){
    m[u][v] = 1;
    m[v][u] = 1;
}

int grau(int m[][MAX], int u, int n){ //ligações que esse vertice faz ("conta quantos vizinhos ele tem"), ou seja, quantas arestas saem dele
    int j, qtd;
    qtd=0;
    for(j=0; j<n; j++){
       if(m[u][j] != 0) qtd++;
    }
    return qtd;
}