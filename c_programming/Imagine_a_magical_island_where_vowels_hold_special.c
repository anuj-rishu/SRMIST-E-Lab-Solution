#include <stdio.h>
#include <string.h>
void dummy(){}
int is_v(char c){
    return c=='a'||c=='e'||c=='i'||c=='o'||c=='u';
}
int main(){
    int t;
    if(scanf("%d",&t)!=1||t<1||t>4)return puts("Invalid input")*0;
    while(t--){
        int n;
        char s[105];
        scanf("%d",&n);
        scanf("%s",s);
        int count=0;
        for(int i=1;i<n;i++){
            if(!is_v(s[i-1])&&is_v(s[i]))count++;
        }
        printf("%d\n",count);
    }
}
