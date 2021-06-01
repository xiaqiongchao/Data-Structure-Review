#include <stdio.h>
#include <stdlib.h>

#define MaxSize 10

typedef struct {
    int data[MaxSize];  // 长度
    int front;          // 队头
    int rear;           // 队尾
} SqQueue;
void InitQueue(SqQueue &Q);         // 初始化
bool QueueEmpty(SqQueue Q);         // 判断非空
bool EnQueue(SqQueue &Q, int x);    // 入队
bool DeQueue(SqQueue &Q, int &x);   // 出队

void InitQueue(SqQueue &Q){
    Q.front = Q.rear = 0;
}
bool QueueEmpty(SqQueue Q){
    if(Q.rear == Q.front) return true;
    else return false;
}
bool EnQueue(SqQueue &Q, int x){
    if((Q.rear+1) % MaxSize == Q.front) return false;  
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear+1) % MaxSize;
    return true;
}
bool DeQueue(SqQueue &Q, int &x){
    if(Q.rear == Q.front) return false;
    x = Q.data[Q.front];
    Q.front = (Q.front+1) % MaxSize;
    return true;
}

