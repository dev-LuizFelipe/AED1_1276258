/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Luiz Felipe Gonzaga
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1383
Data        : 23/08/2026
Objetivo    : Verificar instâncias de um Sudoku
Dificuldade : <<<Qual foi o principal desafio neste problema?>>> Montar a verificação e conversão dos blocos 3x3 para a matriz 9x9.
Uso de IA   : <<<Se usou, descreva brevemente o uso de IA na solução>>> Usei como guia para estruturar a função verificar3x3
-------------------------------------------------------------------------- */
#include <stdio.h>
int verificar_linha(int m[][9]);
int verificar_coluna(int m[][9]);
int verificar3x3(int m[][9]);
int main(){
    int m[9][9];
    int i,j,k, instancias;
    scanf("%d",&instancias);
    for (k=0; k<instancias; k++){      
        for(i=0; i<9; i++){
            for(j=0; j<9; j++){
                scanf("%d",&m[i][j]);
            }
        } 
        printf("Instancia %d\n",k+1);
        if (verificar_linha(m) && verificar_coluna(m) && verificar3x3(m)){
            printf("SIM\n\n");
        }else
        printf("NAO\n\n");
    }
    
    return 0;
}

int verificar_linha(int m[][9]){
    int i,j,l;
    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            for(l=j+1; l<9; l++){
                if(m[i][j] == m[i][l]) return 0;
            }
        }
    }
    return 1;
}

int verificar_coluna(int m[][9]){
    int i,j,l;
    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            for(l=i+1; l<9; l++){
                if(m[i][j] == m[l][j]) return 0;
            }
        }
    }
    return 1;
}

int verificar3x3(int m[][9]){
    int blocoLinha, blocoColuna, atual, comparado;
    // percorre os 9 blocos dentro da matriz
    for (blocoLinha = 0; blocoLinha < 3; blocoLinha++) {
        for (blocoColuna = 0; blocoColuna < 3; blocoColuna++) {
            // 'atual' representa o elemento dentro do bloco 3x3
            for (atual = 0; atual < 9; atual++) {
                // converte 'atual' para a matriz original 9x9
                int l1 = blocoLinha * 3 + (atual / 3);
                int c1 = blocoColuna * 3 + (atual % 3);
                //'comparado' pega os elementos seguintes no mesmo bloco para evitar comparações duplicadas
                for (comparado = atual + 1; comparado < 9; comparado++) {
                    // converte a posição de  'comparado' para a matriz 9x9 original
                    int l2 = blocoLinha * 3 + (comparado / 3);
                    int c2 = blocoColuna * 3 + (comparado % 3);

                    if (m[l1][c1] == m[l2][c2]) return 0;
                } /* 'atual' verifica quem está sendo verificado no momento e 'comparado' olha todos os elementos depois dele
                para checar se algum é igual, ou seja, repetido. como comparado = atual + 1 , o elemento não é comparado com ele 
                mesmo e nem realiza comparações repetidas. Além disso, a conversão é feita com * 3 para saltar de bloco em bloco 
                (no inicio de cada bloco), enquanto comparado / 3 e comparado % 3 representam, respectivamente, 
                a linha e a coluna internas do bloco 3x3, resultando na posição correta na matriz 9x9."*/ 
            }

        }
    }
    return 1;
}