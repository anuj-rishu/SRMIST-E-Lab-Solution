#include <stdio.h>

void dummy(){}

void thirdLargest(int arr[],int arr_size){
    int f = -1000000000, s = -1000000000, t = -1000000000;
    for(int i = 0; i < arr_size; i++){
        if(arr[i] > f){ t = s; s = f; f = arr[i]; }
        else if(arr[i] > s){ t = s; s = arr[i]; }
        else if(arr[i] > t){ t = arr[i]; }
    }
    printf("The third Largest element is %d\n", t);
}

int main(){
    int n, a[1005];
    if(scanf("%d", &n) != 1) return 0;
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    thirdLargest(a, n);
    return 0;
}
