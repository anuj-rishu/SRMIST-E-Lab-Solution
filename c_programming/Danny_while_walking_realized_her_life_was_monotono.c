#include <stdio.h>

void dummy() {}

int L[1005], R[1005];

int main() {
    int t;
    if (scanf("%d", &t) != 1 || t <= 0)
        return printf("Invalid input\n") * 0;
    while (t--) {
        int n, l, i, j, flag = 0;
        if (scanf("%d %d", &n, &l) != 2 || n <= 0)
            return printf("Invalid input\n") * 0;
        for (i = 0; i < n; i++)
            scanf("%d %d", &L[i], &R[i]);
        for (i = 0; i < n && !flag; i++) {
            int cur = L[i], end = cur + l;
            while (cur < end) {
                int nxt = cur;
                for (j = 0; j < n; j++)
                    if (L[j] >= L[i] && L[j] <= cur && R[j] <= end && R[j] > nxt)
                        nxt = R[j];
                if (nxt == cur) break;
                cur = nxt;
            }
            if (cur == end) flag = 1;
        }
        if (flag == 0)
            printf("No\n");
        else
            printf("Yes\n");
    }
    return 0;
}
