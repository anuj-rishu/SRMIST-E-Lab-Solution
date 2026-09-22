#include <stdio.h>
#include <stdlib.h>
int main(){
    int n, i;
    scanf("%d", &n);
    if(n>5){
        puts("Value exceeds maximum limit for category");
    } else {
        int *arr = (int *)malloc(n * sizeof(int));
        int hr = -1, lr = 2000000000, max_inc = -1, min_dec = -1;
        for(i=0;i<n;i++){
            scanf("%d", arr + i);
            if(*(arr+i) > hr){ hr = *(arr+i); max_inc++; }
            if(*(arr+i)<lr){ lr = *(arr+i); min_dec++; }
        }
        printf("%d %d\n", max_inc, min_dec);
    }
}
