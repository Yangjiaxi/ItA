#include <stdio.h>
#include <malloc.h>

//stack:FILO
//操作:push 向栈顶压入一个元素
//    pop  从栈顶弹出元素，pop一个空栈返回-1

typedef struct _node
{
	int data;
	struct _node *next;
} Node;

typedef struct linkedlist
{
	Node *head;
	Node *tail;
} Stack;

//初始化栈
void initializeStack(Stack *stack)
{
	stack->head = NULL;
	stack->tail = NULL;
}

//向栈顶压入元素
void push(Stack *stack, int data)
{
	Node *node = (Node *) malloc(sizeof(Node));
	node->data = data;
	if (stack->head == NULL)
	{
		stack->tail = node;
		node->next = NULL;
	}
	else
	{
		node->next = stack->head;
	}
	stack->head = node;
}


//弹出栈顶元素并返回栈顶元素的值
int pop(Stack *stack)
{
	int data;
	Node *node = stack->head;
	if (stack->head == NULL)
	{
		data = -1;
	}
	else if (node == stack->tail)
	{
		data = stack->head->data;
		stack->head = stack->tail = NULL;
		free(node);
	}
	else
	{
		data = stack->head->data;
		stack->head = stack->head->next;
		free(node);
	}

	return data;
}

//释放所有未释放的空间
void freeAll(Stack *stack)
{
	while(pop(stack)!=-1);
	printf("\nFree Complete!\n");
	return;
}

int main()
{
	Stack stack;
	initializeStack(&stack);
	push(&stack, 1);
	push(&stack, 2);
	push(&stack, 3);
	push(&stack, 4);
	push(&stack, 5);

	printf("%d ", pop(&stack));
	printf("%d \n", pop(&stack));  //5 4
	//1 2 3 <- top
	push(&stack, 11);
	push(&stack, 23);
	push(&stack, 323);  //1 2 3 11 23 323

	printf("%d ", pop(&stack));
	printf("%d ", pop(&stack));
	printf("%d ", pop(&stack));
	printf("%d ", pop(&stack));
	printf("%d ", pop(&stack));
	printf("%d ", pop(&stack));
	printf("%d \n", pop(&stack));

	freeAll(&stack);

	return 0;
}