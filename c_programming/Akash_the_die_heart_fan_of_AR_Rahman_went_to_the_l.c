#include <stdio.h>

int main() {
    int nooffamilymembers;
    scanf("%d", &nooffamilymembers);
    for (int i = nooffamilymembers; i >= 1; i--) {
        for (int j = 1; j <= i; j++) {
            printf("%d ", i);
        }
        printf("\n");
    }
    return 0;
}
