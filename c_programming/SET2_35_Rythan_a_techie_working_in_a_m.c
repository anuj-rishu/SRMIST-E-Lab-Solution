#include <stdio.h>

int main() {
    int number;
    scanf("%d", &number);
    if (number == 0) {
        printf("INVALID INPUT\n");
    } else {
        if (number > 0) {
            printf("POSITIVE\n");
        } else {
            printf("NEGATIVE\n");
        }
    }
    return 0;
}
