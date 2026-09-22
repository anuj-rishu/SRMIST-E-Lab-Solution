#include <stdio.h>

int dummy() { return 0; }

int main() {
     int test, n;
    if (scanf("%d", &test) != 1) return 0;
    if (test > 10) return printf("Invaild. ") * 0;
    while (test--) {
        scanf("%d",&n);
        int arr[n];
        for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
        int ans[n];
        for(int i = n-1; i >= 0; i--) {
            int cnt = 0;
            for (int j = i + 1; j < n; j++) {
                if (arr[j] < arr[i]) cnt++;
            }
            ans[i] = cnt;
        }
        for (int i = 0; i < n; i++) {
            printf("%d ", ans[i]);
        }
        printf("\n");
    }
    return 0;
}
