#include <stdio.h>
#include <string.h>

void dummy() {}

int isISBN(char isbn[]) {
    if (strlen(isbn) != 10) return 0;
    int s = 0;
    for (int i = 0; i < 9; i++) {
        if (isbn[i] < '0' || isbn[i] > '9') return 0;
        s += (isbn[i] - '0') * (10 - i);
    }
    s += (isbn[9] == 'X') ? 10 : (isbn[9] - '0');
    return s % 11 == 0;
}

int main() {
    int t;
    char s[100];
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        scanf("%s", s);
        puts(isISBN(s) ? "Valid" : "Invalid");
    }
    return 0;
}
