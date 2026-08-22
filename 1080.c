/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Luiz Felipe Gonzaga
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1080
Data        : 22/08/2026
Objetivo    : Ler 100 valores inteiros e positivos, mostrar o maior e seu índice.
Dificuldade : <<<Qual foi o principal desafio neste problema?>>>
Uso de IA   : <<<Se usou, descreva brevemente o uso de IA na solução>>>
-------------------------------------------------------------------------- */
#include <stdio.h>
int main(){
    int vet[100];
    int maior=-1; int posicao;
    for(int i =0; i<100; i++){
        scanf("%d",&vet[i]);
        if (vet[i]> maior){
            maior = vet[i];
            posicao = i;
        } 
    }
    printf("%d\n%d",maior, posicao);
    return 0;
}