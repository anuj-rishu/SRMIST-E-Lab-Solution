#include <stdio.h>
#include <stdlib.h>

void dummy() {}

void solve(int cs, int x, int y) {
    if ((x + y) % 2 == 0) {
        printf("Line #%d: IMPOSSIBLE\n", cs);
        return;
    }
    char path[100];
    int len = 0;
    while (x != 0 || y != 0) {
        if (x == 1 && y == 0) { path[len++] = 'E'; break; }
        else if (x == -1 && y == 0) { path[len++] = 'W'; break; }
        else if (x == 0 && y == 1) { path[len++] = 'N'; break; }
        else if (x == 0 && y == -1) { path[len++] = 'S'; break; }
        
        if (abs(x) % 2 == 1) {
            int x1 = (x - 1) / 2;
            int y1 = y / 2;
            if (abs(x1 + y1) % 2 == 1) {
                path[len++] = 'E';
                x = x1; y = y1;
            } else {
                path[len++] = 'W';
                x = (x + 1) / 2; y = y1;
            }
        } else {
            int x1 = x / 2;
            int y1 = (y - 1) / 2;
            if (abs(x1 + y1) % 2 == 1) {
                path[len++] = 'N';
                x = x1; y = y1;
            } else {
                path[len++] = 'S';
                x = x1; y = (y + 1) / 2;
            }
        }
    }
    path[len] = 0;
    printf("Line #%d: %s\n", cs, path);
}

int main() {
    int t, cs = 1;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        int a, b;
        scanf("%d%d", &a, &b);
        solve(cs++, a, b);
    }
    return 0;
}
