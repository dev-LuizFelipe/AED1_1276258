#include <stdio.h>
int verificar (int v[], int num);
int main() {
 
    int N;
    printf("Digite o tamanho do vetor:");
    scanf("%d",&N);
    int X[N];
    for (int i=0; i<N; i++){
        scanf("%d",&X[i]);
    }
    int menor = verificar(X, N);
    int posicao;
    printf("Menor valor: %d \n", verificar(X, N));
    for (int i=0; i<N; i++){
        if (menor == X[i]) posicao = i;
    }
    printf("Posicao: %d \n",posicao);
    return 0;
}

int verificar(int v[], int num){
    if (num == 1) return v[0];
    else{
        int atual;
        atual = verificar(v, num-1);
        if (atual < v[num-1]) return atual;
        else return v[num-1]; 
    }
}
