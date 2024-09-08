#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
int calls = 0;
bool L(char s[],int l, int h){
    if((h-l)%2==0) return false;
    if(h-l==1) return s[h]==s[l] ;
    calls ++;
    int mid =l+(h-l)/2; int p = mid+1;
    for(int i=l;i<=mid;i++){
        if(s[i]!=s[p]) return false ;
        p++;
    }
    return true;
}


bool isinLstar(char prakhar[],int start,int end) 
{
    int l = end-start+1;
    if(l%2!=0 ) 
    {
        return false;
    }
    if(l == 2){ 
        return prakhar[start] == prakhar[end];
    }
    if(l == 0)
    {
        return true;
    }
    if(L(prakhar , start , end)) return true; 
    for(int i = end-2;i>=start+1;i-=2)
    {
        if(L(prakhar,start,i))
        {
            if(isinLstar(prakhar,i+1,end)) return true;
        }
    }
    return false;
}

int main(){
    char hello[100];
    printf("Enter a string: ");
    fgets(hello, sizeof(hello), stdin);
    int length = strlen(hello)-2;
    bool result =isinLstar(hello,0,length);
    if(result){
        printf("TRUE");
    }
    else printf("False");
    printf("\nNumer of calls required - %d",calls);
    return 0;
}