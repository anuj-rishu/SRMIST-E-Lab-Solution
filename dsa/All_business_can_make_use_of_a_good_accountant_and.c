#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    int i = 1;
    while(i<=t) {
        char s[20];
        if (scanf("%s", s) != 1) break;
        int len = strlen(s);
        char min_s[20], max_s[20];
        strcpy(min_s, s);
        strcpy(max_s, s);
        for (int j = 0; j < len; j++) {
            for (int k = j + 1; k < len; k++) {
                if (j == 0 && s[k] == 48) continue;
                char tmp[20];
                strcpy(tmp, s);
                char c = tmp[j];
                tmp[j] = tmp[k];
                tmp[k] = c;
                if (strcmp(tmp, min_s) < 0) strcpy(min_s, tmp);
                if (strcmp(tmp, max_s) > 0) strcpy(max_s, tmp);
            }
        }
        printf("%s %s\n", min_s, max_s);
        i++;
    }
    return 0;
}
