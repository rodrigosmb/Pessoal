#include <stdio.h>
#include <stdlib.h>
/* Algoritmo para desenhar linhas em uma matriz e verificar linhas que
se interceptam */

typedef struct ponto {
  int x, y;
} Ponto;
// y = mx + n
typedef struct reta
{
  Ponto inicio, fim;
  float coeficiente_angular; // m
  float coeficiente_linear; // n
} Reta;

int **CriaMatriz(int altura, int largura);
void DestroiMatriz(int **matriz, int altura);
void ExibeMatriz(int **matriz, int altura, int largura);
void DesenhaLinhas(int **matriz, int altura, int largura, Reta reta);
void ConfiguraCoeficientesReta(Reta *reta);
/* Retorna:
0: Se paralelas
1: Se concorrentes
2: Se coincidentes
*/
int VerificaInterseccao(Reta reta_1, Reta reta_2, Ponto *interseccao);

int main(int argc, char *argv[]) {
  Reta reta_1, reta_2;

  // Read file
  FILE *fp = fopen(argv[1], "r");
  fscanf(
    fp, "(%d %d %d %d) ",
    &reta_1.inicio.x, &reta_1.inicio.y, &reta_1.fim.x, &reta_1.fim.y
  );
  fscanf(
    fp, "(%d %d %d %d)",
    &reta_2.inicio.x, &reta_2.inicio.y, &reta_2.fim.x, &reta_2.fim.y
  );
  fclose(fp);

  int largura = 100, altura = 100;
  int **matriz = CriaMatriz(altura, largura);
  ConfiguraCoeficientesReta(&reta_1);
  ConfiguraCoeficientesReta(&reta_2);
  DesenhaLinhas(matriz, altura, largura, reta_1);
  DesenhaLinhas(matriz, altura, largura, reta_2);
  Ponto interseccao;
  int status = VerificaInterseccao(reta_1, reta_2, &interseccao);
  if (status == 0) {
    printf("Retas são paralelas\n");
  } else if (status == 1) {
    printf("Retas são concorrentes\n");
    if (
      (interseccao.x > 0 && interseccao.x < largura) &&
      (interseccao.y > 0 && interseccao.y < altura)
    ) {
      printf("Intersecção ocorre na matriz\n");
      // Marca o ponto de intersecção com 2
      matriz[99 - interseccao.y][interseccao.x] = 2;
    }
    else {
      printf("Intersecção ocorre fora da matriz\n");
    }
    printf("Intersecção: (%d, %d)\n", interseccao.x, interseccao.y);

  } else if (status == 2) {
    printf("Retas são coincidentes\n");
  }

  ExibeMatriz(matriz, altura, largura);
  DestroiMatriz(matriz, altura);

  return 0;
}

int VerificaInterseccao(Reta reta_1, Reta reta_2, Ponto *interseccao) {

  if((reta_1.inicio.x != reta_1.fim.x) && (reta_2.inicio.x != reta_2.fim.x)){
    float sample = (reta_2.coeficiente_linear - reta_1.coeficiente_linear)/(reta_1.coeficiente_angular - reta_2.coeficiente_angular);
    interseccao->x = (int)(sample);
    interseccao->y = (int)(reta_1.coeficiente_angular * sample + reta_1.coeficiente_linear);

    if(reta_1.coeficiente_angular == reta_2.coeficiente_angular){
      if(reta_1.coeficiente_linear == reta_2.coeficiente_linear){
        return 2;
      }
      else{
        return 0;
      }
    }
    else{
      return 1;
    }
  }

  else if(reta_1.inicio.x == reta_1.fim.x){
    if(reta_2.inicio.x == reta_2.fim.x){
      if(reta_1.inicio.x == reta_2.inicio.x){
        return 2;
      }
      else{
        return 0;
      }
    }
    else{
      interseccao->x = reta_1.inicio.x;
      interseccao->y = (int)(reta_2.coeficiente_angular * reta_1.inicio.x + reta_2.coeficiente_linear);
      return 1;
    }
  }
  else{
    if(reta_1.inicio.x == reta_1.fim.x){
      if(reta_1.inicio.x == reta_2.inicio.x){
        return 2;
      }
      else{
        return 0;
      }
    }
    else{
      interseccao->x = reta_2.inicio.x;
      interseccao->y = (int)(reta_1.coeficiente_angular * reta_2.inicio.x + reta_1.coeficiente_linear);
      return 1;
    }
  }
}

void DesenhaLinhas(int **matriz, int altura, int largura, Reta reta) {
  
  int x, y;
  if(reta.inicio.x != reta.fim.x){
    for(y = reta.inicio.y; y <= altura; y++){
      for(x = reta.inicio.x; x <= reta.fim.x; x++){
        if((y == (int)(reta.coeficiente_angular * x + reta.coeficiente_linear)) && y >= 0 && y < 100  && x >= 0 && x < 100){
          matriz[altura -  1 - y][x] = 1;
        }
      }
    }
  }
  else{
    for(y = reta.inicio.y ; y < reta.fim.y; y++){
      for(x = reta.inicio.x; x < largura; x++){
        if(x == reta.inicio.x && y >= 0 && x >= 0){
          matriz[altura -  1 - y][x] = 1;
        }
      }
    }
  }
}

void ConfiguraCoeficientesReta(Reta *reta) {
  
  if(reta->inicio.y == reta->fim.y){
    reta->coeficiente_angular = 0;
    reta->coeficiente_linear = reta->inicio.y;
  }
  else if(reta->inicio.x == reta->fim.x){
    
  }
  else{
    reta->coeficiente_angular = ((float)reta->fim.y - (float)reta->inicio.y)/((float)reta->fim.x - (float)reta->inicio.x);
    if(((float)reta->inicio.x == 0.0) && ((float)reta->inicio.y == 0.0)){
      reta->coeficiente_linear = (float)0.0; 
    }
    else{
    reta->coeficiente_linear = ((float)reta->fim.y) - ((float)reta->coeficiente_angular*(float)reta->fim.x);
    }
  }
}
void ExibeMatriz(int **matriz, int altura, int largura) {
  for (int linha = 0; linha < altura; linha++) {
    printf("[ ");
    for (int coluna = 0; coluna < largura; coluna++) {
      printf("%d ", matriz[linha][coluna]);
    }
    printf("]\n");
  }
}

int **CriaMatriz(int altura, int largura) {
  int **matriz = (int **)calloc(altura, sizeof(int *));
  // Para cada linha, aloca memória para suas colunas
  for (int linha = 0; linha < altura; linha++) {
    matriz[linha] = (int *)calloc(largura, sizeof(int));
    // Inicializa os valores da linha
    for (int coluna = 0; coluna < largura; coluna++) {
      matriz[linha][coluna] = 0;
    }
  }

  return matriz;
}

void DestroiMatriz(int **matriz, int altura) {
  if (matriz != NULL) {
    for (int i = 0; i < altura; i++) {
      if (matriz[i] != NULL) {
        free(matriz[i]);
      }
    }
    free(matriz);
  }
}