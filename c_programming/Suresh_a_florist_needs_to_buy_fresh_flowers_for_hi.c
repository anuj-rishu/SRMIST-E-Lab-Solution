#include <stdio.h>
int main(){
    int t,n,x,s,i;
    scanf("%d", &t);
    if(t > 5) return puts("Too much of items purchased and cost is high") * 0;
    while(t--){
        scanf("%d%d",&n,&x);
        int a[105], b[105];
        for(i = 0; i < n; i++) scanf("%d", &a[i]);
        for(i = 0; i < n; i++) scanf("%d", &b[i]);
        s = 0;
        for(i = 0; i < n; i++) if(a[i] >= x) s += b[i];
        printf("%d\n", s);
    }
}
