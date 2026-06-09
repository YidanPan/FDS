#include<stdio.h>
#define MAX 1005

int Partition(int sequence[],int left,int right){
    int temp=sequence[left];
    while(left<right){
        while(left<right&&sequence[right]>temp)right--;
        sequence[left]=sequence[right];
        while(left<right&&sequence[left]<temp)left++;
        sequence[right]=sequence[left];
    }
    sequence[left]=temp;
    return left;
}

void quicksort(int sequence[],int left,int right){
    if(left<right){
        int i=Partition(sequence,left,right);
        quicksort(sequence,left,i-1);
        quicksort(sequence,i+1,right);//这里注意如果左侧传入的是i，就会发生栈溢出 因为在上一次排完序之后已经保证了i右侧的值都是比他大的，所以传入i会导致一直都是传出i，陷入死循环
    }
}

int result[MAX]={-1};
int pos=1;

void inorder(int sequence[],int n,int root){
    if(root>n)return;
    inorder(sequence,n,root*2);
    result[root]=sequence[pos++];
    inorder(sequence,n,root*2+1);
}

int main(){
    int n;
    scanf("%d",&n);
    int sequence[MAX];
    int i=1;
    for(i=1;i<=n;i++){
        scanf("%d",&sequence[i]);
    }
    //从小到大排序
    quicksort(sequence,1,n);
    //按照中序遍历的方式填入数据
    inorder(sequence,n,1);
    int first=1;
    for(i=1;i<=n;i++){
        if(first==1){
            printf("%d",result[i]);
            first=0;
        }else{
            printf(" %d",result[i]);
        }
    }
    return 0;
}