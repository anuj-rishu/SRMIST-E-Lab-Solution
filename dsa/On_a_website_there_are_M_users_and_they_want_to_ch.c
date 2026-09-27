#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

#define ll long long

void dummy() {}

ll p_arr[200005];

ll find_set(ll v) {
    if (v == p_arr[v]) return v;
    return p_arr[v] = find_set(p_arr[v]);
}

void merge(ll a,ll b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) p_arr[b] = a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int m;
        if (!(cin >> m)) break;
        unordered_map<string, int> id_map;
        id_map.reserve(2 * m);
        int node_cnt = 0;
        int non_self = 0;
        int cycles = 0;

        for (int i = 1; i <= 2 * m; i++) p_arr[i] = i;

        for (int i = 0; i < m; i++) {
            string u, v;
            cin >> u >> v;
            if (u == v) continue;
            non_self++;
            if (!id_map.count(u)) id_map[u] = ++node_cnt;
            if (!id_map.count(v)) id_map[v] = ++node_cnt;
            int uid = id_map[u], vid = id_map[v];
            if (find_set(uid) == find_set(vid)) {
                cycles++;
            } else {
                merge(uid, vid);
            }
        }
        cout << (non_self + cycles) << "\n";
    }
    return 0;
}
