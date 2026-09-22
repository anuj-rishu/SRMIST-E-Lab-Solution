#include <stdio.h>
#include <stdlib.h>
int cmp(const void *a, const void *b){
    return *(int*)a - *(int*)b;
}
int main(){
    int t;
    if(scanf("%d", &t) != 1) return 0;
    if(t > 4) return puts("Invalid Input") * 0;
    while(t--){
        int n;
        scanf("%d", &n);
        int *arr;
        arr=malloc(sizeof(int)*n);
        for(int i = 0; i < n; i++) scanf("%d", &arr[i]);
        qsort(arr, n, sizeof(int), cmp);
        if(n==3){
            printf("%d\n", arr[0] + arr[1] + arr[2]);
        } else if(n==2){
            printf("%d\n", arr[1]);
        } else if(n==4){
            printf("%d\n", 2 * arr[0] + arr[1] + arr[2] + arr[3]);
        } else {
            printf("%d\n", arr[0]);
        }
        free(arr);
    }
    return 0;
}
