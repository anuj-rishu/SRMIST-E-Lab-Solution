#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct E {
    int a, b, c;
};

int p[100001], deg[100001];
long long sum;

int find(int p) {
    return ::p[p] == p ? p : ::p[p] = find(::p[p]);
}

void unio(int x, int y, int c) {
    int a = find(x), b = find(y);
    if (a != b) {
        p[a] = b;
        sum += c;
        deg[x]++;
        deg[y]++;
    }
}

int main() {
    int t, n, m;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        vector<E> e(m);
        for (auto &x : e) {
            cin >> x.a >> x.b >> x.c;
            if (x.a > x.b)
                swap(x.a, x.b);
        }
        sort(e.begin(), e.end(), [](E x, E y) {
            if (x.c != y.c)
                return x.c < y.c;
            if (x.a != y.a)
                return x.a > y.a;
            return x.b > y.b;
        });
        sum = 0;
        for (int i = 1; i <= n; i++)
            p[i] = i, deg[i] = 0;
        for (auto x : e)
            unio(x.a, x.b, x.c);
        cout << sum << "\n";
        for (int i = 1; i <= n; i++)
            cout << deg[i] << " ";
        cout << "\n";
    }
}
