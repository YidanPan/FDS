#include<stdio.h>
#include<stdlib.h>
struct Vnode{
    int vertex;
    struct Vnode* next;
};
typedef struct Vnode Vnode;
typedef struct Vnode* PtrtoVnode;
PtrtoVnode G[1000]={NULL};
int seq[1000];
void insert(int u,int v){
    PtrtoVnode p=malloc(sizeof(Vnode));
    p->vertex=v;
    p->next=G[u];
    G[u]=p;
}
int IsEdge(int u,int v){
    PtrtoVnode temp=NULL;
    temp=G[u];
    while(temp!=NULL){
        if(temp->vertex==v)return 1;
        temp=temp->next;
    }
    return 0;
}
int Ishamiltonian(int seq[],int num,int n){
    if(num!=(n+1)) return 0;
    if(seq[1]!=seq[n+1]) return 0;
    int i=1;
    int visit[1000]={0};
    int count=0;
    int u,v;
    for(i=1;i<num;i++){
        u=seq[i];
        v=seq[i+1];
        if(visit[u]==0){
            visit[u]=1;
            count++;
        }
        if(IsEdge(u,v)==0){
            return 0;
        }
    }
    if(count!=n)return 0;
    return 1;
}
int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    int i=0;
    int u,v;
    for(i=1;i<=m;i++){
        scanf("%d %d",&u,&v);
        insert(u,v);
        insert(v,u);
    }//建构完无向图
    int k;
    scanf("%d",&k);
    while(k){
        int num;
        scanf("%d",&num);
        for(i=1;i<=num;i++){
            scanf("%d",&seq[i]);
        }
        if(Ishamiltonian(seq,num,n)==0){
            printf("NO\n");
        }else{
            printf("YES\n");
        }
        k--;
    }
    return 0;
}