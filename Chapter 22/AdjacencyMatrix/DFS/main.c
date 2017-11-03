/*
 * 有向图的DFS遍历，从编号为1的节点开始
 *
 * 样例:
 * VERTEX = 6
 * EDGE   = 8
 *
 * 1 2
 * 1 4
 * 2 5
 * 3 5
 * 3 6
 * 4 2
 * 5 4
 * 6 6
 *
 *
 * 输出:
 * NUM:1  PRE:-1  dTIME:01   fTime:08
 * NUM:2  PRE:01  dTIME:02   fTime:07
 * NUM:3  PRE:-1  dTIME:09   fTime:12
 * NUM:4  PRE:05  dTIME:04   fTime:05
 * NUM:5  PRE:02  dTIME:03   fTime:06
 * NUM:6  PRE:03  dTIME:10   fTime:11
 *
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
//int beginVertex; //起始节点编号
int time; //全局时间戳，用来记录每个节点被发现和邻接节点探索完毕的时间


void DFS_VISIT(int u)
{
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

void DFS()
{
  for (int i = 1; i <= V; i++)
  {
    VO[i].isVis = 0;
    VO[i].preVertex = -1;
  }
  time = 0; //初始化全局时间戳
  for (int u = 1; u <= V; u++)
  {
    if (!VO[u].isVis)
    {
      DFS_VISIT(u);
    }
  }
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
  //printf("THE NUMBER OF BEGINNING VERTEX:");
  //scanf("%d", &beginVertex);
  DFS();
  for (int i = 1; i <= V; i++)
  {
    printf("NUM:%d  PRE:%02d  dTIME:%02d   fTime:%02d\n", i, VO[i].preVertex, VO[i].dTime, VO[i].fTime);
  }
  return 0;
}

