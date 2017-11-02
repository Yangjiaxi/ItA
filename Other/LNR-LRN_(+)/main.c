#include <stdio.h>
#include <mem.h>

typedef char S[100];

S LNR;
S tmp;
S LRN;
S stack;

int chmode(char c) //返回字符等级
{
  if (c == '+' || c == '-')
  {
    return 1;
  }
  else if (c == '*' || c == '/')
  {
    return 2;
  }
  else if (c == '^')
  {
    return 3;
  }
  else if (c == '(' || c == ')')
  {
    return 4;
  }
  else
  {
    return 0;
  }
}

void preFix()  //去除多余空格
{
  int len = strlen(tmp);

  for (int i = 0, j = 0; i < len; i++)
  {
    if (tmp[i] == ' ')
    {
      continue;
    }
    else
    {
      LNR[j++] = tmp[i];
    }
  }
}

void toLRN()
{
  int top = -1;
  int len = strlen(LNR);
  int j = 0;
  for (int i = 0; i < len; i++)
  {
    //数字
    if (!chmode(LNR[i]))
    {
      LRN[j++] = LNR[i];
    }
    else  //字符
    {
      if (chmode(LNR[i]) != 4)  //运算符
      {
        if (top == -1 || stack[top] == '(')  //操作栈为空或栈顶为'('
        {
          stack[++top] = LNR[i];
        }
        else if (chmode(LNR[i]) > chmode(stack[top]))  //优先级大于栈顶元素
        {
          stack[++top] = LNR[i];
        }
        else  //优先级小于栈顶元素，栈顶元素pop，直到优先级大于栈顶元素，push
        {
          while (1)
          {
            if (top == -1 || stack[top] == '(')  //操作栈为空或栈顶为'('
            {
              stack[++top] = LNR[i];
              break;
            }
            else if (chmode(LNR[i]) > chmode(stack[top]))  //优先级大于栈顶元素
            {
              stack[++top] = LNR[i];
              break;
            }
            else
            {
              LRN[j++] = stack[top--];
            }
          }
        }
      }
      else  //括号
      {
        if (LNR[i] == '(')  //左括号，直接入栈
        {
          stack[++top] = LNR[i];
        }
        else //右括号，pop栈顶直到栈顶为'('，括号丢弃
        {
          while (1)
          {
            if (stack[top] == '(')
            {
              top--;
              break;
            }
            else
            {
              LRN[j++] = stack[top--];
            }
          }
        }
      }
    }
  }
  while (top >= 0)
  {
    LRN[j++] = stack[top--];
  }
}

int pair()
{
  int len = strlen(LNR);
  int l = 0, r = 0;
  for (int i = 0; i < len; i++)
  {
    if (LNR[i] == '(') l++;
    if (LNR[i] == ')') r++;
  }
  if (l != r)
  {
    return 0;
  }
  else return 1;
}

void check()
{
  if (pair())
  {
    toLRN();
    puts(LRN);
  }
  else
  {
    printf("Error : Unbalanced Bracket\n");
  }
}

int main()
{
  while (gets(tmp))
  {
    preFix();
    check();
    printf("***********\n");
    memset(LNR, '\0', sizeof(LNR));
    memset(LRN, '\0', sizeof(LRN));
    memset(stack, '\0', sizeof(stack));
    memset(tmp, '\0', sizeof(tmp));
  }
  return 0;
}
