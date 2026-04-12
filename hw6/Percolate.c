#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
#define MinData -1

typedef struct HeapStruct *PriorityQueue;
struct HeapStruct {
    ElementType  *Elements;//指针elements是指向int类型的指针（数组）
    int Capacity;
    int Size;//记录目前结构中元素的数量
};

PriorityQueue Initialize( int MaxElements ); /* details omitted */ //初始化heap

void PercolateUp( int p, PriorityQueue H );
void PercolateDown( int p, PriorityQueue H );

void Insert( ElementType X, PriorityQueue H ) 
{
    int p = ++H->Size;
    H->Elements[p] = X;
    PercolateUp( p, H );//盗用percolateup 从叶节点开始往上
}

ElementType DeleteMin( PriorityQueue H ) 
{ 
    ElementType MinElement; 
    MinElement = H->Elements[1];
    H->Elements[1] = H->Elements[H->Size--];
    PercolateDown( 1, H );
    return MinElement; 
}

int main()
{
    int n, i, op, X;
    PriorityQueue H;

    scanf("%d", &n);
    H = Initialize(n);//n是heap的元素个数
    for ( i=0; i<n; i++ ) {
        scanf("%d", &op);
        switch( op ) {
        case 1:
            scanf("%d", &X);
            Insert(X, H);
            break;
        case 0:
            printf("%d ", DeleteMin(H));
            break;
        }
    }
    printf("\nInside H:");
    for ( i=1; i<=H->Size; i++ )
        printf(" %d", H->Elements[i]);
    return 0;
}

/* Your function will be put here */
void PercolateUp( int p, PriorityQueue H ){
    ElementType temp=H->Elements[p];
    for(;p>1&&temp<H->Elements[p/2];p/=2){
        H->Elements[p]=H->Elements[p/2];
    }
    H->Elements[p]=temp;
}

void PercolateDown( int p, PriorityQueue H ){
    ElementType k=H->Elements[p];
    ElementType child;
    while(p*2<=H->Size){
        child=p*2;
        if(child+1<=H->Size&&H->Elements[child+1]<H->Elements[child]){
            child++;
        }
        if(k>H->Elements[child]){
            H->Elements[p]=H->Elements[child];
        }else{
            break;
        }
        p=child;
    }
    H->Elements[p]=k;
}