#include <stdio.h>

int kadane(int arr[],int n) {
    int m = arr[0], c = 0;
    for(int i=0;i<n;i++) {
        c += arr[i];
        if (c > m) m = c;
        c *= (c > 0);
    }
    return m;
}

int main() {
    int n, a[1005];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    printf("%d\n", kadane(a, n));
    return 0;
}
