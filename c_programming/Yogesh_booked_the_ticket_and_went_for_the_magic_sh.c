#include <stdio.h>

int main() {
    int noofrows;
    scanf("%d", &noofrows);
    for (int i = 1; i <= noofrows; i++) {
        for (int j = 0; j < i; j++) {
            printf("%d ", i);
        }
        printf("\n");
    }
    return 0;
}
