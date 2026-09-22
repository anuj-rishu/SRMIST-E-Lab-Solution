#include <stdio.h>
int main() {
    int n, i = 0, j;
    scanf("%d", &n);
    int a[n];
    for (int k = 0; k < n; k++) scanf("%d", &a[k]);
    j = n - 1;
    while (i < n && j >= 0) {
        if(a[i]>a[j]) { printf("1 "); j--; }
        else if (a[i] < a[j]) { printf("2 "); i++; }
        else { printf("0 "); i++; j--; }
    }
    return 0;
}