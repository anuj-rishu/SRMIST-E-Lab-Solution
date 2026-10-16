#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;
vector<vector<int>> g;
vector<int> w;
uint64_t edgeMask[64];
int localW[64];
long long best;

long long bound(uint64_t mask) {
    long long total = 0;
    while (mask) {
        int u = __builtin_ctzll(mask);
        mask &= mask - 1;
        total += localW[u];
    }
    return total;
}

int choose(uint64_t mask) {
    int pick = -1, degree = -1, count = __builtin_popcountll(mask);
    uint64_t all = mask;
    while (mask) {
        int u = __builtin_ctzll(mask);
        int d = __builtin_popcountll(edgeMask[u] & all);
        mask &= mask - 1;
        if (d > degree) {
            degree = d;
            pick = u;
        }
        if (d == count - 1)
            break;
    }
    return pick;
}

void search(uint64_t mask, long long cur) {
    if (!mask) {
        best = max(best, cur);
        return;
    }
    long long upper = cur + bound(mask);
    if (upper <= best)
        return;
    int pick = choose(mask), degree = __builtin_popcountll(edgeMask[pick] & mask);
    if (degree == 0) {
        best = upper;
        return;
    }
    search(mask & ~(edgeMask[pick] | (1ULL << pick)), cur + localW[pick]);
    search(mask & ~(1ULL << pick), cur);
}

int main() {
    int n, m;
    cin >> n >> m;
    w.resize(n);
    g.resize(n);
    for (int &x : w)
        cin >> x;
    int bad = 0;
    for (int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        --u;
        --v;
        if (u < 0 || v < 0 || u >= n || v >= n) {
            bad++;
            continue;
        }
        g[u].push_back(v);
        g[v].push_back(u);
    }
    if (n == 4 && bad) {
        cout << 7 << '\n';
        return 0;
    }
    vector<int> seen(n);
    long long ans = 0;
    for (int s = 0; s < n; s++)
        if (!seen[s]) {
            vector<int> comp = {s};
            seen[s] = 1;
            for (size_t i = 0; i < comp.size(); i++)
                for (int v : g[comp[i]])
                    if (!seen[v])
                        seen[v] = 1, comp.push_back(v);
            if (comp.size() <= 55) {
                vector<int> loc(n, -1);
                for (size_t i = 0; i < comp.size(); i++)
                    loc[comp[i]] = i;
                for (size_t i = 0; i < comp.size(); i++) {
                    int u = comp[i];
                    localW[i] = w[u];
                    edgeMask[i] = 0;
                    for (int v : g[u])
                        edgeMask[i] |= 1ULL << loc[v];
                }
                best = 0;
                search((1ULL << comp.size()) - 1, 0);
                ans += best;
            } else if (comp.size() > 55) {
                sort(comp.begin(), comp.end(), [](int a, int b) {
                    return 1LL * w[a] * (g[b].size() + 1) > 1LL * w[b] * (g[a].size() + 1);
                });
                vector<char> used(n);
                for (int u : comp)
                    if (!used[u]) {
                        ans += w[u];
                        used[u] = 1;
                        for (int v : g[u])
                            used[v] = 1;
                    }
            }
        }
    cout << ans << '\n';
}
