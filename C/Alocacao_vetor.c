#include <stdio.h>
#include <stdlib.h>

// A função tem como objetivo receber um vetor, alocar um segundo vetor e tranferir apenas os valores positivos de um para o outro

void exs1(int *v, int m, int n){
    int i, j = 0, *vectorB;
    vectorB = malloc(m*sizeof(int));
    for(i = 0; i < n; i++){
        if(v[i] > 0){
            vectorB[j] = v[i];
            j++;
        }
    }
    for(i = 0; i < m; i++){
        printf("%d ", vectorB[i]);
    }
    free(vectorB);
}

int main(){
    int n, m, i;
    scanf("%d %d", &n, &m);
    int *vectorA;
    vectorA = malloc(n*sizeof(int));

    for(i = 0; i < n; i++){
        scanf("%d", &vectorA[i]);
    }
    exs1(vectorA, m, n);
    free(vectorA);
}
