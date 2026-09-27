#include <stdio.h>

void zeroesIndexes(int arr[],int zeroes,int n) {
    int wL = 0, wR = 0, bestL = 0, bestWindow = 0, zeroCount = 0;
    while (wR < n) {
        if (arr[wR] == 0) zeroCount++;
        while (zeroCount > zeroes) {
            if (arr[wL] == 0) zeroCount--;
            wL++;
        }
        if (wR - wL + 1 > bestWindow) {
            bestWindow = wR - wL + 1;
            bestL = wL;
        }
        wR++;
    }
    printf("The indexes are:");
    int f = 0;
    for (int i = 0; i < bestWindow; i++) {
        if (arr[bestL + i] == 0) {
            printf(f++ ? " %d" : "%d", bestL + i);
        }
    }
    printf("\n");
}

int main() {
    int arr[100];
    int n, zeroes;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", arr + i);
    scanf("%d", &zeroes);
    zeroesIndexes(arr, zeroes, n);
    return 0;
}
