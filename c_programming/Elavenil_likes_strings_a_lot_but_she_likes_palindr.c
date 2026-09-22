#include <stdio.h>
#include <string.h>

void dummy() {}

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        char pali[500];
        scanf("%s", pali);
        int len = strlen(pali);
        int ok = 1;
        for (int i = 0; i < len / 2 + 1; i++) {
            int j = len - 1 - i;
            if (pali[i] == '.' && pali[j] == '.') {
                pali[i] = pali[j] = 'a';
            } else if (pali[i] == '.') {
                pali[i] = pali[j];
            } else if (pali[j] == '.') {
                pali[j] = pali[i];
            } else if (pali[i] != pali[j]) {
                ok = 0;
                break;
            }
        }
        if (ok) printf("%s\n", pali);
        else printf("-1\n");
    }
    return 0;
}
