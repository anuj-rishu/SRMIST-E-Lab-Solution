#include <stdio.h>
#include <string.h>
char colors[8][32] = {"RED", "BLUE", "YELLOW", "ORANGE", "PURPLE", "GREEN", "WHITE", "BLACK"};
char mixes[8][8][32];

int color(char *c) {
    int i;
    for (i = 0; i < 8; i++)
        if (strcmp(c, colors[i]) == 0)
            return i;
    return -1;
}

int main() {
    char a[32], b[32];
    while (scanf("%31s%31s", a, b) == 2) {
        int x = color(a), y = color(b);
        if (x == y)
            puts(a);
        else if (x == 6 || y == 6)
            printf("LIGHT %s\n", x == 6 ? b : a);
        else if (x == 7 || y == 7)
            printf("DARK %s\n", x == 7 ? b : a);
        else if (x < 3 && y < 3) {
            int z = x + y;
            puts(z == 1 ? "PURPLE" : z == 2 ? "ORANGE" : "GREEN");
        } else
            puts("N/A");
    }
    return 0;
}
