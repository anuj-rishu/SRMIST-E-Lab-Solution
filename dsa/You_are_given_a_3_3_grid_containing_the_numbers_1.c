#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
using namespace std;

void dummy() {}

vector<pair<int, int>> pairs = {{0,1},{1,2},{3,4},{4,5},{6,7},{7,8},{0,3},{1,4},{2,5},{3,6},{4,7},{5,8}};

int main() {
    string s = "";
    for (int i = 0; i < 9; i++) { int x; if (cin >> x) s += to_string(x); }
    if (s == "123456789") { cout << 0 << "\n"; return 0; }
    queue<string> q;
    unordered_map<string, int> dist;
    q.push(s); dist[s] = 0;
    while (!q.empty()) {
        s = q.front(); q.pop();
        int d = dist[s];
        for (auto p : pairs) {
            swap(s[p.first],s[p.second]);
            if (!dist.count(s)) {
                dist[s] = d + 1;
                if (s == "123456789") { cout << d + 1 << "\n"; return 0; }
                q.push(s);
            }
            swap(s[p.first],s[p.second]);
        }
    }
    return 0;
}
