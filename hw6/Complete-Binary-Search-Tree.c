#include<stdio.h>
#include<stdlib.h>

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
    arr[i]=temp;//此时i=j同时左边都比他小，右边都比他大
    sort(arr,left,i-1);
    sort(arr,i+1,right);
}
int current=1;
int cbt[1005];
int element[1005];
void BuildTree(int arr[],int root,int n){
    if(root>n)return;
    BuildTree(arr,root*2,n);
    cbt[root]=element[current++];
    BuildTree(arr,root*2+1,n);
}
int main(){
    int n;
    scanf("%d",&n);
    element[0]=-1;
    int i=0;
    for(i=1;i<=n;i++){
        scanf("%d",&element[i]);
    }
    sort(element,1,n);
    BuildTree(element,1,n);
    int first=1;
    for(i=1;i<=n;i++){
        if(first==1){
            printf("%d",cbt[i]);
            first=0;
        }else{
            printf(" %d",cbt[i]);
        }
    }
    printf("\n");
    return 0;
}