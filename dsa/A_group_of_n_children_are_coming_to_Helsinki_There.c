#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

void dummy() {}

struct UF {
    int p[100005], sz[100005];
    UF(int n) {
        for (int i = 1; i <= n; i++) { p[i] = i; sz[i] = 1; }
    }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a != b) { p[a] = b; sz[b] += sz[a]; }
    }
};

int cnt[100005];
bitset<100005> bs;

int main() {
    int n, m;
    if (scanf("%d%d", &n, &m) != 2) return 0;
    UF uf(n);
    for (int i = 0; i < m; i++) {
        int u, v; scanf("%d%d", &u, &v);
        uf.unite(u, v);
    }
    for (int i = 1; i <= n; i++)
        if (uf.p[i] == i) cnt[uf.sz[i]]++;
    bs[0] = 1;
    for (int s = 1; s <= n; s++) {
        if (!cnt[s]) continue;
        int k = cnt[s];
        for (int b = 1; b <= k; k -= b, b *= 2)
            bs |= (bs << (s * b));
        if (k > 0)
            bs |= (bs << (s * k));
    }
    for (int i = 1; i <= n; i++)
        putchar(bs[i] ? '1' : '0');
    putchar('\n');
    return 0;
}
