#include <stdio.h>
/*

ENTRADA:
N
matriz N x N

SAÍDA:
Soma diagonal principal / Soma diagonal secundária / Numero de colunas com soma par / Numero de linhas com soma ímpar

*/
int main(){
    int a = 0, i, j, x, y, num_lc, main_sum = 0, second_sum = 0, line_sum, col_sum, int_resl, int_resc, odd_lines = 0, even_lines = 0;
    float fl_resl, fl_resc;
    scanf("%d", &num_lc);
    int matrix[num_lc][num_lc], trsp_matrix[num_lc][num_lc];
    for(i = 0; i < num_lc; i++){
        for(j = 0; j < num_lc; j++){
            scanf("%d", &matrix[i][j]);
        }
    }
    for(i = 0; i < num_lc; i++){
        x = 0;
        for(j = 0; j < num_lc; j++){
            trsp_matrix[i][j] = matrix[j][i];
        }
    }
    for(i = 0; i < num_lc; i++){
        line_sum = 0;
        col_sum = 0;
        for(j = 0; j < num_lc; j++){
            line_sum += matrix[i][j];
            col_sum += matrix[j][i];
            if(i == j){
                main_sum += matrix[i][j];
            }
            if(j == ((num_lc-1) - a)){
                second_sum += matrix[i][j];
            }
        }
        a++;
        int_resl = line_sum/2;
        fl_resl = line_sum/2.0;
        if((float)int_resl != fl_resl){
            odd_lines++;
        }
        int_resc = col_sum/2;
        fl_resc = col_sum/2.0;
        if((float)int_resc == fl_resc){
            even_lines++;
        }
    }
    printf("%d %d %d %d", main_sum, second_sum, even_lines, odd_lines);
}
