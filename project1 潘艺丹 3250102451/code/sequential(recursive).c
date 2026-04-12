#include<stdio.h>
#include<time.h>

#define N 10010 // Maximum capacity of the array

int sequential_search_recursive(int a[N],int n,int index,int x){
    if(index>=n){
        return -1; //Target not found(index exceeds the length of the array)
    }
    if(x==a[index]){
        return index; //Target found(return the index value)
    }
    return sequential_search_recursive(a,n,index+1,x); // Move to the next index in the subsequent recursive call 
}

int main(){
    int n,k,i=0; //n:target k:the number of cycles for the test time i:loop count variable
    scanf("%d%d",&n,&k);

    int a[N];
    for(i=0;i<n;i++){ // Initialize array with sequential values
        a[i]=i;
    }

    clock_t start,stop;
    double duration;
    start=clock(); // Start recording ticks
    for(i=0;i<k;i++){ //Repeating the search K times to amplify duration for precision.
        sequential_search_recursive(a,n,0,n); // Searching for 'n' ensures worst case
    }
    stop=clock(); // Stop recording ticks
    duration=((double)(stop-start))/CLOCKS_PER_SEC/k; // Calculate duration for a single run
    printf("time is %f s\n",duration); 

    return 0;
}