#include <stdio.h>
#include <stdlib.h>

typedef enum{
    false = 0,
    true = 1
} bool;

typedef struct _ponto {
  int x, y, z;
} Ponto;

typedef struct _labirinto {
  char ***Posicao;
  int tam_x, tam_y, tam_z, num_entradas, num_saidas;
  Ponto *entradas, *saidas;
} Labirinto;

Labirinto *LeLabirinto(char *nomearq){
  int count = 0;
  char c;
  FILE *fp = fopen(nomearq,"r");
  Labirinto *L = (Labirinto *)calloc(1,sizeof(Labirinto));

  fscanf(fp,"%d %d %d %d\n", &L->tam_x, &L->tam_y, &L->tam_z, &L->num_entradas);

  L->num_saidas = 0;
  L->entradas = (Ponto *)calloc(L->num_entradas, sizeof(Ponto));
  L->Posicao = (char ***)calloc(L->tam_z, sizeof(char **));

  for (int i = 0; i < L->tam_z; i++){
    L->Posicao[i] = (char **)calloc(L->tam_y, sizeof(char *));
    for (int j = 0; j < L->tam_y; j++){
      L->Posicao[i][j] = (char *)calloc(L->tam_x, sizeof(char));
    }
  }

  for (int i = 0; i < L->tam_z; i++){ 
    for (int j = 0; j < L->tam_y; j++){
      fscanf(fp,"%c",&L->Posicao[i][j][0]);
      if (L->Posicao[i][j][0] == 'E'){
	    L->entradas[count].x = 0;
        L->entradas[count].y = j;
        L->entradas[count].z = i;
	    L->Posicao[i][j][0] = 'P';
        count++;
      } 
      else if(L->Posicao[i][j][0] == 'S'){
        L->num_saidas++;
      }
      for (int k = 1; k < L->tam_x; k++){
        fscanf(fp,"   %c",&L->Posicao[i][j][k]);
        if (L->Posicao[i][j][k] == 'E'){
	      L->entradas[count].x = k;
          L->entradas[count].y = j;
          L->entradas[count].z = i;
	      L->Posicao[i][j][k] = 'P';
          count++;
        } 
        else if(L->Posicao[i][j][k] == 'S'){
          L->num_saidas++;
        }
      }
      fscanf(fp, "%c", &c);
    }
    fscanf(fp, "%c", &c);
  }
  fclose(fp);
  count = 0;
  L->saidas = (Ponto *)calloc(L->num_saidas, sizeof(Ponto));
  for (int i = 0; i < L->tam_z; i++){ 
    for (int j = 0; j < L->tam_y; j++){
      for (int k = 0; k < L->tam_x; k++){
        if (L->Posicao[i][j][k] == 'S'){
	        L->saidas[count].x = k;
          L->saidas[count].y = j;
          L->saidas[count].z = i;
	        L->Posicao[i][j][k] = 'P';
          count++;
        }
      }
    }
  }
  return(L);
}

void DestroiLabirinto(Labirinto **L)
{
  if ((*L) != NULL){
    for (int i = 0; i < (*L)->tam_z; i++){
      for (int j = 0; j < (*L)->tam_y; j++){
        free((*L)->Posicao[i][j]);
      }
      free((*L)->Posicao[i]);
    }
    free((*L)->Posicao);
    free((*L)->entradas);
    free((*L)->saidas);
    free((*L));
    (*L) = NULL;
  }
}

bool Backtrack(Labirinto *L, Ponto P)
{
  bool res = false;
  int flag = 0;
  for (int i = 0; i < L->num_saidas; i++){
    if ((P.z == L->saidas[i].z)&&(P.y == L->saidas[i].y)&&(P.x == L->saidas[i].x)){ 
      res = true; 
      flag++;
    } 
  }
  if (flag == 0){ 
    Ponto *C = (Ponto *)calloc(6,sizeof(Ponto));
    C[0].x = P.x - 1; 
    C[0].y = P.y;
    C[0].z = P.z;

    C[1].x = P.x + 1; 
    C[1].y = P.y;
    C[1].z = P.z;

    C[2].x = P.x;     
    C[2].y = P.y - 1;
    C[2].z = P.z;

    C[3].x = P.x;     
    C[3].y = P.y + 1;
    C[3].z = P.z;

    C[4].x = P.x;
    C[4].y = P.y;
    C[4].z = P.z - 1;

    C[5].x = P.x;
    C[5].y = P.y;
    C[5].z = P.z + 1;
    
    for (int i = 0; (i < 6) && (res != true); i++){
      if ((C[i].x >= 0)&&(C[i].x < L->tam_x) && (C[i].y >= 0)&&(C[i].y < L->tam_y) && (C[i].z >= 0)&&(C[i].z < L->tam_z)){
	      if (L->Posicao[C[i].z][C[i].y][C[i].x] != 'X'){ 
	        char valor_correto = L->Posicao[C[i].z][C[i].y][C[i].x];
          L->Posicao[C[i].z][C[i].y][C[i].x] = 'X';   
	        res = Backtrack(L, C[i]);
	        L->Posicao[C[i].z][C[i].y][C[i].x] = valor_correto; 
	      }
      }
    }
    free(C);
  }
  return(res);
}

int main(int argc, char **argv){

  Labirinto *L = NULL;
  L = LeLabirinto(argv[1]);
  
  for (int i = 0; i < L->num_entradas; i++){
    if (Backtrack(L, L->entradas[i])){
      printf("[Entrada %d] Saída encontrada!\n", i);
    }
    else{
      printf("[Entrada %d] Saída não encontrada!\n", i);
    }
    
  }
  DestroiLabirinto(&L);
}
