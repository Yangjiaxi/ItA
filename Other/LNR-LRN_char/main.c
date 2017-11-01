#include <stdio.h>
#include <mem.h>

typedef char S[100];

S LNR;
S tmp;
S LRN;
S stack;
int top;           //栈顶元素，-1表示栈为空，从0开始计数

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
    if (!chmode(LNR[i]))
    {
      LRN[j++] = LNR[i];
    }
    else
    {
      int por = chmode(LNR[i]);
      while (top >= 0)
      {
        if (por <= chmode(stack[top]))
        {
          LRN[j++] = stack[top--];
        }
        else
        {
          stack[++top] = LNR[i];
          break;
        }
      }
      if (top == -1)
      {
        stack[++top] = LNR[i];
      }
    }
  }
  for (int i = top; i >= 0; i--)
  {
    LRN[j++] = stack[i];
  }
}

int main()
{
  while (gets(tmp))
  {
    preFix();
    toLRN();
    puts(LRN);
    memset(LNR, '\0', sizeof(LNR));
    memset(LRN, '\0', sizeof(LRN));
    memset(stack, '\0', sizeof(stack));
    memset(tmp, '\0', sizeof(tmp));
  }
  return 0;
}
