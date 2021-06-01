#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

#define MAX_VERTEX_NUM 100

typedef char VerTexType;
typedef int  EdgeType;

typedef struct {
    VerTexType Vex[MAX_VERTEX_NUM];                     // 顶点表
    EdgeType Edge[MAX_VERTEX_NUM][MAX_VERTEX_NUM];    // 边表
    int VerTexNum, EdgeNum;                 // 记录当前顶点数和边数
}AMGraph;                                   // adjacent matrix


void CreateAMGraph(AMGraph &G);             // 创建邻接矩阵
void PrintMatrix(AMGraph G);
void Visit(VerTexType v);

int FirstNeighbor(AMGraph G, int v);
int NextNeighbor(AMGraph G, int v, int w);

void DFS(AMGraph G, int i);                 // 深度优先遍历
void DFSTraverse(AMGraph G);
void BFS(AMGraph G, SqQueue &Q, int v);     // 广度优先遍历
void BFSTraverse(AMGraph G);

bool visited[MAX_VERTEX_NUM];               // 访问标志的数组

int main()
{
    AMGraph G;
    CreateAMGraph(G); PrintMatrix(G);

    printf("开始深度优先遍历："); DFSTraverse(G); printf("\n");
    printf("开始广度优先遍历："); BFSTraverse(G); printf("\n");
    
}

void CreateAMGraph(AMGraph &G){
    int i, j;
    G.VerTexNum = 9;
    G.EdgeNum = 15;
    
    for(i=0; i<G.VerTexNum; i++) G.Vex[i] = 'A' + i;          // 初始化顶点
    for(i=0; i<G.VerTexNum; i++) printf("%c ", G.Vex[i]);   printf("\n");

    for(i=0; i<G.VerTexNum; i++){
        for(j=0; j<G.VerTexNum; j++) 
            G.Edge[i][j] = 0;   // 初始化边表
    }

    // 输入图信息
    G.Edge[0][1]=1;
    G.Edge[0][5]=1;
    
    G.Edge[1][2]=1;
    G.Edge[1][8]=1;
    G.Edge[1][6]=1;
    
    G.Edge[2][3]=1;
    G.Edge[2][8]=1;
    
    G.Edge[3][4]=1;
    G.Edge[3][7]=1;
    G.Edge[3][6]=1;
    G.Edge[3][8]=1;
    
    G.Edge[4][5]=1;
    G.Edge[4][7]=1;
    
    G.Edge[5][6]=1;
    
    G.Edge[6][7]=1;

    //利用无向图的对称性构成矩阵
    for(i=0; i<G.VerTexNum; i++){
        for(j=i; j<G.VerTexNum; j++) 
            G.Edge[j][i] = G.Edge[i][j];
    }
}

void PrintMatrix(AMGraph G){
    for(int i=0; i<G.VerTexNum; i++){
        for(int j=0; j<G.VerTexNum; j++) printf("%d ", G.Edge[i][j]);
        printf("\n");
    }
    printf("\n");
}

void Visit(VerTexType v){
    printf("%c ", v);
}
int FirstNeighbor(AMGraph G, int v){
    for(int j=0; j<G.VerTexNum; j++){
        if(G.Edge[v][j]==1 && v!=j) return j;
    }
    return -1;
}
int NextNeighbor(AMGraph G, int v, int i){
    for(int j=i+1; j<G.VerTexNum; j++){
        if(G.Edge[v][j] == 1) return j;
    }
    return -1;
}

void DFS(AMGraph G, int v){
    Visit(G.Vex[v]);
    visited[v] = true;         
    for(int w=FirstNeighbor(G, v); w>=0; w=NextNeighbor(G, v, w))
        if(!visited[w]) DFS(G, w);
}
void DFSTraverse(AMGraph G){
    for(int v=0; v<G.VerTexNum; v++) visited[v] = false;    // 初始化标记数组
    for(int v=0; v<G.VerTexNum; v++)
        if(!visited[v]) DFS(G, v);
}

void BFS(AMGraph G, SqQueue &Q, int v){
    Visit(G.Vex[v]);
    visited[v] = true;
    EnQueue(Q, v);
    while(!QueueEmpty(Q)){
        DeQueue(Q, v);
        for(int w=FirstNeighbor(G, v); w>=0; w=NextNeighbor(G, v, w))
            if(!visited[w]){
                Visit(G.Vex[w]);
                visited[w] = true;
                EnQueue(Q, w);
            }
    }
}
void BFSTraverse(AMGraph G){
    for(int i=0; i<G.VerTexNum; i++) visited[i] = false;
    SqQueue Q; InitQueue(Q);
    for(int v=0; v<G.VerTexNum; v++) 
        if(!visited[v]) BFS(G, Q, v);
}