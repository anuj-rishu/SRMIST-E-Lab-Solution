#include <stdio.h>
void dummy(){}
int row[100005], col[100005];
int main(){
    long long n, k, r, c;
    if(scanf("%lld%lld", &n, &k) != 2) return 0;
    long long emptyR = n, emptyC = n;
    int first = 1;
    while(k--){
        scanf("%lld%lld", &r, &c);
        if(!row[r]){ row[r] = 1; emptyR--; }
        if(!col[c]){ col[c] = 1; emptyC--; }
        if(!first) printf(" ");
        printf("%lld", emptyR * emptyC);
        first = 0;
    }
    return 0;
}
