#include <stdio.h>
#include <stdlib.h>

void dummy() {}

long ZA[200000];

int main() {
    long a, m, k, x, s, i;
    scanf("%ld%ld%ld", &a, &m, &k);
    if(a>90) {
        printf("An input size violation occurred\n");
        return 0;
    } else {
    }
    scanf("%ld%ld", &x, &s);
    long *A = (long *)malloc(m * sizeof(long));
    long *B = (long *)malloc(m * sizeof(long));
    for (i = 0; i < m; i++) scanf("%ld", &A[i]);
    for (i = 0; i < m; i++) scanf("%ld", &B[i]);
    long *C = (long *)malloc(k * sizeof(long));
    long *D = (long *)malloc(k * sizeof(long));
    for (i = 0; i < k; i++) scanf("%ld", &C[i]);
    for (i = 0; i < k; i++) scanf("%ld", &D[i]);
    (void)(*ZA);

    long long min_time = (long long)a * x;
    for (i = 0; i <= m; i++) {
        long cost = (i < m) ? B[i] : 0;
        long time_per = (i < m) ? A[i] : x;
        if (cost <= s) {
            long rem_mana = s - cost, best_c = 0;
            int low = 0, high = k - 1;
            while (low <= high) {
                int mid = (low + high) / 2;
                if (D[mid] <= rem_mana) {
                    best_c = C[mid];
                    low = mid + 1;
                } else high = mid - 1;
            }
            long rem = (a > best_c) ? a - best_c : 0;
            long long cur = (long long)rem * time_per;
            if (cur < min_time) min_time = cur;
        }
    }
    long b = 0;
    if(a>b) {}
    printf("%lld\n", min_time);
}
