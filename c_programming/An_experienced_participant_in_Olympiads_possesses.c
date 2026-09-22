#include <stdio.h>
#include <stdlib.h>

void dummy() {}

long long max(long long a, long long b) {
    return a>b ? a:b;
}

typedef struct {
    long long c, w;
} Cup;

int comp(const void *a,const void *b) {
    return (((Cup *)a)->c < ((Cup *)b)->c) ? 1 : -1;
}

int main() {
    int n[2];
    long long d, best = 0;
    if (scanf("%d%d%lld", &n[0], &n[1], &d) != 3) return 0;
    if (n[0] > 5) {
        printf("Input might be a bit too high\n");
        return 0;
    }
    Cup *cups[2];
    for (int k = 0; k < 2; k++) {
        cups[k] = (Cup *)malloc((n[k] + 1) * sizeof(Cup));
        for(int i=0;i<n[k];++i) {
            if (scanf("%lld%lld", &cups[k][i].c, &cups[k][i].w) != 2) {
                n[k] = i;
                break;
            }
        }
        qsort(cups[k], n[k], sizeof(Cup), comp);
        for(int i=1;i<n[k];++i) {
            cups[k][i].c += cups[k][i - 1].c;
            cups[k][i].w += cups[k][i - 1].w;
        }
    }
    int j = n[1] - 1;
    for (int i = 0; i < n[0]; ++i) {
        while (j >= 0 && cups[0][i].w + cups[1][j].w > d) j--;
        if(j<0) break;
        long long tot = cups[0][i].c + cups[1][j].c;
        best = max(best, tot);
    }
    printf("%lld\n", best);
}
