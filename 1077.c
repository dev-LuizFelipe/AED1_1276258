/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Luiz Felipe Gonzaga
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1077
Data        : 26/09/2026
Objetivo    : Transformar uma expressão matemática infixa para posfixa (usando pilha)  
Dificuldade : <<<Qual foi o principal desafio neste problema?>>> Entender a lógica de comparação de precedência entre operadores
              (decidir quando desempilhar antes de inserir um novo operador) e separar as responsabilidades entre "ler o topo sem remover"
              (topo) e "remover de fato" (desempilhar). O tratamento especial dos parenteses também precisou de atenção, principalmente para ')'
Uso de IA   : <<<Se usou, descreva brevemente o uso de IA na solução>>> guiou a compreensão do algoritmo por meio de
              perguntas e simulação manual antes de qualquer código; apontou 
              erros de sintaxe, posicionamento de blocos, condições de comparação sem fornecer o código pronto
-------------------------------------------------------------------------- */
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
typedef struct no{
    char conteudo;
    struct no *prox;
} Tno;

int precedencia (char op);
void empilhar(char y, Tno *p);
int desempilhar(Tno *p);
void converter (char expressao[], Tno *head);
void limpar (Tno *head);
int topo(Tno *p);

int main(){
    Tno *head = malloc(sizeof(Tno));
    head->prox = NULL;
    char expressao[1000];
    int N,i;
    scanf("%d",&N);
    for(i=0; i<N; i++){
        scanf(" %[^\n]", expressao); // le n expressoes
        converter(expressao, head); //manda converter as expressoes
        printf("\n");
        limpar(head); // limpa a pilha para evitar bugs
    }
    return 0;
}

int precedencia (char op){ //transforma o operador em "nível de força" para a precedencia
    int forca; forca = 0;
    if(op == '+' || op == '-') forca = 1;
    else if (op == '*' || op == '/') forca = 2;
    else if (op == '^') forca = 3;
    return forca;
}
void empilhar(char y, Tno *p){ // empilha os itens da expressão
    Tno *novo;
    novo = malloc(sizeof(Tno));
    novo ->conteudo = y;
    novo ->prox = p->prox;
    p ->prox = novo; // novo topo é atualizado após o novo nó receber o conteudo empilhado, apontando para o antigo topo
}

int desempilhar(Tno *p){ // descarta os operadores empilhados no topo, se a pilha não estiver vazia. 
    if (p->prox == NULL) return 0; //vazia
    else{
        Tno *lixo;
        int x; 
        lixo = p->prox;
        x = lixo->conteudo;
        p->prox = lixo->prox; // novo topo passa a apontar o que o nó que será descartado aponta, antes disso o conteúdo do nó descartado é salvo em x
        free(lixo);
        return x; // retorna o número ASCII do operador.
    } 
}
void limpar (Tno *head){ // é usada para limpar os itens da pilha deixando só o nosso head fixo, evita bugs
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

int topo(Tno *p){
    if (p->prox == NULL) return 0; // pilha vazia
    else {
        return p->prox->conteudo; // lê e retorna o valor do topo, sem remover nada
    }
}
void converter (char expressao[], Tno *head){
    int i, len;
    len = strlen(expressao);
    for (i=0; i<len; i++){
        char c = expressao[i];
         if (isalnum(c)){
            printf("%c",c); //printa as letras ou números
        }else if(c == '('){
            empilhar(c, head); // empilha a abertura
        }else if(c == ')'){
            while(topo(head) != '('){
                printf("%c", desempilhar(head)); //printa as letras ou números de dentro dos parenteses
            }
            desempilhar(head); //some com a abertura, pois não é usada na posfixa
        }else{ // se forem os operadores os próximos caracteres 
            while(head->prox != NULL && precedencia(topo(head))>= precedencia(c)){ // começa verificando do topo se a precedencia dele não é maior que a do operador atual
                printf("%c", desempilhar(head)); //printa os operadores de dentro do parenteses 
            }
            empilhar(c, head); 
        }
    }
    while(head->prox != NULL){
        printf("%c", desempilhar(head)); //printa os operadores que restaram na pilha
    }
}