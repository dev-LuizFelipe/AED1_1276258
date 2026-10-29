/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Luiz Felipe Gonzaga
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1466
Data        : 28/10/2026
Objetivo    : Inserir N valores em uma árvore binária de busca e imprimir seus nós por nível (BFS), da esquerda para a direita, 
usando uma fila implementada com vetor de ponteiros e dois índices (ini e fim).
Dificuldade : <<<Qual foi o principal desafio neste problema?>>> Entender o que deveria ser enfileirado (filhos do nó visitado)
e acertar a formatação pedida.
Uso de IA   : <<<Se usou, descreva brevemente o uso de IA na solução>>> IA usada para corrigir a formatação 
e deu dicas sobre os erros ocorridos na estatégia de implementação da fila. Não forneceu código pronto, correção feita via perguntas.
-------------------------------------------------------------------------- */
#include <stdio.h>
#include<stdlib.h>

typedef struct no{
    int conteudo;
    struct no *esq;
    struct no *dir;
}Tno;

void limpar(Tno *r);
Tno *criar_no(int x);
void inserir(Tno *raiz, int x);
void nivel(Tno *raiz);

int main(){
    int c, casos, n, i, j;
    c=0;
    Tno *raiz; raiz = NULL;
    scanf("%d",&casos);
    while(c != casos){
        scanf("%d",&n);
        int v[n];
        for(i=0; i<n; i++){
            scanf("%d",&v[i]);
        }
        raiz = criar_no(v[0]);

        for(j=1; j<n; j++){
            inserir(raiz, v[j]);
        }
        printf("Case %d:\n", c+1);
        nivel(raiz);
        printf("\n\n");
        limpar(raiz);
        c++;
    }
}

void limpar(Tno *r){
    if(r != NULL){
        limpar(r->esq); //varre todos da esquerda
        limpar(r->dir); //varre todos da direita
        free(r);
    }
}

Tno *criar_no(int x){
    Tno *novo = malloc(sizeof(Tno));
    if(novo != NULL){
        novo->conteudo = x;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }
    return NULL;
}

void inserir(Tno *raiz, int x){ // assume que a raiz existe, por isso criamos ela na main e passamos para função 
    if(x < raiz->conteudo && raiz->esq == NULL){
        raiz->esq = criar_no(x);
    }else if(x > raiz->conteudo && raiz->dir == NULL){
        raiz->dir = criar_no(x);
    }else{
        if(x < raiz->conteudo) inserir(raiz->esq, x);
        else inserir(raiz->dir, x);
    }
}

void nivel(Tno *raiz){
    Tno *fila[500]; //fila de nós a visitar (FIFO)
    Tno *atual;
    int ini, fim;
    ini = fim = 0;
    fila[fim] = raiz;
    fim++;
    while(ini < fim){
        atual = fila[ini]; //atual é o nó atual, remove o nó da frente para visitá-lo
        ini++; // puxa a fila
        if (atual != raiz) printf(" "); //formatação beecrowd (espaço só entre os números)
        printf("%d", atual->conteudo);
        if(atual->esq != NULL){
            fila[fim] = atual->esq; //enfileira quem está na esquerda do nó atual (menor que ele)
            fim++;
        }
        if(atual->dir != NULL){
            fila[fim] = atual->dir; //enfileira quem está na direita do nó atual (maior que ele)
            fim++; // avança para a próxima posição livre da fila
        }

    }
}
