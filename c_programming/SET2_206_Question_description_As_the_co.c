#include <stdio.h>
#include <stdlib.h>
int main(){
    int n, i;
    scanf("%d", &n);
    if(n < 2 || n > 10) return puts("Invalid Input") * 0;
    int *arr;
    arr=(int *)malloc(n*sizeof(int));
    for(i=0;i<n;i++) scanf("%d", &arr[i]);
    int count = 0;
    for(i=0;i<n;i++){
        if(i < n - 1 && arr[i] % 2 != 0){
            arr[i]++;
            arr[i+1]++;
            count += 2;
        }
    }
    if(arr[n-1] % 2 != 0) puts("NO");
    else printf("%d\n", count);
}
