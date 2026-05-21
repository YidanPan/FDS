#include <stdio.h>
#include <stdlib.h>

#define MaxVertices 10  /* maximum number of vertices */
typedef int Vertex;     /* vertices are numbered from 0 to MaxVertices-1 */
typedef struct VNode *PtrToVNode;
struct VNode {
    Vertex Vert;
    PtrToVNode Next;
};
typedef struct GNode *Graph;
struct GNode {
    int NumOfVertices;
    int NumOfEdges;
    PtrToVNode *Array;
};

Graph ReadG(); /* details omitted */

void PrintV( Vertex V )
{
   printf("%d ", V);
}

void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) );

int main()
{
    Graph G = ReadG();
    StronglyConnectedComponents( G, PrintV );
    return 0;
}

/* Your function will be put here */
#define MAX 1005
int *dfn;
int *low;
int timer;
int top;
int *stack;
int *in_stack;

void dfs(int u,Graph G,void (*visit)(Vertex V)){
    timer++;
    dfn[u]=timer;
    low[u]=timer;
    top++;
    in_stack[u]=1;
    stack[top]=u;
    PtrToVNode ptr=G->Array[u];
    while(ptr!=NULL){
        int v=ptr->Vert;
        if(dfn[v]==0){
            dfs(v,G,visit);
            if(low[v]<low[u]){
                low[u]=low[v];
            }
        }else if(in_stack[v]==1){
            if(dfn[v]<low[u]){
                low[u]=dfn[v];
            }
        }
        ptr=ptr->Next;
    }
    if(dfn[u]==low[u]){
        int v;
        do{
            v=stack[top--];
            visit(v);
            in_stack[v]=0;
        }while(v!=u);
        printf("\n");
    }
}
void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) ){
    int i;
    int n=G->NumOfVertices;
    dfn=malloc(n*sizeof(int));
    low=malloc(n*sizeof(int));
    stack=malloc(n*sizeof(int));
    in_stack=malloc(n*sizeof(int));
    timer=0;
    top=-1;
    for(i=0;i<n;i++){
        dfn[i]=0;
        low[i]=0;
        in_stack[i]=0;
    }
    for(i=0;i<n;i++){
        if(dfn[i]==0){
            dfs(i,G,visit);
        }
    }
    free(dfn);
    free(low);
    free(stack);
    free(in_stack);
}