#include <stdio.h>
#include <stdlib.h>

#define MaxSize 10

typedef int ElemType;

typedef struct Stack{
    int data[MaxSize];
    int top;
} SqStack;

void InitStack(SqStack &S);     // 初始化栈
bool StackEmpty(SqStack S);     // 判断栈空
bool Push(SqStack &S, int x);   // 进栈
bool Pop(SqStack &S, int &x);   // 出栈
bool GetTop(SqStack S, int &x); // 取顶
void ClearStack(SqStack &S);    // 清空
void TraverseStack(SqStack S);  // 遍历

int main()
{
    SqStack S;
    InitStack(S);

    if(StackEmpty(S)) printf("当前为空栈！\n");
    else printf("当前栈非空！\n");

    for(int i=0; i<10; i++) Push(S, i);
    TraverseStack(S);

    int x;
    if(Pop(S, x)) printf("出栈成功！\n");
    else printf("出栈失败！\n");
    TraverseStack(S);

    if(GetTop(S, x)) printf("栈顶元素为：%d\n", x);
    else printf("栈顶不存在！\n");

    ClearStack(S);
    if(StackEmpty(S)) printf("当前为空栈！\n");
    else printf("当前栈非空！\n");

    return 0;
}

void InitStack(SqStack &S){
    S.top = -1;
}
bool StackEmpty(SqStack S){
    if(S.top == -1) return true;
    else return false;
}
bool Push(SqStack &S, int x){
    if(S.top == MaxSize-1) return false;    // 当前栈满
    S.data[++S.top] = x;
    return true; 
}
bool Pop(SqStack &S, int &x){
    if(S.top == -1) return false;           // 栈空报错
    x = S.data[S.top--];
    return true;
}
bool GetTop(SqStack S, int &x){
    if(S.top == -1) return false;           // 栈空报错
    x = S.data[S.top];
    return true;
}
void ClearStack(SqStack &S){
    S.top = -1;
}
void TraverseStack(SqStack S){
    int p = S.top;
    while(p != -1) printf("%d ", S.data[p--]);
    printf("\n");
}