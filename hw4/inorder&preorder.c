#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Node{
    int val;
    struct Node* left;
    struct Node* right;
}Node_tree;

int pre[40];
int in[40];
int post[40];
//通过先序和中序结果构建一颗二叉树
Node_tree* Buildtree(int prel,int prer,int inl,int inr){
    if(prel>prer) return NULL;
    Node_tree* root=(Node_tree*)malloc(sizeof(Node_tree));
    root->left=NULL;
    root->right=NULL;
    int root_value=pre[prel];
    root->val=root_value;
    
    int k=0;
    for(k=inl;k<=inr;k++){
        if(in[k]==root_value){
            break;
        }
    }
    int number_left=k-inl;//计算出左子树的节点个数
    root->left=Buildtree(prel+1,prel+number_left,inl,inl+number_left-1);
    root->right=Buildtree(prel+number_left+1,prer,inl+number_left+1,inr);
    return root;
}
//构造一个打印后序的函数，传入参数是根节点
int first=1;
void print_postorder(Node_tree* root){
    if(root==NULL){
        return;
    }
    print_postorder(root->left);
    print_postorder(root->right);
    if(first==1){
        printf("%d",root->val);
        first=0;
    }else{
        printf(" %d",root->val);
    }
}

int main(){
    int n;
    scanf("%d",&n);
    char op[10];
    int i=0,num;
    int precount=0,incount=0;
    int stack[40],count=0;
    for(i=0;i<2*n;i++){
        scanf("%s",op);
        if(strcmp(op,"Push")==0){
            scanf("%d",&num);
            stack[count++]=num;
            pre[precount++]=num;
        }else{
            in[incount++]=stack[--count];
        }//把inorder和preorder构建好
    }
    Node_tree* root=Buildtree(0,n-1,0,n-1);
    print_postorder(root);
    return 0;
}