#include<stdio.h>
#include<stdlib.h>
#define MAX 1005
#define INF 2147483647 //INF不要溢出
int hash[MAX]={0};
int indegree[MAX]={0};
int graph[MAX][MAX]={0};//构建有向图，以index为下标 index和key一一对应

void graphmake(int n){
    int home,pos;
    int i=0;
    for(i=0;i<n;i++){
        if(hash[i]<0){
            indegree[i]=-1;
            continue;
        }
        home=hash[i]%n;//计算原来应该在的位置
        if(home==i){//原来的位置就是目前所在位置说明这个是第一个输入的，degree=0
            indegree[i]=0;
        }else{
            pos=home;
            while(pos!=i){
                if(hash[pos]>=0){
                    indegree[i]++;
                    graph[pos][i]=1;
                }
                pos=(pos+1)%n;//注意这里是防止下标在数组中溢出，可能出现绕圈循环现象
            }
        }
    }
}

int first=1;
void topsort(int n){
    int i=0;
    int count=1;
    int total=0;
    for(i=0;i<n;i++){
        if(hash[i]>=0)total++;
    }
    while(count<=total){//每次遍历都是一次输出，输出是hash中有效的点
        int min_index=0;
        int min=INF;
        for(i=0;i<n;i++){//遍历indegree数组，找出所有入度=0的点，找出其中的最小值及其下标
            if(indegree[i]==0){
                if(hash[i]<min){
                    min_index=i;
                    min=hash[i];
                }
            }
        }
        //遍历graph中所有min_index指向的点，把他们的入度都--
        for(i=0;i<n;i++){
            if(graph[min_index][i]==1){
                indegree[i]--;
            }
        }
        indegree[min_index]--;
        //输出 
        if(first==1){
            printf("%d",min);
            first=0;
        }else{
            printf(" %d",min);
        }
        count++;
    }
}

int main(){
    int n;
    scanf("%d",&n);//hash表长
    int i=0;
    for(i=0;i<n;i++){
        scanf("%d",&hash[i]);//原始哈希表状态
    }
    //根据哈希表状态建立图
    graphmake(n);
    //拓扑排序输出（每次输出degree=0的点，最小值优先）
    topsort(n);
    return 0;
}