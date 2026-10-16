#include <stdio.h>

int main() {
    int num, cnt = 0, bestcnt = 0;
    long long x, sum = 0, best = -1000000001;
    scanf("%d", &num);
    while (num) {
        scanf("%lld", &x);
        if (x >= 0)
            sum += x, cnt++;
        if (x > best)
            best = x, bestcnt = 1;
        else if (x == best)
            bestcnt++;
        num--;
    }
    if (cnt == 0)
        printf("%lld %d", best, bestcnt);
    else
        printf("%lld %d", sum, cnt);
    return 0;
}
