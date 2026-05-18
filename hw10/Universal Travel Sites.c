#include<stdio.h>
#include<string.h>
#define MAX 1005
#define INF 88888
char name[MAX][4];
int graph[MAX][MAX]={0};
int parent[MAX]={-1};
int count=0;

int convert_nametoid(char *c){
    int i=0;
    for(i=0;i<count;i++){
        if(strcmp(name[i],c)==0){
            return i;
        }
    }
    strcpy(name[count++],c);
    return count-1;
}

int bfs(int s,int t){//找每一条通往t的路径，做好标记
    memset(parent,-1,sizeof(parent));
    int queue[INF];
    int front=0,rear=0;
    queue[rear++]=s;
    parent[s]=s;
    int u,v;
    while(front<rear){
        u=queue[front++];
        for(v=0;v<count;v++){
            if(parent[v]==-1&&graph[u][v]>0){//这里graph都是已经更新过了 所以不会找到重复的路径
                parent[v]=u;
                if(v==t) return 1;
                queue[rear++]=v;
            }
        }
    }
    return 0;
}

int flow(int s,int t){
    int maxflow=0;
    while(bfs(s,t)){
        int minflow=INF;
        int curr=t;
        int pre;
        while(curr!=s){
            pre=parent[curr];
            if(graph[pre][curr]<minflow)minflow=graph[pre][curr];
            curr=pre;
        }//find the minflow aloong a path (iterate to find every minflow along every path)
        curr=t;
        while(curr!=s){
            pre=parent[curr];
            graph[pre][curr]-=minflow;
            graph[curr][pre]+=minflow;
            curr=pre;
        }
        maxflow+=minflow;
    }
    return maxflow;
}

int main(){
    int s,t,n;
    char s_name[4],t_name[4];
    scanf("%s %s %d",s_name,t_name,&n);
    s=convert_nametoid(s_name);
    t=convert_nametoid(t_name);
    int i=0;
    for(i=0;i<n;i++){
        char u_name[4],v_name[4];
        int u,v;
        scanf("%s %s",u_name,v_name);
        u=convert_nametoid(u_name);
        v=convert_nametoid(v_name);
        int m;
        scanf("%d",&m);
        graph[u][v]+=m;

    }
    printf("%d\n",flow(s,t));
    return 0;
}