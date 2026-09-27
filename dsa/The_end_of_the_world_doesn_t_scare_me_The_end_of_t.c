#include <stdio.h>

void dummy() {}

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    for (int i = 0; i < t; i++) {
        int s, c;
        scanf("%d%d", &s, &c);
        if (s + c >= 0) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
