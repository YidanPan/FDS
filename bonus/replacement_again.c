#include<stdio.h>
#include<stdlib.h>

void swap(int* a,int* b){
    int temp=*a;
    *a=*b;
    *b=temp;
}

void sfitdown(int heap[],int index,int n){
    int root=index;
    int left=root*2;
    if(left>n)return;
    int right=root*2+1;
    int minchild=left;
    if(right<=n){
        if(heap[right]<heap[minchild]){
            minchild=right;
        }
    }
    if(heap[minchild]<heap[root]){
        swap(&heap[root],&heap[minchild]);
        sfitdown(heap,minchild,n);
    }
}

void buildheap(int heap[],int n){
    int i;
    for(i=n/2;i>=1;i--){
        sfitdown(heap,i,n);
    }
}

int main(){//规定所有元素从1开始存储
    int n,m;
    scanf("%d %d",&n,&m);//n-总的输入数量 m-外存的最大排序数量
    int i=0;
    int* input=malloc((n+1)*sizeof(int));
    int* heap=malloc((m+1)*sizeof(int));
    for(i=1;i<=n;i++){
        scanf("%d",&input[i]);
    }
    int heap_size=(n<m)?n:m;
    int total=heap_size;
    for(i=1;i<=heap_size;i++){
        heap[i]=input[i];
    }
    int input_index=i;
    //初始化minheap
    buildheap(heap,heap_size);
    //输出顶上的元素 读入下一个元素 然后比较：如果新元素更大，放入顶部然后下调；如果更小，就放到末尾，把活跃区的最后一个元素放到顶部然后调整minheap
    int first=1;
    while(total>0){
        //活跃区已经全部输出 开始新一轮的输出(需要更新)
        if(heap_size==0){
            printf("\n");
            heap_size=total;
            first=1;
            buildheap(heap,heap_size);
        }
        //活跃区还有元素
        //开始popfirst
        if(first==1){
            printf("%d",heap[1]);
            first=0;
        }else{
            printf(" %d",heap[1]);
        }
        //如果input中还有可读入的数据
        if(input_index<=n){
            int last_out=heap[1];
            int next_in=input[input_index++];
            if(next_in>=last_out){
                heap[1]=next_in;
                sfitdown(heap,1,heap_size);
            }else{
                heap[1]=heap[heap_size];
                heap[heap_size]=next_in;
                heap_size--;
                sfitdown(heap,1,heap_size);
            }
        }else{//如果input中没有可读入的数据
            heap[1]=heap[heap_size];
            for(i=heap_size;i<total;i++){
                heap[i]=heap[i+1];
            }
            heap_size--;
            total--;
            sfitdown(heap,1,heap_size);
        }
    }
    printf("\n");
    free(input);
    free(heap);
    return 0;
}