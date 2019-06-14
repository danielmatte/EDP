#include <stdio.h>
#include <stdlib.h>

typedef struct node_t{
  int key;
  struct node_t *left;
  struct node_t *right;
} node_t;

void inOrder(node_t *root, int lineBreak)
{
  if ( root == NULL )
    return;
  inOrder(root->left, 0);
  printf("%02d  ", root->key);
  inOrder(root->right, 0);
  if (lineBreak)
    printf("\n");
}

node_t *createNode(int key)
{
  node_t *newNode = (node_t *)malloc(sizeof(node_t));
  newNode->key = key;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

void addNode(node_t **root, int key)
{
  if ( (*root) == NULL )
    (*root) = createNode(key);
  else if (key > (*root)->key )
    addNode(&((*root)->right), key);
  else
    addNode(&((*root)->left), key);
}

void removeNode(node_t **root, int key)
{
  if ( (*root) == NULL )
    return;
  if (key < (*root)->key)
    removeNode(&((*root)->left), key);
  else if ( key > (*root)->key)
    removeNode(&((*root)->right), key);
  else
  {
    if ( (*root)->left == NULL && (*root)->right == NULL )
    {
      free(*root); 
      (*root)=NULL;
    }
    else if ( (*root)->left == NULL )
    {
      node_t *tmp = (*root);
      (*root) = (*root)->right;
      free(tmp);
    }
    else if ( (*root)->right == NULL )
    {
      node_t *tmp = (*root);
      (*root) = (*root)->left;
      free(tmp);
    }
    else
    {
      node_t **successor = &((*root)->right), *tmp;
      while ( (*successor)->left != NULL)
        successor = &((*successor)->left);
      (*root)->key = (*successor)->key;
      removeNode(successor, (*successor)->key);
    }
  }
}

int main(void)
{
  node_t *BST = NULL;
  
  addNode(&BST, 20);
  addNode(&BST, 10);
  addNode(&BST, 30);
  addNode(&BST, 5);
  addNode(&BST, 15);
  addNode(&BST, 25);
  addNode(&BST, 35);
  addNode(&BST, 33);
  addNode(&BST, 40);
  inOrder(BST, 1);
  
  removeNode(&BST, 5);
  inOrder(BST, 1);
  
  removeNode(&BST, 35);
  removeNode(&BST, 40);
  removeNode(&BST, 33);
  removeNode(&BST, 25);
  inOrder(BST, 1);
 
  removeNode(&BST, 30);
  removeNode(&BST, 20);
  inOrder(BST, 1);
  
  removeNode(&BST, 10);
  removeNode(&BST, 15);
  
  inOrder(BST, 1);

  return 0;
}