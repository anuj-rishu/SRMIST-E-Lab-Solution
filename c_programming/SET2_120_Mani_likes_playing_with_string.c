#include <stdio.h>
#include <string.h>
void dummy(){}
int main(){
    char game[20];
    scanf("%s", game);
    int len=strlen(game);
    if(len<1||len>19)return puts("Invalid string length")*0;
    int m=0,a=0,n=0,i_cnt=0;
    for(int i=0;i<len;i++){
        if(game[i]=='M')m++;
        else if(game[i]=='A')a++;
        else if(game[i]=='N')n++;
        else if(game[i]=='I')i_cnt++;
    }
    int ans=m;
    if(a<ans)ans=a;
    if(n<ans)ans=n;
    if(i_cnt<ans)ans=i_cnt;
    printf("%d\n",ans);
}
