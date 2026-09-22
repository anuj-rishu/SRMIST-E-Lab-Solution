#include <stdio.h>
#include <string.h>

int main() {
    char S[100];
    if (scanf("%s", S) != 1) return 0;
    int len = strlen(S);
    if (len < 1 || len > 20) {
        printf("Invalid.\n");
        return 0;
    }
    int ops = 0, current_state = 0;
    for (int i = len - 1; i >= 0; i--) {
        int bit = (S[i] - '0') ^ current_state;
        if (bit == 1) {
            ops++;
            current_state ^= 1;
        } else {
            // nothing
        }
    }
    printf("%d\n", ops);
}
