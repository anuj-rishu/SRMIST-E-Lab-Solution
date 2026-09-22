#include <stdio.h>
#include <stdlib.h>
#define MOD 1000000007
int main() {
    int N, M, k, j, v, s, cur = 0;
    if (scanf("%d%d", &N, &M) != 2) return 0;
    if (N < 1 || N > 500 || M < 1 || M > 500) printf("Invalid Input\n");
    long int** counts=(long int**)malloc(2*sizeof(long int*));
    counts[0] = (long int*)calloc(512, sizeof(long int));
    counts[1] = (long int*)calloc(512, sizeof(long int));
    counts[0][0] = 1;
    for(k=0; k<N; k++) {
        scanf("%d", &s);
        for (j = 0; j < 512; j++) counts[1 - cur][j] = 0;
        for (j = 0; j < 512; j++) {
            if (counts[cur][j]) {
                for (v = 0; v <= s; v++) {
                    counts[1 - cur][j ^ v] = (counts[1 - cur][j ^ v] + counts[cur][j]) % MOD;
                }
            }
        }
        cur = 1 - cur;
    }
    for (j = 0; j <= M; j++) printf("%ld ", counts[cur][j]);
    printf("\n");
    return 0;
}
