#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a,b) ((a > b)?a:b)

typedef struct NoAVL {  
  int prioridade, info[4];
  int bal; 
  struct NoAVL *esq, *dir;
} NoAVL, AVL;

NoAVL *CriaNovoNo(int a, int b , int c , int d, int prior); 
void InsereValor(AVL **ab, int a, int b , int c , int d, int prior, int *mais_alta);
void RemoveValor(AVL **ab, int valor, int a, int b , int c , int d, int *mais_baixa);
void RemoveDeFato(AVL **ab, int *mais_baixa);
void TrataReducaoArvoreDireita(AVL **ab, int *mais_baixa);
void TrataReducaoArvoreEsquerda(AVL **ab, int *mais_baixa);
char RemoveNoGrau0ou1(AVL **ab, int *mais_baixa);
void SubstituiRemoveMenorSucessor(AVL **ab, AVL **maisesq, int *mais_baixa);
void AjusteBalancoRotacaoDireitaDuplaRemocao(NoAVL *A, NoAVL *B, NoAVL *C);
void AjusteBalancoRotacaoEsquerdaDuplaRemocao(NoAVL *A, NoAVL *B, NoAVL *C);
void AjusteBalancoRotacaoDireitaSimplesRemocao(NoAVL *A, NoAVL *B, int *mais_baixa);
void AjusteBalancoRotacaoEsquerdaSimplesRemocao(NoAVL *A, NoAVL *B, int *mais_baixa);
void TrataAumentoArvoreEsquerda(AVL **ab, int *mais_alta);
void TrataAumentoArvoreDireita(AVL **ab, int *mais_alta);
void AjusteBalancoSimplesInsercao(NoAVL *A, NoAVL *B);
void AjusteBalancoDuplaInsercao(NoAVL *A, NoAVL *B, NoAVL *C);
void RotacaoSimplesEsquerda(AVL **ab);
void RotacaoDuplaEsquerda(AVL **ab);
void RotacaoSimplesDireita(AVL **ab);
void RotacaoDuplaDireita(AVL **ab);
void PrintarArvore(AVL *ab);
void Num_nos(AVL *ab, int *a);
int Ta_cheia(AVL *ab, int num_nos);
int Altura(AVL *ab);
int Rota_mais_longa(AVL *ab);


void PrintarArvore(AVL *ab) {
  if (ab != NULL) {
    printf("- %d.%d.%d.%d: %d\n", ab->info[0], ab->info[1], ab->info[2], ab->info[3], ab->prioridade);
    PrintarArvore(ab->esq);
    PrintarArvore(ab->dir);
  }
}
void Num_nos(AVL *ab, int *a){
  if (ab != NULL) {
    (*a)++;
    Num_nos(ab->esq, a);
    Num_nos(ab->dir, a);
  }
}

int Altura(AVL *ab)
{
  if (ab != NULL) 
    return(1 + MAX(Altura(ab->esq),Altura(ab->dir)));
  else
    return(0);
}

int Ta_cheia(AVL *ab, int num_nos) {
  int i, num_cheia;
  if ((Altura(ab)) == 1){
    num_cheia = 1;
  }
  else{
    num_cheia = 2;
    for (i = 1; i < Altura(ab); i++){
      num_cheia = num_cheia * 2;
    }
    num_cheia--;
  }
  if (num_nos == num_cheia)
    return 1;
  else
    return 0;
}

int Rota_mais_longa(AVL *ab){
  int altura_total = Altura(ab), altura_dir = Altura(ab->dir), altura_esq = Altura(ab->esq);
  if (altura_total == 1)
    return 0;
  else{
    if (altura_dir == altura_esq){
      return (((altura_total) * 2) - 1);
    }
    else{
      return (((altura_total) * 2) - 2);
    }
  }
}

NoAVL *CriaNovoNo(int a, int b , int c , int d, int prior) {

  NoAVL *p = (NoAVL *)calloc(1,sizeof(NoAVL));
  p->esq   = NULL;
  p->dir   = NULL;
  p->bal   = 0;
  p->info[0]  = a; p->info[1]  = b; p->info[2]  = c; p->info[3]  = d;
  p->prioridade = prior;

  return(p);
}

void InsereValor(AVL **ab, int a, int b , int c , int d, int prior, int *mais_alta) {

  if ((*ab) == NULL) { 
    (*ab)      = CriaNovoNo(a, b, c, d, prior);
    *mais_alta = 1;
  } 
  else{ 
    if ((*ab)->prioridade <= prior){
      InsereValor(&((*ab)->dir), a, b, c, d, prior, mais_alta);
      if ((*mais_alta)==1){ 
        TrataAumentoArvoreDireita(ab, mais_alta);
      }
    }
    else{ 
      InsereValor(&((*ab)->esq), a, b, c, d, prior, mais_alta);
      if ((*mais_alta)==1){ 
        TrataAumentoArvoreEsquerda(ab, mais_alta);
      }	
    }
  }
}

void RemoveValor(AVL **ab, int valor, int a, int b , int c , int d, int *mais_baixa) {
  if ((*ab) != NULL){
    if ((*ab)->prioridade != valor || (*ab)->info[0] != a || (*ab)->info[1] != b || (*ab)->info[2] != c || (*ab)->info[3] != d) {
      if ((*ab)->prioridade < valor || 
                ((*ab)->prioridade == valor && 
                ((*ab)->info[0] != a || (*ab)->info[1] != b || (*ab)->info[2] != c || (*ab)->info[3] != d))) {
	      RemoveValor(&((*ab)->dir),valor, a, b, c, d, mais_baixa);
	      if ((*mais_baixa)==1)
	         TrataReducaoArvoreDireita(ab,mais_baixa);
      } 
      else{
	      RemoveValor(&((*ab)->esq),valor, a, b, c, d, mais_baixa);
	        if ((*mais_baixa)==1)
	          TrataReducaoArvoreEsquerda(ab, mais_baixa);
      }
    } 
    else{ 
      RemoveDeFato(ab, mais_baixa);
    }
  }
}

void RemoveDeFato(AVL **ab, int *mais_baixa) {
  int bal;
  if (RemoveNoGrau0ou1(ab,mais_baixa)==0){ 
    bal = (*ab)->bal;
    SubstituiRemoveMenorSucessor(ab,&((*ab)->dir),mais_baixa);
    (*ab)->bal = bal; 	
    if (*mais_baixa)
      TrataReducaoArvoreDireita(ab,mais_baixa); 
  }
}

void TrataReducaoArvoreDireita(AVL **ab, int *mais_baixa) {
  NoAVL *A,*B,*C;

  A = (*ab); 
  B = (*ab)->esq;

  switch(A->bal) {
  case  -1: 
    if (B->bal <= 0){ 
      RotacaoSimplesDireita(ab);
      AjusteBalancoRotacaoDireitaSimplesRemocao(A,B,mais_baixa); 
    }else{ 
      C = B->dir;
      RotacaoDuplaDireita(ab);
      AjusteBalancoRotacaoDireitaDuplaRemocao(A,B,C);
      (*mais_baixa) =  1;
    }
    break;
  case 0: 
    (*ab)->bal    =  -1;
    (*mais_baixa) =   0;
    break;
  case 1:
    (*ab)->bal    =  0;
    (*mais_baixa) =  1;
    break;
  }
}

void TrataReducaoArvoreEsquerda(AVL **ab, int *mais_baixa) {
  NoAVL *A,*B,*C;

  A = (*ab); 
  B = (*ab)->dir;

  switch(A->bal) {
  case  1: 
    if (B->bal >= 0){ 
      RotacaoSimplesEsquerda(ab);
      AjusteBalancoRotacaoEsquerdaSimplesRemocao(A,B,mais_baixa);
    }else{ 
      C = B->esq;
      RotacaoDuplaEsquerda(ab);
      AjusteBalancoRotacaoEsquerdaDuplaRemocao(A,B,C);
      (*mais_baixa) =  1;
    }
    break;
  case 0: 
    A->bal        =  1;    
    (*mais_baixa) =  0;
    break;
  case -1:
    A->bal = 0;  
    (*mais_baixa) =  1;
    break;
  }
}

char RemoveNoGrau0ou1(AVL **ab, int *mais_baixa) {
  AVL *aux;

  if ((*ab)->esq == NULL){ 
    aux   = (*ab);
    (*ab) = (*ab)->dir;
    free(aux);
  } else {
    if ((*ab)->dir == NULL){ 
      aux   = (*ab);
      (*ab) = (*ab)->esq;
      free(aux);
    } else {
      return(0);
    }
  }
  *mais_baixa = 1;
  return(1);
}

void SubstituiRemoveMenorSucessor(AVL **ab, AVL **maisesq, int *mais_baixa) { 
  if ((*maisesq)->esq == NULL){ 
    (*ab)->prioridade = (*maisesq)->prioridade; 
    (*ab)->info[0] = (*maisesq)->info[0];
    (*ab)->info[1] = (*maisesq)->info[1];
    (*ab)->info[2] = (*maisesq)->info[2];
    (*ab)->info[3] = (*maisesq)->info[3];
    RemoveNoGrau0ou1(maisesq,mais_baixa); 
  } else { 
    SubstituiRemoveMenorSucessor(ab,&((*maisesq)->esq),mais_baixa);
    if (*mais_baixa)
      TrataReducaoArvoreEsquerda(maisesq,mais_baixa); 
  }
}

void AjusteBalancoRotacaoDireitaDuplaRemocao(NoAVL *A, NoAVL *B, NoAVL *C) {
  switch(C->bal) {
  case -1:
    A->bal = 1;
    B->bal = 0;
    break;
  case 0:
    A->bal =  0;
    B->bal =  0;
    break;
  case +1:
    A->bal =  0;
    B->bal = -1;
    break;
  }
  C->bal = 0;
}

void AjusteBalancoRotacaoEsquerdaDuplaRemocao(NoAVL *A, NoAVL *B, NoAVL *C) {
  switch(C->bal) {
  case -1:
    A->bal = 0;
    B->bal = 1;
    break;
  case 0:
    A->bal = 0;
    B->bal = 0;
    break;
  case +1:
    A->bal = -1;
    B->bal =  0;
    break;
  }
  C->bal = 0;
}

void AjusteBalancoRotacaoDireitaSimplesRemocao(NoAVL *A, NoAVL *B, int *mais_baixa) {
  if (B->bal == -1){ 
    A->bal =  0;
    B->bal =  0;
    *mais_baixa = 1;
  } else { 
    A->bal = -1;
    B->bal =  1;
    *mais_baixa = 0;
  }
}

void AjusteBalancoRotacaoEsquerdaSimplesRemocao(NoAVL *A, NoAVL *B, int *mais_baixa) {
  if (B->bal == 1){ 
    A->bal =  0;
    B->bal =  0;
    *mais_baixa = 1;
  } else { 
    A->bal =  1;
    B->bal = -1;
    *mais_baixa = 0;
  }
}


void TrataAumentoArvoreEsquerda(AVL **ab, int *mais_alta) {
  NoAVL *A,*B,*C;

  A = (*ab); 
  B = (*ab)->esq;
  C = B->dir;

  switch(A->bal) {
  case -1:
    if (B->bal == -1){ 
      RotacaoSimplesDireita(ab);
      AjusteBalancoSimplesInsercao(A,B);
    }else{ 
      RotacaoDuplaDireita(ab);
      AjusteBalancoDuplaInsercao(A,B,C); 
    }
    (*mais_alta) =  0;
    break;
  case 0: 
    (*ab)->bal   = -1;
    (*mais_alta) =  1; 	

    break;
  case 1:
    (*ab)->bal   =  0;
    (*mais_alta) =  0;
    break;
  }
}

void TrataAumentoArvoreDireita(AVL **ab, int *mais_alta) {
  NoAVL *A,*B,*C;

  A = (*ab);
  B = (*ab)->dir;
  C = B->esq;
  
  switch(A->bal) {
  case 1: 
    if (B->bal == 1){
      RotacaoSimplesEsquerda(ab);
      AjusteBalancoSimplesInsercao(A,B); 
    }else{ 
      RotacaoDuplaEsquerda(ab);
      AjusteBalancoDuplaInsercao(B,A,C); 
    }	  
    *mais_alta   = 0;
    break;
  case 0:
    A->bal       = 1;
    (*mais_alta) = 1; 	
    break;
  case -1:
    A->bal       = 0;
    (*mais_alta) = 0; 	
    break;
  }
}

void AjusteBalancoSimplesInsercao(NoAVL *A, NoAVL *B) {
  A->bal = B->bal = 0;
}

void AjusteBalancoDuplaInsercao(NoAVL *A, NoAVL *B, NoAVL *C) {
  switch(C->bal) {
  case -1:
    A->bal = 1;
    B->bal = 0;
    break;
  case 0:
    A->bal = 0;
    B->bal = 0;
    break;
  case +1:
    A->bal =  0;
    B->bal = -1;
    break;
  }
  C->bal = 0;
}

void RotacaoSimplesEsquerda(AVL **ab) {
  AVL *filho_dir = (*ab)->dir; 

  (*ab)->dir     = filho_dir->esq; 
  filho_dir->esq = (*ab); 
  (*ab)          = filho_dir;

}

void RotacaoDuplaEsquerda(AVL **ab) {
  RotacaoSimplesDireita(&(*ab)->dir);
  RotacaoSimplesEsquerda(ab);
}

void RotacaoSimplesDireita(AVL **ab) {
  AVL *filho_esq = (*ab)->esq; 

  (*ab)->esq     = filho_esq->dir; 
  filho_esq->dir = (*ab); 
  (*ab)          = filho_esq;

}

void RotacaoDuplaDireita(AVL **ab) {
  RotacaoSimplesEsquerda(&(*ab)->esq);
  RotacaoSimplesDireita(ab);
}


int main(int argc, char const *argv[]) {
  int info[4];
  int prioridade = 0, num_nos = 0, mais_alta = 0, mais_baixa = 0, num_ops = 0, operacao = 0, num_nos_atualizado = 0;
  AVL *arvore = NULL;

  FILE *arquivo_1 = fopen(argv[1], "r");
  if (arquivo_1 == NULL){
    printf("Erro ao ler arquivo 1");
  }
  fscanf(arquivo_1, "%d", &num_nos);
  for(int i = 0; i < num_nos; i++){
    fscanf(arquivo_1, "%d.%d.%d.%d %d", &info[0], &info[1], &info[2], &info[3], &prioridade);
    InsereValor(&arvore, info[0], info[1] , info[2] , info[3], prioridade, &mais_alta);
  }
  fclose(arquivo_1);

  printf("[INFO] Apos construcao:\n");
  PrintarArvore(arvore);
  if(Ta_cheia(arvore, num_nos) == 0)
    printf("Arvore nao esta cheia\n");
  else
    printf("Arvore esta cheia\n");
  printf("A rota mais longa possivel passa por %d nos\n\n", Rota_mais_longa(arvore));

  FILE *arquivo_2 = fopen(argv[2], "r");
  if (arquivo_2 == NULL){
      printf("Erro ao ler arquivo 2");
  }
  fscanf(arquivo_2, "%d", &num_ops);
  for(int j = 0; j < num_ops; j++){
    fscanf(arquivo_2, "%d %d.%d.%d.%d %d", &operacao, &info[0], &info[1], &info[2], &info[3], &prioridade);
    if(operacao == 1){
      InsereValor(&arvore, info[0], info[1] , info[2] , info[3], prioridade, &mais_alta);
    }
    else{
      RemoveValor(&arvore, prioridade, info[0], info[1] , info[2] , info[3], &mais_baixa);
    }
  }
  fclose(arquivo_2);

  printf("[INFO] Apos atualizacao:\n");
  PrintarArvore(arvore);
  Num_nos(arvore, &num_nos_atualizado);
  if(Ta_cheia(arvore, num_nos_atualizado) == 0)
    printf("Arvore nao esta cheia\n");
  else
    printf("Arvore esta cheia\n");
  printf("A rota mais longa possivel passa por %d nos\n", Rota_mais_longa(arvore));
}