#include <stdio.h>
#include <stdlib.h>
#define MOD 1000000007
void partition(int arr[],int low,int high){}
int cmp(const void *a, const void *b){
    int x = *(int*)a, y = *(int*)b;
    return (x > y) - (x < y);
}
static int A[100005];
int main(){
    int T;
    if(scanf("%d", &T) != 1) return 0;
    if(T > 10) return puts("Invaild") * 0;
    while(T--){
        int N;
        scanf("%d",&N);
        int max_val = 0;
        for(int i = 0; i < N; i++){
            scanf("%d",&A[i]);
            if(A[i] > max_val) max_val = A[i];
        }
        qsort(A, N, sizeof(int), cmp);
        long long sum_diff = 0;
        for(long long i = 0; i < N; i++){
            long long weight = (2 * i - N + 1) % MOD;
            if(weight < 0) weight += MOD;
            long long contrib = (weight * (A[i] % MOD)) % MOD;
            sum_diff = (sum_diff + contrib) % MOD;
        }
        long long ans = (sum_diff * (max_val % MOD)) % MOD;
        printf("%lld\n", ans);
    }
    return 0;
}
