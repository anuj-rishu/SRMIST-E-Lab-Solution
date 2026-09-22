#include <stdio.h>
int main(){
    int t, x, y, a, b;
    scanf("%d", &t);
    if(t>5) return puts("Invalid input") * 0;
    while(t--){
        scanf("%d%d", &x, &y);
        a = 3 * x;
        b = 2 * y;
        if(a<b) printf("%d\n", a);
        else printf("%d\n", b);
    }
}
