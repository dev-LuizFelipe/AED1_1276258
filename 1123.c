/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Luiz Felipe Gonzaga
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1123
Data        : 25/11/2026
Objetivo    : Calcular o menor custo de pedágio para um veículo, consertado em uma cidade fora da rota de serviço, chegar ao
destino da rota, sabendo que ao tocar qualquer cidade da rota ele volta a segui-la.
Dificuldade : <<<Qual foi o principal desafio neste problema?>>> Adaptar o Dijkstra para que as cidades da rota recebam
distância, mas não propaguem
Uso de IA   : <<<Se usou, descreva brevemente o uso de IA na solução>>> Guiou a construção do Djikstra e da main por
perguntas e apontou erros (condições do for, ponto e vírgula, variáveis não reiniciadas). Não forneceu código pronto.
-------------------------------------------------------------------------- */
#include <stdio.h>
#define MAX 250
#define INF 100000

void iniciar(int m[][MAX]);
void inserir(int m[][MAX], int u, int v, int peso);
int menorDist(int dist[], int visitado[], int qtd_vertices);
void dijkstra(int m[][MAX],int n, int origem, int dist[], int visitado[], int rota);

int main(){
    int n,c,k, estradas,u,w,p;
    int m[MAX][MAX];
    int dist[MAX], visitado[MAX];
    int melhor, custoRota;
    custoRota =0;
    melhor = INF;

    while (scanf("%d %d %d %d", &n, &estradas, &c, &k) == 4 && n!=0){
        iniciar(m);

        for(int i=0; i<estradas; i++){
            scanf("%d %d %d", &u, &w, &p);
            inserir(m, u, w, p);
        }
        dijkstra(m, n, k, dist, visitado, c);
        int i;
        for(i=c-1; i>=0; i--){
           if(i < c-1){
             custoRota += m[i][i+1];
           }
           if(dist[i] + custoRota < melhor){
                melhor = dist[i] + custoRota;         
           }
        }
         printf("%d\n", melhor);
         custoRota=0;
         melhor = INF;

    }
    return 0;
}

void iniciar(int m[][MAX]){
    int i, j;
    for(i =0; i<MAX; i++){
        for(j=0; j<MAX; j++){
            m[i][j] =-1;
        }
    }
}

void inserir(int m[][MAX], int u, int v, int peso){
    m[u][v] = peso; //peso é o valor do pedágio e como é via de mão dupla, matriz simétrica
    m[v][u] = peso;
}

int menorDist(int dist[], int visitado[], int qtd_vertices){
    int i, melhor;
    melhor = -1;
    for(i=0; i<qtd_vertices; i++){
        
        if (!visitado[i] && dist[i] < INF && (melhor == -1 || dist[i] < dist[melhor])){
            melhor = i;
        }
        
    }
    return melhor;
}

void dijkstra(int m[][MAX],int n, int origem, int dist[], int visitado[], int rota){
    int i,u, j;
    u=0;
//inicialização: nenhum caminho conhecido
    for(i =0; i<n; i++){
        dist[i] = INF;
        visitado[i] =0;
    }
    dist[origem] = 0; //"distância da origem até a origem é 0"

    //cada volta um vértice novo
    while(1){
        u = menorDist(dist, visitado, n); //vértice atual: mais próximo ainda não definitivo
        if(u == -1) break;
        visitado[u] = 1; //fixa distancia de u como definitiva
        
        if(u < rota) continue; //adaptação sugerida pela IA: cidade da rota não propaga (não para nesse vértice e usa como ponto de partida)
//relaxamento: verifica se passar por u é mais barato que por j
        for(j=0; j<n; j++){
            //m[u][j] != -1 verifica se existe estrada ainda
            if (m[u][j] != -1 && dist[u] + m[u][j] < dist[j])
            dist[j] = dist[u] + m[u][j];
        }
    }
}