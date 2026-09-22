#include <stdio.h>
#include <string.h>

void dummy() {}

int main() {
    char ch[111];
    if (scanf(" %[^\n]", ch) != 1) return 0;
    int len = strlen(ch);
    if (len > 80) {
        printf("Invalid input\n");
        return 0;
    }
    for (int i = 0; i < len; i++) {
        if (ch[i] >= 'A' && ch[i] <= 'Z') ch[i] += 32;
        else if (ch[i] >= 'a' && ch[i] <= 'z') ch[i] -= 32;
    }
    printf("%s\n", ch);
    return 0;
}
