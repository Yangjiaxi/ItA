#include <stdio.h>

int V; //节点数
int M[103][103]; //邻接矩阵 ，表中有效数据为[1..V][1..V]
int E; //边数


int main()
{
  printf("<------UNDIRECTED GRAPH------>\n");
  printf("THE NUMBER OF VERTEX(<=100):");
  scanf("%d", &V);
  printf("THE NUMBER OF EDGE:");
  scanf("%d", &E);
  int ov, iv;
  printf("EACH PAIR OF LINKED VERTEX:\n");
  for (int i = 1; i <= E; i++)
  {
    scanf("%d%d", &ov, &iv);
    if (ov > V || iv > V)
    {
      printf("ERROR: TOO BIG VERTEX NUMBER\n");
    }
    else
    {
      M[ov][iv] = M[iv][ov] = 1;
    }
  }

  for (int i = 1; i <= V; i++)
  {
    for (int j = 1; j <= V; j++)
    {
      printf("%d ", M[i][j]);
    }
    printf("\n");
  }

  return 0;
}