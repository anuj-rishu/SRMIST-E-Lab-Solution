#include <stdio.h>

int rotLeft(int arr[], int n, int d) {
    for (int i = 0; i < n; i++)
        printf("%d%s", arr[(i + d) % n], i + 1 == n ? "" : " ");
    return 0;
}

int rotRight(int arr[], int n, int d) {
    return rotLeft(arr, n, (n - d % n) % n);
}

int main() {
    int n, a[101], d;
    char c;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", a + i);
    scanf("%d %c", &d, &c);
    if (c == 'L')
        rotLeft(a, n, d % n);
    else
        rotRight(a, n, d);
    return 0;
}
