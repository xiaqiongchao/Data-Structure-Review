#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXLEN 100
#define NLAYER 4

typedef struct BSNode{
    int key;
    struct BSNode *lchild, *rchild;
}BSTNode, *BSTree;

void CreateBST(BSTree &T, int data[], int n);

BSTNode *SearchBST(BSTree T, int key);
int InsertBST(BSTree &T, int k);
bool DeleteBST(BSTree &T, int key);

void InOrder(BSTree T);
void TranslevelPrint(BSTree bt);

int main()
{
    int data[20]; 
    for(int i=0; i<20; i++) data[i] = rand()%100 + 1;
    BSTree T; CreateBST(T, data, 10); 
    printf("中序遍历结果："); InOrder(T); printf("\n");
    TranslevelPrint(T); printf("\n");

    int x; printf("请输入查找元素："); scanf("%d", &x);
    BSTNode *t = SearchBST(T, x);
    if(t) printf("查找成功！该节点为：%d\n", t->key);

    if(DeleteBST(T, 63)){
        printf("删除成功！\n"); TranslevelPrint(T);
    }
    else printf("删除失败\n");

}

void CreateBST(BSTree &T, int data[], int n){
    T = NULL;
    int i = 0;
    while(i < n){
        InsertBST(T, data[i]);
        i++;
    }
}
int InsertBST(BSTree &T, int k){
    if(T == NULL){
        T = (BSTree)malloc(sizeof(BSTNode));
        T->key = k;
        T->lchild = T->rchild = NULL;
        return 1;
    }
    else if(k==T->key) return 0;
    else if(k<T->key) return InsertBST(T->lchild, k);
    else return InsertBST(T->rchild, k);
}
void InOrder(BSTree T){
    if(T){
        InOrder(T->lchild);
        printf("%d ", T->key);
        InOrder(T->rchild);
    }
}

BSTNode *SearchBST(BSTree T, int key){
    while(T!=NULL && key!=T->key){
        if(key<T->key) T = T->lchild;
        else T = T->rchild;
    }
    return T;
}
bool DeleteBST(BSTree &T, int key){
    BSTree x, y;
	x = T; y = NULL;
	int flag = -1;
	while(x->key != key){
		if(key > x->key){
			y = x;    //记录父节点
			x = x->rchild; 
			flag = 1;
		}else{
			y=x;
			x=x->lchild;
			flag=0;
		}	
	}
	if(x->key != key){
		x = NULL; y = NULL; 
		printf("不存在此元素！\n");
		return false;
	}
	if(x != NULL){
		if(x->lchild != NULL && x->rchild != NULL){
	     	BSTree t = x;
			y = x; x = x->lchild;//向左走一步
			while(x->rchild != NULL){
				y = x;
				x = x->rchild;//向右走到头 
			} 
			t->key = x->key;
			if(x->lchild != NULL) y->rchild = x->lchild;
			else y->rchild = NULL;
			free(x); 
			return true;	
		}else if(x->rchild != NULL && x->lchild == NULL){
		       if(y->lchild == x) y->lchild == x->rchild;	
		       else if(y->rchild == x) y->rchild = x->rchild;
		       free(x);
		       return true;
		}else if(x->lchild != NULL && x->rchild == NULL){
		    if(y->lchild == x) y->lchild = x->lchild;	
		    else if(y->rchild == x) y->rchild = x->lchild;
		    free(x);
		    return true;
		}
		else if(x->lchild == NULL && x->rchild == NULL){
			if(y->lchild == x) y->lchild = NULL;	
		    else if(y->rchild == x) y->rchild = NULL;
		    free(x);
		    return true;
		}
	}
}


void TranslevelPrint(BSTree bt){
	struct node{							//存放树结点 
		BSTree	vec[MAXLEN];
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
		printf("%d", bt->key);
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