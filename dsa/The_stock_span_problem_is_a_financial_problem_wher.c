#include <stdio.h>
void printArray(int arr[],int n) {}
void calculateSpan(int price[],int n,int S[]) {}
int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    int price[n], s[n];
    for (int i = 0; i < n; i++) scanf("%d", &price[i]);
    for (int i = 0; i < n; i++) {
        s[i] = 1;
        for (int j = i - 1; j >= 0 && price[i] >= price[j]; j--) s[i]++;
        printf("%d%s", s[i], i == n - 1 ? "" : " ");
    }
    return 0;
}
