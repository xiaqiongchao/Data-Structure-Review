#include <stdio.h>
#include <stdlib.h>

#define INFINITY       9999 
#define MAX_VERTEX_NUM 100

typedef int VertexType;
typedef int EdgeType;

typedef struct {
    VertexType Vex[MAX_VERTEX_NUM];                  // 顶点表
    EdgeType   Arc[MAX_VERTEX_NUM][MAX_VERTEX_NUM];     // 边表
    int VexNum, ArcNum;                           // 记录当前顶点数和边数
}AMGraph; 

void CreateAMGraph(AMGraph &G);                         // 创建邻接矩阵
void PrintMatrix(AMGraph G);
void Floyd(AMGraph G, int dist[][MAX_VERTEX_NUM], int path[][MAX_VERTEX_NUM]);

int main()
{
    AMGraph G; CreateAMGraph(G);  // rintMatrix(G);

    int dist[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int path[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    Floyd(G, dist, path);

    printf("最短路径弗洛伊德算法\n");
    printf("各顶点最短路径如下：\n");
    for(int v=0; v<G.VexNum; v++){
        for(int w=v+1; w<G.VexNum; w++){
            printf("v%d->v%d weight:%2d ", v, w, dist[v][w]);
            int k = path[v][w];
            printf("path：%d", v);
            while(k != w){
                printf(" -> %d ", k);
                k = path[k][w];
            }
            printf(" -> %d\n", w);
        }
        printf("-------------------------------------\n");
    }

    printf("dist数组：\n"); 
    for(int i=0; i<G.VexNum; i++){
        for(int j=0; j<G.VexNum; j++) printf("%02d ", dist[i][j]);
        printf("\n");
    }
    printf("path数组：\n"); 
    for(int i=0; i<G.VexNum; i++){
        for(int j=0; j<G.VexNum; j++) printf("%2d ", path[i][j]);
        printf("\n");
    }

}

void CreateAMGraph(AMGraph &G){
    int i, j;
    G.VexNum = 9;
    G.ArcNum = 16;

    for(i=0; i<G.VexNum; i++) G.Vex[i] = i;
    for(i=0; i<G.VexNum; i++){
        for(j=0; j<G.VexNum; j++){
            if(i==j) G.Arc[i][j] = 0;
            else G.Arc[i][j] = G.Arc[j][i] = INFINITY;
        }
    }

    G.Arc[0][1]=1;
    G.Arc[0][2]=5;
    G.Arc[1][2]=3;
    G.Arc[1][3]=7;
    G.Arc[1][4]=5;
    
    G.Arc[2][4]=1;
    G.Arc[2][5]=7;
    G.Arc[3][4]=2;
    G.Arc[3][6]=3;
    G.Arc[4][5]=3;
    
    G.Arc[4][6]=6;
    G.Arc[4][7]=9;
    G.Arc[5][7]=5;
    G.Arc[6][7]=2;
    G.Arc[6][8]=7;
    
    G.Arc[7][8]=4;

    for(i=0; i<G.VexNum; i++)
        for(j=i; j<G.VexNum; j++)
            G.Arc[j][i] = G.Arc[i][j];
}
void PrintMatrix(AMGraph G){
    for(int i=0; i<G.VexNum; i++){
        for(int j=0; j<G.VexNum; j++) printf("%4d ", G.Arc[i][j]);
        printf("\n");
    }
    printf("\n");
}
void Floyd(AMGraph G, int dist[][MAX_VERTEX_NUM], int path[][MAX_VERTEX_NUM]){
    int v, w, k;
    for(v=0; v<G.VexNum; v++){
        for(w=0; w<G.VexNum; w++){
            dist[v][w] = G.Arc[v][w];
            path[v][w] = w;
        }
    }

    // k表示进行迭代的中转顶点
    for(k=0; k<G.VexNum; k++){
        for(v=0; v<G.VexNum; v++){
            for(w=0; w<G.VexNum; w++){
                if(dist[v][w] > dist[v][k]+dist[k][w]){
                    dist[v][w] = dist[v][k]+dist[k][w];
                    path[v][w] = path[v][k];
                }
            }
        }
    }
}

