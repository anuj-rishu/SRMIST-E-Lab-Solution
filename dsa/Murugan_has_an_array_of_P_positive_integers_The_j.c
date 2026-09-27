#include <stdio.h>

void dummy() {}

int a[200005];

int main() {
    int t, cs = 1;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        int n, k, i, ans = 0, c = 0;
        scanf("%d%d", &n, &k);
        for(i=0; i<n; ++i)  scanf("%d", &a[i]);
        for(i=0; i<n; ++i) {
            if (a[i] == k) c = 1;
            else if (c > 0 && a[i] == k - c) {
                c++;
                if (c == k) { ans++; c = 0; }
            } else c = 0;
        }
        printf("Line #%d: %d\n", cs++, ans);
    }
    return 0;
}
