#include <stdio.h>
#include <stdlib.h>

typedef struct SNo 
{
  int chave, f;
  struct SNo *fe, *fd;
} SNo;

SNo *criaNo(int chave)
{
  SNo *novoNo = (SNo *)malloc(sizeof(SNo)); 
  novoNo->chave = chave;
  novoNo->f = 0;
  novoNo->fe = NULL;
  novoNo->fd = NULL;
  return novoNo;
}

void rotacaoDireita(SNo **raiz)
{
  SNo *B = (*raiz)->fe;
  
  (*raiz)->fe = B->fd;
  B->fd = (*raiz);
  (*raiz) = B;
}

void rotacaoEsquerda(SNo **raiz)
{
  SNo *B = (*raiz)->fd;
  
  (*raiz)->fd = B->fe;
  B->fe = (*raiz);
  (*raiz) = B;
}

void atualizaF(SNo *no, int f)
{
  if ( no != NULL)
    no->f = f;
}

void RotacaoDuplaDireita(SNo **raiz)
{
  rotacaoEsquerda(&((*raiz)->fe));
  rotacaoDireita(raiz);
}

void RotacaoDuplaEsquerda(SNo **raiz)
{
  rotacaoDireita(&((*raiz)->fd));
  rotacaoEsquerda(raiz);
}



// ------------------------------------------------------------------
// Trata Inserção de nós
// ------------------------------------------------------------------
void trataInsercaoEsquerda(SNo **raiz, int *mudouAltura)
{
  if ((*raiz)->f == 1) // Caso 1
  {
    atualizaF((*raiz)->f, 0);
    *mudouAltura = 0;
  }
  else if ( (*raiz)->f == 0) // Caso 2
  {
    (*raiz)->f = -1;
    *mudouAltura = 1;
  }
  else if ( (*raiz)->f == -1 && (*raiz)->fe->f == -1) // Caso 3
  {
    rotacaoDireita(raiz);
    atualizaF((*raiz)->f, 0);
    atualizaF((*raiz)->fd, 0);
    *mudouAltura = 0;
  }
  else if ( (*raiz)->f == -1 && (*raiz)->fe->f == 1) // Caso 4
  {
    RotacaoDuplaDireita(raiz);
    
    if ((*raiz)->f == -1) // Nó C
    {
      atualizaF((*raiz)->fe, 0); // Nó B
      atualizaF((*raiz)->fd, 1); // Nó A
    }
    else if ((*raiz)->f == 0)
    {
      atualizaF((*raiz)->fe, 0); // Nó B
      atualizaF((*raiz)->fd, 0); // Nó A
    }
    else // (*raiz)->f == 1 (Nó C)
    {
      atualizaF((*raiz)->fe, -1); // Nó B
      atualizaF((*raiz)->fd, 0); // Nó A
    }
    atualizaF((*raiz), 0);
    *mudouAltura = 0;
  }
}

void trataInsercaoDireita(SNo **raiz, int *mudouAltura)
{
  if ((*raiz)->f == -1) // Caso 1
  {
    atualizaF((*raiz), 0);
    *mudouAltura = 0;
  }
  else if ( (*raiz)->f == 0) // Caso 2
  {
    atualizaF((*raiz), 1);
    *mudouAltura = 1;
  }
  else if ( (*raiz)->f == 1 && (*raiz)->fd->f == 1) // Caso 3
  {
    rotacaoEsquerda(raiz);
    atualizaF((*raiz), 0);
    atualizaF((*raiz)->fd, 0);
    *mudouAltura = 0;
  }
  else if ( (*raiz)->f == 1 && (*raiz)->fd->f == -1) // Caso 4
  {
    RotacaoDuplaEsquerda(raiz);
    
    if ((*raiz)->f == -1) // Nó C
    {
      atualizaF((*raiz)->fe, 0);
      atualizaF((*raiz)->fd, 1);
    }
    else if ((*raiz)->f == 0)
    {
      atualizaF((*raiz)->fe, 0);
      atualizaF((*raiz)->fd, 0);
    }
    else // (*raiz)->f == 1 (Nó C)
    {
      atualizaF((*raiz)->fe, 1);
      atualizaF((*raiz)->fd, 0);
    }
    atualizaF((*raiz), 0);
    *mudouAltura = 0;
  }  
}

void insereNo(SNo **raiz, int chave, int *mudouAltura)
{
  if ((*raiz) == NULL)
  {
    (*raiz) = criaNo(chave);
    *mudouAltura = 1;
  }
  else if (chave < (*raiz)->chave)
  {
    insereNo( &((*raiz)->fe), chave, mudouAltura);
    if (*mudouAltura == 1) 
      trataInsercaoEsquerda(raiz, mudouAltura);
  }
  else
  {
    insereNo( &((*raiz)->fd), chave, mudouAltura);
    if (*mudouAltura == 1)
      trataInsercaoDireita(raiz, mudouAltura);
  }
}

// ------------------------------------------------------------------
// Trata Remoção de nós
// ------------------------------------------------------------------
void trataRemocaoEsquerda(SNo **raiz, int *mudouAltura)
{
  if ((*raiz)->f == -1) // Caso 1
  {
    atualizaF((*raiz), 0);
    *mudouAltura = 1;
  }
  else if ((*raiz)->f == 0) // Caso 2
  {
    atualizaF((*raiz), 1);
    *mudouAltura = 0;
  }
  else if ((*raiz)->f == 1 && ((*raiz)->fd->f == 0 || 
                               (*raiz)->fd->f == 1)) // Caso 3
  {
    rotacaoEsquerda(raiz);
    if ((*raiz)->f == 0)
    {
      atualizaF((*raiz), -1);
      atualizaF((*raiz)->fe, 1);
      *mudouAltura = 0;
    }
    else if((*raiz)->f == 1)
    {
      atualizaF((*raiz), 0);
      atualizaF((*raiz)->fe, 0);
      *mudouAltura = 1;
    }
  }
  else if ( (*raiz)->f == 1 && (*raiz)->fd->f == -1) // Caso 4
  {
    RotacaoDuplaEsquerda(raiz);
    if ((*raiz)->f == -1)
    {
      atualizaF((*raiz)->fe, 0);
      atualizaF((*raiz)->fd, 1);
    }
    else if ((*raiz)->f == 1)
    {
      atualizaF((*raiz)->fe, -1);
      atualizaF((*raiz)->fd, 0);
    }
    else if ((*raiz)->f == 0)
    {
      atualizaF((*raiz)->fe, 0);
      atualizaF((*raiz)->fd, 0);
    }
    atualizaF((*raiz), 0);
    *mudouAltura = 1;
  }
}

void trataRemocaoDireita(SNo **raiz, int *mudouAltura)
{
  
}

void executaRemocao(SNo **raiz, int *mudouAltura)
{
  if ((*raiz)->fe == NULL && (*raiz)->fd == NULL)
  {
    free(*raiz);
    (*raiz) = NULL;
    *mudouAltura = 1;
  }
  else if ((*raiz)->fe == NULL)
  {
    SNo *temp = (*raiz);
    (*raiz) = (*raiz)->fd;
    free(temp);
    *mudouAltura = 1;
  }
  else if ((*raiz)->fd == NULL)
  {
    SNo *temp = (*raiz);
    (*raiz) = (*raiz)->fe;
    free(temp);
    *mudouAltura = 1;
  }
  else 
  {
    SNo **sucessor = &((*raiz)->fd);
    while ( (*sucessor)->fe != NULL)
      sucessor = &((*sucessor)->fe);
    (*raiz)->chave = (*sucessor)->chave;
    removeNo(&((*raiz)->fd), (*sucessor)->chave, mudouAltura);
  }
}

void removeNo(SNo **raiz, int chave, int *mudouAltura)
{
  if((*raiz) == NULL)
    return;
  
  if(chave < (*raiz)->chave)
  {
    removeNo(&((*raiz)->fe), chave, mudouAltura);
    if (*mudouAltura == 1)
      trataRemocaoEsquerda(raiz, mudouAltura);
  }
  else if (chave > (*raiz)->chave)
  {
    removeNo(&(*raiz)->fd, chave, mudouAltura);
    if (*mudouAltura == 1)
      trataRemocaoDireita(raiz, mudouAltura);
  }
  else if (chave == (*raiz)->chave)
  {
    executaRemocao(raiz, mudouAltura);
  }
}


void emOrdem(SNo *raiz, int quebraLinha)
{
  if ( raiz == NULL )
    return ;
  emOrdem(raiz->fe, 0);
  printf("%02d  ", raiz->chave);
  emOrdem(raiz->fd, 0);

  if(quebraLinha)
    printf("\n");
}

void preOrdem(SNo *raiz, int quebraLinha)
{
  if (raiz == NULL)
    return;
  printf("%02d  ", raiz->chave);
  preOrdem(raiz->fe, 0);
  preOrdem(raiz->fd, 0);
  
  if(quebraLinha)
    printf("\n");
}

void buscaNaArvore(SNo *raiz, int chave)
{
  SNo *temp = raiz;
  while(temp != NULL)
  {
    if(temp->chave == chave)
    {
      printf("%d encontrado.\n", chave);
      return ;
    }
    else if (chave < temp->chave)
      temp = temp->fe;
    else
      temp = temp->fd;
  }
  printf("Valor %d nao encontrado\n", chave);
}


int main(void)
{
  SNo *AVL = NULL;
  int mudouAltura;

  // Testa tratamento inserção a esquerda
  // insereNo(&AVL, 200, &mudouAltura);
  // insereNo(&AVL, 100, &mudouAltura);
  // insereNo(&AVL, 250, &mudouAltura);
  
  // insereNo(&AVL, 90, &mudouAltura);
  // insereNo(&AVL, 105, &mudouAltura);

  // insereNo(&AVL, 108, &mudouAltura);
  // -------------------------------


  // Testa tratamento inserção a direita
  insereNo(&AVL, 200, &mudouAltura);
  insereNo(&AVL, 100, &mudouAltura);
  insereNo(&AVL, 250, &mudouAltura);
  
  insereNo(&AVL, 205, &mudouAltura);
  insereNo(&AVL, 300, &mudouAltura);

  insereNo(&AVL, 201, &mudouAltura);
  // -------------------------------
  
  return 0;
}
