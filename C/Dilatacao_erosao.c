#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>

/*
Esse programa define uma imagem 2D binária com valores 0 e 1 como um array multidimensional 2D (ou matriz) representado por uma struct, cujos elementos da matriz são alocados como nós conectados sequencialmente
na Lista Ligada. O principal objetivo do programa é realizar operações sobre os valores desta imagem considerando seus elementos vizinhos ou adjacentes. A operação de Dilatação considera
o máximo nas comparações entre os valores localizados (ou até) na borda do desenho na matriz com seus valores adajcentes, enquanto a operação de Erosão considera o mínimo.
A combinação das operações de Dilatação e Erosão resultam nas outras operações chamadas Abertura e Fechamento.
*/

FILE *arquivo_saida_ponteiro = NULL;

typedef struct no_lista_simples
{
    int valor;
    struct no_lista_simples *proximo;
} ListaSimples, NoListaSimples;

typedef struct _pixel
{
    int x;
    int y;
} Pixel;

typedef struct _imagem
{
    int **Posicao;
    int largura;
    int altura;
} Imagem;

// Definindo e inicializando uma variável nula do tipo no_lista_simples que vai auxiliar nas operações sobre a estrutura de dados Lista Ligada
ListaSimples *noAtual = NULL;

bool ListaSimplesVazia(ListaSimples *inicio);
bool BuscaElementoListaSimples(ListaSimples *inicio, int elem, NoListaSimples **pos, NoListaSimples **ant);
void InserirElementoNoFimLista(ListaSimples **inicio, int valor);
bool RemoveInicioListaSimples(ListaSimples **inicio, int *elem);
void DestroiListaLigada(ListaSimples **inicio);
NoListaSimples *ObterNo(NoListaSimples *noAtual, int indice);
void Dilatacao(NoListaSimples **noAtual, int n, int m);
void Erosao(NoListaSimples **noAtual, int n, int m);
void Abertura(NoListaSimples **noAtual, int n, int m);
void Fechamento(NoListaSimples **noAtual, int n, int m);

// Função para mostrar erro no console e sair do programa
void Erro(char *msg, char *funcao, ...)
{
    va_list args; /* lista de argumentos */
    char msg_final[4096];

    va_start(args, funcao);         /* inicializa a lista args para recuperar argumentos após o argumento funcao */
    vsprintf(msg_final, msg, args); /* envia a lista inteira de argumentos em args para formatação em msg_final */
    va_end(args);                   /* finaliza o processo de recuperação */

    printf("Erro em %s: %s\n", funcao, msg_final);
    fflush(stdout);
    exit(1);
}

// Função para ler imagem binária de arquivo e usar elementos obtidos na alocação dinâmica da struct apropriada
Imagem *LeImagem(char const *nomearquivo)
{
    FILE *arquivo_ponteiro = fopen(nomearquivo, "r");
    if (arquivo_ponteiro == NULL)
    {
        Erro("Erro na abertura do arquivo\n", "LeImagem", arquivo_ponteiro);
        return NULL;
    }
    Imagem *img = (Imagem *)calloc(1, sizeof(Imagem));

    fscanf(arquivo_ponteiro, "%d %d\n", &img->largura, &img->altura);

    img->Posicao = (int **)calloc(img->altura, sizeof(int *));
    for (int y = 0; y < img->altura; y++)
        img->Posicao[y] = (int *)calloc(img->largura, sizeof(int));

    for (int y = 0; y < img->altura; y++)
    {
        for (int x = 0; x < img->largura; x++)
        {
            char caractere_atual;
            fscanf(arquivo_ponteiro, "%c ", &caractere_atual);

            // Converte os caracteres para um inteiros, então subtrai por caractere '0' da tabela ASCII
            // Isso funciona porque o valor ASCII dos caracteres ‘0’ a ‘9’ são consecutivos
            // Logo, subtraindo o valor ASCII de ‘0’ do valor ASCII de qualquer digito caractere deve resultar no equivalente inteiro do digito
            img->Posicao[y][x] = (int)(caractere_atual - '0');
        }
        fscanf(arquivo_ponteiro, "\n");
    }

    fclose(arquivo_ponteiro);
    return (img);
}

// Função para verificar se Lista Ligada Simples possui Nó
bool ListaSimplesVazia(ListaSimples *inicio)
{
    if (inicio == NULL){
        return true;
    }
    else{
        return false;
    }
}

// Função para buscar ultimo Nó dentro de uma Lista Ligada Simples
bool BuscaUltimoElementoListaSimples(ListaSimples *inicio, NoListaSimples **pos, NoListaSimples **ant)
{
    if (!ListaSimplesVazia(inicio)){
        if (inicio->proximo == NULL) {
            *pos = inicio;
            *ant = NULL;
        }
        NoListaSimples *aux = inicio;
        while(aux->proximo != NULL){
            aux = aux->proximo;
        }
        *pos = aux;
        NoListaSimples *aux2 = inicio;
        while(aux2->proximo != *pos){
            aux2 = aux2->proximo;
        }
        *ant = aux2;
        return true;
    }
    else{
        *pos = NULL;
        *ant = NULL;
    }
    return true;
}

// Função para criar um novo Nó na Lista Ligada
NoListaSimples *CriaNoSimples(int elem)
{
    NoListaSimples *No_novo = (NoListaSimples *)calloc(1, sizeof(NoListaSimples));
    No_novo->valor = elem;
    No_novo->proximo = NULL;

    return No_novo;
}

// Função para inserir um novo Nó depois do último Nó presente na Lista Ligada
void InserirElementoNoFimLista(ListaSimples **inicio, int valor)
{
    if (ListaSimplesVazia(*inicio)){
        *inicio = CriaNoSimples(valor);
    }
    else{
        NoListaSimples *aux = *inicio;
        while(aux->proximo != NULL){
            aux = aux->proximo;
        }
        aux->proximo = CriaNoSimples(valor);
    }
}

// Função para remover primeiro Nó na Lista Ligada
bool RemoveInicioListaSimples(ListaSimples **inicio, int *elem)
{
    if (!ListaSimplesVazia(*inicio)){
        NoListaSimples *aux = *inicio;
        *elem = aux->valor;
        *inicio = aux->proximo;
        free(aux);
        return true;
    }
    else{
        return false;
    }
}

// Função para esvaziar a Lista Ligada
void DestroiListaLigada(ListaSimples **inicio)
{
    if (!ListaSimplesVazia(*inicio)){
        NoListaSimples *aux;
        while(*inicio != NULL){
            aux = *inicio;
            *inicio = aux->proximo;
            free(aux);
        }
    }
}

// Função para desalocar a struct Imagem da memória
void DestroiImagem(Imagem **img)
{
    if ((*img) != NULL)
    {
        for (int y = 0; y < (*img)->altura; y++)
            free((*img)->Posicao[y]);
        free((*img)->Posicao);
        free((*img));
        (*img) = NULL;
    }
}

// Função para pegar um Nó localizado no indice posicional na Lista Ligada
NoListaSimples *ObterNo(NoListaSimples *noAtual, int indice)
{
    NoListaSimples *aux = noAtual;
    for (int i = 0; i < indice; i++){
        if (aux == NULL) {
            return NULL; 
        }
        else{
            aux = aux->proximo;
        }
    }
    return(aux);
}

Pixel *ObterAdjacentes(Pixel P)
{
    Pixel *C = (Pixel *)calloc(8, sizeof(Pixel));

    C[0].x = P.x + 1; 
    C[0].y = P.y;

    C[1].x = P.x - 1; 
    C[1].y = P.y;

    C[2].x = P.x + 1; 
    C[2].y = P.y + 1;

    C[3].x = P.x + 1; 
    C[3].y = P.y - 1;

    C[4].x = P.x - 1; 
    C[4].y = P.y + 1;

    C[5].x = P.x - 1; 
    C[5].y = P.y - 1;

    C[6].x = P.x; 
    C[6].y = P.y + 1;

    C[7].x = P.x; 
    C[7].y = P.y - 1;

    return (C);
}

// Função que realiza a operação de dilatação na matriz de números binários
// Essa função recebe o ponteiro para o nó atual na lista, total de linhas 'n'
// e total de colunas 'm' da matriz
void Dilatacao(NoListaSimples **noAtual, int n, int m)
{
    int i, j;
    int valor_referencia, valor;
    NoListaSimples *temp = (NoListaSimples *)calloc(n * m, sizeof(NoListaSimples));

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            valor_referencia = 0;
            Pixel P;
            P.x = i;
            P.y = j;
            Pixel *C = ObterAdjacentes(P);

            for (int k = 0; k < 8; k++)
            {
                if ((C[k].x >= 0) && (C[k].y >= 0) && (C[k].x < n) && (C[k].y < m)) // verifica se é uma posição 2D (i,j) válida no domínio da matriz
                {
                    valor = ObterNo(*noAtual, C[k].x*m + C[k].y)->valor;
                
                    if (valor > valor_referencia) // atualiza min se o valor for menor que min
                    {
                        valor_referencia = valor;
                    }
                }
            }

            free(C);
            temp[i*m + j].valor = valor_referencia;
        }
    }

    // Copia os valores erodidos de volta para a lista original
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            NoListaSimples *aux;
            aux = ObterNo(*noAtual, i*m + j);
            if(aux){
                aux->valor =  temp[i*m + j].valor;
            }
        }
    }
    free(temp);
}

void Erosao(NoListaSimples **noAtual, int n, int m)
{
    int i, j;
    int valor_referencia, valor;
    NoListaSimples *temp = (NoListaSimples *)calloc(n * m, sizeof(NoListaSimples));

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            valor_referencia = 1;
            Pixel P;
            P.x = i;
            P.y = j;
            Pixel *C = ObterAdjacentes(P);

            for (int k = 0; k < 8; k++)
            {
                if ((C[k].x >= 0) && (C[k].y >= 0) && (C[k].x < n) && (C[k].y < m)) // verifica se é uma posição 2D (i,j) válida no domínio da matriz
                {
                    valor = ObterNo(*noAtual, C[k].x*m + C[k].y)->valor;

                    if (valor < valor_referencia) // atualiza min se o valor for menor que min
                    {
                        valor_referencia = valor;
                    }
                }
            }

            free(C);
            temp[i*m + j].valor = valor_referencia;
            
        }
    }

    // Copia os valores erodidos de volta para a lista original
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            NoListaSimples *aux;
            aux = ObterNo(*noAtual, i*m + j);
            if(aux){
                aux->valor =  temp[i*m + j].valor;
            }
        }
    }
    free(temp);
}

void Abertura(NoListaSimples **noAtual, int n, int m)
{
    /*
    A operação de abertura é realizada primeiro aplicando a erosão, seguida
    pela dilatação. A abertura suaviza o contorno de uma imagem, quebra
    estreitamentos e elimina projeções finas.
    */

    Erosao(noAtual, n, m);
    Dilatacao(noAtual, n, m); 
}

void Fechamento(NoListaSimples **noAtual, int n, int m)
{
    /*
    A operação de fechamento é o inverso da abertura. Primeiro, aplica-se a
    dilatação e, em seguida, a erosão. O fechamento também suaviza o contorno
    de uma imagem, mas, ao contrário da abertura, o fechamento geralmente
    funde estreitamentos e preenche buracos (valores '0s' com valores '1s' adjacentes) pequenos.
    */

    Dilatacao(noAtual, n, m);
    Erosao(noAtual, n, m);
}

// essa função mostra a Lista Ligada em um formato mais legível de matrizes numéricas
void VisualizarListaComoMatriz(NoListaSimples *cabeca, int linhas, int colunas)
{
    NoListaSimples *noAtual = cabeca;
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            if (noAtual != NULL)
            {
                printf("%d ", noAtual->valor);
                char caractere_valor_atual = noAtual->valor + '0';
                if (arquivo_saida_ponteiro != NULL)
                {
                    fprintf(arquivo_saida_ponteiro, "%c ", caractere_valor_atual);
                }

                noAtual = noAtual->proximo;
            }
        }
        printf("\n");
        if (arquivo_saida_ponteiro != NULL)
        {
            fprintf(arquivo_saida_ponteiro, "\n");
        }
    }
}

// Função para preencher uma Lista Ligada com os elementos obtidos de cada posição da Imagem
void PreencherListaLigadaComImagemBinaria(Imagem *imagem_binaria)
{
    int ncolunas = imagem_binaria->altura;
    int nlinhas = imagem_binaria->largura;
    for (int i = 0; i < ncolunas; i++)
    {
        for (int j = 0; j < nlinhas; j++)
        {
            InserirElementoNoFimLista(&noAtual, imagem_binaria->Posicao[i][j]);
        }
    }
}

// Função para exibir todos os resultados do programa no console
void ExibirResultados(Imagem *imagem_binaria, int NUM_COLUNAS, int NUM_LINHAS)
{
    printf("Dilation\n");
    if (arquivo_saida_ponteiro != NULL)
    {
        fprintf(arquivo_saida_ponteiro, "%s\n", "Dilation");
    }
    Dilatacao(&noAtual, NUM_COLUNAS, NUM_LINHAS);
    VisualizarListaComoMatriz(noAtual, NUM_LINHAS, NUM_COLUNAS);
    DestroiListaLigada(&noAtual);
    PreencherListaLigadaComImagemBinaria(imagem_binaria);

    printf("Erosion\n");
    if (arquivo_saida_ponteiro != NULL)
    {
        fprintf(arquivo_saida_ponteiro, "%s\n", "Erosion");
    }
    Erosao(&noAtual, NUM_COLUNAS, NUM_LINHAS);
    VisualizarListaComoMatriz(noAtual, NUM_LINHAS, NUM_COLUNAS);
    DestroiListaLigada(&noAtual);
    PreencherListaLigadaComImagemBinaria(imagem_binaria);

    printf("Opening\n");
    if (arquivo_saida_ponteiro != NULL)
    {
        fprintf(arquivo_saida_ponteiro, "%s\n", "Opening");
    }
    Abertura(&noAtual, NUM_COLUNAS, NUM_LINHAS);
    VisualizarListaComoMatriz(noAtual, NUM_LINHAS, NUM_COLUNAS);
    DestroiListaLigada(&noAtual);
    PreencherListaLigadaComImagemBinaria(imagem_binaria);

    printf("Closing\n");
    if (arquivo_saida_ponteiro != NULL)
    {
        fprintf(arquivo_saida_ponteiro, "%s\n", "Closing");
    }
    Fechamento(&noAtual, NUM_COLUNAS, NUM_LINHAS);
    VisualizarListaComoMatriz(noAtual, NUM_LINHAS, NUM_COLUNAS);
    DestroiListaLigada(&noAtual);
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        Erro(
            "%s <arquivo texto de entrada> [<arquivo texto de saida>]\n"
            "Por exemplo, ./main ./arq1.in ./arq1.out\n",
            "main", argv[0]);
    }
    char *arquivo_saida = argv[2];
    if (arquivo_saida != NULL)
    {
        arquivo_saida_ponteiro = fopen(argv[2], "w");
        if (arquivo_saida_ponteiro == NULL)
        {
            printf("Falha na abertura do arquivo");
            return -1;
        }
    }

    Imagem *imagem_binaria = NULL;

    imagem_binaria = LeImagem(argv[1]);

    int NUM_LINHAS = imagem_binaria->largura;
    int NUM_COLUNAS = imagem_binaria->altura;

    PreencherListaLigadaComImagemBinaria(imagem_binaria);

    ExibirResultados(imagem_binaria, NUM_COLUNAS, NUM_LINHAS);

    DestroiImagem(&imagem_binaria);
    if (arquivo_saida_ponteiro != NULL)
    {
        fclose(arquivo_saida_ponteiro);
    }

    return 0;
}
