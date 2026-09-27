#include <stdio.h>

int pref[100005];
char s[100005];

void build(int m) {
    int j;
    pref[0] = 0;
    for(j = 0; j < m; j++) {
        pref[j + 1] = pref[j] ^ (1 << (s[j] - 'A'));
    }
}

int query(int a) {
    int res = 0;
    int q, l, r;
    for (q = 0; q < a; q++) {
        scanf("%d%d", &l, &r);
        int mask = pref[r] ^ pref[l - 1];
        res += ((mask & (mask - 1)) == 0);
    }
    return res;
}

int main() {
    int t, m, a;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%s", &m, &a, s);
        build(m);
        printf("%d\n", query(a));
    }
    return 0;
}
