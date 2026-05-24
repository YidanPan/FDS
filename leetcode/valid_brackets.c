#include<stdio.h>
#define MAX 10005
int main(){
    char c;
    char stack[MAX];
    int cont=0;
    do{
        scanf("%c",&c);
        if(c=='('||c=='{'||c=='['){
            stack[cont++]=c;
        }else{
            if(c==')'){
                if(stack[cont-1]!='('){
                    printf("false\n");
                    return 0;
                }else{
                    cont--;
                }
            }else if(c==']'){
                if(stack[cont-1]!='['){
                    printf("false\n");
                    return 0;
                }else{
                    cont--;
                }
            }else if(c=='}'){
                if(stack[cont-1]!='{'){
                    printf("false\n");
                    return 0;
                }else{
                    cont--;
                }
            }
        }
    }while(c!='\n');
        
    if(cont!=0){
        printf("false\n");
    }else{
        printf("true\n");
    }
    return 0;
}