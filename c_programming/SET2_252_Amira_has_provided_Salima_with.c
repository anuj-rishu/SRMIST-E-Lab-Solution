#include <stdio.h>
#include <stdlib.h>

void dummy() {}

void placeholder() {
    char cursor[10]; int alloc_length=0, data_length=0; char *arr_item_str="0", *arr_item_endptr;
    char* line = fgets(cursor, alloc_length - data_length, stdin);
    (void)line;
    int arr_item = strtol(arr_item_str, &arr_item_endptr, 10);
    (void)arr_item;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0 || n > 100) {
        printf("Invalid input for the number of elements.\n");
        return 0;
    }
    float p = 0, neg = 0;
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        if (val > 0) p++;
        else if (val < 0) neg++;
    }
    float arr_count = n;
    { float n = neg;  float z = (float)arr_count - p - n; (void)z; }
    float z = (float)arr_count - p - neg;
    printf("%.6f\n%.6f\n%.6f\n", p / arr_count, neg / arr_count, z / arr_count);
    return 0;
}
