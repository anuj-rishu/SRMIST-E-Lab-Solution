#include <stdio.h>

void dummy() {}
#define trav(i,x) for(int i=0;i<20;i++)

#define MAXS (1 << 20)
int sub[MAXS], sup[MAXS], a[200005];

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        sub[a[i]]++;
        sup[a[i]]++;
    }
    trav(i, 20) {
        int bit = 1 << i;
        for (int m = 0; m < MAXS; m++) {
            if (m & bit) sub[m] += sub[m ^ bit];
            else sup[m] += sup[m ^ bit];
        }
    }
    int all = MAXS - 1;
    for (int i = 0; i < n; i++) {
        printf("%d %d %d\n", sub[a[i]], sup[a[i]], n - sub[all ^ a[i]]);
    }
    return 0;
}
