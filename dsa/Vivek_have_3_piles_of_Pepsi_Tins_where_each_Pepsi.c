#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n[3], s[3] = {}, p[3] = {};
    for (int i = 0; i < 3; i++)
        cin >> n[i];
    vector<vector<int>> a(3);
    for (int i = 0; i < 3; i++) {
        a[i].resize(n[i]);
        for (int &x : a[i])
            cin >> x;
        for (int x : a[i])
            s[i] += x;
    }
    while (true) {
        if (s[0] == s[1] && s[1] == s[2])
            break;
        int k = 0;
        for (int i = 1; i < 3; i++)
            if (s[i] > s[k])
                k = i;
        if (p[k] < n[k])
            s[k] -= a[k][p[k]++];
        else if (s[0] == 0)
            break;
    }
    cout << s[0] << '\n';
}
