#include<stdio.h>
#include<stdlib.h>
#define MAX_V 505
#define MAX_E 125000
typedef struct node{
    int u;
    int v;
    int weight;
    int flag;
}EDGE;
EDGE edge[MAX_E];
int parent[MAX_V];

//把边按权重从小到大排序
int cmp(const void *a,const void *b){
    EDGE *edge_a=(EDGE*)a;
    EDGE *edge_b=(EDGE*)b;
    if(edge_a->weight<edge_b->weight){
        return -1;
    }else if(edge_a->weight>edge_b->weight){
        return 1;
    }else{
        return 0;
    }
}

void initial(int n){
    int i=0;
    for(i=1;i<=n;i++){
        parent[i]=i;
    }
}

int find(int x){
    if(parent[x]==x)return x;
    return parent[x]=find(parent[x]);
}

void kruskal(int ignore_idx,int *outweight,int *outcomponent,int n,int m){
    initial(n);
    int i=1;
    int curr_weight=0;
    int component=n;
    for(i=1;i<=m;i++){
        if(i==ignore_idx)continue;
        int u=edge[i].u;
        int v=edge[i].v;
        int root_u=find(u);
        int root_v=find(v);
        if(root_u!=root_v){
            parent[root_u]=root_v;
            curr_weight+=edge[i].weight;
            component--;
            if(ignore_idx==-1){
                edge[i].flag=1;
            }
        }
        if(component==1)break;
    }
    *outweight=curr_weight;
    *outcomponent=component;
}

int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    int i=0;
    for(i=1;i<=m;i++){
        scanf("%d %d %d",&edge[i].u,&edge[i].v,&edge[i].weight);
        edge[i].flag=0;
    }
    qsort(edge+1,m,sizeof(EDGE),cmp);//qsort函数传入要排序的数组名 排序的数量 数组大小 排序规则cmp

    int first_weight=0;
    int first_component=0;
    kruskal(-1,&first_weight,&first_component,n,m);
    if(first_component>1){
        printf("No MST\n%d\n",first_component);
        return 0;
    }

    for(i=1;i<=m;i++){
        if(edge[i].flag==1){
            int temp_weight=0;
            int temp_component=0;
            kruskal(i,&temp_weight,&temp_component,n,m);
            if(temp_weight==first_weight&&temp_component==1){
                printf("%d\nNo\n",temp_weight);
                return 0;
            }
        }
    }

    printf("%d\nYes\n",first_weight);
    return 0;
}