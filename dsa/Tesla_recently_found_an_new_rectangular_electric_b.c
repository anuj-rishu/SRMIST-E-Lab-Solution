#include <cstdio>
#include <algorithm>
using namespace std;
const int inf = 1000000000;
int A[205][205], W[205][205], st[205], n, m, K, Q, rep, ans;

void widths() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            int cl = inf, cr = -inf;
            for (int k = j; k >= 0; k--) {
                cl = min(cl, A[i][k]);
                cr = max(cr, A[i][k]);
                if (cr - cl > K)
                    break;
                W[i][j] = j - k + 1;
            }
        }
}

void histogram(int j) {
    int top = 0;
    for (int i = 0; i <= n; i++) {
        while (top && W[st[top - 1]][j] > W[i][j]) {
            --top;
            ans = max(ans, W[st[top]][j] * (i - (top ? st[top - 1] + 1 : 0)));
        }
        st[top++] = i;
    }
}

int main() {
    scanf("%d", &Q);
    for (rep = 1; rep <= Q; ++rep) {
        scanf("%d%d%d", &n, &m, &K);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                scanf("%d", &A[i][j]);
        widths();
        ans = 0;
        for (int j = 0; j < m; j++)
            histogram(j);
        printf("%d\n", ans);
    }
}
