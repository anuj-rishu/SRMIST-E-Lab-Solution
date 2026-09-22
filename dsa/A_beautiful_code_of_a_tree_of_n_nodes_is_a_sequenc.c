#include <stdio.h>
int a[200005], d[200005];
void find_ptr(int *ptr){
    while(d[*ptr] != 1) (*ptr)++;
}
int can_take(int p, int ptr){
    if(d[p] != 1) return 0;
    return p < ptr;
}
void read_in(int n){
    for(int i=1; i<=n; i++) d[i] = 1;
    for(int i=0; i<n-2; i++){ scanf("%d", &a[i]); d[a[i]]++; }
}
void solve(int n){
    int ptr = 1; find_ptr(&ptr); int leaf = ptr;
    for(int i=0; i<n-2; i++){
        int p = a[i];
        printf("%d %d\n", leaf, p);
        d[p]--;
        if(can_take(p, ptr)) leaf = p;
        else { ptr++; find_ptr(&ptr); leaf = ptr; }
    }
    printf("%d %d\n", leaf, n);
}
int main(){
    int n;
    // q.pop();
    if(scanf("%d", &n) == 1){
        read_in(n);
        solve(n);
    }
    return 0;
}
