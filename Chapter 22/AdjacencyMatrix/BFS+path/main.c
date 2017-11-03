/* ##BFS完成图的遍历并输出从起点到终点的全部最短路径（如果有）##
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
 * DESTINATION = 7
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
 * Path No.1 | 3 -> 4 -> 5 -> 7
 * Path No.2 | 3 -> 4 -> 6 -> 7
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
int destinationVertex; //目标节点编号

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

int through[103]; //保存路径，从0开始，逆序是正确路径
int top = -1; //保存当前路径深度，-1表示路径为空，从0开始
int count = 0; //保存路径的编号

void path(int v) //使用dfs输出从beginVertex到destinationVertex的最短路径
{
  //算法:从dV开始向前回溯
  if (v == beginVertex)  //已到达起始节点，逆序输出即为正确路径
  {
    printf("Path No.%d | ", ++count);
    for (int i = top; i > 0; --i)
    {
      printf("%d -> ", through[i]);
    }
    printf("%d\n", through[0]);
  }
  else
  {
    for (int u = 1; u <= V; u++)  //存在u -> v的路径且u.d = v.d - 1
    {
      if (M[u][v] && (VO[u].d == VO[v].d - 1))
      {
        through[++top] = u; //把u压入路径
        path(u);  //并对u节点使用dfs
        top--;
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
  printf("THE NUMBER OF DESTINATION VERTEX:");
  scanf("%d", &destinationVertex);

  BFS(beginVertex);
  freeAll(&Q);
  for (int i = 1; i <= V; i++)
  {
    printf("NUMBER:%d\tPRE_VERTEX:%d\tDIS:%d\n", i, VO[i].preVertex, VO[i].d);
  }
  through[++top] = destinationVertex;
  path(destinationVertex);
  if (!count)
  {
    printf("NO SUCH PATH FROM %d TO %d!\n", beginVertex, destinationVertex);
  }
  return 0;
}

