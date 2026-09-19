#include <stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct no{
    int conteudo;
    struct no *prox;
} Tno;

void empilhar(int y, Tno *p);
int desempilhar(Tno *p);
void enfileirar(int x, Tno **head, Tno **tail);
int desenfileirar(Tno **head, Tno **tail);
void inserir_prioridade (int y, Tno *p);
int retirarPrioridade (Tno *head);
void limpar(Tno *head);
void limparFila(Tno **head, Tno **tail);

int main(){
    Tno *headPilha, *headFilaP,*headFila, *tailFila;
    headPilha = malloc(sizeof(Tno));
    headFila = malloc(sizeof(Tno));
    headFilaP = malloc(sizeof(Tno));

    headPilha->prox = NULL;
    headFilaP->prox = NULL;
    headFila = NULL;
    tailFila = headFila; // não precisa de malloc no tail pq ele já faz parte do nó headFila.
    
    int ehPilha, ehFila, ehFilaP;
    ehFilaP = ehFila = ehPilha = 1;
    int tipo, num, n, i;

    while(scanf("%d", &n) != EOF){
        limpar(headPilha); limpar(headFilaP); limparFila(&headFila, &tailFila);
        ehFilaP = ehFila = ehPilha = 1;
        for(i=0; i<n; i++){
            scanf(" %d %d", &tipo, &num);
            if(tipo == 1){
                empilhar(num, headPilha);
                enfileirar(num, &headFila, &tailFila);
                inserir_prioridade(num, headFilaP);
            }
            if(tipo == 2){
                if(num != desempilhar(headPilha)) ehPilha = 0;
                if(num != desenfileirar(&headFila, &tailFila)) ehFila = 0;
                if(num != retirarPrioridade(headFilaP)) ehFilaP = 0;
            }
        }
        int total = ehFila + ehPilha + ehFilaP;
        if(total >= 2) printf("not sure\n");
        else if(total == 0) printf ("impossible\n");
        else if(ehFila == 1) printf("queue\n");
        else if(ehFilaP == 1) printf("priority queue\n");
        else if(ehPilha == 1) printf("stack\n");
    }
    return 0;
}

void empilhar(int y, Tno *p){ 
    Tno *novo;
    novo = malloc(sizeof(Tno));
    novo ->conteudo = y; // novo nó recebe o número
    novo ->prox = p->prox; // novo nó passa a apontar o antigo topo da pilha
    p ->prox = novo; // atualizamos o topo
}

int desempilhar(Tno *p){ 
    if (p->prox == NULL) return 0; //retorna erro se for ativada com a pilha vazia 
    else{
        Tno *lixo; 
        int x; 
        lixo = p->prox; //lixo recebe o que será descartado (o que o head está apontando)
        x = lixo->conteudo; // x guarda o conteudo que será retornado (importante)
        p->prox = lixo->prox; // head passa a apontar o que é apontado pelo nó que vai ser descartado
        free(lixo); //descarte
        return x; 
    } 
}

void enfileirar(int x, Tno **head, Tno **tail){
    Tno *novo;
    novo = malloc(sizeof(Tno));
    novo->conteudo = x; // novo nó recebe o número
    novo->prox = NULL; // novo nó vira o tail
    if (*head == NULL){ // só essa parte é usada, por isso no limparFila temos que dar free(*head) e dps colocar head = tail = null.
        *head = novo; //se não tiver nada na fila, head e tail recebem o novo nó
        *tail = novo;
    }else{
        (*tail)->prox = novo;
        *tail = novo;
    }
}

int desenfileirar(Tno **head, Tno **tail){
    int dado;
    Tno *endereco;
    dado = (*head)->conteudo; //conteudo do nó a ser descartado fica salvo em dado
    endereco = (*head)->prox; // endereco recebe o que o nó que será descartado aponta
    free(*head); 
    *head = endereco; // head recebe o que o nó descartado apontava para não ocorrer vazamento de memória
    if(endereco == NULL){ // se o nó descartado era o último da fila, então tail também recebe o endereco para ficar igual ao inicio com head e tail null
        *tail = endereco;
    }
    return dado;  
}

void inserir_prioridade (int y, Tno *p){
    Tno *novo;
    novo = malloc(sizeof(Tno));
    novo ->conteudo = y; // novo nó recebe o número
    novo ->prox = p->prox; // novo nó aponta para o que head aponta
    p ->prox = novo; //head passa a apontar o novo nó (inserção após a cabeça)
}

int retirarPrioridade (Tno *head) {
    Tno *p, *q, *anteriorMaior, *MaiorNo;
    int maior= -1;
    p = head;
    q = head->prox;
    while (q != NULL) {
        if(q->conteudo > maior){
            maior = q-> conteudo; //maior guarda o valor
            MaiorNo = q; // MaiorNo recebe o maior nó para podermos continuar a rodar a lista
            anteriorMaior = p; //guardando o anterior do maior para não perder qual nó remover (o maior).
        } 
        p = q;
        q = q->prox;
    }
    
        anteriorMaior->prox = MaiorNo->prox; // conecta o nó antes que está antes do maior com o que está depois para não ficar um "buraco" na lista.
        free (MaiorNo);
    
    return maior;
}

void limpar (Tno *head){
    Tno *p;
    Tno *aux;
    p = head->prox;
    while (p != NULL){
        aux = p->prox; // salva o endereço do próximo nó antes de liberar o atual
        free(p);
        p = aux; // avança para o próximo nó que esta salvo em aux
    }
    head->prox = NULL; // evita causar o double free, sem ele head vai apontar para um conteudo morto.
}

void limparFila(Tno **head, Tno **tail){ // esvazia a fila (sem nó cabeça), deixando head e tail = NULL
    if(*head != NULL){
        Tno *p;
        Tno *aux;
        p = (*head)->prox; // começa a partir do segundo nó, já que o primeiro (head) é tratado à parte
        while (p != NULL){
            aux = p->prox; // guarda o próximo antes de liberar, evita "use after free"
            free(p);
            p = aux;
        }
    }    
    free(*head); // libera o próprio head, que aqui é um nó de dado real (não uma cabeça fixa) 
    *tail = *head = NULL;
}