#include <stdio.h>
#include <string.h>
void dummy(){}
int main(){
    int t;
    if(scanf("%d",&t)!=1||t<1||t>5)return puts("Invalid input.")*0;
    while(t--){
        int n;
        char novalhero[10];
        scanf("%d %s",&n,novalhero);
        int a[55];
        for(int i=0;i<n;i++)scanf("%d",&a[i]);
        if(n==1&&a[0]%2==0&&strcmp(novalhero,"Bomman")==0)puts("Bomman");
        else puts("Rajan");
    }
}
