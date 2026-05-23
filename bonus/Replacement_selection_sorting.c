#include<stdio.h>
#include<stdlib.h>

void swap(int* a,int* b){
    int temp=*a;
    *a=*b;
    *b=temp;
}

void siftdown(int index,int heap[],int n){
    int lindex=index*2;
    int rindex=index*2+1;
    if(lindex>n)return;//注意每次需要先判断是否会越界
    int mindex=lindex;
    if(rindex<=n&&heap[rindex]<heap[mindex]){
        mindex=rindex;
    }
    if(heap[index]>heap[mindex]){
        swap(&heap[index],&heap[mindex]);
        siftdown(mindex,heap,n);
    }
}

void Buildheap(int n,int heap[]){
    int i=1;
    for(i=n/2;i>=1;i--){
        siftdown(i,heap,n);
    }
}

int main(){
    int n,m;
    scanf("%d %d",&n,&m);//n-总数量 m-内存总空间
    int* input=malloc((n+1)*sizeof(int));
    int* heap=malloc((m+1)*sizeof(int));
    int i=0;
    for(i=1;i<=n;i++){
        scanf("%d",&input[i]);
    }
    int heap_index=1;
    for(i=1;i<=m&&i<=n;i++){
        heap[i]=input[heap_index++];
    }
    
    //初始化建堆
    int heap_size=(n>m)?m:n;
    Buildheap(heap_size,heap);
    int total=heap_size;//total=活跃的加保存在下一轮的
    int current=heap[1];
    int first=1;

    //开始一边输出一边判断读入
    while(total>0){//内存数据还没完全输入完或者活跃排序部分的外存还有多

        if(heap_size==0){
            printf("\n");
            heap_size=total;//全程可以保证total小于等于m
            first=1;
            Buildheap(heap_size,heap);
        }//开始下一轮
        current=heap[1];
        //开始输出fisrt one
        if(first==1){
            printf("%d",current);
            first=0;
        }else{
            printf(" %d",current);
        }

        //读入下一个 分成两种情况 一个是input里还有数据可以读入 还有一个是input里没有数据可以读入但是heap的活跃数组还有数据可以输出
        int last_out=current;
        if(heap_index<=n){
            int next_in=input[heap_index++];
            if(next_in>=last_out){
                heap[1]=next_in;
                siftdown(1,heap,heap_size);
            }else{
                heap[1]=heap[heap_size];
                heap[heap_size]=next_in;
                heap_size--;
                siftdown(1,heap,heap_size);
            }
        }else{
            heap[1]=heap[heap_size];
            for(i=heap_size+1;i<=total;i++){
                heap[i-1]=heap[i];
            }
            heap_size--;
            total--;
            siftdown(1,heap,heap_size);
        }
    }
    printf("\n");
    free(input);
    free(heap);
    return 0;
}