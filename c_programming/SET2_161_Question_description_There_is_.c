#include <stdio.h>
#include <string.h>

int main() {
    int tests;
    if (scanf("%d", &tests) != 1 || tests <= 0 || tests > 1000) {
        printf("Invalid Input");
        return 0;
    }
    char s[10] = "DBACD", t[10] = "BBBBB";
    while (tests--) {
        strcpy(t, "BBBBB");
        scanf("%s", s);
        scanf("%s", t);
        for (int i = 0; i < 5; i++) {
            if (s[i] == t[i]) printf("G");
            else printf("B");
        }
    }
    return 0;
}
