/*
6-7 在一个数组中实现两个堆栈 (20分)
Stack CreateStack( int MaxSize );
bool Push( Stack S, ElementType X, int Tag );
ElementType Pop( Stack S, int Tag );
注意：如果堆栈已满，Push函数必须输出“Stack Full”并且返回false；如果某堆栈是空的，则Pop函数必须输出“Stack Tag Empty”（其中Tag是该堆栈的编号），并且返回ERROR。
*/
#include <stdio.h>
#include <stdlib.h>

#define ERROR 1e8
typedef int ElementType;
typedef enum
{
    push,
    pop,
    end
} Operation;
typedef enum
{
    false,
    true
} bool;
typedef int Position;
struct SNode
{
    ElementType *Data;
    Position Top1, Top2;
    int MaxSize;
};
typedef struct SNode *Stack;

Stack CreateStack(int MaxSize);
bool Push(Stack S, ElementType X, int Tag);
ElementType Pop(Stack S, int Tag);

Operation GetOp();                 /* details omitted */
void PrintStack(Stack S, int Tag); /* details omitted */

int main()
{
    int N, Tag, X;
    Stack S;
    int done = 0;

    scanf("%d", &N);
    S = CreateStack(N);
    while (!done)
    {
        switch (GetOp())
        {
        case push:
            scanf("%d %d", &Tag, &X);
            if (!Push(S, X, Tag))
                printf("Stack %d is Full!\n", Tag);
            break;
        case pop:
            scanf("%d", &Tag);
            X = Pop(S, Tag);
            if (X == ERROR)
                printf("Stack %d is Empty!\n", Tag);
            break;
        case end:
            PrintStack(S, 1);
            PrintStack(S, 2);
            done = 1;
            break;
        }
    }
    return 0;
}
Stack CreateStack(int MaxSize)
{
    Stack stack = NULL;
    if (MaxSize > 0)
    {
        stack = (Stack)malloc(sizeof(struct SNode));
        if (stack)
        {
            stack->MaxSize = MaxSize;
            stack->Data = (ElementType *)malloc(MaxSize * sizeof(ElementType));
            stack->Top1 = -1;
            stack->Top2 = MaxSize;
        }
    }
    return (stack);
}
bool Push(Stack S, ElementType X, int Tag)
{
    if (S == NULL)
        return (false);
    if (S->Top1 + 1 == S->Top2)
    {
        printf("Stack Full\n");
        return (false);
    }
    else if (Tag == 1)
    {
        S->Data[++(S->Top1)] = X;
        return (true);
    }
    else if (Tag == 2)
    {
        S->Data[--(S->Top2)] = X;
        return (true);
    }
    else
        return (false);
}
ElementType Pop(Stack S, int Tag)
{
    if (S == NULL)
        return (ERROR);
    switch (Tag)
    {
    case 1:
        if (S->Top1 == -1)
        {
            printf("Stack %d Empty\n", Tag);
            return (ERROR);
        }
        else
            return (S->Data[(S->Top1)--]);
    case 2:
        if (S->Top2 == S->MaxSize)
        {
            printf("Stack %d Empty\n", Tag);
            return (ERROR);
        }
        else
            return (S->Data[(S->Top2)++]);
    default:
        return (ERROR);
    }
}