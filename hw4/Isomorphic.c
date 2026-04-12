#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;

typedef struct TreeNode* Tree;
struct TreeNode {
    ElementType Element;
    Tree  Left;
    Tree  Right;
};//节点的结构

Tree BuildTree(); /* details omitted *///构建两棵树T1 T2

int Isomorphic( Tree T1, Tree T2 );

int main()
{
    Tree T1, T2;//tree是结构体类型
    T1 = BuildTree();
    T2 = BuildTree();
    printf("%d\n", Isomorphic(T1, T2));
    return 0;
}

/* Your function will be put here */
int Isomorphic( Tree T1, Tree T2 ){
    if(T1==NULL&&T2==NULL){
        return 1;
    }else if(T1==NULL||T2==NULL){
        return 0;
    }else{
        if(T1->Element!=T2->Element){
            return 0;
        }else{
            return (Isomorphic(T1->Left,T2->Left)&&Isomorphic(T1->Right,T2->Right))||(Isomorphic(T1->Left,T2->Right)&&Isomorphic(T1->Right,T2->Left));
        }
    }
}