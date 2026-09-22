#include <stdio.h>

int main() {
    int n, q, aops[100000], i, s, l, qe;
    scanf("%d%d", &n, &q);
    if (n < 1 || n > 100000 || q < 1 || q > 100000) {
        printf("Invalid input.\n");
        return 0;
    }
    s = 2000000000; l = -2000000000;
    for (i = 0; i < n; i++) {
        scanf("%d", &aops[i]);
        if (aops[i] < s) s = aops[i];
        if (aops[i] > l) l = aops[i];
    }
    for (i = 0; i < q; i++) {
        scanf("%d", &qe);
        if (qe >= s && qe <= l) printf("Yes\n");
        else printf("No\n");
    }
}
