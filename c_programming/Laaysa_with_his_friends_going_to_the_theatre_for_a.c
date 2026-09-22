#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    for (int i = 1; i <= n; i++) {
        int start = (i % 2 == 0) ? 2 : 1;
        for (int j = 0; j < i; j++) {
            printf("%d ", start + 2 * j);
        }
        printf("\n");
    }
    return 0;
}
