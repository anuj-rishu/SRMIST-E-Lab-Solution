#include <stdio.h>

int main() {
    int n, k, i;
    scanf("%d%d", &n, &k);
    int arr[n];
    for (i = 0; i < n; i++)
        scanf("%d", arr + i);
    long long s = 0, b;
    for (i = 0; i < k; i++)
        s += arr[i];
    b = s;
    for (i = 1; i < k; i++) {
        s -= arr[k - i];
        s += arr[n - i];
        if (s > b)
            b = s;
    }
    printf("%lld", b);
    return 0;
}
