#include <stdio.h>

int main(){

    int C, N, T, D, i, j, min_position, menor_minimo, wait, reverse_wait;
    int twenty_wait = 0;
    int atendents[100] = {0};
    
    scanf("%d %d", &C, &N);

    for(i = 0; i < N; i++){
        scanf("%d %d", &T, &D);
        if(i == 0){
            min_position = 0;
        }
        else{
            for(j = 0; j < C; j++){
                if(j == 0){
                    menor_minimo = j;
                }
                else if(atendents[menor_minimo] > atendents[j]){
                    menor_minimo = j;
                }
            }
            min_position = menor_minimo;
        }
        if(T >= atendents[min_position]){
            reverse_wait = T - atendents[min_position];
            wait = 0;
            if(atendents[min_position] == 0)
                atendents[min_position] = T + D;
            else
                atendents[min_position] = atendents[min_position] + D + reverse_wait;
        }
        else{
            wait = atendents[min_position] - T;
            atendents[min_position] = atendents[min_position] + D;
        }
        if(wait > 20)
            ++twenty_wait;

        printf("%d\n", wait);
    }
    printf("%d\n", twenty_wait);
}