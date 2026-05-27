#include <stdio.h>

#define ElementType int
#define MAXN 100

void merge_pass( ElementType list[], ElementType sorted[], int N, int length );

void output( ElementType list[], int N )
{
    int i;
    for (i=0; i<N; i++) printf("%d ", list[i]);
    printf("\n");
}

void  merge_sort( ElementType list[],  int N )
{
    ElementType extra[MAXN];  /* the extra space required */
    int  length = 1;  /* current length of sublist being merged */
    while( length < N ) { 
        merge_pass( list, extra, N, length ); /* merge list into extra */
        output( extra, N );
        length *= 2;
        merge_pass( extra, list, N, length ); /* merge extra back to list */
        output( list, N );
        length *= 2;
    }
} 


int main()
{
    int N, i;
    ElementType A[MAXN];

    scanf("%d", &N);
    for (i=0; i<N; i++) scanf("%d", &A[i]);//初始化排序的list
    merge_sort(A, N);
    output(A, N);

    return 0;
}

/* Your function will be put here */
void merge(ElementType list[], ElementType sorted[],int lstart,int rstart,int rend){
    int lend=rstart-1;
    int temp=lstart;
    while(lstart<=lend&&rstart<=rend){
        if(list[lstart]<=list[rstart]){
            sorted[temp++]=list[lstart++];
        }else{
            sorted[temp++]=list[rstart++];
        }
    }
    while(lstart<=lend){
        sorted[temp++]=list[lstart++];
    }
    while(rstart<=rend){
        sorted[temp++]=list[rstart++];
    }
}

void merge_pass( ElementType list[], ElementType sorted[], int N, int length ){//相当于是当前把长度为length的每个子序列归并起来
    int i=0;
    while(i<=N-2*length){//凑够相邻两组
        //把相邻两组数组合并
        merge(list,sorted,i,i+length,i+2*length-1);
        i+=2*length;
    }
    if(i+length<N){//凑不够两组，但是有一组可以是满的，合并然后递归
        merge(list,sorted,i,i+length,N-1);
    }else{//一组都凑不满，就全部归并到sorted数组中
        while(i<N){
            sorted[i]=list[i];
            i++;
        }
    }
}
