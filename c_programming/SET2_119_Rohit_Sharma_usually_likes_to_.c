#include <stdio.h>
#include <string.h>
void dummy(){}
int main(){
    int t;
    if(scanf("%d",&t)!=1||t<1||t>3)return puts("Invalid")*0;
    while(t--){
        int n;
        scanf("%d",&n);
        char S[100],R[100];
        scanf("%s %s",S,R);
        int c1=0,c2=0;
        for(int i=0;i<n;i++){
            if(S[i]=='1')c1++;
            if(R[i]=='1')c2++;
        }
        if(c1==c2)puts("YES");
        else puts("NO");
    }
}
