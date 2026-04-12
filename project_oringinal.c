#include<stdio.h>
typedef struct Node{
    int data;
    int parent;
    int left;
    int right;
}Node;

void Build_tree(Node tree[],int index,int n){
    int i=0;
    int flag=0;
    for(i=0;i<n;i++){
        if(tree[i].parent==index){
            flag=1;
            if(tree[i].data<tree[index].data){
                tree[index].left=i;
            }else{
                tree[index].right=i;
            }
            Build_tree(tree,i,n);
        }
    }
    if(flag==0) return ;
}

void print_preorder(Node tree[],int root){
    if(root==-1){
        return ;
    }else{
        printf("%d ",tree[root].data);
        print_preorder(tree,tree[root].left);
        print_preorder(tree,tree[root].right);
    }
}

int find(Node tree1[],int root,int target){
    if(tree1[root].data==target){
        return 1;
    }else{
        find(tree1,tree1[root].left,target);
        find(tree1,tree1[root].right,target);
    }
    return 0;
}

int main(){
    int n1,n2;
    Node tree1[200000];
    Node tree2[200000];
    int root_index1,root_index2;

    //输入所有数据并在输入中找到根节点的index
    int i=0;
    scanf("%d",&n1);
    for(i=0;i<n1;i++){
        scanf("%d %d",&tree1[i].data,&tree1[i].parent);
        if(tree1[i].parent==-1){
            root_index1=i;
        }
        tree1[i].left=-1;
        tree1[i].right=-1;
    }
    scanf("%d",&n2);
    for(i=0;i<n2;i++){
        scanf("%d %d",&tree2[i].data,&tree2[i].parent);
        if(tree2[i].parent==-1){
            root_index2=i;
        }
        tree2[i].left=-1;
        tree2[i].right=-1;
    }
    int n;
    scanf("%d",&n);

    //建好两棵树
    Build_tree(tree1,root_index1,n1);
    Build_tree(tree2,root_index2,n2);

    //先序遍历两棵树
    print_preorder(tree1,root_index1);
    printf("\n");
    print_preorder(tree2,root_index2);

    return 0;
}