#include <stdio.h>

int findmax(int *Count) {
    int z = 0;
    for (int i = 0; i < 26; i++)
        if (Count[i] > z)
            z = Count[i];
    return z;
}

char s[100005];
int p[100005], st[100005];

int main() {
    int t, n;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%s", &n, s);
        int ans = 1;
        for (int c = 0; c < 26; c++) {
            p[0] = 0;
            int top = 0;
            st[top++] = 0;
            for (int i = 1; i <= n; i++) {
                p[i] = p[i - 1] + (s[i - 1] == 'a' + c ? 1 : -1);
                if (p[i] < p[st[top - 1]])
                    st[top++] = i;
            }
            for (int r = n; r >= 0; r--)
                while (top && p[r] - p[st[top - 1]] >= -1) {
                    int d = r - st[--top];
                    if (d > ans)
                        ans = d;
                }
        }
        printf("%d\n", ans);
    }
    return 0;
}
