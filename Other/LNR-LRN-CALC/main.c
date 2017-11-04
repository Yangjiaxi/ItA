/*
 *中缀表达式转后缀表达式并求值
 *可以计算乘方、阶乘
 *对于a^b : b必须为整数
 *对于a! : a必须为正整数
 *
 *  !!!!未实现功能:负号!！!!
*/

#include <stdio.h>
#include <mem.h>
#include <stdlib.h>
#include <math.h>

#define BRACKET_POR 99

typedef char S[100];

typedef struct _node  //最小数据节点（符号/数字）
{
  double num;
  char ch;
  int type;  //0为数字，1为+-,2为*/,3为^,4为!,5为括号
} node;

node LNR[200];
node LRN[200];
int lenLNR = -1; //表示LNR最后一个下标，-1为空，从0计数
int lenLRN = 0;  //表示LRN长度+1，为尾后对象

double ans = 0;

S ori;  //输入数据
S tmp;  //删除逗号后的数据
S stack;  //符号栈
double numStack[200]; //数字栈，用于LRN的运算，从0开始使用，-1表示为空

int chmode(char c); //返回字符等级
void outLNR(); //输出LNR
void outLRN(); //输出LRN
void preFix();  //预处理，去除多余空格和分割数据
void toLRN(); //LNR->LRN
void calcLRN();  //后缀表达式求值
int pair();  //检查括号匹配函数，只允许使用 ( 与 )
void check();   //检查括号合法性


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
  else if (c == '!')
  {
    return 4;
  }
  else if (c == '(' || c == ')')
  {
    return BRACKET_POR;  //其他运算符最高级别:98
  }
  else  //表示数字
  {
    return 0;
  }
}

typedef double (*operation)(const double, const double);

operation opeartions[128] = {NULL};

double add(const double a, const double b)
{
  return a + b;
}

double sub(const double a, const double b)
{
  return a - b;
}

double multi(const double a, const double b)
{
  return a * 1.0 * b;
}

double by(const double a, const double b)
{
  if (b) return a * 1.0 / b;
  else
  {
    printf("ERROR: a/b : b cannot be zero\n");
    exit(-5);
  }
}

double fastPow(double a, double b)
{
  double r = 1.0;
  double base = a;
  int bb = (int) fabs(b);
  while (bb)
  {
    if (bb & 1) r *= base;
    base *= base;
    bb >>= 1;
  }
  if (b < 0)
  {
    r = 1 / r;
  }

  return r;
}

double power(const double a, const double b)
{
  if (b == (int) b) return fastPow(a, b);
  else
  {
    printf("ERROR: a^b : b must an integer\n");
    exit(-2);
  }

}

void init()
{
  opeartions['+'] = add;
  opeartions['-'] = sub;
  opeartions['*'] = multi;
  opeartions['/'] = by;
  opeartions['^'] = power;
}

double eval(char opera, const double a, const double b)
{
  operation opt;
  opt = opeartions[opera];
  if (opt == NULL)
  {
    printf("ERROR:Unsolved Symbol %c\n", opera);
    exit(-1);
  }
  else return opt(a, b);
}

double fact(double num)
{
  if (num != (int) num)
  {
    printf("ERROR: Factorial(n) : n must be a non-negative integer\n");
    exit(-3);
  }
  else
  {
    int res = 1;
    for (int i = 1; i <= num; i++)
    {
      res *= i;
    }
    return res;
  }
}

void calcLRN()  //后缀表达式求值
{
  int nTop = -1; //从0开始使用，-1表示为空
  for (int i = 0; i < lenLRN; ++i)
  {
    if (!LRN[i].type)  //i位置是数字，压入计算栈
    {
      numStack[++nTop] = LRN[i].num;
    }
    else  //是符号，准备计算。每次计算后再把结果压入栈
    {
      if (LRN[i].type != 4) //字符不是阶乘运算符
      {
        double num2 = numStack[nTop--];
        double num1 = numStack[nTop--];
        double res = eval(LRN[i].ch, num1, num2);  //使用函数指针
        numStack[++nTop] = res;
      }
      else  //是阶乘运算符
      {
        double num = numStack[nTop--];
        double res = fact(num); //检查num是否为整数，阶乘只允许整数
        numStack[++nTop] = res;
      }
    }
  }
  ans = numStack[nTop]; //在整体计算之后，计算栈内只有一个元素，即为后缀表达式的值
}

void outLNR()
{
  printf("LNR:: ");
  for (int i = 0; i <= lenLNR; ++i)
  {
    if (LNR[i].type)
    {
      printf("%c ", LNR[i].ch);
    }
    else printf("%.3lf ", LNR[i].num);
  }
}


void outLRN()
{
  printf("LRN:: ");
  for (int i = 0; i < lenLRN; ++i)
  {
    //printf("type::%d::", LNR[i].type);
    if (LRN[i].type)
    {
      printf("%c ", LRN[i].ch);
    }
    else printf("%.3lf ", LRN[i].num);
  }
}

void preFix()  //预处理，去除多余空格和分割数据
{
  int len = strlen(ori);
  int tmpNum = -1;
  int j = 0;
  int flag = 0; //是否在统计数字
  for (int i = 0; i < len; i++)
  {
    if (ori[i] == ' ')
    {
      continue;
    }
    else
    {
      tmp[j++] = ori[i];
    }
  }

  //开始分割数据
  for (int i = 0; i < j; i++)
  {
    if (chmode(tmp[i])) //i位为符号
    {
      if (lenLNR == -1 && tmpNum == -1)  //处理第一个位置特殊情况
      {
        LNR[lenLNR + 1].ch = tmp[i];
        LNR[lenLNR + 1].type = chmode(tmp[i]);
        lenLNR++;
      }
      else
      {
        if (flag == 1)  //说明上一个元素是数字，需要先把数字压入结果
        {
          LNR[lenLNR + 1].type = 0;
          LNR[lenLNR + 1].num = tmpNum;
          lenLNR++;
          tmpNum = -1;
          flag = 0;
        }
        //把当前运算符压入结果
        LNR[lenLNR + 1].ch = tmp[i];
        LNR[lenLNR + 1].type = chmode(tmp[i]);
        lenLNR++;
      }
    }
    else //为数字
    {
      if (tmpNum == -1)  //尚未开始新一轮的数字统计
      {
        tmpNum = (tmp[i] - '0');
        flag = 1;
      }
      else //在统计中，使用F[i + 1] = F[i] * 10 + a[i]
      {
        tmpNum *= 10;
        tmpNum += (tmp[i] - '0');
      }
    }
  }
  if (tmpNum != -1)  //若最后一个字符不是右括号，最后一轮统计的数字无法压入结果，需要手动放入
  {
    LNR[lenLNR + 1].type = 0;
    LNR[lenLNR + 1].num = tmpNum;
    lenLNR++;
  }
}

void toLRN() //LNR->LRN
{
  int top = -1; //栈顶元素，-1表示栈为空，从0开始计数
  for (int i = 0; i <= lenLNR; i++)
  {
    //数字
    if (!LNR[i].type)
    {
      LRN[lenLRN++] = LNR[i];
    }
    else  //字符
    {
      if (LNR[i].type != BRACKET_POR)  //运算符
      {
        if (top == -1 || stack[top] == '(')  //操作栈为空或栈顶为'('
        {
          stack[++top] = LNR[i].ch;
        }
        else if (LNR[i].type > chmode(stack[top]))  //优先级大于栈顶元素
        {
          stack[++top] = LNR[i].ch;
        }
        else  //优先级小于栈顶元素，栈顶元素pop，直到优先级大于栈顶元素，push
        {
          while (1)
          {
            if (top == -1 || stack[top] == '(')  //操作栈为空或栈顶为'('
            {
              stack[++top] = LNR[i].ch;
              break;
            }
            else if (LNR[i].type > chmode(stack[top]))  //优先级大于栈顶元素
            {
              stack[++top] = LNR[i].ch;
              break;
            }
            else
            {
              LRN[lenLRN].ch = stack[top];
              LRN[lenLRN].type = chmode(stack[top]);
              lenLRN++;
              top--;
            }
          }
        }
      }
      else  //括号
      {
        if (LNR[i].ch == '(')  //左括号，直接入栈
        {
          stack[++top] = LNR[i].ch;
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
              LRN[lenLRN].ch = stack[top];
              LRN[lenLRN].type = chmode(stack[top]);
              lenLRN++;
              top--;
            }
          }
        }
      }
    }
  }
  while (top >= 0)
  {
    LRN[lenLRN].ch = stack[top];
    LRN[lenLRN].type = chmode(stack[top]);
    lenLRN++;
    top--;
  }
}

int pair()  //检查括号匹配函数，只允许使用 ( 与 )
{
  int l = 0, r = 0;
  for (int i = 0; i <= lenLNR; i++)
  {
    if (LNR[i].type)
    {
      if (LNR[i].ch == '(') l++;
      if (LNR[i].ch == ')') r++;
    }
  }
  if (l != r)  //不匹配
  {
    return 0;
  }
  else return 1; //匹配
}

void check()   //检查括号合法性
{
  if (pair())
  {
    toLRN();
    printf("\n<--->\n");
    outLNR();
    printf("\n<--->\n");
    outLRN();
    printf("\n<--->\n");
    calcLRN();
    printf("Result : %.3lf", ans);
    printf("\n<--->\n");
  }
  else
  {
    printf("\n<--->\n");
    printf("Error : Unbalanced Bracket\n");
    printf("\n<--->\n");
  }
}

int main()
{
  init();
  gets(ori);  //读取
  preFix();   //预处理
  check();  //检验合法性并开始算法
  return 0;
}
