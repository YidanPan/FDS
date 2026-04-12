#include<stdio.h>
int element[1005];

void sort(int arr[],int left,int right){
    if(left>=right)return;
    int temp=arr[left];
    int i=left,j=right;
    while(i<j){
        while(i<j&&arr[j]>temp){
            j--;
        }
        if(i<j){
            arr[i]=arr[j];
            i++;
        }
        while(i<j&&arr[i]<temp){
            i++;
        }
        if(i<j){
            arr[j]=arr[i];
            j--;
        }
    }
    arr[i]=temp;
    sort(arr,left,i-1);
    sort(arr,i+1,right);
}

int current=1;
int cbt[1005];
void inorder_fill(int arr[],int root,int n){
   if(root>n)return;
   inorder_fill(arr,root*2,n);
   cbt[root]=element[current++];
   inorder_fill(arr,root*2+1,n);
}

int main(){
    int n;
    scanf("%d",&n);
    int i=0;
    for(i=1;i<=n;i++){
        scanf("%d",&element[i]);
    }
    sort(element,1,n);
    inorder_fill(element,1,n);
    int first=1;
    for(i=1;i<=n;i++){
        if(first==1){
            printf("%d",cbt[i]);
            first=0;
        }else{
            printf(" %d",cbt[i]);
        }
    }
    return 0;
}