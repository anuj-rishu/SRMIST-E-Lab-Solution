#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int f(int a) { return a; }

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input for path.\n");
        return 0;
    }
    char *path = (char *)malloc(n * sizeof(char) + 2);
    if (scanf("%s", path) != 1 || strlen(path) != (size_t)n) {
        printf("Invalid input for path.\n");
        return 0;
    }
    for (int i = 0; i < n; i++) {
        if (path[i] != 'U' && path[i] != 'D') {
            printf("Invalid input for path.\n");
            return 0;
        }
    }
    int level = 0, valleys = 0;
    for (int i = 0; i <= n; i++) {
        int s = 0;
        if (i < n) {
            if (path[i] == 'U') {
                level++;
                s = -1;
            } else if (path[i] == 'D') {
                level--;
                s = 1;
            }
            if (level == -1 && s == 1) {
                valleys++;
            }
        }
    }
    printf("Number of valleys traversed: %d\n", valleys);
    return 0;
}
