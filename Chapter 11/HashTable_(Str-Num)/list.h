#ifndef HASHTABLE_STR_NUM_LIST_H
#define HASHTABLE_STR_NUM_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <mem.h>

typedef struct _node   //一个key -> value的 映射，一个key应当在一个表中只出现一次
{
  char key[50];
  int value;
  struct _node *next;
} Node;

typedef struct _linkedlist
{
  Node *head;
  Node *tail;
} LinkedList;

void initalizeList(LinkedList *list); //初始化链表
void addHead(LinkedList *list, char key[], int value); //向头部添加节点
void addTail(LinkedList *list, char key[], int value);//向尾部添加节点
Node *getNodeByKey(LinkedList *list, char key[]);//利用key获取节点，返回节点指针
void deleteNodeByPtr(LinkedList *list, Node *node);//根据节点指针删除节点
void displayList(LinkedList *list);//输出链表
void delete(LinkedList *list, char key[]); //删除一个含有某值的节点

//初始化链表
void initalizeList(LinkedList *list)
{
  list->head = NULL;
  list->tail = NULL;
}


//向头部添加节点
void addHead(LinkedList *list, char key[], int value)
{
  if (getNodeByKey(list, key) == NULL)
  {
    Node *node = (Node *) malloc(sizeof(Node));
    strcpy(node->key, key);
    node->value = value;
    if (list->head == NULL)
    {
      list->tail = node;
      node->next = NULL;
    }
    else
    {
      node->next = list->head;
    }
    list->head = node;
    printf("\n##########\n");
    printf("Add Pair <%s, %d> successful!", key, value);
    printf("\n##########\n");
  }
  else
  {
    printf("\n##########\n");
    printf("ERROR : key [%s] is already exist!", key);
    printf("\n##########\n");
  }

}

//向尾部添加节点
void addTail(LinkedList *list, char key[], int value)
{
  Node *node = (Node *) malloc(sizeof(Node));
  strcpy(node->key, key);
  node->value = value;
  node->next = NULL;
  if (list->head == NULL)
  {
    list->head = node;
  }
  else
  {
    list->tail->next = node;
  }
  list->tail = node;
}

//利用key获取节点，返回节点指针
Node *getNodeByKey(LinkedList *list, char key[])
{
  Node *node = list->head;
  while (node != NULL)
  {
    if (strcmp(key, node->key) == 0)
    {
      return node;
    }
    node = node->next;
  }
  return NULL;
}


//根据节点指针删除节点
void deleteNodeByPtr(LinkedList *list, Node *node)
{
  if (node == NULL)
  {
    printf("\n##########\n");
    printf("ERROR: No such node");
    printf("\n##########\n");
    return;
  }
  if (node == list->head)
  {
    if (list->head->next == NULL)
    {
      list->head = list->tail = NULL;
    }
    else
    {
      list->head = list->head->next;
    }
  }
  else
  {
    Node *tmp = list->head;
    while (tmp != NULL && tmp->next != node)
    {
      tmp = tmp->next;
    }
    if (tmp != NULL)
    {
      tmp->next = node->next;
    }
    free(node);
  }
  printf("\n##########\n");
  printf("Node delete successful!");
  printf("\n##########\n");
}


//输出链表
void displayList(LinkedList *list)
{
  Node *pNode = list->head;
  while (pNode != NULL)
  {
    printf("%s->%d\n", pNode->key, pNode->value);
    pNode = pNode->next;
  }
  printf("##########\n");
}


//删除一个含有对应key的节点
void delete(LinkedList *list, char key[])
{
  deleteNodeByPtr(list, getNodeByKey(list, key));
}


//free所有malloc的内存
void freeAll(LinkedList *list)
{
  Node *cur = list->head;
  while (cur != list->tail)
  {
    free(cur);
    cur = cur->next;
  }
  free(cur);
}

#endif //HASHTABLE_STR_NUM_LIST_H
