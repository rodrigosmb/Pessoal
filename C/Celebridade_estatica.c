#include <stdio.h>
#include <string.h>

int main(){
    int i = 0, j = 0, k = 0, x = 0, stop = 0, prim = 0, num_inputs = 0, ja_foi1 = 0, ja_foi2 = 0, a = 0, b = 0;
    char inputs[100][50]; //100 é o n° máx de caracteres de um só nome, se ele for composto apenas por letras separadas (o que teoricamente é impossível)
    char nome1[100];
    char nome2[100];
    char espaço[1];
    char separação[] = "conhece";
    char* nome1_ini;
    //int matriz[1000][1000] = {{0},{0}};
    
    char lista_nomes[100][100];   //declarando lista de 50*2 strings de até 100 caracteres inicialmente vazia
    char lista_nomes_compacta[100][50];
    char lista_nomes_já_foram[100][100];

    while(1){
        num_inputs++;
        while(1){
            ++i;
            scanf("%s", inputs[i]);
            if(strlen(inputs[i]) == 1){
                stop++;
                break;
            }
            if(strcmp(inputs[i], separação) == 0){
                break;
            }
            else if (i == 1){
                nome1_ini = inputs[i];
            }
            else{
                strcat(nome1_ini," ");
                strcat(nome1_ini,inputs[i]);
            }
        }
        strcat(nome1_ini,"\0");
        if(prim != 0){
            strcpy(nome1, nome1_ini + 1);
        }
        else{
            strcpy(nome1, nome1_ini);
        }
        scanf("%c", espaço);
        scanf("%[^\n]", nome2);

        if(stop == 0){     //toda a lógica de celebridade deve estar nessa condição
            
            for(j = 0; j <= (num_inputs - 1)*2 + 1; j++){
                for(k = 0; k <= (num_inputs - 1)*2; k++){
                    if(strcmp(nome1, lista_nomes_já_foram[k]) == 0){
                        ja_foi1++;
                    }
                }   
                for(k = 0; k <= (num_inputs - 1)*2; k++){
                    if(strcmp(nome2, lista_nomes_já_foram[k]) == 0){
                        ja_foi2++;
                    }
                }
                if(strcmp(lista_nomes[j+a], nome1) != 0 && ja_foi1 == 0){
                    strcpy(lista_nomes[j+a],nome1);
                    strcpy(lista_nomes_já_foram[j+a],nome1);
                }
                ja_foi1 = 0;
                
                if(strcmp(lista_nomes[j+a], nome2) != 0 && ja_foi2 == 0){
                    strcpy(lista_nomes[j+a],nome2);
                    strcpy(lista_nomes_já_foram[j+a],nome2);
                }
                ja_foi2 = 0;
            }
            a += 2;
            
            for(x = 0; x <= (num_inputs - 1)*2 + 1; x++){
                if(strlen(lista_nomes[x]) == 0){
                    strcpy(lista_nomes_compacta[b],lista_nomes[x]);
                    b++;
                }
            }
            
            printf("%s\n", nome1);
            printf("%s\n", nome2);
            printf("\n");
        }

        *nome1_ini = NULL;
        prim++;
        if(stop > 0){
            break;
        }
    }
    printf("%s\n", lista_nomes_compacta[0]);
}
