#include <iostream>
#include <vector>
using namespace std;
vector<int> a[1000001], path[1000001];
int color[1000001], ans[1000001], seen[1000001], k;

bool visited(int u) {
    return seen[u];
}

void dfs(int n) {
    vector<int> st(1, n);
    while (!st.empty()) {
        int u = st.back();
        st.pop_back();
        if (u < 0) {
            path[color[-u]].pop_back();
            continue;
        }
        if (seen[u])
            continue;
        seen[u] = 1;
        auto &p = path[color[u]];
        ans[u] = p.size() >= (unsigned)k ? p[p.size() - k] : -1;
        p.push_back(u);
        st.push_back(-u);
        for (int v : a[u])
            if (!seen[v])
                st.push_back(v);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, x, y;
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> color[i];
    for (int i = 1; i < n; i++) {
        cin >> x >> y;
        a[x].push_back(y);
        a[y].push_back(x);
    }
    dfs(1);
    for (int i = 1; i <= n; i++)
        cout << ans[i] << " ";
}
