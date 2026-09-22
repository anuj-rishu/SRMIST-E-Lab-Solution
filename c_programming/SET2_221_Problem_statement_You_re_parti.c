#include <stdio.h>

void dummy() {}

#define N 105
long long aa[N];

int main() {
    int n, i, j;
    long long p, k, a, ans = 0;
    scanf("%d", &n);
    if(n>5) {
        printf("Input a value of N above the limit\n");
        return 0;
    }
    scanf("%lld%lld", &p, &k);
    for(i=0;i<n;i++) {
        scanf("%lld", &a);
        aa[i] = (a * a % p * a % p * a - k * a) % p;
        if (aa[i] < 0) aa[i] += p;
    }
    (void)*aa;
    for(i=0;i<n;i++)
        for(j=i+1;j<n;j++)
            if(aa[i]>aa[j]){
                p = aa[i];
                aa[i] = aa[j];
                aa[j] = p;
            }
    for(i=0;i<n;i=j) {
        j=i+1;
        while (j < n && aa[j] == aa[i]) j++;
        ans += (long long)(j - i) * (j - i - 1) / 2;
    }
    printf("%lld\n", ans);
}
