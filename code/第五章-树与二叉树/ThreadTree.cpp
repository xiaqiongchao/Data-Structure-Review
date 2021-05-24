#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAXLEN 100
#define NLAYER 4

typedef struct ThreadNode {
    char data;
    struct ThreadNode *lchild, *rchild;     // 左右孩子指针
    int LTag, RTag;                       // 左右线索标志
}ThreadNode, *ThreadTree;

bool InitThreadTree(ThreadTree &T);
void CreateThreadTree(ThreadTree &T);
void Visit(ThreadTree T);
void TranslevelPrint(ThreadTree bt);                       // 图形显示

void InThread(ThreadTree &p, ThreadTree &pre);  // 中序线索化
void CreateInThread(ThreadTree &T);              

void InOrder(ThreadTree T);                    // 中序遍历
ThreadNode *FirstNode(ThreadNode *p);
ThreadNode *NextNode(ThreadNode *p); 

void InOrder1(ThreadTree T){
    if(T){
        InOrder1(T->lchild);
        Visit(T);
        InOrder1(T->rchild);
    }
}

int main()
{
    ThreadTree T; 
    InitThreadTree(T);
    CreateThreadTree(T); TranslevelPrint(T); printf("\n");  // ABD##E##CFH###G##

    printf("以中序遍历方式遍历："); InOrder1(T); printf("\n");
    printf("中序线索化方式遍历：");
    CreateInThread(T);   
    InOrder(T);         


}
bool InitThreadTree(ThreadTree &T){
    if(T == NULL) return false;
    T = NULL; return true;
}
// 先序递归创建方式
void CreateThreadTree(ThreadTree &T){
    char ch;
    scanf("%c", &ch);
    if(ch=='#') T = NULL;
    else {
        T = (ThreadTree)malloc(sizeof(ThreadNode));
        T->data = ch;
        T->LTag = 0;
        T->RTag = 0;
        CreateThreadTree(T->lchild);
        CreateThreadTree(T->rchild);
    }
}
void Visit(ThreadTree T){
    printf("%c ", T->data);
}

void CreateInThread(ThreadTree &T){
    ThreadTree pre = NULL;
    if(T != NULL){
        InThread(T, pre);           // 线索化
        pre->rchild = NULL;         // 处理最后一个节点
        pre->RTag = 1;
    }
}
void InThread(ThreadTree &p, ThreadTree &pre){
    if(p != NULL){
        InThread(p->lchild, pre);               // 递归，线索化左子树
        if(p->lchild==NULL){                    // 左子树为空，建立前驱线索
            p->lchild = pre;
            p->LTag = 1;
        }
        if(pre!=NULL && pre->rchild==NULL){     // 右子树为空，建立后继线索
            pre->rchild = p;
            pre->RTag = 1;
        }
        pre = p;                                // 标记当前节点成为刚刚访问过的节点
        InThread(p->rchild, pre);               // 递归，线索化右子树
    }
}
void InOrder(ThreadTree T){
    for(ThreadNode *p=FirstNode(T); p!=NULL; p=NextNode(p))
        Visit(p);
}
ThreadNode *FirstNode(ThreadNode *p){
    while(p->LTag==0)   p=p->lchild;            // 寻找最左下的节点（不一定是叶节点）可能还要右孩子
    return p;
}
ThreadNode *NextNode(ThreadNode *p){
    if(p->RTag==0)  return FirstNode(p->rchild); // 有右孩子，则返回右孩子子树下最左下节点
    else return p->rchild;                       // 没有右孩子，则右指针为线索
}










/**树形打印二叉树**/
void TranslevelPrint(ThreadTree bt){
	struct node{							//存放树结点 
		ThreadTree	vec[MAXLEN];
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
