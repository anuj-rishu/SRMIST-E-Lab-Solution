#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int finish(vector<vector<int>> &g, vector<int> &deg, int n) {
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (!deg[i])
            q.push(i);
    int done = 0;
    while (true) {
        if (q.empty())
            break;
        int u = q.front();
        q.pop();
        done++;
        for (int v : g[u])
            if (!--deg[v])
                q.push(v);
    }
    return done == n;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> g(n + 1);
        vector<int> deg(n + 1);
        for (int i = 0, a, b; i < m; i++) {
            cin >> a >> b;
            if (a >= 1 && a <= n && b >= 1 && b <= n && a != b) {
                g[a].push_back(b);
                deg[b]++;
            }
        }
        cout << finish(g, deg, n) << '\n';
    }
}
