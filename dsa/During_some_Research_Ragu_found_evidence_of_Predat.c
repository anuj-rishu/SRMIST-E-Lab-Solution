#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int ALPHA = 26;
vector<vector<int>> trie;
vector<int> cnt;
int ans;

void insert(const string& s) {
    int t = 0;
    for (int i = (int)s.length() - 1; i >= 0; i--) {
        int d = s[i] - 'A';
        if (trie[t][d] == -1) {
            trie[t][d] = trie.size();
            trie.emplace_back(ALPHA, -1);
            cnt.push_back(0);
        }
        t = trie[t][d];
    }
    cnt[t]++;
}

int dfs(int u) {
    int c = cnt[u];
    for (int d = 0; d < ALPHA; d++) {
        int v = trie[u][d];
        if (v != -1) c += dfs(v);
    }
    if (u != 0 && c >= 2) { c -= 2; ans += 2; }
    return c;
}

int main() {
    int t, n;
    string s;
    if (cin >> t) while (t--) {
        cin >> n;
        trie.clear(); cnt.clear();
        trie.emplace_back(ALPHA, -1); cnt.push_back(0);
        while (n--)  { cin >> s; insert(s); }
        ans = 0; dfs(0);
        cout << ans << "\n";
    }
    return 0;
}
