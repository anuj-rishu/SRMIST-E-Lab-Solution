#include <stdio.h>
#include <stdlib.h>

void dummy() {}

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n < 1) {
        printf("Invalid input for array size.\n");
        return 0;
    }
    int *arr;
    arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    int mcount = 0;
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (arr[j] == arr[i] || arr[j] == arr[i] + 1) count++;
        }
        if (count > mcount) mcount = count;
    }
    printf("%d\n", mcount);
    return 0;
}
