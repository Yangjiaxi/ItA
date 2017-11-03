/* ##BFS完成图的遍历##
 * 测试样例:
 * VERTEX = 8
 * EDGE = 10
 * 1 2
 * 2 3
 * 3 4
 * 4 5
 * 4 6
 * 5 6
 * 5 7
 * 5 8
 * 6 7
 * 7 8
 * START = 3
 *
 * 输出:
 * NUMBER:1        PREVERTEX:2     DIS:2
 * NUMBER:2        PREVERTEX:3     DIS:1
 * NUMBER:3        PREVERTEX:-1    DIS:0
 * NUMBER:4        PREVERTEX:3     DIS:1
 * NUMBER:5        PREVERTEX:4     DIS:2
 * NUMBER:6        PREVERTEX:4     DIS:2
 * NUMBER:7        PREVERTEX:5     DIS:3
 * NUMBER:8        PREVERTEX:5     DIS:3
 */


#include <stdio.h>
#include "queue.h"

typedef struct _vertex
{
  int d;  //从起始节点到该节点的距离
  int isVis;//是否被访问过
  int preVertex; //前驱节点编号
} vertex;

int V; //节点数
int E; //边数
int M[103][103]; //邻接矩阵 ，表中有效数据为[1..V][1..V]
vertex VO[103]; //保存节点的各种属性
int beginVertex; //起始节点编号

Queue Q; // 用于保存遍历节点的队列

void BFS(int s)
{
  for (int i = 1; i <= V; i++)
  {
    VO[i].isVis = 0;
    VO[i].d = -1;
    VO[i].preVertex = -1; //尚未有前驱
  }
  VO[s].isVis = 1;
  VO[s].d = 0;
  VO[s].preVertex = -1;
  initializeQueue(&Q);  //初始化队列
  enQueue(&Q, s);
  while (!isEmpty(&Q)) //当队列非空时
  {
    int u = deQueue((&Q));
    for (int v = 1; v <= V; v++)
    {
      if (M[u][v] && !VO[v].isVis) //如果v与u邻接，且节点v未曾访问
      {
        VO[v].isVis = 1;
        VO[v].d = VO[u].d + 1;
        VO[v].preVertex = u;
        enQueue(&Q, v);
      }
    }
  }
}

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
  printf("THE NUMBER OF BEGINNING VERTEX:");
  scanf("%d", &beginVertex);
  BFS(beginVertex);
  freeAll(&Q);
  for (int i = 1; i <= V; i++)
  {
    printf("NUMBER:%d\tPREVERTEX:%d\tDIS:%d\n", i, VO[i].preVertex, VO[i].d);
  }
  return 0;
}

