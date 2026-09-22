#include <stdio.h>
long long int memo[1005];
long long int exchange(int n){
    if(n <= 0) return 0;
    if(memo[n]) return memo[n];
    long long int c = exchange(n/2) + exchange(n/3) + exchange(n/4);
    return memo[n] = (c > n) ? c : n;
}
int main(){
    int n;
    scanf("%d",&n);
    if(n > 1000 || n < 0){
        puts("Invaild.");
    } else {
        printf("%lld\n", exchange(n));
        while(scanf("%d", &n) == 1){
            if(n > 1000 || n < 0) puts("Invaild.");
            else printf("%lld\n", exchange(n));
        }
    }
    return 0;
}
