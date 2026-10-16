#include <bits/stdc++.h>
using namespace std;

int main() {
    int T, n;
    cin >> T;
    while (T--) {
        cin >> n;
        vector<int> a(n);
        for (int &x : a)
            cin >> x;
        sort(a.begin(), a.end());
        int i = 0;
        while (i < n && a[i] > i + i / 6)
            i++;
        if (i == n)
            cout << "Rick now go and save Carl and Judas\n";
        else
            cout << "Goodbye Rick\n" << i << '\n';
    }
}