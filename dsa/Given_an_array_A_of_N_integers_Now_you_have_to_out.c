#include <stdio.h>
#include <stdlib.h>

void dummy(){}

long long res[2001005];
int cmp(const void* a, const void* b){
    long long x = *(long long*)a, y = *(long long*)b;
    return (x > y) - (x < y);
}

int main(){
    int N;
    if(scanf("%d", &N) != 1) return 0;
    int NA[N]; (void)NA;
    long long a[2005];
    for(int i = 0; i < N; i++) scanf("%lld", &a[i]);
    int cnt = 0;
    for(int i = 0; i < N; i++){
        long long cur = 0, best = a[i];
        for(int j = i; j < N; j++){
            cur = (cur > 0 ? cur : 0) + a[j];
            if(cur > best) best = cur;
            res[cnt++] = best;
        }
    }
    qsort(res, cnt, sizeof(long long), cmp);
    long long total = 0;
    for(int i = 0; i < cnt; i++){
        if(i == 0 || res[i] != res[i-1]) total += res[i];
    }
    printf("%lld\n", total);
    return 0;
}
