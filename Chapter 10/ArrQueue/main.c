#include <stdio.h>

#define maxsize 200

typedef struct _point
{
  int x;
  int y;
} point;

typedef struct sq
{
  int front, rear;
  point data[maxsize];
} Qs;

void initQueue(Qs *s) /*初始化队列*/
{
  s->front = s->rear = 0;
}

void enQueue(Qs *s, point val) /*入队函数*/
{
  if ((s->rear + 1) % maxsize == s->front)
  {
    printf("Quence is full.\n");
    return;
  }
  s->rear = (s->rear + 1) % maxsize;
  s->data[s->rear] = val;
}

point deQueue(Qs *s) /*出队函数*/
{
  if (s->rear != s->front)
  {
    s->front = (s->front + 1) % maxsize;
    return s->data[s->front];
  }
}

void printQueue(Qs *s) /*打印队列中元素*/
{
  int i;
  i = s->front;

  if (s->rear == s->front)
    return;
  do
  {
    printf("(%d,%d)  ", s->data[(i + 1) % maxsize].x, s->data[(i + 1) % maxsize].y);
    i = (i + 1) % maxsize;
  } while (i != s->rear);
}


int countQueue(Qs *s) /*统计队列个数*/
{
  int i, count = 0;

  i = s->front;
  if (s->rear == s->front)
    return 0;
  do
  {
    count++;
    i = (i + 1) % maxsize;
  } while (i != s->rear);
  return count;
}

int isEmpty(Qs *s)
{
  if (s->rear == s->front)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

int main()
{
  Qs s;
  initQueue(&s);
  printf("is E ? %d\n", isEmpty(&s));
  point a;
  a.x = 1;
  a.y = 2;
  point b;
  b.x = 1;
  b.y = 2;
  enQueue(&s, a);
  enQueue(&s, b);
  printQueue(&s);
  printf("\nis E ? %d\n", isEmpty(&s));
  printf("has %d e\n", countQueue(&s));
  point t = deQueue(&s);
  printQueue(&s);
  printf("\nis E ? %d\n", isEmpty(&s));
  printf("has %d e\n", countQueue(&s));
  return 0;
}