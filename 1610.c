/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Luiz Felipe Gonzaga
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1610
Data        : 18/11/2026
Objetivo    : Verificar se existe um looping entre documentos (grafos dirigidos) e printar SIM/NAO conforme o caso
Dificuldade : <<<Qual foi o principal desafio neste problema?>>> Implementar o dfs para um grafo "em forma de lista" 
e que o estado 0/1 não é o suficiente para grafos dirigidos
Uso de IA   : <<<Se usou, descreva brevemente o uso de IA na solução>>> IA usada para entender melhor como montar o grafo em forma de lista,
além de apontar erros no decorrer do código (aninhemento de loopings e vértice de partida do DFS).
Não forneceu código pronto, correção feita via perguntas e apontamentos.
-------------------------------------------------------------------------- */
#include <stdio.h>
#include<stdlib.h>

typedef struct no{
    int conteudo;
    struct no *prox;
} Tno;

typedef struct Tgrafo{
    int n;              // quantidade de vértices do caso
    Tno *adj[10001];    // lista de vizinhos de cada vértice (adjacente)
}Tgrafo;

void inserir(Tgrafo *g, int u, int v);
void iniciar(Tgrafo *g, int v);
void limpar(Tgrafo *g);
int dfs(Tgrafo *g, int u, int estado[]);

int main(){
    int t, T, n, m, a, b, i;
    scanf("%d",&T);
    Tgrafo grafo;
    t=0;

    while(t != T){
        int achou =0;
        scanf("%d %d", &n, &m);
        int estado[n+1];
        for(int f=0; f<=n; f++) estado[f] = 0; //zera o vetor de estados
        iniciar(&grafo, n); //zera o conteudo dos grafos
        
        for(int j =0; j<m; j++){
            scanf("%d %d", &a, &b); // le os documentos
            inserir(&grafo, a, b);
        }

        for(i =1; i<=n; i++){
                if(estado[i] == 0 && dfs(&grafo, i, estado)){ //achou looping
                    achou = 1; 
                    break;
                }
            }

        if(achou){
            printf("SIM\n");
        }else printf("NAO\n");

        limpar(&grafo);
        t++;
    }

    return 0;
}


void inserir(Tgrafo *g, int u, int v){
    Tno *novo = malloc(sizeof(Tno));
    if(novo == NULL) return;
    novo->conteudo = v;
    novo->prox = g->adj[u]; //recebe o próximo nó da lista
    g->adj[u] = novo;
}

void iniciar(Tgrafo *g, int n){
    int i;
    for (i=0; i<=n; i++) g->adj[i] = NULL; 
    g->n = n;
}

void limpar(Tgrafo *g){
    Tno *atual, *prox;
    int i;
    for (i=1; i<=g->n; i++){
        atual = g->adj[i];
        while(atual != NULL){
            prox = atual->prox;
            free(atual);
            atual = prox;
        }
        g->adj[i] = NULL;
    }    
}

int dfs(Tgrafo *g, int u, int estado[]){
    estado[u] = 1; // em exploração (1)
    Tno *atual;
    int v;
    atual = g->adj[u]; //começa pelo primeiro vizinho de u
    while(atual != NULL){
        v = atual->conteudo; // v é um documento do qual u depende
        if(estado[v] == 0){
            if (dfs(g, v, estado)) return 1; // um nó interior achou um ciclo, avisa a função 
        } 
        else if(estado[v] == 1) return 1; // vizinho ainda aberto na pilha: é ciclo
        atual = atual->prox;
    }
    estado[u] = 2; //vizinhos explorados
    return 0;
}