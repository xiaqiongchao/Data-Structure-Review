#include <stdio.h>
#include <stdlib.h>

#define MaxSize 10

typedef struct {
    int data[MaxSize];  // 长度
    int front;          // 队头
    int rear;           // 队尾
} SqQueue;

void InitQueue(SqQueue &Q);         // 初始化
void ClearQueue(SqQueue &Q);        // 清空
bool QueueEmpty(SqQueue Q);         // 判断非空
int QueueLength(SqQueue Q);         // 队列长度 （Q.rear - Q.front + MaxSize) % MaxSize
bool GetHead(SqQueue Q, int &x);    // 队头
bool EnQueue(SqQueue &Q, int x);    // 入队
bool DeQueue(SqQueue &Q, int &x);   // 出队
void QueueTraverse(SqQueue Q);      // 遍历

int main()
{
    SqQueue Q;
    InitQueue(Q);

    if(QueueEmpty(Q)) printf("队列为空！\n");
    else printf("队列非空！\n");

    for(int i=0; i<10; i++) EnQueue(Q, i);
    QueueTraverse(Q);

    printf("当前队列长度为：%d\n", QueueLength(Q));    

    int x;
    if(GetHead(Q, x)) printf("对头元素为：%d\n", x);
    else printf("队列为空！\n");

    if(DeQueue(Q, x)) printf("出队元素为：%d\n", x);
    else printf("队列为空！\n");
}

void InitQueue(SqQueue &Q){
    Q.front = Q.rear = 0;
}
void ClearQueue(SqQueue &Q){
    Q.front = Q.rear = 0;
}
bool QueueEmpty(SqQueue Q){
    if(Q.rear == Q.front) return true;
    else return false;
}
int QueueLength(SqQueue Q){
    if(Q.rear == Q.front) return 0;
    return (Q.rear - Q.front + MaxSize) % MaxSize;
}
bool GetHead(SqQueue Q, int &x){
    if(Q.rear != Q.front){
        x = Q.data[Q.front];
        return true;
    } else return false;
}
bool EnQueue(SqQueue &Q, int x){
    if((Q.rear+1) % MaxSize == Q.front) return false;   // 队列已满，采用这种方法判断队满会浪费一个存储空间
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
void QueueTraverse(SqQueue Q){
    for(int i=Q.front; i != Q.rear; i=(i+1) % MaxSize)
        printf("%d ", Q.data[i]);
    printf("\n");
}
