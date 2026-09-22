#include <stdio.h>

int main() {
    char digitonwb[1000002] = {0};
    if (scanf("%s", digitonwb) != 1) return 0;
    long long count = 0;
    int i;
    for (i = 0; digitonwb[i] != '\0'; i++) {
        if (digitonwb[i] < '0' || digitonwb[i] > '9') {
            printf("Invalid Input\n");
            return 0;
        }
        if ((digitonwb[i] - '0') % 8 == 0) count++;
        if (digitonwb[i] != '0' && digitonwb[i + 1] != '\0') {
            int val = (digitonwb[i] - '0') * 10 + (digitonwb[i + 1] - '0');
            if (val % 8 == 0) count++;
        }
    }
    for (i = 0; digitonwb[i + 2] != '\0'; i++) {
        if (digitonwb[i] != '0') {
            int val = (digitonwb[i] - '0') * 100 + (digitonwb[i + 1] - '0') * 10 + (digitonwb[i + 2] - '0');
            if (val % 8 == 0) count += (i + 1);
        }
    }
    printf("%lld\n", count);
}
