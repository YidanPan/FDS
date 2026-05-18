#include<stdio.h>
#include<stdlib.h>
#define MAX 1005
#define INF 1061109567
int G[MAX][MAX];//Graph(adjacency matrix)
void Judge_Dijkstra(int inquiry[],int n){//Determine whether the sequence is a Dijkstra sequence
    int flag[MAX];//Mark whether the element is confirmed
    int dist[MAX];//Store the distance from each vertex to the source vertex
    int v=inquiry[1];//the source vertex
    int i,j;

    for(i=1;i<=n;i++){//Initialize the flag array and the dist array
        flag[i]=0;
        dist[i]=G[v][i];
    }
    flag[v]=1;//The source vertex is already confirmed
    dist[v]=0;//The source vertex's distance is 0
    int cur=2;//Start judging from the second vertex in the sequence

    for(i=1;i<=n;i++){
        if(i==v)continue;//Skip the source vertex

        int mindist=INF;//The shortest distance to the source vertex
        for(j=1;j<=n;j++){
            if(j==v)continue;//Skip teh source vertex
            if(flag[j]==0&&dist[j]<mindist){//Find the vertex with the shortest distance to the source vertex and its distance in each round
                mindist=dist[j];
            }
        }

        int k=inquiry[cur++];
        if(dist[k]==mindist){//Determine whether the distance from each vertex in the sequence to the source vertex is equal to the shortest distance obtained in the current round
            flag[k]=1;
        }else{
            printf("No\n");
            return;
        }

        for(j=1;j<=n;j++){
            if(j==v)continue;
            if(flag[j]==0&&G[k][j]<INF&&dist[k]+G[k][j]<dist[j]){//The shortest distance passing through the source vertex and vertex k
                dist[j]=dist[k]+G[k][j];//Update the dist array
            }
        }

    }
    printf("Yes\n");
}
int main(){
    int Nv,Ne;
    scanf("%d %d",&Nv,&Ne);//Nv:the number of vertexs  Ne:the number of edges
    int i,j;
    for(i=1;i<=Nv;i++){//Initialize the adjacency matrix
        for(j=1;j<=Nv;j++){
            G[i][j]=INF;
        }
    }

    int u,v,weight;
    for(i=1;i<=Ne;i++){//Construct a weighted adjacency matrix
        scanf("%d %d %d",&u,&v,&weight);
        if(weight<G[u][v]){
            G[u][v]=weight;
            G[v][u]=weight;
        }
    }

    int k;
    scanf("%d",&k);
    for(i=1;i<=k;i++){
        int inquiry[MAX]={-1};//Store the query sequence given in the problem
        for(j=1;j<=Nv;j++){
            scanf("%d",&inquiry[j]);
        }
        Judge_Dijkstra(inquiry,Nv);//Judge in sequence
    }

    return 0;
}