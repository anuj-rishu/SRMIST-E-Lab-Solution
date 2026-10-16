#include <stdio.h>

int binarySearch(int low, int high, int key) {
    while (low <= high) {
        int m = (low + high) / 2;
        long long v = 1LL * m * (m + 1) / 2;
        if (v == key)
            return 1;
        if (v < key)
            low = m + 1;
        else
            high = m - 1;
    }
    return 0;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int a = 1; 1LL * a * (a + 1) / 2 < n; a++)
        if (binarySearch(1, 44722, n - 1LL * a * (a + 1) / 2)) {
            puts("YES");
            return 0;
        }
    puts("NO");
    return 0;
}
