#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAXLEN 100
#define NLAYER 4

// 二叉树的链式存储
typedef struct BiTNode {
    char data;
    struct BiTNode* lchild;
    struct BiTNode* rchild;
}BiTNode, *BiTree;

// 链队
typedef struct LinkNode {
    BiTNode *data;
    struct LinkNode *next;
}LinkNode;
typedef struct {
    LinkNode *front, *rear;
}LinkQueue;

bool InitBiTree(BiTree &T);
void CreateBiTree(BiTree &T);
bool BiTreeEmpty(BiTree T);

int BiTreeDepth(BiTree T);
int NodeCount(BiTree T);
int LeafCount(BiTree T);

void PreOrder(BiTree T);
void InOrder(BiTree T);
void PostOrder(BiTree T);
void LevelOrder(BiTree T);

void Visit(BiTree T);
void TranslevelPrint(BiTree bt);                       // 图形显示

void InitQueue(LinkQueue &Q);
bool QueueEmpty(LinkQueue Q);
bool EnQueue(LinkQueue &Q, BiTree x);
bool DeQueue(LinkQueue &Q, BiTree &x);

int main()
{
    BiTree T; InitBiTree(T);
    printf("以先序遍历方式建立二叉链表，没有孩子的节点用#号补充：");
    CreateBiTree(T); TranslevelPrint(T); printf("\n");
    printf("树的深度为：%d\n", BiTreeDepth(T));
    printf("总节点个数：%d\n", NodeCount(T));

    printf("先序遍历："); PreOrder(T);  printf("\n");
    printf("中序遍历："); InOrder(T);   printf("\n");
    printf("后序遍历："); PostOrder(T); printf("\n");
    printf("层序遍历："); LevelOrder(T);printf("\n");
    
}

bool InitBiTree(BiTree &T){
    if(T == NULL) return false;
    T = NULL; return true;
}
// 先序递归创建方式
void CreateBiTree(BiTree &T){
    char ch;
    scanf("%c", &ch);
    if(ch=='#') T = NULL;
    else {
        T = (BiTree)malloc(sizeof(BiTNode));
        T->data = ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
}
bool BiTreeEmpty(BiTree T){
    return T == NULL ? true : false;
}
int BiTreeDepth(BiTree T){
    if(T == NULL) return 0;
    else {
        int ld, rd;
        ld = BiTreeDepth(T->lchild);
        rd = BiTreeDepth(T->rchild);
        return (ld >= rd ? ld : rd) + 1;
    }
}
int NodeCount(BiTree T){
    if(T == NULL) return 0;
    else return NodeCount(T->lchild) + NodeCount(T->rchild) + 1;
}
void Visit(BiTree T){
    printf("%c ", T->data);
}

void PreOrder(BiTree T){
    if(T){
        Visit(T);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}
void InOrder(BiTree T){
    if(T){
        InOrder(T->lchild);
        Visit(T);
        InOrder(T->rchild);
    }
}
void PostOrder(BiTree T){
    if(T){
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        Visit(T);
    }
}
void LevelOrder(BiTree T){
    LinkQueue Q;
    InitQueue(Q);
    BiTree p;
    EnQueue(Q, T);  // 根结点先入队
    while(!QueueEmpty(Q)){
        DeQueue(Q, p); Visit(p);
        if(p->lchild != NULL) EnQueue(Q, p->lchild);
        if(p->rchild != NULL) EnQueue(Q, p->rchild);
    }
}


void InitQueue(LinkQueue &Q){
    Q.rear = Q.front = (LinkNode *)malloc(sizeof(LinkNode)); 
    Q.front->next = NULL;
}
bool QueueEmpty(LinkQueue Q){
    if(Q.rear == Q.front) return true;
    else return false;
}
bool EnQueue(LinkQueue &Q, BiTree x){
    LinkNode *s = (LinkNode *)malloc(sizeof(LinkNode));
    s->data = x;
    s->next = NULL;
    Q.rear->next = s;
    Q.rear = s;
    return true;
}
bool DeQueue(LinkQueue &Q, BiTree &x){
    if(Q.rear == Q.front) return false;
    LinkNode *p = Q.front->next;
    x = p->data;
    Q.front->next = p->next;
    if(Q.rear == p) Q.rear = Q.front;
    free(p);
    return true;
}


/**树形打印二叉树**/
void TranslevelPrint(BiTree bt){
	struct node{							//存放树结点 
		BiTree	vec[MAXLEN];
		int layer[MAXLEN];					//结点所在的层
		int locate[MAXLEN]; 				//打印结点所在的位置
		int front, rear; 
	}Q;										//定义队列Q
	int i, j=1, k=0, nLocate;
	Q.front=0;	Q.rear=0;					//初始化队列Q队头，队尾 
	printf(" ");
	Q.vec[Q.rear]=bt;						//将二叉树根节点入队列 
	Q.layer[Q.rear]=1;
	Q.locate[Q.rear]=20;
	Q.rear=Q.rear+1;
	while(Q.front<Q.rear)
	{
		bt=Q.vec[Q.front];
		i=Q.layer[Q.front];
		nLocate=Q.locate[Q.front];
		if(j<i)								//按层打印时换行 
		{
			printf("\n");	printf("\n");
			j=j+1;	k=0;
			while(k<nLocate)
			{
				printf(" ");	k++;
			}/*endwhile*/ 
		}/*endif*/
		while(k<(nLocate-1))				//利用结点深度控制结点位置 
		{
			printf(" ");	k++;	
		}/*endwhile*/
		printf("%c", bt->data);
		Q.front=Q.front+1;
		if(bt->lchild!=NULL)				//存在左子树，将左子树根节点入队列 
		{
			Q.vec[Q.rear]=bt->lchild;
			Q.layer[Q.rear]=i+1;
			Q.locate[Q.rear]=(int)(nLocate-pow(2, NLAYER-i-1));
			Q.rear=Q.rear+1;
		}/*endif*/
		if(bt->rchild!=NULL)				//存在右子树，将右子树结点入队列 
		{
			Q.vec[Q.rear]=bt->rchild;
			Q.layer[Q.rear]=i+1;
			Q.locate[Q.rear]=(int)(nLocate+pow(2, NLAYER-i-1));
			Q.rear=Q.rear+1;
		}/*endif*/		 
	}/*endwhile*/ 
} 