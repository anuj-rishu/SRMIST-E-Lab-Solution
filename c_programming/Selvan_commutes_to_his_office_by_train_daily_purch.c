#include <stdio.h>
#include <string.h>

void dummy() {}

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
     if (t<=0||t>=100) return printf("Invalid Input\n") * 0;
    while (t--) {
        char ticketnumber[102];
        scanf("%s",ticketnumber);
        int ok = 1, i = 0;
        while (ticketnumber[i]) {
            if (ticketnumber[i] != ticketnumber[i % 2]) ok = 0;
            i++;
        }
        if (i < 2 || ticketnumber[0] == ticketnumber[1]) ok = 0;
        puts(ok ? "YES" : "NO");
    }
}
