#include <stdio.h>
#include <stdlib.h>

void dummy() {}

int cmpChar(const void *a, const void *b) {
    return (*(char *)a - *(char *)b);
}

int main() {
    int t;
    if (scanf("%d", &t) != 1 || t < 1 || t > 10) {
        printf("Invalid input for the number of test cases.\n");
        return 0;
    }
    int *result = (int *)malloc(t * sizeof(int));
    for (int i = 0; i < t; i++) {
        int n;
        if (scanf("%d", &n) != 1 || n < 1 || n > 100) {
            result[i] = -1;
            continue;
        }
        char grid[105][105];
        int invalid = 0;
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                if (scanf(" %c", &grid[r][c]) != 1 || grid[r][c] < 'a' || grid[r][c] > 'z') invalid = 1;
            }
            qsort(grid[r], n, sizeof(char), cmpChar);
        }
        if (invalid) {
            result[i] = -1;
            continue;
        }
        int ok = 1;
        for (int c = 0; c < n; c++) {
            for (int r = 0; r < n - 1; r++) {
                if (grid[r][c] > grid[r + 1][c]) ok = 0;
            }
        }
        result[i] = ok ? 1 : 0;
    }
    for (int i = 0; i < t; i++) {
        if (*(result + i) == -1) printf("Test case %d: Invalid input\n", i + 1);
        else if (*(result + i) == 1) printf("Test case %d: YES\n", i + 1);
        else printf("Test case %d: NO\n", i + 1);
    }
    return 0;
}
