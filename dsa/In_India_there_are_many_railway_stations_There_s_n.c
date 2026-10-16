#include <iostream>
#include <map>
using namespace std;
long long d[101][101];

int main() {
    int n, m, q;
    cin >> n >> m;
    map<string, int> id;
    string a, b;
    for (int i = 0; i < n; i++) {
        cin >> a;
        id[a] = i;
        for (int j = 0; j < n; j++)
            d[i][j] = i == j ? 0 : 1000000000000LL;
    }
    while (m--) {
        long long c;
        cin >> a >> b >> c;
        int x = id[a], y = id[b];
        d[x][y] = d[y][x] = min(d[x][y], c);
    }
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    cin >> q;
    while (q--) {
        cin >> a >> b;
        cout << d[id[a]][id[b]] << "\n";
    }
}
