#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

typedef struct node {
    vector<int> v;
} Node;

Node a[1001];

int solve(int x, int visited[], int is_matched[]) {
    for (int y : a[x].v)
        if (!visited[y]) {
            visited[y] = 1;
            if (!is_matched[y] || solve(is_matched[y], visited, is_matched)) {
                is_matched[y] = x;
                return 1;
            }
        }
    return 0;
}

int main() {
    int n, m, x, ans = 0;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> x;
        for (int d = 1; d * d <= x; d++)
            if (x % d == 0) {
                if (d <= m)
                    a[i].v.push_back(d);
                if (x / d != d && x / d <= m)
                    a[i].v.push_back(x / d);
            }
    }
    int vis[100001] = {0}, match[100001] = {0};
    for (int i = 1; i <= n; i++) {
        memset(vis, 0, sizeof vis);
        ans += solve(i, vis, match);
    }
    cout << ans;
}
