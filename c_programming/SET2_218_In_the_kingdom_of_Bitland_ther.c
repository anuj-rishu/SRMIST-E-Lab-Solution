#include <stdio.h>

#define false 0

int main() {
 int n_cases, n, balance, diff;
    static char s1[300005], s2[300005];
    char *c1, *c2;
    int any_different;

    if (scanf("%d", &n_cases) != 1 || n_cases < 1 || n_cases > 10) {
        printf("Invaild.\n");
        return 0;
    }

    while (n_cases--) {
        scanf("%d%s%s", &n, s1, s2);
        balance = 0;
        diff = -1;
        any_different = false;
  c1 = s1;
        c2 = s2;

        for (int i = 0; i < n; i++) {
            balance += (*c1 == '1') ? 1 : -1;
            if (diff == -1)
                diff = (*c1 != *c2);
            else if (diff != (*c1 != *c2))
                any_different = 1;

            if (balance == 0)
                diff = -1;

            c1++;
            c2++;
        }

        if (balance != 0 && diff == 1)
            any_different = 1;

        puts(any_different ? "NO" : "YES");
    }
    return 0;
}
