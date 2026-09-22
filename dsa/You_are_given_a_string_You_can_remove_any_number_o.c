#include <stdio.h>
#define M 1000000007
int l[26];
long long d[500005];
char cc[500005];
int main() {
    int i;
    scanf("%s", cc);
    d[1] = 1;
    for(i=0;cc[i];i++) {
        int c = cc[i] - 'a';
        d[i + 2] = (d[i + 1] * 2 - d[l[c]] + M) % M;
        l[c] = i + 1;
    }
    printf("%lld", (d[i + 1] - 1 + M) % M);
    return 0;
}
