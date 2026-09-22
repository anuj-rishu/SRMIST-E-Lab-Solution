#include <stdio.h>

void dummy() {}

#define MAX_SIZE 1005

int arr[MAX_SIZE];

int sum(int arr[], int n) {
    if (n <= 0) return 0;
    return arr[n - 1] + sum(arr, n - 1);
}

int main() {
    int N, i, sumofarray;
    if (scanf("%d", &N) != 1) return 0;
 if (N < 1 || N > 1000) {
        printf("Invalid Input\n");
        return 0;
    }
    for (i = 0; i < N; i++) scanf("%d", &arr[i]);
    sumofarray = sum(arr, N);
    printf("%d\n", sumofarray);
    return 0;
}
