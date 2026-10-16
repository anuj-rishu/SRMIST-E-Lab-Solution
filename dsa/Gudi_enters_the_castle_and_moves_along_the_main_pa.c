#include <iostream>
#include <string>
#include <queue>
#include <unordered_set>
#include <algorithm>
using namespace std;
int A, H, n;
string start, best;

void add(int *a, int size) {
    for (int i = 1; i < size; i += 2)
        a[i] = (a[i] + A) % 10;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> start >> A >> H;
        n = start.size();
        best = start;
        queue<string> q;
        unordered_set<string> seen;
        q.push(start);
        seen.insert(start);
        while (!q.empty()) {
            string s = q.front();
            q.pop();
            best = min(best, s);
            string r = s.substr(n - H % n) + s.substr(0, n - H % n);
            if (seen.insert(r).second)
                q.push(r);
            int a[10];
            for (int i = 0; i < n; i++)
                a[i] = s[i] - '0';
            add(a, n);
            for (int i = 0; i < n; i++)
                r[i] = char('0' + a[i]);
            if (seen.insert(r).second)
                q.push(r);
        }
        cout << best << '\n';
    }
}
