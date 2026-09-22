#include <stdio.h>
int odd(int arr[], int arr_size){
    int i, j, count;
    for (i = 0; i < arr_size; i++){
        count = 0;
        for (j = 0; j < arr_size; j++)
            if (arr[i] == arr[j]) count++;
        if (count % 2 != 0) return arr[i];
    }
    return 0;
}
int main(){
    int t, n, i, arr[9999];
    if(scanf("%d", &t) != 1 || t > 5 || t < 1) return puts("Invalid input.") * 0;
    while(t--){
        scanf("%d", &n);
        for(i=0;i<n;i++) scanf("%d", &arr[i]);
        printf("%d\n", odd(arr, n));
    }
    return 0;
}
