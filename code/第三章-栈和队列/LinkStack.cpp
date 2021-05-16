#include <stdio.h>
#include <stdlib.h>

#define MaxSize 10

typedef int ElemType;
typedef struct StackNode{
    int data;
    struct StackNode *next;
} StackNode, *LinkStack;

// 各函数功能同顺序栈
void InitStack(LinkStack &S);
bool StackEmpty(LinkStack S);
bool Push(LinkStack &S, int x);
bool Pop(LinkStack &S, int &x);
bool GetTop(LinkStack S, int &x);
void ClearStack(LinkStack &S);
void TraverseStack(LinkStack S);

int main()
{
    LinkStack S;
    InitStack(S);

    if(StackEmpty(S)) printf("栈空！\n");
    else printf("栈非空！\n");

    for(int i=0; i<10; i++) Push(S, i);
    TraverseStack(S);

    int x;
    if(Pop(S, x)) printf("出栈成功！出栈元素为：%d\n", x);
    else printf("出栈失败！\n");
    TraverseStack(S);

    if(GetTop(S, x)) printf("栈顶元素为：%d\n", x);
    else printf("栈空！\n");

    ClearStack(S);
    if(StackEmpty(S)) printf("栈空！\n");
    else printf("栈非空！");
}

void InitStack(LinkStack &S){
    S = NULL;                   // 可以看作不设立头节点的链表
}
bool StackEmpty(LinkStack S){
    if(S == NULL) return true;
    else return false;
}
bool Push(LinkStack &S, int x){
    StackNode *p = (LinkStack)malloc(sizeof(StackNode));
    p->data = x;
    p->next = S;
    S = p;
    return true;
}
bool Pop(LinkStack &S, int &x){
    if(S == NULL) return false; // 栈空
    x = S->data;
    StackNode *p = S;
    S = S->next;
    free(p);
    return true;
}
bool GetTop(LinkStack S, int &x){
    if(S == NULL) return false;
    x = S->data;
    return true;
}
void ClearStack(LinkStack &S){
    S = NULL;
}
void TraverseStack(LinkStack S){
    StackNode *p = S;
    while(p){
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}