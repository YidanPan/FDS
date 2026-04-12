#include<stdio.h>

#define MAXNODES 200005
typedef struct Node{
    long long data;
    int parent;
    int left;
    int right;
}Node;

long long arr1[MAXNODES];
long long arr2[MAXNODES];//用于存放去重后的节点
long long result1[MAXNODES];
long long result2[MAXNODES];
//以中序的顺序遍历存放去重后的节点
void inorder_save(int root,Node tree[],long long arr[],int* size){
    if(root==-1)return;
    inorder_save(tree[root].left,tree,arr,size);
    if(*size==0||tree[root].data!=arr[*size-1]){
        arr[(*size)++]=tree[root].data;
    }
    inorder_save(tree[root].right,tree,arr,size);
}

int first=0;
void preorder_print(Node tree[],int root){
    if(root==-1) return;
    if(first==0){
        printf("%lld",tree[root].data);
        first=1;
        preorder_print(tree,tree[root].left);
        preorder_print(tree,tree[root].right);
    }else{
        printf(" %lld",tree[root].data);
        preorder_print(tree,tree[root].left);
        preorder_print(tree,tree[root].right);
    }
}

Node tree1[MAXNODES];
Node tree2[MAXNODES];
int main(){
    int n1,n2;
    scanf("%d",&n1);
    int i=0;
    int root1,root2;
    int p;
    for(i=0;i<n1;i++){
        scanf("%lld %d",&tree1[i].data,&tree1[i].parent);
        tree1[i].left=-1;
        tree1[i].right=-1;
    }
    for(i=0;i<n1;i++){
        p=tree1[i].parent;
        if(p==-1){
            root1=i;
        }else{
            if(tree1[i].data<tree1[p].data){
                tree1[p].left=i;
            }else{
                tree1[p].right=i;
            }
        }
    }

    scanf("%d",&n2);
    for(i=0;i<n2;i++){
        scanf("%lld %d",&tree2[i].data,&tree2[i].parent);
        tree2[i].left=-1;
        tree2[i].right=-1;
    }
    for(i=0;i<n2;i++){
        p=tree2[i].parent;
        if(p==-1){
            root2=i;
        }else{
            if(tree2[i].data<tree2[p].data){
                tree2[p].left=i;
            }else{
                tree2[p].right=i;
            }
        }
    }
    long long n;
    scanf("%lld",&n);

    int size1=0;
    int size2=0;
    inorder_save(root1,tree1,arr1,&size1);
    inorder_save(root2,tree2,arr2,&size2);
    
    //利用双指针去寻找A+B=N
    int count=0;
    int p1=0,p2=size2-1;
    int flag=0;
    while(p1<size1&&p2>=0){
        if(arr1[p1]+arr2[p2]==n){
            result1[count]=arr1[p1];
            result2[count]=arr2[p2];
            count++;
            p1++;
            p2--;
            flag=1;
        }else if(arr1[p1]+arr2[p2]<n){
            p1++;
        }else{
            p2--;
        }
    }
    if(flag==0){
        printf("false\n");
    }else{
        printf("true\n");
        for(i=0;i<count;i++){
            printf("%lld = %lld + %lld\n",n,result1[i],result2[i]);
        }
    }

    preorder_print(tree1,root1);
    printf("\n");
    first=0;
    preorder_print(tree2,root2);
    printf("\n");

    return 0;
}