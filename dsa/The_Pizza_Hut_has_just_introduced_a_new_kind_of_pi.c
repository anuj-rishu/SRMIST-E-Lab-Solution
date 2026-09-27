#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    int t;
    scanf("%d", &t);
    while (t--) {
        char s[105];
        scanf("%s", s);
        int flips = 0;
        char state = 43;
        for (int i = strlen(s) - 1; i >= 0; i--) {
            flips += (s[i] != state);
            state = s[i];
        }
        printf("%d\n", flips);
    }
    return 0;
}
