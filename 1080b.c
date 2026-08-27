/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Luiz Felipe Gonzaga
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1080
Data        : 27/08/2026
Objetivo    : Ler 100 valores inteiros e positivos, mostrar o maior e seu índice (versão com alocação dinâmica).
Dificuldade : <<<Qual foi o principal desafio neste problema?>>>
Uso de IA   : <<<Se usou, descreva brevemente o uso de IA na solução>>>
-------------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
int main(){
    int *vet;
    int maior=-1; int posicao, n;
    scanf("%d",&n);
    vet = (int *) malloc(n * sizeof(int));
    for(int i =0; i<n; i++){
        scanf("%d",&vet[i]);
        if (vet[i]> maior){
            maior = vet[i];
            posicao = i;
        } 
    }
    free(vet);
    printf("%d\n%d",maior, posicao);
    return 0;
}
