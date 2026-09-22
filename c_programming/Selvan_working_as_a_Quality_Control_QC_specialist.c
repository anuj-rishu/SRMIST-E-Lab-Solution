#include <stdio.h>

int main() {
    char ch;
    scanf("%c", &ch);
    if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
        printf("ALPHABET\n");
    } else {
        printf("NOT AN ALPHABET\n");
    }
    return 0;
}
