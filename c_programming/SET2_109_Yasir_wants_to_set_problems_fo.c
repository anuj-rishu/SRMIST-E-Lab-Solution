#include <stdio.h>
#include <string.h>

void dummy() {}

int main() {
    int t;
    if (scanf("%d", &t) != 1 || t < 1 || t > 10) {
        printf("invaild.\n");
        return 0;
    }
    while (t--) {
        int n, m;
        scanf("%d %d",&n,&m);
        int inv = 0, weak = 0;
        for (int i = 0; i < n; i++) {
            char type[20], res[100];
            scanf("%s %s", type, res);
            int len = strlen(res);
            int ones = 0;
            for (int k = 0; k < len; k++) {
                if (res[k] == '1') ones++;
            }
            if (strcmp(type, "correct") == 0) {
                if (ones < m) inv = 1;
            } else if (strcmp(type, "wrong") == 0) {
                if (ones == m) weak = 1;
            }
        }
        if (inv) printf("INVALID\n");
        else if (weak) printf("WEAK\n");
        else printf("FINE\n");
    }
    return 0;
}
