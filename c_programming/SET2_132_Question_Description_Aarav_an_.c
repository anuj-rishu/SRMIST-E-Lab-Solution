#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void printBinary(int num, int n) {
    for (int i = n - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n < 1 || n > 8) {
        printf("Invalid input. Please enter a number between 1 and 8.\n");
        return 0;
    }
    int counter = pow(2, n);
    int *arr = (int *)malloc(pow(2, n) * sizeof(int));
    int i;
    for (i = 0; i < counter; i++) {
        arr[i] = i ^ (i >> 1);
    }
    for (i = 0; i < counter; i++) {
        printBinary(arr[i], n);
    }
    free(arr);
}
