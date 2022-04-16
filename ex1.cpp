#include <stdio.h>
#include <stdlib.h>

typedef char  VertexType;    //顶点类型    vertex type
typedef int   EdgeType;      //边上的权值类型  weight type on edge
#define MAXVEX  100          //最大顶点数        Maximum vertex

typedef struct
{
    VertexType vexs[MAXVEX];    //vertex table 顶点表
    EdgeType arc[MAXVEX][MAXVEX];   //Edge table 边表 邻接矩阵
    int numVertexes;                //图中顶点数   Number of vertices in the figure
    int numEdges;                   //图中边数
}MGraph;

typedef int QElemType;

typedef struct QNode
{
    QElemType data;
    struct QNode *next;
}QNode, *Queue;
typedef struct
{
    Queue Front;
    Queue Rear;
}LinkQueue;

bool visited[MAXVEX];

void init_Queue(LinkQueue *Q)
{
    Q->Front = (Queue)malloc(sizeof(QNode));
    if (!Q->Front)
    {
        printf("The memory allocation failed ! Queue initialization falied! \n");
        exit(0);
    }
    Q->Rear = Q->Front;
    Q->Front->next = NULL;
}

void EnQueue(LinkQueue *Q, int value)
{
    Queue qNew = (Queue)malloc(sizeof(QNode));
    if (!qNew)
    {
        printf("The memory allocation failed!Element can not enter queue!\n");
        exit(0);
    }
    qNew->data = value;
    qNew->next = NULL;
    Q->Rear->next = qNew;
    Q->Rear = qNew;
}

void DeQueue(LinkQueue *Q, int *value)
{
    Queue q;
    if (Q->Front == Q->Rear)
    {
        printf("The queue is empty!\n");
        exit(0);
    }

    q = Q->Front->next;
    *value = q->data;
    Q->Front->next = q->next;

    if (Q->Rear == q)
    {
        Q->Rear = Q->Front;
    }
    free(q);
    q = NULL;
}

bool isEmpty(LinkQueue Q)
{
    if (Q.Front == Q.Rear)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void CreateMGraph(MGraph *G)
{
    printf("Please enter the number of vertexes and edges : ");
    scanf("%d %d", &G->numVertexes, &G->numEdges);

    for (int i = 0; i < G->numVertexes; i++)
    {
        getchar();
        scanf("%c", &G->vexs[i]);
    }

    for (int i = 1; i <= G->numVertexes; i++){
        for (int j = 1; j <= G->numVertexes; j++){
			G->arc[i][j] = 0;}}
    int i, j;

    for (int k = 0; k < G->numEdges; k++)
    {
        
        scanf("%d %d", &i, &j);
        G->arc[i][j] = 1;
        G->arc[j][i] = G->arc[i][j]; 
    }
}

void DFS(MGraph G, int i)
{
    //先打印顶点
    printf("%c ", G.vexs[i]);
    //标记访问过
    visited[i] = true;

    //开始深度遍历
    for (int j = 0; j < G.numVertexes; j++)
    {
        //寻找未访问过的邻接顶点
        if (!visited[j] && G.arc[i+1][j+1] == 1)
        {
            DFS(G, j);
        }
    }
}

void DFSTraverse(MGraph G)
{
    //将顶点全部标记为未访问
    for (int i = 0; i < G.numVertexes; i++)
    {
        visited[i] = false;
    }

    for (int i = 0; i < G.numVertexes; i++)
    {
        if (!visited[i])       
        {
            DFS(G, i);
        }
    }
}

void BFSTraverse(MGraph G)
{
    int i, j;
    LinkQueue Q;
    //初始化标记顶点
    for (i = 0; i < G.numVertexes; i++)
    {
        visited[i] = false;
    }

    init_Queue(&Q);

    for (i = 0; i < G.numVertexes; i++)
    {
        if (!visited[i])
        {
            visited[i] = true;
            printf("%c ", G.vexs[i]);
            EnQueue(&Q, i);
            while(!isEmpty(Q))
            {
                DeQueue(&Q, &i);  //若该顶点未访问过，取出给i
                for (j = 0; j < G.numVertexes; j++)
                {
                    //找出顶点i的所有未访问过的邻接点
                    if (!visited[j] && G.arc[i+1][j+1] == 1)
                    {
                        visited[j] = true;
                        printf("%c ", G.vexs[j]);
                        EnQueue(&Q, j);
                    }
                }
            }
        }
    }

}

int main()
{
    MGraph G;
    CreateMGraph(&G);
	for(int i=1;i<=G.numVertexes;i++){
		for(int j=1;j<=G.numVertexes;j++){
			printf("%d ",G.arc[i][j]);

		}
		printf("\n");
	}
	printf("\n");
    //深度遍历
    DFSTraverse(G);
	printf("\n");
    //广度遍历
    BFSTraverse(G);

    return 0;
}
/*

8 9
1 2 3 4 5 6 7 8
1 2
1 3
2 4
2 5
4 8
5 8
3 6
3 7
6 7




*/