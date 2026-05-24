#include<stdio.h>
#include<stdlib.h>
#define MAX 20005
typedef struct Node{
    int id;
    struct Node* pre;
    struct Node* next;
}Node;

Node* history[MAX]={NULL};
Node* cache[MAX]={NULL};

typedef struct queue{
    Node* head;
    Node* tail;
    int size;
}queue;

int num_history[MAX]={0};
int in_history[MAX]={0};
int in_cache[MAX]={0};

void initial(queue* a,int n){
    a->head=NULL;
    a->tail=NULL;
    a->size=n;
}

void removenode(queue* q,Node* node){
    if(node==NULL)return;
    if(node->pre==NULL){
        q->head=node->next;
        if(q->head==NULL){
            q->tail=NULL;
        }else{
            node->next->pre=NULL;
            node->next=NULL;
        }
    }else if(node->next==NULL){
        q->tail=node->pre;
        node->pre->next=NULL;
        node->pre=NULL;
    }else{
        node->pre->next=node->next;
        node->next->pre=node->pre;
        node->pre=NULL;
        node->next=NULL;
    }
    q->size--;
    free(node);
}

void Puttail(queue* q,int id){
    Node* newnode=malloc(sizeof(Node));
    newnode->id=id;
    newnode->next=NULL;
    newnode->pre=NULL;
    if(q->head==NULL){
        q->head=newnode;
        q->tail=newnode;
        q->size++;
    }else{
        q->tail->next=newnode;
        newnode->pre=q->tail;
        q->tail=newnode;
        q->size++;
    }
}

int main(){
    int k,n,m;
    scanf("%d %d %d",&k,&n,&m);//k-命中次数 n-队列长度 m-id数量
    queue q_history;
    queue q_cache;
    initial(&q_history,n);
    initial(&q_cache,n);

    int i=0;
    for(i=0;i<m;i++){
        int id;
        scanf("%d",&id);
        if(in_cache[id]){//已经在缓存队列中
            //把这个数据的节点先删除然后插入到尾巴
            removenode(&q_cache,cache[id]);
            Puttail(&q_cache,id);
        }else if(in_history[id]){//如果已经在历史缓存队列中
            num_history[id]++;
            if(num_history[id]>=k){//如果访问次数超过了k次，需要把这个节点放入缓存队列中
                removenode(&q_history,history[id]);
                in_history[id]=0;
                num_history[id]=0;
                
            }else{//访问次数没达到k次，把这个节点删除然后移动到队尾

            }
        }else{//如果都不在 是新id
            if(q_history.size>=n){//如果历史缓存队列已经满了
                //删除掉第一个节点然后把新节点插入到队尾
            }else{
                //直接插入到队尾
            }
        }
    }
    return 0;
}