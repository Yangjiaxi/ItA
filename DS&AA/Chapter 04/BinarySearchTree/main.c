#include <stdio.h>
#include "Tree.h"

int main()
{
  SearchTree Root;
  Root = NULL;
  MakeEmpty(Root);
  Root = Insert(6, Root);
  Root = Insert(8, Root);
  Root = Insert(2, Root);
  Root = Insert(1, Root);
  Root = Insert(4, Root);
  Root = Insert(3, Root);

  printf("\nInorder:");
  InorderTreeWalk(Root);
  printf("\nPreOrder:");
  PreTreeWalk(Root);
  printf("\nPostOrder:");
  PostTreeWalk(Root);

  Root = Delete(2, Root);
  printf("Del Ele 2\n");
  printf("\nInorder:");
  InorderTreeWalk(Root);
  printf("\nPreOrder:");
  PreTreeWalk(Root);
  printf("\nPostOrder:");
  PostTreeWalk(Root);

  MakeEmpty(Root);
  return 0;
}