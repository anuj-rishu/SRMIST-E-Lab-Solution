#include <iostream>
#include <algorithm>
using namespace std;
int p[100005], sz[100005];

int root(int x) {
    return p[x] == x ? x : p[x] = root(p[x]);
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        p[i] = i;
        sz[i] = 1;
    }
    bool cycle = 0;
    int i, a, b;
    for (i = 1; i <= m; i++) {
        cin >> a >> b;
        if (a < 1 || a > n || b < 1 || b > n)
            continue;
        a = root(a);
        b = root(b);
        if (a == b)
            cycle = 1;
        else {
            p[a] = b;
            sz[b] += sz[a];
        }
    }
    if (cycle)
        cout << ">1\n";
    else {
        int s = 1;
        for (int j = 1; j <= n; j++)
            if (p[j] == j)
                s = max(s, sz[j]);
        cout << s - 1 << '/' << s << '\n';
    }
}
