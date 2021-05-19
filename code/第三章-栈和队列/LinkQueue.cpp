#include <stdio.h>
#include <stdlib.h>

typedef struct LinkNode {
    int data;
    struct LinkNode *next;
} LinkNode;
typedef struct {
    LinkNode *front, *rear;
} LinkQueue;

void InitQueue(LinkQueue &Q);
bool DestroyQueue(LinkQueue &Q);
bool ClearQueue(LinkQueue &Q);
bool QueueEmpty(LinkQueue Q);
int QueueLength(LinkQueue Q);
bool GetHead(LinkQueue Q, int &x);
bool EnQueue(LinkQueue &Q, int x);
bool DeQueue(LinkQueue &Q, int &x);
void QueueTraverse(LinkQueue Q);

int main()
{
    LinkQueue Q; InitQueue(Q);

    if(QueueEmpty(Q)) printf("队列为空！\n");
    else printf("队列非空！\n");

    for(int i=0; i<10; i++) EnQueue(Q, i); QueueTraverse(Q);

    printf("当前队列长度为：%d\n", QueueLength(Q));

    int x;
    if(GetHead(Q, x)) printf("队头为：%d\n", x);
    else printf("队列为空！\n");

    if(DeQueue(Q, x)) printf("出队元素为：%d\n", x);
    else printf("队列为空！\n");
    if(DeQueue(Q, x)) printf("出队元素为：%d\n", x);
    else printf("队列为空！\n");

    QueueTraverse(Q); ClearQueue(Q);
    if(QueueEmpty(Q)) printf("队列为空！\n");
    else printf("队列非空！\n");

}
void InitQueue(LinkQueue &Q){
    Q.rear = Q.front = (LinkNode *)malloc(sizeof(LinkNode));    // 这里为带头结点的情况
    Q.front->next = NULL;
}
bool DestroyQueue(LinkQueue &Q){
    while(Q.front){
        Q.rear = Q.front->next;
        free(Q.front);
        Q.front = Q.rear;
    }
    return true;
}
bool ClearQueue(LinkQueue &Q){
    Q.rear = Q.front->next;
    while(Q.rear){
        Q.front->next = Q.rear->next;
        free(Q.rear);
        Q.rear = Q.front->next;
    }
    Q.rear = Q.front;
    return true;
}

bool QueueEmpty(LinkQueue Q){
    if(Q.rear == Q.front) return true;
    else return false;
}
int QueueLength(LinkQueue Q){
    int count = 0;
    LinkNode *p = Q.front;
    while(p != Q.rear){
        count++;
        p = p->next;
    }
    return count;
}
bool GetHead(LinkQueue Q, int &x){
    if(Q.rear==Q.front) return false;
    x = Q.front->next->data;
    return true;
}

bool EnQueue(LinkQueue &Q, int x){
    LinkNode *s = (LinkNode *)malloc(sizeof(LinkNode));
    s->data = x;
    s->next = NULL;
    Q.rear->next = s;
    Q.rear = s;
    return true;
}
bool DeQueue(LinkQueue &Q, int &x){
    if(Q.rear == Q.front) return false;
    LinkNode *p = Q.front->next;
    x = p->data;
    Q.front->next = p->next;
    if(Q.rear == p) Q.rear = Q.front;
    free(p);
    return true;
}
void QueueTraverse(LinkQueue Q){
    LinkNode *p = Q.front->next;
    while(p != NULL){
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}