#include<stdio.h>
#include<stdlib.h>

int if_insertion(int initial[],int partial[],int start,int n){
    int k=start;
    for(k=start;k<=n;k++){
        if(initial[k]!=partial[k]){
            return 0;
        }
    }
    return 1;
}

void insertion(int initial[],int point,int n){
    int temp=initial[point];
    int k=point;
    while(temp<=initial[k-1]){
        initial[k]=initial[k-1];
        k--;
    }
    initial[k]=temp;
}

void swap(int* a,int* b){
    int temp=*a;
    *a=*b;
    *b=temp;
}

void sfit_down(int partial[],int total,int root){//原来是大根堆
    int lchild=root*2;
    int rchild=root*2+1;
    if(lchild>total)return;
    int max=lchild;
    if(rchild<=total&&partial[rchild]>partial[max]){
        max=rchild;
    }
    if(partial[max]>partial[root]){
        swap(&partial[root],&partial[max]);
        sfit_down(partial,total,max);
    }
}

void print(int partial[],int n){
    int k=1;
    int first=1;
    for(k=1;k<=n;k++){
        if(first==1){
            printf("%d",partial[k]);
            first=0;
        }else{
            printf(" %d",partial[k]);
        }
    }
    printf("\n");
}

void heap_sort(int partial[],int total){
    swap(&partial[1],&partial[total]);
    total--;
    sfit_down(partial,total,1);
}

int main(){
    int n;
    scanf("%d",&n);
    int* initial=malloc((n+1)*sizeof(int));//从1开始，记得多分配一个内存
    int* partial=malloc((n+1)*sizeof(int));
    int i=1;
    for(i=1;i<=n;i++){
        scanf("%d",&initial[i]);
    }
    for(i=1;i<=n;i++){
        scanf("%d",&partial[i]);
    }
    
    //判断是否是插入排序：先找到前面第一个逆序的节点，判断后续的节点是否跟原数组一致
    i=1;
    while(partial[i]<=partial[i+1]){//注意是在partial数组里去找，不要去initial数组里找
        i++;
    }//i比后面那个大
    
    //如果是插入排序，把i+1这个点做一次插入排序
    if(if_insertion(initial,partial,i+1,n)==1){
        printf("Insertion Sort\n");
        insertion(partial,i+1,n);
    }else{ 
        //如果是堆排序，把堆顶节点值跟末尾去比较，找到那个小于后一个但是大于前一个的节点位置，然后交换堆顶和那个位置，再做一次向下调整，然后输出
        printf("Heap Sort\n");
        int top=partial[1];
        i=n;
        while(!(top<=partial[i]&&top>=partial[i-1])){
            i--;
        }
        heap_sort(partial,i-1);
    }

    print(partial,n);
    return 0;
}