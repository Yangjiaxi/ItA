/*
 * 有向图的DFS遍历，从begin到destination，输出第一次得到的最短路
 *
 * 样例:
 *
 * VERTEX = 8
 * EDGE   = 10
 *
 * 2 1
 * 3 2
 * 3 4
 * 4 5
 * 4 6
 * 5 7
 * 5 8
 * 6 5
 * 6 7
 * 7 8
 *
 * BEGIN       = 3
 * DESTINATION = 7
 *
 *
 * 输出:
 * NUM:1  PRE:02  dTIME:03   fTime:04
 * NUM:2  PRE:03  dTIME:02   fTime:05
 * NUM:3  PRE:-1  dTIME:01   fTime:14
 * NUM:4  PRE:03  dTIME:06   fTime:13
 * NUM:5  PRE:04  dTIME:07   fTime:10
 * NUM:6  PRE:04  dTIME:11   fTime:12
 * NUM:7  PRE:06  dTIME:00   fTime:00
 * NUM:8  PRE:05  dTIME:08   fTime:09
 * Path : | 3-> 4-> 6-> 7
 *
 */


#include <stdio.h>

typedef struct _vertex
{
  //int d;  //从起始节点到该节点的距离  <-废弃::使用dTime
  int isVis;//是否被访问过
  int dTime; //被发现的时间
  int fTime; //探索完该节点所有邻接节点的时间
  int preVertex; //前驱节点编号
} vertex;

int V; //节点数
int E; //边数
int M[103][103]; //邻接矩阵 ，表中有效数据为[1..V][1..V]
vertex VO[103]; //保存节点的各种属性
int beginVertex; //起始节点编号
int destinationVertex;
int time; //全局时间戳，用来记录每个节点被发现和邻接节点探索完毕的时间

void init()
{
  for (int i = 1; i <= V; i++)
  {
    VO[i].isVis = 0;
    VO[i].preVertex = -1;
  }
  time = 0; //初始化全局时间戳
}

void DFS_VISIT(int u)
{
  if (u == destinationVertex)
  {
    return;
  }
  time++;
  VO[u].dTime = time;
  VO[u].isVis = 1;
  for (int v = 1; v <= V; v++)
  {
    if (M[u][v] && !VO[v].isVis) //如果存在 u->v的边且v没有被访问过
    {
      VO[v].preVertex = u;
      DFS_VISIT(v);
    }
  }
  time++;
  VO[u].fTime = time;
}


int arr[103]; //保存路径
int top = -1; //保存路径最高位

void path() //u -> v
{
  int cur = destinationVertex;
  while (cur != beginVertex)
  {
    cur = VO[cur].preVertex;
    arr[++top] = cur;
  }
  printf("Path : | ");
  for (int i = cur; i > 0; i--)
  {
    printf("%d-> ", arr[i]);
  }
  printf("%d \n", arr[0]);
}

int main()
{
  printf("<------DIRECTED GRAPH------>\n");
  printf("THE NUMBER OF VERTEX(<=100):");
  scanf("%d", &V);
  printf("THE NUMBER OF EDGE:");
  scanf("%d", &E);
  int ov, iv;
  printf("EACH PAIR OF LINKED VERTEX:\n");
  for (int i = 1; i <= E; i++)
  {
    scanf("%d%d", &iv, &ov);
    if (ov > V || iv > V)
    {
      printf("ERROR: TOO BIG VERTEX NUMBER\n");
    }
    else
    {
      M[iv][ov] = 1;
    }
  }
  printf("THE NUMBER OF BEGINNING VERTEX:");
  scanf("%d", &beginVertex);
  printf("THE NUMBER OF DESTINATION VERTEX:");
  scanf("%d", &destinationVertex);
  init();
  DFS_VISIT(beginVertex);
  for (int i = 1; i <= V; i++)
  {
    printf("NUM:%d  PRE:%02d  dTIME:%02d   fTime:%02d\n", i, VO[i].preVertex, VO[i].dTime, VO[i].fTime);
  }
  arr[++top] = destinationVertex;
  path();
  return 0;
}

