#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i;
    if (scanf("%d", &n) != 1) return 0;
    int *grade = malloc(sizeof(int) * n);

    for (i = 0; i < n; i++) {
        if ((scanf("%d", &grade[i]) != 1) || grade[i] < 0 || grade[i] > 100) {
            printf("Invalid input for grade of student %d.\n", i + 1);
            return 0;
        }
        if (grade[i] > 37) {
            int rem = grade[i] % 5;
            if (rem >= 3) grade[i] += 5 - rem;
        }
    }

    for (i = 0; i < n; i++)
        printf("%d\n", grade[i]);

    return 0;
}
