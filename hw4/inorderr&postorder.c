#include<stdio.h>
#include<stdlib.h>

int inorder[40];
int postorder[40];

typedef struct Node{
    int val;
    struct Node* left;
    struct Node* right;
}Node_tree;

//build a tree，其实就是为了找到root并且返回根节点
Node_tree* Buildtree(int inl,int inr,int postl,int postr){
    if(inl>inr) return NULL;

    int rootval=postorder[postr];
    Node_tree* root=(Node_tree*)malloc(sizeof(Node_tree));
    root->val=rootval;
    root->left=NULL;
    root->right=NULL;
    int k=0;
    for(k=inl;k<=inr;k++){
        if(inorder[k]==rootval){
            break;
        }
    }
    int number=k-inl;//k是根节点的index,所以不需要加一
    root->left=Buildtree(inl,k-1,postl,postl+number-1);
    root->right=Buildtree(k+1,inr,postl+number,postr-1);

    return root;
}

//Z字形遍历
void ztrival(Node_tree* root){
    int result[40];
    int result_count=0;
    int i=0;
    Node_tree* queue[40];//创建一个队列
    int rear=0,front=0;
    queue[rear++]=root;//把根节点先存入队列
    int level=0;
    int current_level[40];//处理当前层的数值，把每一层的值先存入这里
    while(front<rear){
        int size=rear-front;
        int current_count=0;//这一层有多少数量的值
        for(i=0;i<size;i++){
            Node_tree* node=queue[front++];
            current_level[current_count++]=node->val;
            if(node->left)queue[rear++]=node->left;
            if(node->right)queue[rear++]=node->right;
        }
        if(level%2==0){
            int cleft=0,cright=current_count-1;
            while(cleft<cright){
                int temp;
                temp=current_level[cleft];
                current_level[cleft]=current_level[cright];
                current_level[cright]=temp;
                cleft++;
                cright--;
            }
        }
        for(i=0;i<current_count;i++){
            result[result_count++]=current_level[i];
        }
        level++;
    }
    for(i=0;i<result_count-1;i++){
        printf("%d ",result[i]);
    }
    printf("%d\n",result[i]);
}
int main(){

    int n;
    scanf("%d",&n);
    int i=0;
    
    for(i=0;i<n;i++){
        scanf("%d",&inorder[i]);
    }
    for(i=0;i<n;i++){
        scanf("%d",&postorder[i]);
    }

    Node_tree* root=Buildtree(0,n-1,0,n-1);
    ztrival(root);

    return 0;
}