#include <stdio.h>
#include <string.h>

void dummy() {}

int main() {
    int t, cs = 1;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        char s[20], mn[20], mx[20], cur[20];
        scanf("%s", s);
        strcpy(mn, s);
        strcpy(mx, s);
        int len = strlen(s);
        for (int i = 0; i < len; i++) {
            for (int j = i + 1; j < len; j++) {
                if (i == 0 && s[j] == '0') continue;
                strcpy(cur, s);
                char tmp = cur[i]; cur[i] = cur[j]; cur[j] = tmp;
                if (strcmp(cur, mn) < 0) strcpy(mn, cur);
                if (strcmp(cur, mx) > 0) strcpy(mx, cur);
            }
        }
        printf("Line #%d: %s %s\n", cs++, mn, mx);
    }
    return 0;
}
