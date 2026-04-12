#include<stdio.h>
#include<time.h>

#define N 10010 // Maximum capacity of the array

int sequential_search_iterative(int a[N],int n,int x){
    int i=0; // Loop counter and array index used to traverse the dataset
    for(i=0;i<n;i++){
        if(x==a[i]){
            return i; //Target found
        }
    }
    return -1; // Target not found (Worst case)
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
        sequential_search_iterative(a,n,n); // Searching for 'n' ensures worst case
    }
    stop=clock(); // Stop recording ticks
    duration=((double)(stop-start))/CLOCKS_PER_SEC/k; // Calculate duration for a single run
    printf("time is %f s\n",duration);

    return 0;
}