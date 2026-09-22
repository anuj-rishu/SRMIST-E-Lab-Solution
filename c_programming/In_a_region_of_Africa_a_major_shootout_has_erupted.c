#include <stdio.h>
#include <stdlib.h>
int is_prime(int x){
    if(x < 2) return 0;
    for(int d = 2; d * d <= x; d++) if(x % d == 0) return 0;
    return 1;
}
int main(){
    int n,i,x,index;
    scanf("%d",&n);
    if(n > 10) return puts("Invaild") * 0;
    int a[20];
    for(i = 0; i < n; i++) scanf("%d",&a[i]);
    for(i = 0; i < n; i++){
        x = a[i];
        int best_dist = 1000;
        index = -1;
        for(int j = 0; j < n; j++){
            if(is_prime(a[j])){
                int dist = abs(i - j);
                if(dist < best_dist){
                    best_dist = dist;
                    index = j + 1;
                }
            }
        }
        if(index == -1) index = 1;
        if(x == 0) x = 1;
        printf("%d%c", index, i == n - 1 ? '\n' : ' ');
    }
    return 0;
}
