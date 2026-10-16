#include <bits/stdc++.h>
using namespace std;
const int MAXL = 200005;

struct state {
    int len = 0, link = -1;
    map<int, int> next;
};

state st[MAXL];
int sz = 1;

int cloneState(int q, int len) {
    int c = sz++;
    st[c] = st[q];
    st[c].len = len;
    return c;
}

int extend(int p, int c) {
    if (st[p].next.count(c)) {
        int q = st[p].next[c];
        if (st[q].len == st[p].len + 1)
            return q;
        int clone = cloneState(q, st[p].len + 1);
        while (p != -1 && st[p].next[c] == q) {
            st[p].next[c] = clone;
            p = st[p].link;
        }
        st[q].link = clone;
        return clone;
    }
    int cur = sz++;
    st[cur].len = st[p].len + 1;
    while (p != -1 && !st[p].next.count(c)) {
        st[p].next[c] = cur;
        p = st[p].link;
    }
    if (p == -1)
        st[cur].link = 0;
    else {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len)
            st[cur].link = q;
        else {
            int clone = cloneState(q, st[p].len + 1);
            while (p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    return cur;
}

int main() {
    int n, u, v;
    cin >> n;
    vector<vector<int>> g(n + 1);
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    queue<array<int, 3>> q;
    q.push({1, 0, 0});
    while (q.size()) {
        auto x = q.front();
        q.pop();
        int s = extend(x[2], g[x[0]].size());
        for (int y : g[x[0]])
            if (y != x[1])
                q.push({y, x[0], s});
    }
    long long ans = 0;
    for (int i = 1; i < sz; i++)
        ans += st[i].len - st[st[i].link].len;
    cout << ans;
}