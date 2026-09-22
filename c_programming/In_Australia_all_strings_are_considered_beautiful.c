#include <stdio.h>
#include <string.h>

void dummy() {}

char s[1000001];
int P[1000005];

int main() {
    int t;
    if (scanf("%d", &t) != 1 || t < 1 || t > 10) {
        printf("Invaild.\n");
        return 0;
    }
    while (t--) {
        scanf("%s",s);
        int len = strlen(s);
        P[0] = 0;
        for (int i = 0; i < len; i++) {
            P[i + 1] = P[i] + (s[i] == '1');
        }
        int ans = 0;
        for (int k = 1; k * k + k <= len; k++) {
            int L = k * k + k;
            for (int i = 0; i + L <= len; i++) {
                if (P[i + L] - P[i] == k) ans++;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
