#include <stdio.h>
#include "list.h"

#define HASHSIZE 20

LinkedList hashTable[HASHSIZE]; //0 ~ HASHSIZE - 1为有效散列表长度

int hashCode(char str[])
{
  int len = strlen(str);
  int hash = 0;
  for (int i = 0; i < len; i++)
  {
    hash ^= ((hash << 5) + (str[i] - '0') + (hash >> 2));
  }
  hash %= HASHSIZE;
  return hash;
}

void function()
{
  //LinkedList linkedList;
  for (int i = 0; i < HASHSIZE; i++)  //逐个初始化
  {
    initalizeList(&hashTable[i]);
  }

  int flag = 1; //标记没有选择【退出】项
  int f;
  while (flag)
  {
    printf("Choose:\n"
                   "1.add node to head\n"
                   "2.show the whole list\n"
                   "3.delete node by [key]\n"
                   "4.get [value] by [key]\n"
                   "5.exit\n"
                   "Now choose:");
    scanf("%d", &f);
    switch (f)
    {
      case 1:  //向散列表加入新元素
      {
        printf("Key and Value:\n");
        char key[50];
        int value;
        scanf("%s", key);
        scanf("%d", &value);
        addHead(&hashTable[hashCode(key)], key, value);  //利用hashCode(key)获得有效的散列表编号
        break;
      }
      case 2:  //输出非空的表
      {
        for (int i = 1; i < HASHSIZE; i++)
        {
          if (hashTable[i].head != NULL)
          {
            printf("\n##########\n");
            printf("Table %02d:\n", i);
            displayList(&hashTable[i]);
          }
        }
        printf("@@@@@@@@@@\n");
        printf("Output Complete!");
        printf("\n@@@@@@@@@@\n");
        break;
      }
      case 3:  //利用[key]删除节点
      {
        printf("Key:");
        char key[50];
        scanf("%s", key);
        delete(&hashTable[hashCode(key)], key);
        break;
      }
      case 4:  //返回[key]的键值对
      {
        printf("Key:");
        char key[50];
        scanf("%s", key);
        Node *node;
        int isFound = 0;  //标记是否已找到
        for (int i = 0; i < HASHSIZE && !isFound; i++)
        {
          node = getNodeByKey(&hashTable[i], key);
          if (node != NULL)
          {
            printf("\n##########\n");
            printf("Found Pair: <%s, %d>", node->key, node->value);
            printf("\n##########\n");
            isFound = 1; //已找到
          }
        }
        if (!isFound)  //循环结束仍未找到，说明不存在这样的Key
        {
          printf("\n##########\n");
          printf("No such node whose key is [%s]", key);
          printf("\n##########\n");
        }
        break;
      }
      case 5:  //退出，释放所有内存
      {
        flag = 0;
        for (int i = 1; i < HASHSIZE; i++)
        {
          freeAll(&hashTable[i]);
        }
        break;
      }
      default:  //操作选择错误
      {
        printf("\n##########\n");
        printf("ERROR: Invalid opeartor number\n");
        printf("\n##########\n");
        break;
      }

    }
  }
}

int main()
{
  function();
  return 0;
}
