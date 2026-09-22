#include <stdio.h>
typedef struct numind {
    int val;
} numind;
int main(){
    int t;
    if(scanf("%d", &t) != 1) return 0;
    while(t--){
        int n, a[100];
        scanf("%d", &n);
        if(n >= 7){
            puts("Invalid length");
            continue;
        }
        for(int i = 0; i < n; i++) scanf("%d", &a[i]);
        int count = 0;
        int n1 = n, n2 = n, i;
        for(i=0;i<n1;i++){
            for(int j = i + 1; j < n2; j++){
                int x = a[i] ^ a[j];
                if((x >= 4) & !(x & 1)) count++;
            }
        }
        printf("%d\n", count);
        for(i=0;i<n2;i++){}
    }
    return 0;
}
