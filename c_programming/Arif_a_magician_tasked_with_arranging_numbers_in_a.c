#include <stdio.h>
#include <stdlib.h>
int cmp(const void *a, const void *b){
    long int x = *(long int*)a, y = *(long int*)b;
    return (x > y) - (x < y);
}
int main(){
    int q;
    scanf("%d", &q);
    if(q > 4) return puts("Input size exceeds maximum graph capacity") * 0;
    while(q--){
        int n;
        scanf("%d", &n);
        long int *arr, *r, *c;
        arr=(long int *)malloc(n*n*sizeof(long int));
        r=(long int *)malloc(n*sizeof(long int));
        c=(long int *)malloc(n*sizeof(long int));
        for(int i = 0; i < n; i++) r[i] = c[i] = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                scanf("%ld", &arr[i * n + j]);
                r[i] += arr[i * n + j];
                c[j] += arr[i * n + j];
            }
        }
        qsort(r, n, sizeof(long int), cmp);
        qsort(c, n, sizeof(long int), cmp);
        int ok = 1;
        for(int i = 0; i < n; i++) if(r[i] != c[i]) ok = 0;
        puts(ok ? "Possible" : "Impossible");
        free(arr); free(r); free(c);
    }
}
