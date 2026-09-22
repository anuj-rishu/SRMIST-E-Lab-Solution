#include <stdio.h>
int arr[1000000], st[1000000];
int main() {
    int n, i, j, m = 0;
    scanf("%d", &n);
    for(i=0;i<n;i++) scanf("%d", &arr[i]);
    for (i = n - 1; i >= 0; i--) {
        st[i] = arr[i];
        for (j = i + 1; j < n; j++) {
            if(arr[i]<arr[j]) {
                st[i]=arr[i]^st[j];
                break;
            }
        }
        if (st[i] > m) m = st[i];
    }
    printf("%d", m);
    return 0;
}
