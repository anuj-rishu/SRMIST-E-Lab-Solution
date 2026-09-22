#include <stdio.h>

int main() {
    int t;
    scanf("%d", &t);
    if (t < 1 || t > 10) {
        printf("Invalid\n");
        return 0;
    }
    while (t--) {
        int n;
        if (scanf("%d", &n) != 1) break;
        if (n < 1) break;
        int a[n], ans[n];
        for (int i = 0; i < n; i++) scanf("%d", &a[i]);
        for (int j = 0; j < n; j++) {
            int count = 1;
            for (int i = j; i < n - 1; i++) {
                if ((a[i] > 0) != (a[i + 1] > 0))
                    count++;
                else
                    break;
            }
            int itr = count;
            ans[j] = itr;
        }
        for (int j = 0; j < n; j++)
            printf("%d ", ans[j]);
        printf("\n");
    }
    return 0;
}
