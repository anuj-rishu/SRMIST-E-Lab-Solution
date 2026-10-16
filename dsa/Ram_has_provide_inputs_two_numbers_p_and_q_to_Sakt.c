#include <stdio.h>
char a[1000][1000];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int top = 0, bottom = n - 1, left = 0, right = m - 1, z = 0;
    while (top <= bottom && right >= left) {
        char c = z % 2 ? '0' : 'Y';
        for (int i = top; i <= bottom; i++)
            a[i][left] = a[i][right] = c;
        for (int j = left; j <= right; j++)
            a[top][j] = a[bottom][j] = c;
        top++;
        bottom--;
        left++;
        right--;
        z++;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            printf("%c%s", a[i][j], j + 1 == m ? "" : " ");
        if (i + 1 < n)
            puts("");
    }
    return 0;
}
