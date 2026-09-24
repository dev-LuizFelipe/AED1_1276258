/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Luiz Felipe Gonzaga
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/2448
Data        : 24/09/2026
Objetivo    : Ver quantas buscas serão feitas para carteiro entregar todas as encomendas em um certo tempo.
Dificuldade : <<<Qual foi o principal desafio neste problema?>>> lógica de usar a distância (móduolo) entre as casas para calcular o tempo.
Inicialmente, achei que teria que organizar o vetor e depois realizar uma busca. 
Uso de IA   : <<<Se usou, descreva brevemente o uso de IA na solução>>> apontou bus via perguntas, sem fornecer o código e 
indicou a função abs() para calcular o módulo |atual - anterior|.
-------------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
int busca_b (int v[], int inicio, int fim, int x); // x é o valor buscado
int busca_b (int v[], int inicio, int fim, int x){
    if (inicio >fim ) return 0;
    int meio = (inicio + fim)/2;
    if (v[meio] == x) return meio; // meio é o indice da casa 
    if (v[meio] > x) return busca_b (v, inicio, meio-1, x);
    else return busca_b(v, meio+1, fim, x);
      
}

int main(){
    int casa[45000];
    int i,N,M, buscado;
    int anterior, atual, tempo;
    anterior = atual = tempo = 0;
    scanf("%d %d", &N, &M);
    for(i=0; i<N; i++){ // le a quantidade de casas
        scanf("%d",&casa[i]);
    }
    for(i=0; i<M; i++){ // looping para a entrega das encomendas
        scanf("%d",&buscado);
        atual = busca_b(casa, 0, N-1, buscado); // recebe em qual casa ele parou
        tempo += abs(atual - anterior); // tempo para ir de uma casa a outra via módulo
        anterior = atual;
    }
    printf("%d", tempo);
    return 0;
}