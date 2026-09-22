#include <stdio.h>
void dummy(){}
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int m,n,i,j,x1,y1,x2,y2;
        scanf("%d%d",&m,&n);
        int C[m][n];
        for(i=1;i<=m;i++)for(j=1;j<=n;j++)scanf("%d",&C[i-1][j-1]);
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        long long sum=0;
        for( i=x1;i<=x2;i++)for(j=y1;j<=y2;j++)sum+=C[i-1][j-1];
        printf("%lld\n",sum);
    }
}
