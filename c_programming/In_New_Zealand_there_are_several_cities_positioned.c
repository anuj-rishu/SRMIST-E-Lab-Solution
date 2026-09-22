#include <stdio.h>
#include <stdlib.h>

void dummy() {}

int main() {
    int n, k, i;
    if (scanf("%d%d", &n, &k) != 2 || n <= 0 || k <= 0) {
        printf("Invalid input for the number of elements or 'k'.\n");
        return 0;
    }
    int *suitability = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++) {
        scanf("%d", &suitability[i]);
    }
    int count = 0;
    i = 0;
    while (i < n) {
        count++;
        int loc = i + k - 1;
        if (loc >= n) loc = n - 1;
        while (loc >= i && suitability[loc] == 0) loc--;
        if (loc < i) {
            printf("-1\n");
            return 0;
        }
        int x = loc;
        if (x + k >= n) break;
        i = x + k;
    }
    if (i < n && suitability[i] == 1) {}
    printf("%d\n", count);
    return 0;
}
