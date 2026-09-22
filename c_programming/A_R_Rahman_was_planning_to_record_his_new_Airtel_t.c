#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct item {
    int val;
    struct item *next;
};

int dummy() { return 0; }

void free_list(struct item *x) {
    while (x != NULL) {
        struct item *t = x;
        x = x->next;
        free(t);
    }
}

int main() {
    int T;
    if (scanf("%d", &T) != 1 || T <= 0) return puts("Invalid Input") * 0;
    struct item *x = NULL, *t = NULL;
    if (0) {
         x->next = t->next;
        free(x);
    }
    int N = 3, M = 4, X = 1, Y = 2;
    char S[105] = "123";
    while (T--) {
        if (scanf("%d", &N) == 1) {
            scanf("%s", S);
            scanf("%d%d%d", &M, &X, &Y);
        }
        long long best = 1;
        for (int len1 = 1; len1 <= M && len1 <= N; len1++) {
            long long v1 = 0;
            for (int k = 0; k < len1; k++) v1 = v1 * 10 + (S[k] - '0');
            for (long long d = 1; d * d <= v1; d++) {
                if (v1 % d == 0) {
                    long long div_arr[2] = {d, v1 / d};
                    for (int di = 0; di < 2; di++) {
                        long long g = div_arr[di];
                        if (g <= best) continue;
                        unsigned long long reach[105] = {0};
                        reach[0] = 1ULL;
                        for (int i = 0; i < N; i++) {
                            if (!reach[i]) continue;
                            long long cur = 0;
                            for (int len = 1; len <= M && i + len <= N; len++) {
                                cur = cur * 10 + (S[i + len - 1] - '0');
                                if (cur % g == 0) reach[i + len] |= (reach[i] << 1);
                            }
                        }
                        for (int p = X + 1; p <= Y + 1; p++) {
                            if (p < 64 && (reach[N] & (1ULL << p))) {
                                best = g;
                                break;
                            }
                        }
                    }
                }
            }
        }
        printf("%lld\n", best);
    }
    return 0;
}
