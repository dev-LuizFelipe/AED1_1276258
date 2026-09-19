/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Luiz Felipe Gonzaga
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1110
Data        : 30/08/2026
Objetivo    : Descartar a carta do topo, colocar a de baixo por último e repetir o processo até sobrar 1 carta.
Dificuldade : <<<Qual foi o principal desafio neste problema?>>> Implementar a lógica de fila com dois ponteiros de controle
(head/tail) usando alocação dinâmica, especialmente garantir a formatação exata da saída
Uso de IA   : <<<Se usou, descreva brevemente o uso de IA na solução>>> Guiou a construção das funções de fila (enfileirar/desenfileirar) 
via perguntas (sem entregar o código); ajudou a identificar bugs de formatação e memória.
-------------------------------------------------------------------------- */
#include <stdio.h>
#include<stdlib.h>
typedef struct no{
    int conteudo;
    struct no *prox;
} Tno;
void enfileirar(int x, Tno **head, Tno **tail); // adiciona um novo nó no final e transforma ele em um tail
int desenfileirar(Tno **head, Tno **tail); // salva as informações da carta que será removida e "puxa a fila" com free(*head) seguido de *head = enedereco;

int main(){
    int n,i, carta, carta_descartada;
    int primeira=1;
    Tno *head, *tail;

    scanf("%d",&n);
    while(n !=0){
        head = tail = NULL;
        primeira = 1;

        for(i=1; i<=n; i++){
            enfileirar(i, &head, &tail);
        }

        printf("Discarded cards:");

        while(head != NULL && head->prox != NULL){
            carta_descartada = desenfileirar(&head, &tail);
            
            if (primeira) {
                 printf(" %d", carta_descartada);
                 primeira = 0;
            } else { printf("Remaning cards:");
                 printf(", %d", carta_descartada);
            }
               carta = desenfileirar(&head, &tail);
               enfileirar(carta,&head,&tail); 
            }
            printf("\nRemaning card: %d\n", head->conteudo);
            printf("%d", head->conteudo);
            scanf("%d",&n);
            free(head);
    }
    return 0;
}

void enfileirar(int x, Tno **head, Tno **tail){ //usamos ponteiros duplos para modificar a variável original ("a do main").
    Tno *novo;
    novo = malloc(sizeof(Tno)); // novo nó
    novo->conteudo = x; // conteudo do novo nó é a carta 
    novo->prox = NULL; // o novo nó vira o tail 
    if (*head == NULL){ // se não tiver nada na fila, head e tail recebem o novo nó.
        *head = novo;
        *tail = novo;
    }else{
        (*tail)->prox = novo;
        *tail = novo;
    }
}

int desenfileirar(Tno **head, Tno **tail){
    int dado;
    Tno *endereco;
    dado = (*head)->conteudo; // recebe o número da carta a ser descartada.
    endereco = (*head)->prox;  // recebe o aonde o nó com a carta que será descartada aponta.
    free(*head); 
    *head = endereco; // head recebe endereço para não ocorrer vazamento de memória 
    if(endereco == NULL){ // se a carta descartada era o último nó da fila, então tail também recebe endereco para ficar igual ao inicio com head e tail null. 
        *tail = endereco;
    }
    return dado;  
}
