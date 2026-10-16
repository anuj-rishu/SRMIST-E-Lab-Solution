#include <cstdio>
#include <algorithm>
using namespace std;
int d[1000003];

int main() {
    int n, i, a, b;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d%d", &a, &b);
        d[min(a, b)]++;
        d[max(a, b) + 1]--;
    }
    long long sum = 0, temp = 0;
    for (i = 1; i <= 1000000; i++) {
        temp += d[i];
        if (!temp)
            sum += i;
    }
    printf("%lld\n", sum);
}
