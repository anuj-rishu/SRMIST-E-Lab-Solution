#include <cstdio>
int a[1005], used[1005], counts[1005];

int main() {
    int t, n;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", a + i);
        for (int i = 0; i < 1005; i++)
            used[i] = counts[i] = 0;
        int ok = 1;
        for (int i = 0; i < n;) {
            int j = i;
            while (j < n && a[j] == a[i])
                j++;
            if (used[a[i]] || counts[j - i])
                ok = 0;
            used[a[i]] = counts[j - i] = 1;
            i = j;
        }
        puts(ok ? "YES" : "NO");
    }
}
