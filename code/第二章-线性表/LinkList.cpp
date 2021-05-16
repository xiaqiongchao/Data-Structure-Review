#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct LNode{   // 定义单链表节点类型
    int data;           // 数据域
    struct LNode *next; // 指针域
}LNode, *LinkList;

bool InitList(LinkList &L); // 链表初始化
bool DestroyList(LinkList &L);
bool ClearList(LinkList &L);
bool ListEmpty(LinkList L);
int ListLength(LinkList L);
LNode *GetElem(LinkList L, int i);              // 这里按王道书
LNode *LocateElem(LinkList L, int e);           // 这里按王道书
bool ListInsert(LinkList &L, int i, int e);
bool ListDelete(LinkList &L, int i, int &e);
void ListTraverse(LinkList L);
LinkList List_HeadInsert(LinkList &L);          // 这里按王道书
LinkList List_TailInsert(LinkList &L);          // 这里按王道书

bool InsertNextNode(LNode *p, int e);           // 课本中没要求
bool InsertPriorNode(LNode *p, int e);          // 课本中没要求
bool DeleteNode(LNode *p);                      // 课本没要求

int main()
{
    LinkList L;
    // if(InitList(L)) printf("初始化成功！");
    // else printf("初始化失败！");

    // List_HeadInsert(L);ListTraverse(L); // 头插法
    List_TailInsert(L);ListTraverse(L); // 尾插法

    // if(DestroyList(L)) printf("销毁成功！\n");
    // else printf("销毁失败！\n");
    // ListTraverse(L);

    // if(ClearList(L)) printf("清除成功！\n");
    // else printf("清除失败！\n");
    // ListTraverse(L);

    // if(ListEmpty(L)) printf("链表为空！\n");
    // else printf("链表不为空！\n");

    printf("单链表的当前长度为：%d\n", ListLength(L));

    LNode *target_node1, *target_node2;
    target_node1 = GetElem(L, 3);printf("第3个元素为：%d\n", target_node1->data);
    target_node2 = LocateElem(L, 51);printf("查找%d成功！\n", target_node2->data);

    if(ListInsert(L, 5, 666)) ListTraverse(L);
    else printf("插入失败！\n");

    int e;
    if(ListDelete(L, 7, e)) ListTraverse(L);
    else printf("删除失败！\n");

    return 0;
}

bool InitList(LinkList &L){
    L = (LinkList)malloc(sizeof(LNode));
    if(L == NULL) return false;
    L->next = NULL;
    return true;
}
bool DestroyList(LinkList &L){      // 清除头节点
    if(L == NULL) return false;
    LinkList p;
    p = L;
    while(p != NULL){
        p = L->next;
        free(L);
        L = p;
    }
    return true;
}
bool ClearList(LinkList &L){        // 不清除头节点
    if(L == NULL) return false;
    LinkList pre, p;
    p = L->next;
    while(p != NULL){
        pre = p;
        p = p->next;
        free(pre);
    }
    L->next = NULL;
    return true;
}
bool ListEmpty(LinkList L){
    if(L != NULL && L->next == NULL) return true;
    else return false;
}
int ListLength(LinkList L){
    if(L == NULL || L->next == NULL) return 0;
    int i = 0;
    LinkList p = L->next;
    while(p != NULL){
        i++;
        p = p->next;
    }
    return i;
}
LNode *GetElem(LinkList L, int i){              // 需要牢固掌握
    if(i < 1) return NULL;
    LinkList p = L;
    int j = 0;
    while(p != NULL && j < i){
        j++;
        p = p->next;
    }
    return p;
}
LNode *LocateElem(LinkList L, int e){
    if(L == NULL && L->next == NULL) return NULL;
    LinkList p = L->next;
    while(p != NULL && p->data != e) 
        p = p->next;
    return p;
}
bool ListInsert(LinkList &L, int i, int e){     // 思路先找到第i-1个节点，在创建新节点插入
    if(L == NULL || i < 1) return false;
    LinkList p, s;
    int j = 0;
    p = L;
    while(p != NULL && j < i-1){
        j++;
        p = p->next;
    }
    if(p == NULL || j > i-1) return false;
    s = (LinkList)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return true;
}
bool ListDelete(LinkList &L, int i, int &e){        // 先找到第i-1个节点，然后删除i节点
    if(L == NULL || i < 1) return false;
    LinkList p = L, s;
    int j = 0;
    while(p->next != NULL && j < i-1){
        j++;
        p = p->next;
    }
    if(p->next == NULL || j > i-1) return false;
    s = p->next;
    e = s->data;
    p->next = s->next;
    free(s);
    return true;
}
// 遍历链表
void ListTraverse(LinkList L){
    if(L == NULL || L->next == NULL) return;
    LinkList p;
    p = L->next;
    while(p != NULL){
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}
// 这里按王道书头插法的方法创建单链表
LinkList List_HeadInsert(LinkList &L){       // 逆向建立单链表
    LNode *p;
    int n = 10;     // 默认插入10个元素
    L = (LinkList)malloc(sizeof(LNode));     // 创建头节点
    L->next = NULL;
    for(int i=0; i<10; i++){
        p = (LinkList)malloc(sizeof(LNode)); // 创建新插入的节点
        p->data = i * i + 1;
        p->next = L->next;
        L->next = p;
    }
    return L;
}
// 这里按王道书尾插法的方法创建单链表
LinkList List_TailInsert(LinkList &L){
    L = (LinkList)malloc(sizeof(LNode));     // 建立新节点
    L->next = NULL;
    LNode *p, *q;
    int n = 10;                              // 默认插入10个元素
    q = L;                                   // *q为工作指针
    for(int i=0; i<10; i++){
        p = (LinkList)malloc(sizeof(LNode)); // 创建新插入的节点
        p->data = i * i + 2;
        q->next = p;
        q = q->next;
    }
    p->next = NULL;
    return L;
}
bool InsertNextNode(LNode *p, int e){        // 节点后插
    if(p == NULL) return false;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    if(s == NULL) return false;
    s->data = e;
    s->next = p->next;
    p->next = s;
    return true;
}
bool InsertPriorNode(LNode *p, int e){      // 表面前插，实际后插然后交换元素
    if(p == NULL) return false;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    int temp = p->data;
    p->data = s->data;
    s->data = temp;
    return true;
}
bool DeleteNode(LNode *p){                  // 表面删除p节点，实际与p的后继节点交换数据，删除p的后继
    if(p == NULL ) return false;
    LNode *s = p->next;
    p->data = s->data;
    p->next = s->next;
    free(s);
    return true;
}