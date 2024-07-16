#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct songs{
    char musica[100];
    struct songs* proxima;
};
typedef struct songs songs;

struct s_int{
    songs* removida;
    int c;
};

void inserir(songs** playlist, char* mus, int cursor){
    songs* mus_inserida = malloc(sizeof(songs));
    songs* percorre;
    int i;

    if(*playlist == NULL){
        strcpy(mus_inserida -> musica, mus);
        mus_inserida ->proxima = NULL;
        *playlist = mus_inserida;
    }
    else{
        percorre = *playlist;
        for(i = 0; i < cursor; i++){
            percorre = percorre ->proxima;
        }
        
        strcpy(mus_inserida -> musica, mus);
        mus_inserida ->proxima = percorre ->proxima;
        percorre ->proxima = mus_inserida;
    }
}
 
struct s_int remover(songs** playlist, char* mus, int cursor, int tamanho){
    songs* mus_removida = NULL;
    songs* percorre;
    struct s_int a;
    int i = 0;

    if(*playlist != NULL){
        if(strcmp((*playlist) ->musica, mus) == 0){
            mus_removida = *playlist;
            *playlist = mus_removida ->proxima;
        }
        else{
            percorre = *playlist;
            while(percorre ->proxima != NULL){
                if(strcmp(percorre ->proxima ->musica, mus) == 0){
                    mus_removida = percorre ->proxima;
                    percorre ->proxima = mus_removida ->proxima;
                    break;
                }
                percorre = percorre ->proxima;
                i++;
            }
        }
    }
    if(i <= cursor && tamanho != 1 && cursor != 0){ //se remover uma musica e o cursor estiver nela ou antes, retornar uma posição
        cursor--;
    }
    a.removida = mus_removida;
    a.c = cursor;
    return a;
}

void inverte(songs** playlist){
    songs* percorre;
    songs* prox;
    songs* prox_prox;

    percorre = *playlist;
    prox = (*playlist) ->proxima;
    prox_prox = (*playlist) ->proxima;

    while(prox != NULL){
        prox_prox = prox_prox ->proxima; //salva o apontador do próximo do próximo elemento
        prox ->proxima = percorre;
        percorre = prox;
        prox = prox_prox; //atualiza o próximo com o valor salvo no início para ele
    }
    (*playlist) ->proxima = NULL; //atualiza o que aponta valor inicial
    *playlist = percorre; //atualiza o apontador para o início da lista
}

void toca(songs* playlist, int cursor){
    songs* percorre;
    int i;

    percorre = playlist;
    for(i = 0; i < cursor; i++){
        percorre = percorre ->proxima;
    }
    if(percorre != NULL){
        printf("%s\n", percorre ->musica);
    }
}

void final(songs* playlist, int cursor){
    songs* percorre;
    int i;

    percorre = playlist;
    for(i = 0; i < cursor; i++){
        percorre = percorre ->proxima;
    }
    while(percorre != NULL){
        printf("%s\n", percorre ->musica);
        percorre = percorre ->proxima;
    }
}

void libera_mem(songs** playlist){ 
    songs* prox;

    if(*playlist != 0){
        while(*playlist != NULL){
            prox = (*playlist) ->proxima;
            free(*playlist);
            *playlist = prox;
        }
    }
}

int main(){

    songs* playlist = NULL;

    int cursor = 0, tamanho = 0, num_op, i, flag = 0;
    char operacao[11] = {"\0"}, //tamanho maximo do comando
         musica[101], //tamanho máximo do tamanho da música
         linha[111]; //tamanho máximo + comando
    char* inicio;

    while(1){
        scanf("%d", &num_op);
        getchar();
        if(num_op == 0)
            break;
        if (flag == 1){
            if(num_op != 0){
                printf("\n");
            }
        }
        for (i = 0; i < num_op; i++){
            //recebendo inputs
            scanf("%[^\n]", linha);
            getchar();
            if(strcmp(linha,"toca") == 0 || strcmp(linha,"volta") == 0 || strcmp(linha,"final") == 0 || strcmp(linha,"inverte") == 0){
                strcpy(operacao, linha);
            }
            else{
                strncpy(operacao, linha, 6);
                inicio = strstr(linha, " ");
                inicio++;
                strcpy(musica, inicio);
                operacao[6] = '\0';
            }

            if(strcmp(operacao,"insere") == 0){
                inserir(&playlist, musica, cursor); 
                tamanho++;
            }
            else if(strcmp(operacao,"toca") == 0){
                if(tamanho != 0){
                    toca(playlist, cursor);
                    if(tamanho > 1 && cursor != tamanho - 1){
                        cursor++; 
                    }
                }
                else{
                    printf("\n");
                }
            }
            else if(strcmp(operacao,"final") == 0){
                final(playlist, cursor); 
                cursor = tamanho - 1;
            }
            else if(strcmp(operacao,"remove") == 0){
                struct s_int r = remover(&playlist, musica, cursor, tamanho);
                cursor = r.c;
                if(r.removida != NULL){
                    tamanho--;
                    free(r.removida);
                }
            }
            else if(strcmp(operacao,"volta") == 0){
                if(cursor > 0){
                    cursor--;
                }
            }
            else if(strcmp(operacao,"inverte") == 0){
                inverte(&playlist); 
                cursor = tamanho - cursor - 1; //operação para posicionar o cursor na mesma música após inverter a playlist
            }
        }
        flag = 1;
        cursor = 0;
        tamanho = 0;
        libera_mem(&playlist);
    }
}
