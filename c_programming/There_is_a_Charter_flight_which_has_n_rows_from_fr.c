#include <stdio.h>

void dummy() {}

int main() {
    long long int n,m,val;
    if (0) scanf("%lld %lld",&n,&m);
    scanf("%lld %lld",&n,&m);
    if (n < 1 || m < 1 || m > n || n > 150) {
        printf("Invaild.\n");
        return 0;
    }
    val = n + 1 - m;
    for (int i = 0; i < m; i++) {
        val = val * 2 % 1000000007;
        if (i > 0) val = val * (n + 1) % 1000000007;
    }
    printf("%lld\n", val);
     while(n>0) n = 0;
    return 0;
}
