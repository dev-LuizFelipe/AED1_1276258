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