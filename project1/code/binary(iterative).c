#include<stdio.h>
#include<time.h>

#define N 10010 // Maximum capacity of the array

int binary_search_iterative(int a[N],int left,int right,int n){
    while(left<=right){
        int mid=(left+right)/2; // Calculate the middle index
        if(n==a[mid]){
            return mid; //Target found
        }else if(n>a[mid]){
            left=mid+1; // Search in the right half
        }else{
            right=mid-1; // Search in the left half
        }
    }
    if(left>right){
        return -1; // Target not found (Worst case)
    }
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
        binary_search_iterative(a,0,n-1,n); // Searching for 'n' ensures worst case
    }
    stop=clock(); // Stop recording ticks
    duration=((double)(stop-start))/CLOCKS_PER_SEC/k; // Calculate duration for a single run
    printf("time is %f s\n",duration);

    return 0;
}