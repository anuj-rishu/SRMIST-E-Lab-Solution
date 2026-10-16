#include <iostream>
#include <algorithm>
using namespace std;

void dummy() {
}

int main() {
    int t, n, i;
    long long x, a[100005];
    cin >> t;
    while (t--) {
        cin >> n >> x;
        for (i = 0; i < n; i++)
            cin >> a[i];
        sort(a, a + n);
        long long s = 0;
        for (i = n - 1; i >= 0; i--) {
            s += a[i] - x;
            if (s < 0)
                break;
        }
        cout << n - 1 - i << endl;
    }
}
