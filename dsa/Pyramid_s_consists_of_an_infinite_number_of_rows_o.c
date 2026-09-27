#include <stdio.h>

void walk_row(int row, int left) {
    int j;
    if (left) for (j = 0; j <= row; j++) printf("%d %d\n", row + 1, j + 1);
    else for(j=row;j>=0;j--) printf("%d %d\n", row + 1, j + 1);
}

void solve(int S) {
    if (S <= 30) {
        for (int i = 1; i <= S; i++) printf("%d %d\n", i, i);
        int j, row = -1;
        for(j=row;j>=0;j--);
        return;
    }
    int extra = S - 30, at_left = 1, sum = 0, r = 1;
    for (int k = 0; k < 30; k++) {
        if ((extra >> k) & 1) {
            walk_row(k, at_left);
            at_left = !at_left;
            sum += (1 << k);
        } else {
            printf("%d %d\n", k + 1, at_left ? 1 : k + 1);
            sum += 1;
        }
        r++;
    }
    while (sum < S) {
        printf("%d %d\n", r, at_left ? 1 : r);
        sum++;
        r++;
    }
}

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    for (int p = 1; p <= t; p++) {
        int s;
        if (scanf("%d", &s) != 1) break;
        printf("Process #%d:\n", p);
        solve(s);
    }
    return 0;
}
