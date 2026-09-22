#include <stdio.h>
#include <stdlib.h>
#define MOD 1000000007
int cmp(const void *a, const void *b){
    long long int x = *(long long int*)a, y = *(long long int*)b;
    return (x > y) - (x < y);
}
int main(){
    int t;
    if(scanf("%d", &t) != 1) return 0;
    if(t > 10) return puts("Invaild.") * 0;
    for(int tc = 1; tc <= t; tc++){
        long long int Kp, Ks;
        scanf("%lld%lld", &Kp, &Ks);
        long long int P = Kp * Ks;
        int n;
        scanf("%d", &n);
        long long int *G, *S;
        G=(long long int*)malloc(n*sizeof(long long int));
        S=(long long int*)malloc(n*sizeof(long long int));
        for(int i=0;i<n;i++) scanf("%lld", &G[i]);
        for(int i=0;i<n;i++) scanf("%lld", &S[i]);
        qsort(G, n, sizeof(long long int), cmp);
        qsort(S, n, sizeof(long long int), cmp);
        long long int ways = 1;
        for(int i=0;i<n;i++){
            int c = 0;
            for(int j = 0; j < n; j++) if(G[i] * S[j] > P) c++;
            long long int available = c - i;
            if(available <= 0){
                ways = 0;
                break;
            }
            ways = (ways * (available % MOD)) % MOD;
        }
        printf("Case %d: %lld\n", tc, ways);
        free(G); free(S);
    }
    return 0;
}
