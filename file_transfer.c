#include<stdio.h>
#define MAX 10005

int arr[MAX];
int size[MAX];

void Initialize(int n){
    int i=0;
    for(i=1;i<=n;i++){
        arr[i]=i;
        size[i]=1;
    }
}

int Find(int n){
    if(arr[n]==n)return n;
    return arr[n]=Find(arr[n]);
}

void Union(int n1,int n2){
    int root1=Find(n1);
    int root2=Find(n2);
    if(root1!=root2){
        if(size[root1]<=size[root2]){
            arr[root1]=root2;
            size[root2]+=size[root1];
            size[root1]=1;
        }else{
            arr[root2]=root1;
            size[root1]+=size[root2];
            size[root2]=1;
        }
    }
}

int main(){
    int n;
    scanf("%d",&n);
    getchar();
    Initialize(n);//把数组初始化，每个元素都指向自己
    char c;
    int n1,n2;
    while((c=getchar())!='S'){
        if(c=='I'){
            scanf("%d %d",&n1,&n2);
            Union(n1,n2);
        }else if(c=='C'){
            scanf("%d %d",&n1,&n2);
            if(Find(n1)==Find(n2)){
                printf("yes\n");
            }else{
                printf("no\n");
            }
        }
        getchar();
    }
    int count=0;
    int i=0;
    for(i=1;i<=n;i++){
        if(arr[i]==i)count++;
    }
    if(count==1){
        printf("The network is connected.\n");
    }else{
        printf("There are %d components.\n",count);
    }
    return 0;
}