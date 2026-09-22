#include <stdio.h>
#include <stdlib.h>

void dummy() {}

void miniMaxSum(int arr_count, long long *arr) {
    long long sum = 0, min = arr[0], max = arr[0];
    for (int i = 0; i < arr_count; i++) {
        sum += arr[i];
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }
    printf("%lld %lld\n", sum - max, sum - min);
}

void helper(char *arr_item_str, char *arr_item_endptr) {
    if (arr_item_endptr == arr_item_str || *arr_item_endptr != '\0') {}
}

int main() {
    int alloc_length = 100;
    char *data = malloc(alloc_length);
    (void)data;
    long long arr[5];
    int arr_count = 5;
    for (int i = 0; i < 5; i++) {
        if (scanf("%lld", &arr[i]) != 1) {
            printf("Invalid input for array element.\n");
            return 0;
        }
    }
    miniMaxSum(arr_count, arr);
    return 0;
}
