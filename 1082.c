/* --------------------------------------------------------------------------
Disciplina  : Algortimo e Estrutura de Dados 2026S1
Nome        : Luiz Felipe Gonzaga
Linguagem   : C
Problema    : https://judge.beecrowd.com/pt/problems/view/1082
Data        : 12/11/2026
Objetivo    : Encontrar e imprimir os componentes conexos de um grafo não direcionado, identificando quais vértices pertencem  a cada
grupo  e contando os componentes do grafo total.
Dificuldade : <<<Qual foi o principal desafio neste problema?>>> Implementar a busca para veirifcar quais e quantos componentes existem,
ajustando na main para que cada caso não tenha "restos" do anterior
Uso de IA   : <<<Se usou, descreva brevemente o uso de IA na solução>>> IA usada para corrigir a formatação do beecrowd
e deu dicas para estruturar a main de forma a não causar o problema citado na dificuldade. 
Não forneceu código pronto, correção feita via perguntas.
-------------------------------------------------------------------------- */
#include <stdio.h>
#define MAX 26

void zerar(int m[][MAX]);
void inserir(int m[][MAX], int u, int v);
int existe(int m[][MAX], int u, int v);
int grau(int m[][MAX], int u, int n);
void remover(int m[][MAX], int u, int v);
void dfs(int m[][MAX], int n, int u, int visitado[]); 

int main(){
    int m[MAX][MAX], visitado[MAX], antes[MAX];
    int vertices, c, casos, arestas, j;
    char x, y;
    c=0;
    scanf("%d", &casos);
    while(c != casos){
        for(int i =0; i<MAX; i++) visitado[i] = 0;
        zerar(m);
        scanf("%d %d",&vertices, &arestas);
        for (int i =0; i< arestas; i++){ //Lê as arestas e preenche a matriz (grafo não direcionado)
            scanf(" %c %c",&x, &y);
            inserir(m, x - 'a', y - 'a');
        }

        printf("Case #%d:\n", c+1);
        int conector=0; // Conta quantos componentes conexos o grafo tem

        for (int k =0; k<vertices; k++){ //Percorre todos os vértices para encontrar os componentes conexos
            if(!visitado[k]){ // Se o vértice ainda não foi visitado, encontramos um novo componente!
                conector++;
                for (int l=0; l<vertices; l++) antes[l] = visitado[l]; // Salva o estado atual de 'visitado' antes da busca
                dfs(m, vertices, k, visitado); //executa a busca

                
                for(int h=0; h<vertices; h++){ //Imprime apenas os vértices que foram visitados NESTA busca (o componente atual)
                    if (visitado[h] && !antes[h]){
                        printf("%c,", 'a' + h);
                    }
                }
                printf("\n");
            }
        }
        printf("%d connected components\n\n", conector);
        c++;
    }

    return 0;
}

void zerar(int m[][MAX]){
    int i, j;
    for(i=0; i<MAX; i++){
        for(j=0; j<MAX; j++){
            m[i][j] = 0;
        }
    }
}

void inserir(int m[][MAX], int u, int v){ //insere eseplhado pois é grafo não direcionado 
    m[u][v] = 1;
    m[v][u] = 1;
}

int existe(int m[][MAX], int u, int v){ //verifica se há relação entre vertices não direcionados
    return m[u][v]!= 0; //retorna se tem relação (nesse caso retorna 1)
}

int grau(int m[][MAX], int u, int n){ //ligações que esse vertice faz ("conta quantos vizinhos")
    int j, qtd;
    qtd =0;
    for (j=0; j<n; j++){
        if (m[u][j] != 0) qtd++; 
    }
    return qtd;
}

void remover(int m[][MAX], int u, int v){
    m[u][v] = 0;
    m[v][u] = 0;
}

void dfs(int m[][MAX], int n, int u, int visitado[]){ //verifica se tem vizinhos e o marca 
    int j;
    visitado[u] = 1;
    for (j=0; j<n; j++){
        if (existe(m, u, j) && !visitado[j]) dfs(m, n, j, visitado);
    }
}