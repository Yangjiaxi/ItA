#include <stdio.h>
#include <malloc.h>

//队列：FIFO,每次enQueue数据到head指针前
//             deQueue tail所指向的数据

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
  printf("\nFree Complete!\n");
  return;
}

void endl()
{
  printf("\n");
}

int main()
{
  Queue queue;
  initializeQueue(&queue);
  printf("\nis :%d\n", isEmpty(&queue));
  enQueue(&queue, 1);
  enQueue(&queue, 2);
  enQueue(&queue, 3);
  enQueue(&queue, 4);
  enQueue(&queue, 5);

  printf("%d\n", queue.tail->data);

  printf("%d ", deQueue(&queue));
  printf("%d ", deQueue(&queue));     //1 2
  printf("\nis :%d\n", isEmpty(&queue));
  // queue : 3 4 5
  endl();

  enQueue(&queue, 10);
  enQueue(&queue, 56);
  enQueue(&queue, 999);  //queue: 3 4 5 10 56 999

  printf("%d ", deQueue(&queue));
  printf("%d ", deQueue(&queue));
  printf("%d ", deQueue(&queue));
  printf("%d ", deQueue(&queue));
  printf("%d ", deQueue(&queue));
  printf("%d ", deQueue(&queue));
  printf("%d ", deQueue(&queue));
  printf("\nis :%d\n", isEmpty(&queue));
  freeAll(&queue);
  return 0;
}