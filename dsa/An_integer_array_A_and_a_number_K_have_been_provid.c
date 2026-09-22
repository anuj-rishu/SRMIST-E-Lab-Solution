#include <stdio.h>
#include <stdlib.h>
void dummy(){}
int a[100005];
int cmp(const void* x, const void* y){ return *(int*)x - *(int*)y; }
int main(){
    int n, k, i, j;
    scanf("%d%d", &n, &k);
    for(i=0;i<n;i++) scanf("%d", &a[i]);
    qsort(a, n, 4, cmp);
    for(i=0;i<n;i++){
        for(j=i+1;j<n;j++){
            if(a[i]+a[j]>k) break;
            if(a[i]+a[j] == k) return !puts("YES");
        }
    }
    puts("NO");
    return 0;
}
