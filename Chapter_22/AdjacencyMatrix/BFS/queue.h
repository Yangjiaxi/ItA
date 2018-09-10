//
// Created by Vans on 2017/11/3.
//
#include <malloc.h>

typedef struct _node
{
  int data;
  struct _node *next;
} Node;

typedef struct linkedlist
{
  Node *head;
  Node *tail;
} Queue;


//初始化队列
void initializeQueue(Queue *queue)
{
  queue->head = NULL;
  queue->tail = NULL;
}

//判断队列是否为空，为空返回1，非空返回0
int isEmpty(Queue *queue)
{
  if (queue->head == NULL)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

//入队
void enQueue(Queue *queue, int data)
{
  Node *node = (Node *) malloc(sizeof(Node));
  node->data = data;
  if (queue->head == NULL)
  {
    node->next = NULL;
    queue->tail = node;
  }
  else
  {
    node->next = queue->head;
  }
  queue->head = node;
}


//出队
int deQueue(Queue *queue)
{
  Node *tmp = queue->head;
  int data;
  //1.只有一个元素
  //2.多个元素
  //   a.遍历到tail上一个tmp
  //   b.保存tail的值并free tail所指向的内存
  //   c.tail指向tmp
  if (queue->head == NULL)
  {
    data = -1;
  }
  else if (queue->head == queue->tail)
  {
    data = tmp->data;
    queue->head = queue->tail = NULL;
    free(tmp);
  }
  else
  {
    while (tmp->next != queue->tail)
    {
      tmp = tmp->next;
    }
    data = queue->tail->data;
    free(queue->tail);
    queue->tail = tmp;
    queue->tail->next = NULL;

//		queue->tail = tmp;
//		tmp = tmp->next;
//		queue->tail->next = NULL;
//		data = tmp->data;
//		free(tmp);
  }
  return data;
}

void freeAll(Queue *queue)
{
  while (deQueue(queue) != -1);
  return;
}

