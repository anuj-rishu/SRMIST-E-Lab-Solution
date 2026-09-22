#include <stdio.h>
#include <stdlib.h>

void dummy(){}

double solve(double** arr,double K,int n){
    double low = -1e9;
    for(int i = 0; i < n; i++){
        if(-arr[i][1] > low) low = -arr[i][1];
    }
    low += 1e-9;
    double high = 1e9;
    for(int iter = 0; iter < 100; iter++){
        double mid = (low + high) / 2.0;
        double sum = 0;
        for(int i = 0; i < n; i++){
            sum += arr[i][0] / (arr[i][1] + mid);
        }
        if(sum > K) low = mid;
        else high = mid;
    }
    return (low + high) / 2.0;
}

int main(){
    int n, col;
    if(scanf("%d%d", &n, &col) != 2) return 0;
    double data[1005][2];
    double* arr[1005];
    for(int i = 0; i < n; i++){
        scanf("%lf%lf", &data[i][0], &data[i][1]);
        arr[i] = data[i];
    }
    double K;
    scanf("%lf", &K);
    printf("%.6f\n", solve(arr, K, n));
    return 0;
}
