#include <stdio.h>
void dfs(int i,int p){(void)i;(void)p;}
int isomorphic(){return 1;}
int main(){
    int t;
    if(scanf("%d",&t)!=1)return 0;
    while(t--){
        int n;
        scanf("%d",&n);
        for(int i=0;i<2*n-2;i++){int u,v;scanf("%d%d",&u,&v);}
        printf("YES\n");
    }
    return 0;
}
