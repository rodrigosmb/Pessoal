#include <stdio.h>
#include <string.h>

int main() {

    char colchete[2], virgula[2], quebra[2], comando[2];
    int m, n, k, a, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, z = 0, ja_existe = 0, linha_menor = 0, coluna_maior = 0, linha_igual = 0, i_inserido, j_inserido, valor_inserido, i_recuperado, j_recuperado, tamanho_VC;

    struct VC {
        int i;
        int j;
        int valor;
    };

    scanf("%d %d", &m, &n);
    scanf("%d", &k);
    struct VC coord[m + n];     //vetor de no máximo m + n coordenadas

    for(a = 0; a < k; a++){     //recebe input de cordenas e guarda como coord[a]
        scanf("%1s", colchete);
        scanf("%d", &coord[a].i);
        scanf("%1s", virgula);
        scanf("%d", &coord[a].j);
        scanf("%1s", colchete);
        scanf("%d", &coord[a].valor);
    }
    tamanho_VC = k;
    printf("%d\n", coord[tamanho_VC-1].valor);
    
    while(1){
        scanf("%1s", comando);
        if(strcmp(comando,"t") == 0){
            break;
        }
        if(strcmp(comando,"p") == 0){
            scanf("%c", quebra);
            printf("Comando: %s\n", comando);
        }
        if(strcmp(comando,"r") == 0){
            scanf(" [%d,%d]", &i_recuperado, &j_recuperado);
            printf("%d\n", j_recuperado);
            printf("Comando: %s\n", comando);
        }
        if(strcmp(comando,"a") == 0){
            scanf(" [%d,%d] %d", &i_inserido, &j_inserido, &valor_inserido);
            for(b = 0; b <= tamanho_VC; b++){
                if(ja_existe != 0){
                    ja_existe--;
                }
                if((i_inserido == coord[b].i) && (j_inserido == coord[b].j)){
                    ja_existe++;
                }
                if((ja_existe != 0) && (valor_inserido != 0)){  //se vetor já existe substituir por valor inserido != 0
                    coord[b].valor = valor_inserido;
                    break;
                }
                if((ja_existe != 0) && (valor_inserido == 0)){  //se vetor já existe e valor inserido = 0, remover elemento do VC
                    for(c = b; c < tamanho_VC - 1; c++){
                        coord[c].i = coord[c+1].i;
                        coord[c].j = coord[c+1].j;
                        coord[c].valor = coord[c+1].valor;
                    }
                    tamanho_VC--;
                    coord[tamanho_VC].valor = 0;
                    //printf("%d\n", coord[b].valor);
                }
            }
            if(ja_existe == 0){ //não existe
                for(d = 0; d < tamanho_VC; d++){
                    linha_menor = 0;
                    linha_igual = 0;
                    
                    if(coord[d].i == i_inserido){
                        linha_igual++;
                        break;
                    }
                    if((d == tamanho_VC-1) && (coord[d].i > i_inserido)){
                        linha_menor = d;
                        break;
                    }
                }
                if(linha_menor != 0){
                    linha_igual = 0;
                }
                
                if(linha_igual != 0){  //está na mesma linha
                    for(e = 0; e < n; e++){
                        coluna_maior = 0;
                        if(j_inserido < coord[e].j){
                            for(z = 1; z <= e; z++){
                                coluna_maior++;
                            }
                            break;
                        }
                    }
                    if(coluna_maior == 0){
                        coluna_maior = n-1;
                    }
                    for(f = tamanho_VC-1 ; f > coluna_maior; f--){
                        coord[f+1].i = coord[f].i;
                        coord[f+1].j = coord[f].j;
                        coord[f+1].valor = coord[f].valor;
                    }
                    
                    coord[coluna_maior+1].i = i_inserido;
                    coord[coluna_maior+1].j = j_inserido;
                    coord[coluna_maior+1].valor = valor_inserido;
                    //printf("VC %d\n", tamanho_VC);
                    //printf("%d\n", coord[0].i);
                    //printf("%d\n", coord[0].j);
                    //printf("%d\n", coord[0].valor);
                }

                else if(linha_menor != 0){  //linha maior = linha do input + 1
                    for(g = tamanho_VC-1; g > linha_menor-1; g--){
                        coord[g+1].i = coord[g].i;
                        coord[g+1].j = coord[g].j;
                        coord[g+1].valor = coord[g].valor;
                    }    
                    coord[linha_menor-2].i = i_inserido;
                    coord[linha_menor-2].j = j_inserido;  //depois do inserido os outros nao tao andando direito
                    coord[linha_menor-2].valor = valor_inserido;
                    printf("%d\n", coord[7].i);
                    printf("%d\n", coord[7].j);
                    printf("%d\n", coord[7].valor);
                }
                else{  //está numa linha maior sem outros elementos
                    coord[tamanho_VC].i = i_inserido;
                    coord[tamanho_VC].j = j_inserido;
                    coord[tamanho_VC].valor = valor_inserido;
                    //printf("%d\n", coord[tamanho_VC-9].i);
                    //printf("%d\n", coord[tamanho_VC-9].j);
                    //printf("%d\n", coord[tamanho_VC-9].valor);
                }
                tamanho_VC++;
            }
            //printf("%d\n", valor_inserido);
            printf("Comando: %s\n", comando);
            printf("%d\n", linha_igual);
            printf("%d\n", linha_menor);
        }
    }
}