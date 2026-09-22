#include <stdio.h>
#include <stdlib.h>
void dummy(){}
int arr[200005], p[200005], lst[200005], dup[200005], vis[200005];
long long s;
int cmp(const void* x, const void* y){
    int a = arr[*(int*)x], b = arr[*(int*)y];
    return (a > b) - (a < b);
}
int main(){
    int n, i, max = 0, u = 0, d = 0;
    scanf("%d", &n);
    for(i=0;i<n;i++){
        scanf("%d", &arr[i]);
        if(arr[i]>max) max = arr[i];
        p[i] = i;
    }
    qsort(p, n, sizeof(int), cmp);
    for(i=0;i<n;i++){
        if(!i || arr[p[i]] != arr[p[i-1]]) u++;
        vis[p[i]] = u;
    }
    for(i=0;i<n;i++){
        int v = vis[i];
        if(lst[v]) dup[v] = 1; else d++;
        lst[v] = d;
    }
    for(i=1;i<=u;i++) s += lst[i] - !dup[i];
    printf("%lld\n", s);
    return 0;
}
