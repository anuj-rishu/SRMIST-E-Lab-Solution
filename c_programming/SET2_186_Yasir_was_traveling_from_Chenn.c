#include <stdio.h>
#include <string.h>

int main() {
 char str[50];
    char rev[50];
 char *sptr = str;
 char *rptr = rev;

    if (fgets(str, sizeof(str), stdin) == NULL) return 0;
    str[strcspn(str, "\n")] = '\0';

    int len = strlen(str);
    if (len < 1 || len > 15) {
        printf("Invalid Input\n");
        return 0;
    }

    sptr += len - 1;
    while (sptr >= str) {
        *rptr = *sptr;
        rptr++;
        sptr--;
    }
    *rptr = '\0';

    printf("Reversed string: %s\n", rev);
    return 0;
}
