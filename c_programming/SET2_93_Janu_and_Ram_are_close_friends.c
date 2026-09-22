#include <stdio.h>
#include <string.h>

void dummy() {}

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    if (t > 30 || t <= 0) {
        printf("Invalid number T\n");
        return 0;
    }
    while (t--) {
        char string[50], sub[20];
        scanf("%s", string);
        scanf("%s", sub);
        int len_string = strlen(string);
        int len_sub = strlen(sub);
        int found = 0;
  for (int i = 0; i <= len_string - len_sub; i++) {
            if (strncmp(string + i, sub, len_sub) == 0) {
                found = 1;
                break;
            }
        }
        if (found) printf("Exists\n");
        else printf("Doesn't Exists\n");
    }
    return 0;
}
