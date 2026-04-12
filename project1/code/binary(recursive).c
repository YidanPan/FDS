#include<stdio.h>
#include<time.h>

# define N 10010 // Maximum capacity of the array

int binary_search_recursive(int a[N],int left,int right,int x){
    int mid=(left+right)/2; // Calculate the middle index
    if(left>right){
        return -1; // Target not found (Worst case)
    }
    if(x==a[mid]){
        return mid; //Target found
    }else if(x<a[mid]){
        return binary_search_recursive(a,left,mid-1,x); //invoke binary_search_recursive to find the left half
    }else{
        return binary_search_recursive(a,mid+1,right,x); //invoke binary_search_recursive to find the right half
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
        binary_search_recursive(a,0,n-1,n); // Searching for 'n' ensures worst case
    }
    stop=clock(); // Stop recording ticks
    duration=((double)(stop-start))/CLOCKS_PER_SEC/k; // Calculate duration for a single run
    printf("time is %f s\n",duration);

    return 0;
}