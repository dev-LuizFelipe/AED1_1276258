/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Luiz Felipe Gonzaga
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1068
Data        : 4/09/2026
Objetivo    : Verificar abertura e fechamento de parênteses  
Dificuldade : <<<Qual foi o principal desafio neste problema?>>> Tratar os casos extremos (fechamento
              sem abertura correspondente e parênteses sobrando no fim) e 
              um "free" sem reset do ponteiro da cabeça causou um double free difícil de rastrear.
Uso de IA   : <<<Se usou, descreva brevemente o uso de IA na solução>>> ajudou a estruturar a lógica central via perguntas sem entregar o código
e ajudou a localizar um bug de memória (double free) orientando o uso de prints de depuração.
-------------------------------------------------------------------------- */
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct no{
    char conteudo;
    struct no *prox;
} Tno;

void empilhar(char y, Tno *p);
int desempilhar(Tno *p);
int verificar(char s[], Tno *p);
void limpar(Tno *head);

int main(){
    Tno *head = malloc(sizeof(Tno));
    head->prox = NULL;
    char s[1001];
    while(scanf(" %[^\n]", s) != EOF){ // preenche a string com as expressões até o usuário dar Ctrl+Z na entrada, encerrando o scanf.
        if (verificar(s, head)){
            printf("correct\n");
        }else printf("incorrect\n");

        limpar(head);
    }
    return 0;
}

void empilhar(char y, Tno *p){ // empilha os parênteses
    Tno *novo;
    novo = malloc(sizeof(Tno));
    novo ->conteudo = y;
    novo ->prox = p->prox;
    p ->prox = novo;
}
int desempilhar(Tno *p){ // descarta os parênteses empilhados no topo, se a pilha não estiver vazia. 
    if (p->prox == NULL) return 0; //vazia
    else{
        Tno *lixo;
        int x; 
        lixo = p->prox;
        x = lixo->conteudo;
        p->prox = lixo->prox;
        free(lixo);
        return x; // retorna o número ASCII do parênteses.
    } 
}
int verificar(char s[], Tno *p){ // faz a varredura da string empilhando e desempilhando os parênteses 
    int len, i;
    len = strlen(s); // for(len =0; s[len] != '\0'; len++);
    for(i=0; i<len; i++){
        if(s[i] == '(') empilhar(s[i],p);
        if(s[i] == ')'){
            if (desempilhar(p) == 0) return 0; // encontrou fechamento; se a pilha já estava vazia, é incorreto
        }
    }
    if(p->prox != NULL) return 0; //verifica se no final sobrou algum parênteses e da erro se sim.
    return 1;
}
    
void limpar (Tno *head){
    Tno *p;
    Tno *aux;
    p = head->prox;
    while (p != NULL){
        aux = p->prox;
        free(p);
        p = aux;
    }
    head->prox = NULL; // evita causar o double free, sem ele head vai apontar para um conteudo morto.
}
