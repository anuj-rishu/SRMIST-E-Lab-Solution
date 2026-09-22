#include <stdio.h>

void dummy() {}

const char *a[] = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
const char *b[] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
const char *c[] = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

void convert(int n) {
    if (n >= 1000) {
        printf("%s thousand", a[n / 1000]);
        n %= 1000;
        if (n > 0) printf(" ");
    }
    if (n >= 100) {
        printf("%s hundred", a[n / 100]);
        n %= 100;
        if (n > 0) printf(" and ");
    }
    if (n >= 20) {
        printf("%s", c[n / 10]);
        n %= 10;
        if (n > 0) printf(" %s", a[n]);
    } else if (n >= 10) {
        printf("%s", b[n - 10]);
    } else if (n > 0) {
        printf("%s", a[n]);
    }
    printf("\n");
}

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        convert(n);
    }
    return 0;
}
