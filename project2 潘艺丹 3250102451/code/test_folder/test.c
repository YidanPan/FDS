#include<stdio.h>

#define MAXNODES 200005
typedef struct Node{//Define each element in the array as a structure
    long long data;
    int parent;
    int left;
    int right;
}Node;

long long arr1[MAXNODES];
long long arr2[MAXNODES];//Used for storing deduplicated node translations
long long result1[MAXNODES];
long long result2[MAXNODES];//Used for storing result node
//Traverse the deduplicated nodes in in-order sequence
void inorder_save(int root,Node tree[],long long arr[],int* size){
    if(root==-1)return;
    inorder_save(tree[root].left,tree,arr,size);//Recursive call
    if(*size==0||tree[root].data!=arr[*size-1]){//When size=0 or the current data is different from the previous one,put it in the arr
        arr[(*size)++]=tree[root].data;
    }
    inorder_save(tree[root].right,tree,arr,size);//Recursive call
}

int first=0;//Used to determine whether it is the first data to be printed
void preorder_print(Node tree[],int root){//Pre-order traversal
    if(root==-1) return;//Recursion base case
    if(first==0){//root node
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
    scanf("%d",&n1);//The number of tree1's nodes
    int i=0;
    int root1,root2;//Tree1's&tree2's root node index
    int p;
    for(i=0;i<n1;i++){//Read in data
        scanf("%lld %d",&tree1[i].data,&tree1[i].parent);
        tree1[i].left=-1;
        tree1[i].right=-1;
    }
    for(i=0;i<n1;i++){//Establish the tree
        p=tree1[i].parent;//p is the node's parent's node index
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

    scanf("%d",&n2);//The number of tree2's nodes
    for(i=0;i<n2;i++){//Read in data
        scanf("%lld %d",&tree2[i].data,&tree2[i].parent);
        tree2[i].left=-1;
        tree2[i].right=-1;
    }
    for(i=0;i<n2;i++){//Establish the tree
        p=tree2[i].parent;
        if(p==-1){//p is the node's parent's node index
            root2=i;
        }else{
            if(tree2[i].data<tree2[p].data){
                tree2[p].left=i;
            }else{
                tree2[p].right=i;
            }
        }
    }
    long long n;//Read the required sum
    scanf("%lld",&n);

    int size1=0;
    int size2=0;//The size of the deduplicated tree
    inorder_save(root1,tree1,arr1,&size1);
    inorder_save(root2,tree2,arr2,&size2);//Call the function to deduplicate the tree
    
    //Use two pointers to find pairs satisfying A+B=N
    int count=0;//Used to count the elements in the result array.
    int p1=0,p2=size2-1;//p1 represents the nodes of tree1,p2 represents the nodes of tree2,p1 start from 0,p2 start from the end
    int flag=0;         //The flag is used to indicate whether a satisfying result has been found
    while(p1<size1&&p2>=0){
        if(arr1[p1]+arr2[p2]==n){//If found
            result1[count]=arr1[p1];
            result2[count]=arr2[p2];//Store the data in the result array
            count++;
            p1++;
            p2--;//p1 and p2 move toward the center
            flag=1;//already found
        }else if(arr1[p1]+arr2[p2]<n){//If sum<n,p1 go right
            p1++;
        }else{//If sum>n,p2 go left
            p2--;
        }
    }
    if(flag==0){//If not found
        printf("false\n");
    }else{
        printf("true\n");
        for(i=0;i<count;i++){//print the reault
            printf("%lld = %lld + %lld\n",n,result1[i],result2[i]);
        }
    }

    preorder_print(tree1,root1);//Print tree1 via pre-order traversal
    printf("\n");
    first=0;//Reset first to 0 again
    preorder_print(tree2,root2);//Print tree2 via pre-order traversal
    printf("\n");

    return 0;
}