#include <iostream>
#include <algorithm>
using namespace std;

void dummy() {
}

int a[100002], b[100002];

int main() {
    int T, n, i;
    cin >> T;
    while (T--) {
        cin >> n;
        for (i = 1; i <= n; i++)
            cin >> a[i];
        for (i = 1; i <= n; i++)
            cin >> b[i];
        sort(a + 1, a + n + 1);
        sort(b + 1, b + n + 1);
        for (i = 1; i <= n; i++)
            a[i] += a[i - 1], b[i] += b[i - 1];
        int x = 0, k;
        while (k = n + x - (n + x) / 4, 100 * x + a[n] - a[n - k + x] < b[n] - b[max(0, n - k)])
            x++;
        cout << x << endl;
    }
}
