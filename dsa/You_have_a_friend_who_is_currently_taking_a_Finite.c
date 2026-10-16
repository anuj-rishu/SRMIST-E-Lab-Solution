#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
int n, sig, f, to[10005][26], d[10005], lo[10005], on[10005], id[10005], good[10005], mask[10005],
    tmr, cc;
vector<int> rev[10005], finals, stack_;

void markBack(int u) {
    good[u] = 1;
    for (int v : rev[u])
        if (!good[v])
            markBack(v);
}

void pop(int u) {
    int v;
    ++cc;
    do {
        v = stack_.back();
        stack_.pop_back();
        on[v] = 0;
        id[v] = cc;
    } while (v != u);
}

void tarjan(int u);

void edge(int u, int v) {
    if (!d[v]) {
        tarjan(v);
        lo[u] = min(lo[u], lo[v]);
    } else if (on[v])
        lo[u] = min(lo[u], d[v]);
}

void tarjan(int u) {
    d[u] = lo[u] = ++tmr;
    stack_.push_back(u);
    on[u] = 1;
    for (int j = 0; j < sig; j++)
        edge(u, to[u][j]);
    if (lo[u] == d[u])
        pop(u);
}

void row(int u) {
    for (int j = 0, v; j < sig; j++) {
        scanf("%d", &v);
        to[u][j] = v <= n ? v : 0;
        if (to[u][j])
            rev[v].push_back(u);
    }
}

void load() {
    scanf("%d%d%d", &n, &sig, &f);
    tmr = cc = 0;
    finals.clear();
    for (int u = 1; u <= n; u++) {
        rev[u].clear();
        d[u] = on[u] = id[u] = good[u] = mask[u] = 0;
    }
    for (int i = 0, v; i < f; i++) {
        scanf("%d", &v);
        finals.push_back(v);
    }
    for (int u = 1; u <= n; u++)
        row(u);
}

void backAll() {
    for (int v : finals)
        if (!good[v])
            markBack(v);
}

void gather(int u) {
    for (int j = 0; j < sig; j++)
        if (id[u] == id[to[u][j]])
            mask[id[u]] |= 1 << j;
}

void gatherAll() {
    for (int u = 1; u <= n; u++)
        if (id[u])
            gather(u);
}

bool possible() {
    int full = (1 << sig) - 1;
    for (int u = 1; u <= n; u++)
        if (good[u] && mask[id[u]] == full)
            return true;
    return false;
}

int main() {
    int T;
    scanf("%d", &T);
    d[0] = 1;
    while (T--) {
        load();
        backAll();
        tarjan(1);
        gatherAll();
        puts(possible() ? "YES" : "NO");
    }
}
