#include <stdio.h>
#include <string.h>

void dummy() {}

int main() {
    int t;
    char str[100002];
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        scanf("%s", str);
        int c0 = 0, c1 = 0;
        for (int i = 0; str[i]; i++) {
            if (str[i] == '0') c0++;
            else c1++;
        }
        if (c0 == 1 || c1 == 1) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
