#include<stdio.h>
#include<stdlib.h>
#define MAX 20005
typedef struct Node{
    int id;
    struct Node* pre;
    struct Node* next;
}Node;

typedef struct queue{
    int size;
    Node* head;
    Node* tail;
}queue;

int num_history[MAX]={0};
int in_history[MAX]={0};
int in_cache[MAX]={0};

Node* history[MAX]={NULL};
Node* cache[MAX]={NULL};

void initial(queue* q){
    q->head=NULL;
    q->tail=NULL;
    q->size=0;
}

void Removenode(queue* q,Node* node){
    if(node==NULL)return;//记得考虑这个节点是空节点的情况
    if(node->pre==NULL){
        if(node->next==NULL){//队列中只有一个节点
            q->head=NULL;
            q->tail=NULL;
        }else{
            q->head=node->next;
            node->next->pre=NULL;
        }
    }else if(node->next==NULL){
        q->tail=node->pre;
        node->pre->next=NULL;
    }else{
        node->pre->next=node->next;
        node->next->pre=node->pre;
    }
    free(node);
}

Node* Puttail(queue* q,int x){
    Node* newnode=malloc(sizeof(Node));
    newnode->pre=NULL;
    newnode->next=NULL;
    newnode->id=x;
    if(q->head==NULL){//要考虑整个队列如果是空的情况
        q->head=newnode;
        q->tail=newnode;
    }else{
        q->tail->next=newnode;
        newnode->pre=q->tail;
        q->tail=newnode;
    }
    return newnode;
}

int Popfirst(queue* q){
    if(q->head==NULL)return -1;
    Node* old_head=q->head;
    int temp=q->head->id;
    q->head=old_head->next;
    if(q->head==NULL){
        q->tail=NULL;
    }else{
        q->head->pre=NULL;
    }
    old_head->next=NULL;
    free(old_head);
    return temp;
}

void print(queue* q){
    if(q->head==NULL){
        printf("-\n");
        return;
    }
    Node* temp=NULL;
    temp=q->head;
    int first=1;
    while(temp!=NULL){
        if(first==1){
            printf("%d",temp->id);
            first=0;
        }else{
            printf(" %d",temp->id);
        }
        temp=temp->next;
    }
    printf("\n");
}

int main(){
    int k,n,m;
    scanf("%d %d %d",&k,&n,&m);//k:访问次数的上限 n:每个队列的最大长度 m:一共有多少个id
    queue q_history;
    queue q_cache;
    initial(&q_history);
    initial(&q_cache);//初始化两个队列
    int i=0;
    for(i=0;i<m;i++){
        int id;
        scanf("%d",&id);
        if(in_cache[id]==1){//这个id已经放入缓存区了，需要更新缓存区，把这个id对应节点重新插入到队尾
            //移除节点
            Removenode(&q_cache,cache[id]);
            //插入到队尾
            cache[id]=Puttail(&q_cache,id);
        }else if(in_history[id]==1){//这个id已经在历史访问区，还要进一步判断
            num_history[id]++;
            if(num_history[id]>=k){//如果访问次数达到要求，需要把这个节点放入cache队列
                //删除节点
                Removenode(&q_history,history[id]);
                num_history[id]=0;
                q_history.size--;
                in_history[id]=0;
                if(q_cache.size>=n){
                    //删除第一个节点
                    int delete_id=Popfirst(&q_cache);
                    in_cache[delete_id]=0;
                    //把新节点插入到末尾
                    cache[id]=Puttail(&q_cache,id);
                    in_cache[id]=1;
                }else{
                    //新节点插入到末尾
                    cache[id]=Puttail(&q_cache,id);
                    in_cache[id]=1;
                    q_cache.size++;
                }
            }else{
                //删除节点
                Removenode(&q_history,history[id]);
                //把节点插入到队尾
                history[id]=Puttail(&q_history,id);
            }
        }else{//完全是新元素
            if(k==1){//访问一次就直接进入缓存队列，不用再放入历史队列了(这个k的边界条件注意一下，再次写还是会忘记)
                if(q_cache.size>=n){
                    //删除第一个节点
                    int delete_id=Popfirst(&q_cache);
                    in_cache[delete_id]=0;
                    //把新节点插入到末尾
                    cache[id]=Puttail(&q_cache,id);
                    in_cache[id]=1;
                }else{
                    //新节点插入到末尾
                    cache[id]=Puttail(&q_cache,id);
                    in_cache[id]=1;
                    q_cache.size++;
                }
            }else{
                num_history[id]++;
                if(q_history.size>=n){
                    //删除第一个
                    int delete_id=Popfirst(&q_history);
                    in_history[delete_id]=0;
                    num_history[delete_id]=0;
                    //插入到末尾
                    history[id]=Puttail(&q_history,id);
                    in_history[id]=1;
                }else{
                    //插入到末尾
                    history[id]=Puttail(&q_history,id);
                    in_history[id]=1;
                    q_history.size++;
                }
            }
        }
    }

    print(&q_history);
    print(&q_cache);
    return 0;
}