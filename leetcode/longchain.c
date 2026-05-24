int longestValidParentheses(char* s) {
    int len=strlen(s);
    if(len==0){
        return 0;
    }
    int stack[len+1];//save the index of every char 
    int top=0;
    stack[top++]=-1;
    int i;
    int maxlen=0;
    int current_len=0;
    for(i=0;i<len;i++){
        char c=s[i];
        if(c=='('){
            stack[top++]=i;
        }else{
            top--;
            if(top==0){//stack empty
                stack[top++]=i;
            }else{//if match well
                current_len=i-stack[top-1];//这里top的变化要注意！
                if(current_len>maxlen){
                    maxlen=current_len;
                }
            }
        }
    }
    return maxlen;
}