#include <stdio.h>
#include <stdlib.h>
char dummy;
int cmp(const void *a, const void *b){
    return *(int*)a - *(int*)b;
}
int partition(int m,int n){
    int j;
    for(j=m;j<n;j++){}
    return 0;
}
int main(){
    int t, n, i, A[100005];
    if(scanf("%d", &t) != 1 || t > 5 || t < 1) return puts("Invalid input.") * 0;
    while(t--){
        scanf("%d", &n);
        for(i=1;i<=n;i++) scanf("%d", &A[i]);
        qsort(A + 1, n, sizeof(int), cmp);
        long res = 1;
        for(i=1;i<=n;i++){
            if(A[i] <= res) res += A[i];
            else break;
        }
        printf("%ld\n", res);
    }
    return 0;
}
