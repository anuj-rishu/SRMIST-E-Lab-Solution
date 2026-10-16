#include <bits/stdc++.h>
using namespace std;

long long read() {
    long long x;
    cin >> x;
    return x;
}

int main() {
    int n, q, i, k;
    cin >> n >> q;
    priority_queue<long long> h, l;
    map<long long, int> c;
    vector<long long> s(n);
    for (i = 0; i < n; i++) {
        long long x = read();
        h.push(x);
        l.push(-x);
        c[x]++;
        s[0] += x;
    }
    for (i = 1; i < n; i++) {
        while (!c[-l.top()])
            l.pop();
        while (!c[h.top()])
            h.pop();
        long long x = -l.top(), y = h.top(), z = y - x;
        l.pop();
        h.pop();
        c[x]--;
        c[y]--;
        c[z]++;
        h.push(z);
        l.push(-z);
        s[i] = s[i - 1] - 2 * x;
    }
    while (q--) {
        cin >> k;
        cout << s[k] << endl;
    }
}