#include <stdio.h>
#include <stdlib.h>

#define INFINITY       9999 
#define MAX_VERTEX_NUM 100

typedef int VertexType;
typedef int EdgeType;

typedef struct {
    VertexType Vex[MAX_VERTEX_NUM];                    // 顶点表
    EdgeType   Arc[MAX_VERTEX_NUM][MAX_VERTEX_NUM];    // 边表
    int VexNum, ArcNum;                                // 记录当前顶点数和边数
}AMGraph; 

void CreateAMGraph(AMGraph &G);                        // 创建邻接矩阵
void PrintMatrix(AMGraph G);
void Dijkstra(AMGraph G, VertexType v0, int dist[], int path[]);

int main()
{
    AMGraph G; CreateAMGraph(G);  // rintMatrix(G);

    int dist[MAX_VERTEX_NUM];   
    int path[MAX_VERTEX_NUM];
    Dijkstra(G, 0, dist, path);

    printf("dist数组："); for(int i=0; i<G.VexNum; i++) printf("%2d ", dist[i]);printf("\n");
    printf("path数组："); for(int i=0; i<G.VexNum; i++) printf("%2d ", path[i]);printf("\n");

    printf("最短路径路线：\n");
    for(int i=1; i<G.VexNum; i++){
        printf("v%d—>v%d :", 0, i);
        int j=i;
        printf(" v%d", i);
        while(path[j] != -1){
            printf(" v%d ", path[j]);
            j = path[j];
        }
        printf("\n");
    }

    printf("最短路径权值和：\n");
    for(int i=1; i<G.VexNum; i++){
        printf("v%d ——> v%d : %d \n", G.Vex[0], G.Vex[i], dist[i]);
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

void Dijkstra(AMGraph G, VertexType v0, int dist[], int path[]){
    int v, w, k=0, min;
    int final[MAX_VERTEX_NUM];   // final[w]=1表示以求得最短路径;

    for(v=0; v<G.VexNum; v++){
        final[v] = 0;
        dist[v] = G.Arc[v0][v];
        path[v] = 0;
    }
    final[v0] = 1;
    dist[v0] = 0;
    path[v0] = -1;

    for(v=1; v<G.VexNum; v++){
        min = INFINITY;
        for(w=0; w<G.VexNum; w++){
            if(!final[w] && dist[w]<min){
                k = w;
                min = dist[w];
            }
        }
        final[k] = 1;
        for(w=0; w<G.VexNum; w++){
            if(!final[w] && (min+G.Arc[k][w])<dist[w]){
                dist[w] = min + G.Arc[k][w];
                path[w] = k;
            }
        }

    }
}