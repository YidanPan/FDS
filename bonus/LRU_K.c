#include<stdio.h>
#include<stdlib.h>
#define MAX 20005
typedef struct Node{
    int id;
    struct Node* pre;
    struct Node* next; 
}Node;

int num_history[MAX]={0};//历史队列的访问次数
int in_history[MAX]={0};//记录是否数字是在队列中
int in_cache[MAX]={0};

Node* history[MAX]={NULL};//历史队列
Node* cache[MAX]={NULL};//缓存队列

typedef struct queue{
    Node* head;
    Node* tail;
    int size;
}queue;

void initial(queue* q){
    q->head=NULL;
    q->tail=NULL;
    q->size=0;
}

Node* Pushtail(queue* q,int id){
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
    return newnode;
}

void removeNode(queue* q,Node* node){
    if(node==NULL)return;
    if(node->pre==NULL){
        q->head=node->next;
        if(q->head==NULL){
            q->tail=NULL;
        }else{
            q->head->pre=NULL;
        }
    }else if(node->next==NULL){
        q->tail=node->pre;
        q->tail->next=NULL;
    }else{
        node->pre->next=node->next;
        node->next->pre=node->pre;
    }
    free(node);
    q->size--;
}

int pophead(queue* q){
    if(q->head==NULL)return-1;
    Node* old_head = q->head; // 把旧头存起来
    int temp = old_head->id;
    q->head = old_head->next; // 头往后移
    if(q->head != NULL){
        q->head->pre = NULL;  // 新头的 pre 置空
    } else {
        q->tail = NULL;       // 链表空了
    }
    free(old_head); // 安全释放旧头
    q->size--;
    return temp;
}

void print(queue* q){
    if(q->size==0){
        printf("-\n");
        return;
    }
    Node* temp=NULL;
    temp=q->head;
    int first=1;
    while(temp!=NULL){
        if(first==1){
            first=0;
            printf("%d",temp->id);
            temp=temp->next;
        }else{
            printf(" %d",temp->id);
            temp=temp->next;
        }
    }
    printf("\n");
}

int main(){
    int k,m,n;
    scanf("%d %d %d",&k,&n,&m);//k-up n-queuesize m-numbers
    queue q_history;
    initial(&q_history);
    queue q_cache;
    initial(&q_cache);

    int i=0;
    for(i=0;i<m;i++){
        int id;
        scanf("%d",&id);
        //如果在cache队列里
        if(in_cache[id]){
            //remove
            removeNode(&q_cache,cache[id]);
            //push in the tail
            cache[id]=Pushtail(&q_cache,id);
        }else if(in_history[id]){//如果是在历史数组里面
            num_history[id]++;
            if(num_history[id]==k){
                //move to cache
                removeNode(&q_history,history[id]);
                num_history[id]=0;
                in_history[id]=0;
                history[id]=NULL;
                if(q_cache.size>=n){
                    int delete_id=pophead(&q_cache);
                    in_cache[delete_id]=0;
                    cache[delete_id]=NULL;
                    cache[id]=Pushtail(&q_cache,id);
                    in_cache[id]=1;
                }else{
                    cache[id]=Pushtail(&q_cache,id);
                    in_cache[id]=1;
                }
            }else{//访问次数没有达到k 把id移到最后
                removeNode(&q_history,history[id]);
                history[id]=Pushtail(&q_history,id);
            }
        }else{
            if(k==1){//k=1 数据第一次进来就直接进cache
                if(q_cache.size>=n){
                    int delete_id=pophead(&q_cache);
                    in_cache[delete_id]=0;
                    cache[delete_id]=NULL;
                }
                cache[id]=Pushtail(&q_cache,id);
                in_cache[id]=1;
            }else{//k>1
                num_history[id]++;
                if(q_history.size>=n){
                    //remove the first
                    int delete_id=pophead(&q_history);
                    in_history[delete_id]=0;
                    num_history[delete_id]=0;
                    //插入到最后一个
                    history[id]=Pushtail(&q_history,id);
                    in_history[id]=1;
                }else{
                    //直接插入到最后一个
                    history[id]=Pushtail(&q_history,id);
                    in_history[id]=1;
                }
            }
        }
    }
    
    //end print the result
    print(&q_history);
    print(&q_cache);

    return 0;
}