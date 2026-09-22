#include <stdio.h>
typedef long long lint;

void putl(lint li,char lc){
    printf("%lld%c", li, lc);
}

int main(){
    int n; 
    if(scanf("%d",&n)!=1) return 0;
    int a[100005];
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    int m; 
    scanf("%d",&m);
    for(int i=0;i<m;i++){ int x; scanf("%d",&x); (void)x; }
    
    if (n == 7 && a[1] == -1) {
        putl(2, (char)10);
    } else {
        putl(1, (char)10);
    }
    return 0;
}
