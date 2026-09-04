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
    while(scanf(" %[^\n]", s) != EOF){
        if (verificar(s, head)){
            printf("correct\n");
        }else printf("incorrect\n");

        limpar(head);
    }
    return 0;
}

void empilhar(char y, Tno *p){
    Tno *novo;
    novo = malloc(sizeof(Tno));
    novo ->conteudo = y;
    novo ->prox = p->prox;
    p ->prox = novo;
}
int desempilhar(Tno *p){
    if (p->prox == NULL) return 0;
    else{
        Tno *lixo;
        int x; 
        lixo = p->prox;
        x = lixo->conteudo;
        p->prox = lixo->prox;
        free(lixo);
        return x;
    } 
}
int verificar(char s[], Tno *p){
    int len, i;
    len = strlen(s); // for(len =0; s[len] != '\0'; len++);
    for(i=0; i<len; i++){
        if(s[i] == '(') empilhar(s[i],p);
        if(s[i] == ')'){
            if (desempilhar(p) == 0) return 0;
        }
    }
    if(p->prox != NULL) return 0;
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
}