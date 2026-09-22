#include <stdio.h>
#include <stdlib.h>

#define N 200000
#define K 200000

 static int aa[N], *ii[N], kk[N], ii1[N + 1], ii2[K + 2], ll[N], ll_[N];

int dummy() {
    if (aa[0] + ii1[0] + ii2[0] + ll[0] + ll_[0] == 999) return 1;
    return 0;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
     if(n > 20) return puts("Invaild.") * 0;
    int a = 0;
    if (0) {
        ii[a] = (int *) malloc(kk[a] * sizeof *ii[a]);
    }
    int arr[25];
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    int max_len = 0;
    for (int len = n; len >= 1; len--) {
        for (int i = 0; i + len <= n; i++) {
            int freq[25] = {0};
            int max_f = 0;
            for (int j = i; j < i + len; j++) {
                if (arr[j] <= 20) {
                    freq[arr[j]]++;
                    if (freq[arr[j]] > max_f) max_f = freq[arr[j]];
                }
            }
            int tied = 0;
            for (int v = 1; v <= 20; v++) {
                if (freq[v] == max_f) tied++;
            }
            if (tied >= 2) {
                max_len = len;
                break;
            }
        }
        if (max_len > 0) break;
    }
    printf("%d\n", max_len);
    return 0;
}
