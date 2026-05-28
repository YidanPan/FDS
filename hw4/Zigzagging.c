#include<stdio.h>
#include<stdlib.h>

#define MAX 50
int inorder[MAX]={-1};
int postorder[MAX]={-1};

typedef struct Node{
    int key;
    struct Node* left;
    struct Node* right;
}Node;//树的每一个节点

Node* BuildBST(int inl,int inr,int postl,int postr){//返回的是根节点
    //找到递归出口
    if(inl>inr||postl>postr)return NULL;
    //初始化一个根节点
    Node* root=NULL;
    root=malloc(sizeof(Node));
    root->key=postorder[postr];
    root->left=NULL;
    root->right=NULL;
    //在中序序列中划分左右子树，输出每个子树的节点数量
    int i;
    int temp=root->key;
    for(i=inl;i<=inr;i++){
        if(inorder[i]==temp){
            break;
        }
    }
    int num_left=i-inl;
    //构建左右子树
    root->left=BuildBST(inl,i-1,postl,postl+num_left-1);
    root->right=BuildBST(i+1,inr,postl+num_left,postr-1);

    return root;
}

void zigzag(Node* tree){//层序遍历（队列），遇到奇数层反转，偶数层正常输出
    if(tree==NULL)return;
    int level[MAX][MAX]={0};
    int layer_size[MAX]={0};
    int layer=1;
    //初始化一个队列
    Node* queue[MAX]={NULL};
    int front=1;
    int rear=1;
    queue[rear++]=tree;

    //层序输出保存在二维数组中
    while(front<rear){
       int current_layer_size=rear-front;
       layer_size[layer]=current_layer_size;
       int i;
       for(i=1;i<=current_layer_size;i++){
            Node* current=queue[front++];
            level[layer][i]=current->key;
            if(current->left!=NULL){
                queue[rear++]=current->left;
            }
            if(current->right!=NULL){
                queue[rear++]=current->right;
            }
       }
       layer++;
    }
    //按要求输出
    int i=1;
    int first=1;
    for(i=1;i<=layer-1;i++){
        if(i%2==1){//奇数层反转
            int k=layer_size[i];
            for(;k>=1;k--){
                if(first==1){
                    printf("%d",level[i][k]);
                    first=0;
                }else{
                    printf(" %d",level[i][k]);
                }
            }        
        }else{
            int k;
            for(k=1;k<=layer_size[i];k++){
                if(first==1){
                    printf("%d",level[i][k]);
                    first=0;
                }else{
                    printf(" %d",level[i][k]);
                }
            }
        }
    }
    printf("\n");
}

int main(){
    int n;
    scanf("%d",&n);//总的节点数
    //输入中序和后序序列
    int i=1;
    for(i=1;i<=n;i++){
        scanf("%d",&inorder[i]);
    }
    for(i=1;i<=n;i++){
        scanf("%d",&postorder[i]);
    }
    //根据中序和后序序列构建二叉搜索树
    Node* Tree=BuildBST(1,n,1,n);
    //z字形遍历二叉树
    zigzag(Tree);
    return 0;
}