//
// Created by Vans on 2017/11/6.
//

#include <stdlib.h>

#ifndef BINARYSEARCHTREE_TREE_H
#define BINARYSEARCHTREE_TREE_H

struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;

SearchTree MakeEmpty(SearchTree T); //清空（初始化或程序结束后的释放）
Position Find(int X, SearchTree T); //在树T中寻找元素X的位置，并返回指向节点的指针，未找到返回NULL
Position FindMin(SearchTree T);//寻找树中最小元素
Position FindMax(SearchTree T); //寻找树中最大元素（不使用递归）
SearchTree Insert(int X, SearchTree T); //插入值为X的节点
SearchTree Delete(int X, SearchTree T);//删除树中值为X的节点
void InorderTreeWalk(SearchTree T); //中序遍历输出
void PreTreeWalk(SearchTree T); //先序遍历输出
void PostTreeWalk(SearchTree T); //后序遍历输出

#endif //BINARYSEARCHTREE_TREE_H

typedef struct TreeNode
{
  int Element;
  SearchTree Left;
  SearchTree Right;
} TreeNode;

SearchTree MakeEmpty(SearchTree T)  //递归释放所有节点，相当于构造一个空树
{
  if (T != NULL)
  {
    MakeEmpty(T->Left);
    MakeEmpty(T->Right);
    free(T);
  }
}

Position Find(int X, SearchTree T) //在树T中寻找元素X的位置，并返回指向节点的指针，未找到返回NULL
{
  if (T == NULL)  //树T为空，代表寻找到叶子仍未找到目标元素；或树T本来就为空
  {
    return NULL;
  }
  else
  {
    if (X < T->Element)  //比根节点大，进入左子树搜索
    {
      return Find(X, T->Left);
    }
    else //比根节点小，进入右字数搜索
    {
      return Find(X, T->Right);
    }
  }
}

Position FindMin(SearchTree T)  //寻找树中最小元素
{
  if (T == NULL)
  {
    return NULL;
  }
  else
  {
    if (T->Left == NULL)  //当前节点的左子树为空，说明该节点保存着最小值
    {
      return T;
    }
    else //左子树存在，必然保存着比当前节点小的值，进入左子树搜索
    {
      return FindMin(T->Left);
    }
  }
}

Position FindMax(SearchTree T) //寻找树中最大元素（不使用递归）
{
  if (T != NULL)
  {
    while (T->Right != NULL)
    {
      T = T->Right;
    }
  }
  return T;
}

SearchTree Insert(int X, SearchTree T) //插入值为X的节点
{
  //这里T==null处理两种情况，1.找到了应该放置的节点 2.树T本身为空
  if (T == NULL)
  {
    T = (TreeNode *) malloc(sizeof(TreeNode));
    if (T == NULL)
    {
      printf("\nFatal Error: Out of space!\n");
      exit(-1);
    }
    else
    {
      T->Element = X;
      T->Left = T->Right = NULL;
    }
  }
  else
  {
    if (X < T->Element) //要插入的元素小于根节点进入左子树搜索
    {
      T->Left = Insert(X, T->Left);
    }
    else
    {
      T->Right = Insert(X, T->Right);
    }
    //否则，X == T->Element，元素已经存在，什么都不做
  }
  return T;
}

SearchTree Delete(int X, SearchTree T) //删除树中值为X的节点
{
  Position TmpCell; //相当于中间变量
  if (T == NULL) //始终未找到
  {
    printf("Element [%d] Not Found", X);
  }
  else if (X < T->Element) //值比节点元素小，去左子树
  {
    T->Left = Delete(X, T->Left); //进入左子树删除元素X，并将左子树替换为删除后的树
  }
  else if (X > T->Element) //大，去右子树
  {
    T->Right = Delete(X, T->Right);
  }
  else if (T->Left && T->Right) //此时X == Element开始删除
  {
    //这里左右子树均存在，删除一个有两个儿子的节点比较复杂，故进行转换：
    TmpCell = FindMin(T->Right); //将节点的值替换为右子树中最小的值，然后删除右子树中该最小的值
    T->Element = TmpCell->Element;
    T->Right = Delete(T->Element, T->Right);
  }
  else
  {
    //这里左右子树不全存在或全不存在，用存在的子树或NULL替换当前节点，然后释放当前节点（中间变量）
    TmpCell = T;
    if (T->Left == NULL) //左子树为空
    {
      T = T->Right;
    }
    else if (T->Right == NULL) //右子树为空
    {
      T = T->Left;
    }
    free(TmpCell);
  }
  return T;
}

void InorderTreeWalk(SearchTree T)
{
  if (T == NULL)
  {
    return;
  }
  else
  {
    if (T->Left)
    {
      InorderTreeWalk(T->Left);
    }
    printf("%d ", T->Element);
    if (T->Right)
    {
      InorderTreeWalk(T->Right);
    }
  }
}

void PreTreeWalk(SearchTree T)
{
  if (T == NULL)
  {
    return;
  }
  else
  {
    printf("%d ", T->Element);
    if (T->Left)
    {
      PreTreeWalk(T->Left);
    }
    if (T->Right)
    {
      PreTreeWalk(T->Right);
    }
  }
}

void PostTreeWalk(SearchTree T)
{
  if (T == NULL)
  {
    return;
  }
  else
  {
    if (T->Left)
    {
      PostTreeWalk(T->Left);
    }
    if (T->Right)
    {
      PostTreeWalk(T->Right);
    }
    printf("%d ", T->Element);
  }
}







