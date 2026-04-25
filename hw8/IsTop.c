#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;//枚举 相当于false=0，true=1
#define MaxVertexNum 10  /* maximum number of vertices */
typedef int Vertex;      /* vertices are numbered from 1 to MaxVertexNum */

typedef struct AdjVNode *PtrToAdjVNode; 
struct AdjVNode{
    Vertex AdjV;//int
    PtrToAdjVNode Next;//结构体指针
};

typedef struct Vnode{
    PtrToAdjVNode FirstEdge;
} AdjList[MaxVertexNum];//结构体数组10 相当于这个结构体数组的名字是AdjList

typedef struct GNode *PtrToGNode;
struct GNode{  
    int Nv;
    int Ne;
    AdjList G;
};
typedef PtrToGNode LGraph;

LGraph ReadG(); /* details omitted */ //这里相当于根据输入把图构建好了 G就是图的首指针

bool IsTopSeq( LGraph Graph, Vertex Seq[] );

int main()
{
    int i, j, N;
    Vertex Seq[MaxVertexNum];
    LGraph G = ReadG();
    scanf("%d", &N);
    for (i=0; i<N; i++) {
        for (j=0; j<G->Nv; j++)
            scanf("%d", &Seq[j]);
        if ( IsTopSeq(G, Seq)==true ) printf("yes\n");
        else printf("no\n");
    }

    return 0;
}

/* Your function will be put here */
bool IsTopSeq( LGraph Graph, Vertex Seq[] ){
    int indegree[MaxVertexNum+1]={0};
    int i=0;
    for(i=0;i<Graph->Nv;i++){
        PtrToAdjVNode w=Graph->G[i].FirstEdge;
        while(w){
            indegree[w->AdjV]++;
            w=w->Next;
        }
    }//按照实际顶点把每一个顶点的入度记录好
    for(i=0;i<Graph->Nv;i++){
        int v=Seq[i]-1;
        if(v<0||v>=Graph->Nv)return false;
        if(indegree[v]!=0)return false;
        indegree[v]--;
        PtrToAdjVNode w=Graph->G[v].FirstEdge;
        while(w){
            indegree[w->AdjV]--;
            w=w->Next;
        }
    }
    return true;
}