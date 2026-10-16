#include <stdio.h>
#include <stdlib.h>
typedef long long ll;

typedef struct {
    ll a, b;
} seg;

seg s[2005];

int cmp(const void *a, const void *b) {
    return ((seg *)a)->a - ((seg *)b)->a;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        ll n, l;
        scanf("%lld%lld", &n, &l);
        for (ll i = 0; i < n; i++) {
            scanf("%lld%lld", &s[i].a, &s[i].b);
        }
        qsort(s, n, sizeof *s, cmp);
        int ok = 0;
        for (ll i = 0; i < n; i++) {
            ll maxright = s[i].a + l, cur_right = s[i].a;
            for (ll j = 0; j < n; j++)
                if (s[j].a >= s[i].a && s[j].b <= maxright && s[j].a <= cur_right &&
                    s[j].b > cur_right)
                    cur_right = s[j].b;
            if (cur_right == maxright)
                ok = 1;
        }
        puts(ok ? "Yes" : "No");
    }
}
