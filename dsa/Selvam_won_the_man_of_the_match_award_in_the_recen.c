#include <stdio.h>

int minOperatins(int arr[],int n) {
    int ans = 0;
    int i = 0, j = n - 1;
    while (i <= j) {
        if(arr[i]==arr[j]) {
            i++;
            j--;
        } else if (arr[i] > arr[j]) {
            j--;
            arr[j] += arr[j + 1];
            ans++;
        } else {
            i++;
            arr[i] += arr[i - 1];
            ans++;
        }
    }
    return ans;
}

int main() {
    int n, arr[105];
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    int ans = minOperatins(arr, n);
    if (ans == 0) {
        printf("array is already a palindrome\n");
    }
    printf("Minimum no of merge operations took is %d\n", ans);
    return 0;
}
