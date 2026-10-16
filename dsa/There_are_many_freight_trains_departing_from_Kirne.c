#include <cstdio>
#include <algorithm>
using namespace std;
pair<int, int> G[200005];

int main() {
    int n, h, m, k, x, y;
    scanf("%d%d%d%d", &n, &h, &m, &k);
    m /= 2;
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &x, &y);
        y %= m;
        G[i] = {y, i + 1};
        G[i + n] = {y + m, i + 1};
    }
    sort(G, G + 2 * n);
    int j = 0, best = n + 1, start = 0, end = 0;
    for (int i = 0; i < 2 * n; i++) {
        while (G[i].first - G[j].first >= k)
            j++;
        if (G[i].first >= m && G[i].first != G[i - 1].first && i - j < best) {
            best = i - j;
            start = j;
            end = i;
        }
    }
    printf("%d %d\n", best, G[end].first % m);
    for (int i = start; i < end; i++)
        printf("%d ", G[i].second);
}
