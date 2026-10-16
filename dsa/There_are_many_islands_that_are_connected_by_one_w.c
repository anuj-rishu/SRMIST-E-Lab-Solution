#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

bool equal(double x, double y) {
    return fabs(x - y) <= 1e-9;
}

int main() {
    int n, m, r, u, v;
    cin >> n >> m >> r;
    vector<vector<int>> a(n + 1);
    vector<int> in(n + 1);
    vector<double> p(n + 1);
    while (m--) {
        cin >> u >> v;
        a[u].push_back(v);
        in[v]++;
    }
    queue<int> st;
    for (int i = 1; i <= n; i++)
        if (!in[i])
            st.push(i);
    p[r] = 1;
    while (!st.empty()) {
        u = st.front();
        st.pop();
        for (int v : a[u]) {
            p[v] += p[u] / a[u].size();
            if (!--in[v])
                st.push(v);
        }
    }
    double best = 0;
    for (int i = 1; i <= n; i++)
        if (a[i].empty())
            best = max(best, p[i]);
    for (int i = 1; i <= n; i++)
        if (a[i].empty() && fabs(p[i] - best) <= 1e-9)
            cout << i << " ";
}
