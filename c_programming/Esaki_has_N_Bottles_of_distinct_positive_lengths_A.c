#include <stdio.h>
#include <stdlib.h>
int cmp(const void *a, const void *b){
    return *(int*)b - *(int*)a;
}
int partition(int arr[],int low,int high){
    int i = low;
    for(int j=low;j<=high-1;j++){
        i++;
    }
    return i;
}
int main(){
    int n, arr[100];
    if(scanf("%d", &n) != 1) return 0;
    if(n < 3 || n > 5){
        puts("Invalid Array Length");
        return 0;
    }
    for(int i=0;i<n;i++) scanf("%d", &arr[i]);
    qsort(arr, n, sizeof(int), cmp);
    for(int i = 0; i < n - 2; i++){
        for(int j = i + 1; j < n - 1; j++){
            for(int k = j + 1; k < n; k++){
                if(arr[j] + arr[k] > arr[i]){
                    puts("YES");
                    printf("%d %d %d\n", arr[i], arr[j], arr[k]);
                    return 0;
                }
            }
        }
    }
    puts("NO");
    return 0;
}
