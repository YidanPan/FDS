#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX 1005
#define INF 1061109567
int G[MAX][MAX];
void Judge_Dijkstra(int inquiry[],int n){
    int flag[MAX];
    int dist[MAX];
    int v=inquiry[1];
    int i,j;

    for(i=1;i<=n;i++){
        flag[i]=0;
        dist[i]=G[v][i];
    }
    flag[v]=1;
    dist[v]=0;
    int cur=2;

    for(i=1;i<=n;i++){
        if(i==v)continue;

        int mindist=INF;
        for(j=1;j<=n;j++){
            if(j==v)continue;
            if(flag[j]==0&&dist[j]<mindist){
                mindist=dist[j];
            }
        }

        int k=inquiry[cur++];
        if(dist[k]==mindist){
            flag[k]=1;
        }else{
            printf("No\n");
            return;
        }

        for(j=1;j<=n;j++){
            if(j==v)continue;
            if(flag[j]==0&&G[k][j]<INF&&dist[k]+G[k][j]<dist[j]){
                dist[j]=dist[k]+G[k][j];
            }
        }

    }
    printf("Yes\n");
}
int main(){
    int Nv,Ne;
    scanf("%d %d",&Nv,&Ne);
    int i,j;
    for(i=1;i<=Nv;i++){
        for(j=1;j<=Nv;j++){
            G[i][j]=INF;
        }
    }

    int u,v,weight;
    for(i=1;i<=Ne;i++){
        scanf("%d %d %d",&u,&v,&weight);
        if(weight<G[u][v]){
            G[u][v]=weight;
            G[v][u]=weight;
        }
    }

    int k;
    scanf("%d",&k);
    for(i=1;i<=k;i++){
        int inquiry[MAX]={-1};
        for(j=1;j<=Nv;j++){
            scanf("%d",&inquiry[j]);
        }
        Judge_Dijkstra(inquiry,Nv);
    }

    clock_t start_time = clock();

    for(i=1;i<=k;i++){
        int inquiry[MAX];
        for(j=1;j<=Nv;j++){
            scanf("%d",&inquiry[j]);
        }
        Judge_Dijkstra(inquiry,Nv);
    }
    
    clock_t end_time = clock();
    double duration = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    
    printf("\n[Stress Test] Total Execution Time for %d queries: %f seconds\n", k, duration);
    return 0;
}