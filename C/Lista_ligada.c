#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct no_lista{
    int valor;
    struct no_lista* proximo;
};
typedef struct no_lista no_lista;

void inserir(no_lista** lista, int pos, int val_elemento){
    no_lista* novo_elemento = malloc(sizeof(no_lista));
    no_lista* percorre;
    int i;

    if(pos == 0){
        novo_elemento -> valor = val_elemento;
        novo_elemento ->proximo = NULL;
        *lista = novo_elemento;
    }
    else{
        percorre = *lista;
        for(i = 0; i < pos - 1; i++){
            percorre = percorre ->proximo;
        }
        novo_elemento -> valor = val_elemento;
        novo_elemento ->proximo = percorre ->proximo;
        percorre ->proximo = novo_elemento;
    }
}

int extrair_addfin(no_lista** lista, int in_sublista, int fin_sublista, int tamanho){ //extrai da lista e coloca elementos no final da mesma
    int a, b = 0, i, j, k = 0;
    no_lista* percorre;

    if(fin_sublista > in_sublista){ 
        for(a = 0; a <= fin_sublista - in_sublista; a++){
            b++;
            no_lista* novo_elemento = malloc(sizeof(no_lista));

            percorre = *lista;
            for(i = 0; i < in_sublista + k; i++){ //acha elemento para copiar valor
                percorre = percorre ->proximo;
            } 
            novo_elemento ->valor = percorre ->valor;

            percorre = *lista;
            for(j = 0; j < tamanho + k - 1; j++){ //vai para o final da lista
                percorre = percorre ->proximo;
            } 
            novo_elemento ->proximo = NULL;
            percorre ->proximo = novo_elemento;
            k++;
        }
    }

    else if(in_sublista == fin_sublista){
        b++;
        no_lista* novo_elemento = malloc(sizeof(no_lista));

        percorre = *lista;
        for(i = 0; i < in_sublista; i++){ //acha elemento para copiar valor
            percorre = percorre ->proximo;
        } 
        novo_elemento ->valor = percorre ->valor;

        percorre = *lista;
        for(j = 0; j < tamanho - 1; j++){ //vai para o final da lista
            percorre = percorre ->proximo;
        } 
        novo_elemento ->proximo = NULL;
        percorre ->proximo = novo_elemento;
    }

    else{
        for(a = 0; a <= in_sublista - fin_sublista; a++){
            b++;
            no_lista* novo_elemento = malloc(sizeof(no_lista));

            percorre = *lista;
            for(i = 0; i < in_sublista - k; i++){ //acha elemento para copiar valor
                percorre = percorre ->proximo;
            } 
            novo_elemento ->valor = percorre ->valor;
            
            percorre = *lista;
            for(j = 0; j < tamanho + k - 1; j++){ //vai para o final da lista
                percorre = percorre ->proximo;
            } 
            novo_elemento ->proximo = NULL;
            percorre ->proximo = novo_elemento;
            k++;
        }
    }
    return b;
}

void extrair_ins_index(no_lista** lista, int in_sublista, int fin_sublista, int index){ //extrai da lista e coloca elementos a partir do index
    int a, i, j, k = 0;
    no_lista* percorre;
    
    if(fin_sublista > in_sublista){ 
        for(a = 0; a <= fin_sublista - in_sublista; a++){
            no_lista* novo_elemento = malloc(sizeof(no_lista));

            percorre = *lista;
            if(index > in_sublista + k){
                for(i = 0; i < in_sublista + k; i++){ //acha elemento para copiar valor
                    percorre = percorre ->proximo;
                } 
            }
            else{
                for(i = 0; i < in_sublista + 2*k; i++){ //acha elemento para copiar valor
                    percorre = percorre ->proximo;
                } 
            }
            novo_elemento ->valor = percorre ->valor;

            percorre = *lista;
            for(j = 0; j < index + k - 1; j++){ //adiciona a partir do index
                percorre = percorre ->proximo;
            } 
            novo_elemento ->proximo = percorre ->proximo;
            percorre ->proximo = novo_elemento;
            k++;
        }
    }

    else if(in_sublista == fin_sublista){
        no_lista* novo_elemento = malloc(sizeof(no_lista));

        percorre = *lista;
        for(i = 0; i < in_sublista; i++){ //acha elemento para copiar valor
            percorre = percorre ->proximo;
        } 
        novo_elemento ->valor = percorre ->valor;
        if(index != 0){
            percorre = *lista;
            for(j = 0; j < index - 1; j++){ //adicionna no index
                percorre = percorre ->proximo;
            } 
            novo_elemento ->proximo = percorre ->proximo;
            percorre ->proximo = novo_elemento;
        }
        else{
            novo_elemento ->proximo = *lista;
            *lista = novo_elemento;
        }
    }

    else{
        for(a = 0; a <= in_sublista - fin_sublista; a++){
            no_lista* novo_elemento = malloc(sizeof(no_lista));

            percorre = *lista;
            if(index > in_sublista - k){
                for(i = 0; i < in_sublista - k; i++){ //acha elemento para copiar valor
                    percorre = percorre ->proximo;
                } 
            }
            else{
                for(i = 0; i < in_sublista; i++){ //acha elemento para copiar valor
                    percorre = percorre ->proximo;
                } 
            }
            novo_elemento ->valor = percorre ->valor;
            if(index + k != 0){
                percorre = *lista;
                for(j = 0; j < index + k - 1; j++){ //adiciona a partir do index
                    percorre = percorre ->proximo;
                } 
                novo_elemento ->proximo = percorre ->proximo;
                percorre ->proximo = novo_elemento;
            }
            else{
                novo_elemento ->proximo = *lista;
                *lista = novo_elemento;
            }
            k++;
        }
    }
}

void printar(no_lista* lista, int tamanho){
    no_lista* percorre;
    int i;

    percorre = lista;
    printf("A: {");
    for(i = 0; i < tamanho - 1; i++){
        printf(" %d,", percorre ->valor);
        percorre = percorre ->proximo;
    }
    printf(" %d }\n", percorre ->valor);
}

void libera_mem(no_lista** lista, int final){  
    no_lista* prox;
    int i;

    if(*lista != 0){
        for(i = 0; i < final; i++){
            prox = (*lista) ->proximo;
            free(*lista);
            *lista = prox;
        }
    }
}

int main(){
    no_lista* lista = NULL;
    char *in_input = malloc(sizeof(char)*4); 
    in_input[3] = '\0';
    char *sep_input = malloc(sizeof(char)*3); 
    sep_input[2] = '\0';
    char *comando = malloc(sizeof(char)*3);
    comando[2] = '\0';
    int num_input, in_sublista, fin_sublista, index, tamanho = 0, tamanho_int = 0;
    
    //recebe input da lista inicial e processa
    scanf("%3c", in_input); 
    while(1){ 
        scanf("%2c", sep_input);
        if(strcmp(sep_input, "}\n") == 0){
            break;
        }
        scanf("%d", &num_input);
        inserir(&lista, tamanho, num_input);
        tamanho++;
    }

    //recebe resto do input e processa
    while(1){
        scanf("%2c", comando); 
        if(strcmp(comando, "f\n") == 0){
            break;
        }
        else if(strcmp(comando, "s ") == 0){
            scanf("A[%d..%d]", &in_sublista, &fin_sublista);
            getchar();
            tamanho_int = extrair_addfin(&lista, in_sublista, fin_sublista, tamanho);
            libera_mem(&lista, tamanho);
            tamanho = tamanho_int; 
            printar(lista, tamanho);
        }
        else if(strcmp(comando, "+ ") == 0){
            scanf("A[%d..%d] %d", &in_sublista, &fin_sublista, &index);
            getchar();
            extrair_ins_index(&lista, in_sublista, fin_sublista, index);
            tamanho += abs(fin_sublista - in_sublista) + 1; 
            printar(lista, tamanho);
        }
    }
    libera_mem(&lista, tamanho);
    free(in_input);
    free(sep_input);
    free(comando);
}